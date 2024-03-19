#include "sdcard.h"
#include <delay.h>

static SD_Error SD_PowerON(SDIO_TypeDef * SDIOx);
static SD_Error SD_InitializeCards(SDIO_TypeDef * SDIOx);
static SD_Error SD_GetCardInfo(SD_CardInfo * cardinfo);
static SD_Error SD_SelectDeselect(SDIO_TypeDef * SDIOx, uint32_t addr);
static SD_Error SD_SetBlockSize(SDIO_TypeDef * SDIOx, uint32_t BlockSize);
static SD_Error SD_EnableWideBusOperation(SDIO_TypeDef * SDIOx, uint8_t WideMode);
static SD_Error SD_Enable_WideBus(SDIO_TypeDef * SDIOx, FunctionalState NewState);
static SD_Error CmdResp1Error(SDIO_TypeDef * SDIOx, SDIO_CmdInitTypeDef * SDIO_CmdInitStruct);
static SD_Error CmdResp2Error(SDIO_TypeDef * SDIOx, SDIO_CmdInitTypeDef * SDIO_CmdInitStruct);
static SD_Error CmdResp6Error(SDIO_TypeDef * SDIOx, SDIO_CmdInitTypeDef * SDIO_CmdInitStruct, uint16_t * prca);
static SD_Error CmdResp7Error(SDIO_TypeDef * SDIOx, SDIO_CmdInitTypeDef * SDIO_CmdInitStruct);

static uint32_t CardType = SDIO_STD_CAPACITY_SD_CARD_V1_1; // 存储卡的类型，先把它初始化为1.1协议的卡
static uint32_t CSD_Tab[4], CID_Tab[4], RCA = 0;           // 存储CSD，DID，寄存器和卡相对地址
SD_CardInfo SDCardInfo;
/*
 * 函数名：GPIO_Configuration
 * 描述  ：初始化SDIO用到的引脚，开启时钟。
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static SD_Error SDIO_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  if(SD_DETECT != 0)
  {
    return SD_SWITCH_ERROR;
  }

  CCU_BUS0_GatingClockCmd(CCU_BUS0Gating_SD0, ENABLE);
  CCU_BUS0_GatingResetCmd(CCU_BUS0Gating_SD0, ENABLE);

  GPIO_AF_Remap(GPIOF, GPIO_PinSource0, GPIO_AF_PF0_SDC0_D1);
  GPIO_AF_Remap(GPIOF, GPIO_PinSource1, GPIO_AF_PF1_SDC0_D0);
  GPIO_AF_Remap(GPIOF, GPIO_PinSource2, GPIO_AF_PF2_SDC0_CLK);
  GPIO_AF_Remap(GPIOF, GPIO_PinSource3, GPIO_AF_PF3_SDC0_CMD);
  GPIO_AF_Remap(GPIOF, GPIO_PinSource4, GPIO_AF_PF4_SDC0_D3);
  GPIO_AF_Remap(GPIOF, GPIO_PinSource5, GPIO_AF_PF5_SDC0_D2);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |
                                GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  return SD_OK;
}

/**
 * 函数名：SD_Init
 * 描述  ：初始化SD卡，使卡处于就绪状态(准备传输数据)
 * 输入  ：无
 * 输出  ：-SD_Error SD卡错误代码
 *         成功时则为 SD_OK
 * 调用  ：外部调用
 */
SD_Error SD_Init(SDIO_TypeDef * SDIOx)
{
  /*重置SD_Error状态*/
  SD_Error errorstatus = SD_OK;

  /* SDIO 外设底层引脚初始化 */
  errorstatus = SDIO_GPIO_Configuration();

  if(errorstatus != SD_OK)
  {
    /*!< CMD Response TimeOut (wait for CMDSENT flag) */
    return (errorstatus);
  }

  /*上电并进行卡识别流程，确认卡的操作电压  */
  errorstatus = SD_PowerON(SDIOx);

  /*如果上电，识别不成功，返回“响应超时”错误 */
  if(errorstatus != SD_OK)
  {
    /*!< CMD Response TimeOut (wait for CMDSENT flag) */
    return (errorstatus);
  }

  delay_ms(1);

  /*卡识别成功，进行卡初始化    */
  errorstatus = SD_InitializeCards(SDIOx);

  if(errorstatus != SD_OK)  // 失败返回
  {
    /*!< CMD Response TimeOut (wait for CMDSENT flag) */
    return (errorstatus);
  }

  delay_ms(1);

  /* 用来读取csd/cid寄存器 */
  errorstatus = SD_GetCardInfo(&SDCardInfo);

  if(errorstatus != SD_OK)
  {
    /*!< CMD Response TimeOut (wait for CMDSENT flag) */
    return (errorstatus);
  }

  delay_ms(1);

  /* 通过cmd7  ,rca选择要操作的卡 */
  errorstatus = SD_SelectDeselect(SDIOx, (uint32_t)(RCA << 16));

  if(errorstatus != SD_OK)
  {
    /*!< CMD Response TimeOut (wait for CMDSENT flag) */
    return (errorstatus);
  }

  delay_ms(1);

  // 设置块大小
  SDCardInfo.CardBlockSize = 512;
  errorstatus = SD_SetBlockSize(SDIOx, SDCardInfo.CardBlockSize);

  if(errorstatus != SD_OK)
  {
    /*!< CMD Response TimeOut (wait for CMDSENT flag) */
    return (errorstatus);
  }

  delay_ms(1);

  errorstatus = SDIO_Config_Clock(SDIOx, 20000000);

  if(errorstatus != SD_OK)
  {
    /*!< CMD Response TimeOut (wait for CMDSENT flag) */
    return (errorstatus);
  }

  delay_ms(1);

  /* 最后为了提高读写，开启4bits模式 */
  errorstatus = SD_EnableWideBusOperation(SDIOx, MMCSD_BUS_WIDTH_4);

  return (errorstatus);
}

/*
 * 函数名：SD_PowerON
 * 描述  ：确保SD卡的工作电压和配置控制时钟
 * 输入  ：无
 * 输出  ：-SD_Error SD卡错误代码
 *         成功时则为 SD_OK
 * 调用  ：在 SD_Init() 调用
 */
static SD_Error SD_PowerON(SDIO_TypeDef * SDIOx)
{
  SD_Error errorstatus = SD_OK;
  uint32_t response = 0, count = 0, validvoltage = 0;
  uint32_t SDType = SD_STD_CAPACITY;
  SDIO_CmdInitTypeDef SDIO_CmdInitStructure;

  SDIO_CmdInitStructure.SDIO_Resp[0] = 0;
  SDIO_CmdInitStructure.SDIO_Resp[1] = 0;
  SDIO_CmdInitStructure.SDIO_Resp[2] = 0;
  SDIO_CmdInitStructure.SDIO_Resp[3] = 0;

  SDIO_Set_Clk(SDIOx, 24000000);

  SDIO_Set_Ios(SDIOx, 400000, MMCSD_BUS_WIDTH_1);

  /********************************************************************************************************/
  /* 下面发送一系列命令,开始卡识别流程
   * CMD0: GO_IDLE_STATE(复位所以SD卡进入空闲状态)
   * 没有响应
   */
  SDIO_CmdInitStructure.SDIO_Argument = 0x0;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_GO_IDLE_STATE;
  SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_NONE;
  SDIO_SendCommand(SDIOx, &SDIO_CmdInitStructure, 0);
  delay_ms(1);
  /********************************************************************************************************/
  /* CMD8: SEND_IF_COND
   * Send CMD8 to verify SD card interface operating condition
   *
   * Argument: - [31:12]: Reserved (shall be set to '0')
   *           - [11:8] : Supply Voltage (VHS) 0x1 (Range: 2.7-3.6 V)
   *           - [7:0]  : Check Pattern (recommended 0xAA)
   * CMD Response: R7
   */
  /* 接收到命令sd会返回这个参数 */
  SDIO_CmdInitStructure.SDIO_Argument = SD_CHECK_PATTERN;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SEND_IF_COND;
  SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R7;

  /*检查是否接收到命令*/
  errorstatus = CmdResp7Error(SDIOx, &SDIO_CmdInitStructure);
  delay_ms(1);
  /* 有响应则card遵循sd协议2.0版本 */
  if(errorstatus == SD_OK)
  {
    /* SD Card 2.0 ，先把它定义会sdsc类型的卡 */
    CardType = SDIO_STD_CAPACITY_SD_CARD_V2_0;
    /* 这个变量用作ACMD41的参数，用来询问是sdsc卡还是sdhc卡 */
    SDType = SD_HIGH_CAPACITY;
  }
  else /* 无响应，说明是1.x的或mmc的卡 */
  {
    /* 发命令 CMD55 */
    SDIO_CmdInitStructure.SDIO_Argument = 0x00;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_APP_CMD;
    SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R1;
    SDIO_SendCommand(SDIOx, &SDIO_CmdInitStructure, 0);
    errorstatus = CmdResp1Error(SDIOx, &SDIO_CmdInitStructure);
    delay_ms(1);
  }

  /* CMD55
   * 发送cmd55，用于检测是sd卡还是mmc卡，或是不支持的卡
   * CMD 响应: R1
   */
  SDIO_CmdInitStructure.SDIO_Argument = 0x00;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_APP_CMD;
  SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R1;
  SDIO_SendCommand(SDIOx, &SDIO_CmdInitStructure, 0);

  /* 是否响应，没响应的是mmc或不支持的卡 */
  errorstatus = CmdResp1Error(SDIOx, &SDIO_CmdInitStructure);
  delay_ms(1);
  if(errorstatus == SD_OK)  // 响应了cmd55，是sd卡，可能为1.x,可能为2.0
  {
    /*下面开始循环地发送sdio支持的电压范围，循环一定次数*/

    /* SD CARD
     * Send ACMD41 SD_APP_OP_COND with Argument 0x80100000
     */
    while((!validvoltage) && (count < SD_MAX_VOLT_TRIAL))
    {
      /* 在发送ACMD命令前都要先向卡发送CMD55
       * SEND CMD55 APP_CMD with RCA as 0
       */
      SDIO_CmdInitStructure.SDIO_Argument = 0x00;
      SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_APP_CMD;
      SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R1;
      SDIO_SendCommand(SDIOx, &SDIO_CmdInitStructure, 50);

      /* ACMD41
       * 命令参数由支持的电压范围及HCS位组成，HCS位置一来区分卡是SDSC还是SDHC
       * 0:SDSC
       * 1:SDHC
       * 响应：R3,对应的是OCR寄存器
       */
      SDIO_CmdInitStructure.SDIO_Argument = SD_VOLTAGE_WINDOW_SD | SDType;
      SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_SD_APP_OP_COND;
      SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R3;
      SDIO_SendCommand(SDIOx, &SDIO_CmdInitStructure, 50);

      // /* 若卡需求电压在SDIO的供电电压范围内，会自动上电并标志pwr_up位
      //  * 读取卡寄存器，卡状态
      //  */
      response = SDIOx->RESP0;
      /* 读取卡的ocr寄存器的pwr_up位，看是否已工作在正常电压 */
      validvoltage = (((response >> 31) == 1) ? 1 : 0);
      count++; /* 计算循环次数 */
    }

    if(count >= SD_MAX_VOLT_TRIAL)  /* 循环检测超过一定次数还没上电 */
    {
      errorstatus = SD_INVALID_VOLTRANGE; /* SDIO不支持card的供电电压 */
      return (errorstatus);
    }
    /*检查卡返回信息中的HCS位*/
    /* 判断ocr中的ccs位 ，如果是sdsc卡则不执行下面的语句 */
    if(response &= SD_HIGH_CAPACITY)
    {
      CardType = SDIO_HIGH_CAPACITY_SD_CARD; /* 把卡类型从初始化的sdsc型改为sdhc型 */
    }
    else
    {
      CardType = SDIO_STD_CAPACITY_SD_CARD_V2_0; /* 把卡类型改为sdsc型 */
    }

  } /* else MMC Card */
  return (errorstatus);
}

/*
 * 函数名：SD_InitializeCards
 * 描述  ：初始化所有的卡或者单个卡进入就绪状态
 * 输入  ：无
 * 输出  ：-SD_Error SD卡错误代码
 *         成功时则为 SD_OK
 * 调用  ：在 SD_Init() 调用，在调用power_on（）上电卡识别完毕后，调用此函数进行卡初始化
 */
static SD_Error SD_InitializeCards(SDIO_TypeDef * SDIOx)
{
  SD_Error errorstatus = SD_OK;
  uint16_t rca = 0x01;
  SDIO_CmdInitTypeDef SDIO_CmdInitStructure;

  SDIO_CmdInitStructure.SDIO_Resp[0] = 0;
  SDIO_CmdInitStructure.SDIO_Resp[1] = 0;
  SDIO_CmdInitStructure.SDIO_Resp[2] = 0;
  SDIO_CmdInitStructure.SDIO_Resp[3] = 0;

  /* 判断卡的类型 */
  if(SDIO_SECURE_DIGITAL_IO_CARD != CardType)
  {
    /* Send CMD2 ALL_SEND_CID
     * 响应：R2，对应CID寄存器
     */
    SDIO_CmdInitStructure.SDIO_Argument = 0x0;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_ALL_SEND_CID;
    SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R2;
    SDIO_SendCommand(SDIOx, &SDIO_CmdInitStructure, 100);

    errorstatus = CmdResp2Error(SDIOx, &SDIO_CmdInitStructure);
    if(SD_OK != errorstatus)
    {
      return (errorstatus);
    }
    /* 将返回的CID信息存储起来 */
    CID_Tab[0] = SDIO_CmdInitStructure.SDIO_Resp[0];
    CID_Tab[1] = SDIO_CmdInitStructure.SDIO_Resp[1];
    CID_Tab[2] = SDIO_CmdInitStructure.SDIO_Resp[2];
    CID_Tab[3] = SDIO_CmdInitStructure.SDIO_Resp[3];
  }
  /********************************************************************************************************/
  if((SDIO_STD_CAPACITY_SD_CARD_V1_1 == CardType) || (SDIO_STD_CAPACITY_SD_CARD_V2_0 == CardType) ||
     (SDIO_SECURE_DIGITAL_IO_COMBO_CARD == CardType) || (SDIO_HIGH_CAPACITY_SD_CARD == CardType)) /* 使用的是2.0的卡 */
  {
    /* Send CMD3 SET_REL_ADDR with argument 0
     * SD Card publishes its RCA.
     * 响应：R6，对应RCA寄存器
     */
    SDIO_CmdInitStructure.SDIO_Argument = 0x00;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_SET_REL_ADDR;
    SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R6;

    /* 把接收到的卡相对地址存起来 */
    errorstatus = CmdResp6Error(SDIOx, &SDIO_CmdInitStructure, &rca);
    if(SD_OK != errorstatus)
    {
      return (errorstatus);
    }
  }

  /********************************************************************************************************/
  if(SDIO_SECURE_DIGITAL_IO_CARD != CardType)
  {
    RCA = rca + 1;
    /* Send CMD9 SEND_CSD with argument as card's RCA
     * 响应:R2  对应寄存器CSD(Card-Specific Data)
     */
    SDIO_CmdInitStructure.SDIO_Argument = (uint32_t)(RCA << 16);
    SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_SEND_CSD;
    SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R2;
    SDIO_CmdInitStructure.SDIO_Resp[0] = 0;
    SDIO_CmdInitStructure.SDIO_Resp[1] = 0;
    SDIO_CmdInitStructure.SDIO_Resp[2] = 0;
    SDIO_CmdInitStructure.SDIO_Resp[3] = 0;
    SDIO_SendCommand(SDIOx, &SDIO_CmdInitStructure, 100);

    errorstatus = CmdResp2Error(SDIOx, &SDIO_CmdInitStructure);
    if(SD_OK != errorstatus)
    {
      return (errorstatus);
    }
    CSD_Tab[0] = SDIO_CmdInitStructure.SDIO_Resp[0];
    CSD_Tab[1] = SDIO_CmdInitStructure.SDIO_Resp[1];
    CSD_Tab[2] = SDIO_CmdInitStructure.SDIO_Resp[2];
    CSD_Tab[3] = SDIO_CmdInitStructure.SDIO_Resp[3];
  }
  /********************************************************************************************************/
  /*全部卡初始化成功 */
  errorstatus = SD_OK;

  return (errorstatus);
}

/*
 * 函数名：SD_GetCardInfo
 * 描述  ：获取SD卡的具体信息
 * 输入  ：-cardinfo 指向SD_CardInfo结构体的指针
 *         这个结构里面包含了SD卡的具体信息
 * 输出  ：-SD_Error SD卡错误代码
 *         成功时则为 SD_OK
 * 调用  ：外部调用
 */
static SD_Error SD_GetCardInfo(SD_CardInfo * cardinfo)
{
  SD_Error errorstatus = SD_OK;
  uint8_t tmp = 0;

  cardinfo->CardType = (uint8_t)CardType;
  cardinfo->RCA = (uint16_t)RCA;

  /*!< Byte 0 */
  tmp = (uint8_t)((CSD_Tab[0] & 0xFF000000) >> 24);
  cardinfo->SD_csd.CSDStruct = (tmp & 0xC0) >> 6;
  cardinfo->SD_csd.SysSpecVersion = (tmp & 0x3C) >> 2;
  cardinfo->SD_csd.Reserved1 = tmp & 0x03;

  /*!< Byte 1 */
  tmp = (uint8_t)((CSD_Tab[0] & 0x00FF0000) >> 16);
  cardinfo->SD_csd.TAAC = tmp;

  /*!< Byte 2 */
  tmp = (uint8_t)((CSD_Tab[0] & 0x0000FF00) >> 8);
  cardinfo->SD_csd.NSAC = tmp;

  /*!< Byte 3 */
  tmp = (uint8_t)(CSD_Tab[0] & 0x000000FF);
  cardinfo->SD_csd.MaxBusClkFrec = tmp;

  /*!< Byte 4 */
  tmp = (uint8_t)((CSD_Tab[1] & 0xFF000000) >> 24);
  cardinfo->SD_csd.CardComdClasses = tmp << 4;

  /*!< Byte 5 */
  tmp = (uint8_t)((CSD_Tab[1] & 0x00FF0000) >> 16);
  cardinfo->SD_csd.CardComdClasses |= (tmp & 0xF0) >> 4;
  cardinfo->SD_csd.RdBlockLen = tmp & 0x0F;

  /*!< Byte 6 */
  tmp = (uint8_t)((CSD_Tab[1] & 0x0000FF00) >> 8);
  cardinfo->SD_csd.PartBlockRead = (tmp & 0x80) >> 7;
  cardinfo->SD_csd.WrBlockMisalign = (tmp & 0x40) >> 6;
  cardinfo->SD_csd.RdBlockMisalign = (tmp & 0x20) >> 5;
  cardinfo->SD_csd.DSRImpl = (tmp & 0x10) >> 4;
  cardinfo->SD_csd.Reserved2 = 0; /*!< Reserved */

  if((CardType == SDIO_STD_CAPACITY_SD_CARD_V1_1) || (CardType == SDIO_STD_CAPACITY_SD_CARD_V2_0))
  {
    cardinfo->SD_csd.DeviceSize = (tmp & 0x03) << 10;

    /*!< Byte 7 */
    tmp = (uint8_t)(CSD_Tab[1] & 0x000000FF);
    cardinfo->SD_csd.DeviceSize |= (tmp) << 2;

    /*!< Byte 8 */
    tmp = (uint8_t)((CSD_Tab[2] & 0xFF000000) >> 24);
    cardinfo->SD_csd.DeviceSize |= (tmp & 0xC0) >> 6;

    cardinfo->SD_csd.MaxRdCurrentVDDMin = (tmp & 0x38) >> 3;
    cardinfo->SD_csd.MaxRdCurrentVDDMax = (tmp & 0x07);

    /*!< Byte 9 */
    tmp = (uint8_t)((CSD_Tab[2] & 0x00FF0000) >> 16);
    cardinfo->SD_csd.MaxWrCurrentVDDMin = (tmp & 0xE0) >> 5;
    cardinfo->SD_csd.MaxWrCurrentVDDMax = (tmp & 0x1C) >> 2;
    cardinfo->SD_csd.DeviceSizeMul = (tmp & 0x03) << 1;
    /*!< Byte 10 */
    tmp = (uint8_t)((CSD_Tab[2] & 0x0000FF00) >> 8);
    cardinfo->SD_csd.DeviceSizeMul |= (tmp & 0x80) >> 7;

    cardinfo->CardCapacity = (cardinfo->SD_csd.DeviceSize + 1);
    cardinfo->CardCapacity *= (1 << (cardinfo->SD_csd.DeviceSizeMul + 2));
    cardinfo->CardBlockSize = 1 << (cardinfo->SD_csd.RdBlockLen);
    cardinfo->CardCapacity *= cardinfo->CardBlockSize;
  }
  else if(CardType == SDIO_HIGH_CAPACITY_SD_CARD)
  {
    /*!< Byte 7 */
    tmp = (uint8_t)(CSD_Tab[1] & 0x000000FF);
    cardinfo->SD_csd.DeviceSize = (tmp & 0x3F) << 16;

    /*!< Byte 8 */
    tmp = (uint8_t)((CSD_Tab[2] & 0xFF000000) >> 24);

    cardinfo->SD_csd.DeviceSize |= (tmp << 8);

    /*!< Byte 9 */
    tmp = (uint8_t)((CSD_Tab[2] & 0x00FF0000) >> 16);

    cardinfo->SD_csd.DeviceSize |= (tmp);

    /*!< Byte 10 */
    tmp = (uint8_t)((CSD_Tab[2] & 0x0000FF00) >> 8);

    cardinfo->CardCapacity = (uint64_t)(cardinfo->SD_csd.DeviceSize + 1) * 512 * 1024;
    cardinfo->CardBlockSize = 512;
  }

  cardinfo->SD_csd.EraseGrSize = (tmp & 0x40) >> 6;
  cardinfo->SD_csd.EraseGrMul = (tmp & 0x3F) << 1;

  /*!< Byte 11 */
  tmp = (uint8_t)(CSD_Tab[2] & 0x000000FF);
  cardinfo->SD_csd.EraseGrMul |= (tmp & 0x80) >> 7;
  cardinfo->SD_csd.WrProtectGrSize = (tmp & 0x7F);

  /*!< Byte 12 */
  tmp = (uint8_t)((CSD_Tab[3] & 0xFF000000) >> 24);
  cardinfo->SD_csd.WrProtectGrEnable = (tmp & 0x80) >> 7;
  cardinfo->SD_csd.ManDeflECC = (tmp & 0x60) >> 5;
  cardinfo->SD_csd.WrSpeedFact = (tmp & 0x1C) >> 2;
  cardinfo->SD_csd.MaxWrBlockLen = (tmp & 0x03) << 2;

  /*!< Byte 13 */
  tmp = (uint8_t)((CSD_Tab[3] & 0x00FF0000) >> 16);
  cardinfo->SD_csd.MaxWrBlockLen |= (tmp & 0xC0) >> 6;
  cardinfo->SD_csd.WriteBlockPaPartial = (tmp & 0x20) >> 5;
  cardinfo->SD_csd.Reserved3 = 0;
  cardinfo->SD_csd.ContentProtectAppli = (tmp & 0x01);

  /*!< Byte 14 */
  tmp = (uint8_t)((CSD_Tab[3] & 0x0000FF00) >> 8);
  cardinfo->SD_csd.FileFormatGrouop = (tmp & 0x80) >> 7;
  cardinfo->SD_csd.CopyFlag = (tmp & 0x40) >> 6;
  cardinfo->SD_csd.PermWrProtect = (tmp & 0x20) >> 5;
  cardinfo->SD_csd.TempWrProtect = (tmp & 0x10) >> 4;
  cardinfo->SD_csd.FileFormat = (tmp & 0x0C) >> 2;
  cardinfo->SD_csd.ECC = (tmp & 0x03);

  /*!< Byte 15 */
  tmp = (uint8_t)(CSD_Tab[3] & 0x000000FF);
  cardinfo->SD_csd.CSD_CRC = (tmp & 0xFE) >> 1;
  cardinfo->SD_csd.Reserved4 = 1;

  /*!< Byte 0 */
  tmp = (uint8_t)((CID_Tab[0] & 0xFF000000) >> 24);
  cardinfo->SD_cid.ManufacturerID = tmp;

  /*!< Byte 1 */
  tmp = (uint8_t)((CID_Tab[0] & 0x00FF0000) >> 16);
  cardinfo->SD_cid.OEM_AppliID = tmp << 8;

  /*!< Byte 2 */
  tmp = (uint8_t)((CID_Tab[0] & 0x000000FF00) >> 8);
  cardinfo->SD_cid.OEM_AppliID |= tmp;

  /*!< Byte 3 */
  tmp = (uint8_t)(CID_Tab[0] & 0x000000FF);
  cardinfo->SD_cid.ProdName1 = tmp << 24;

  /*!< Byte 4 */
  tmp = (uint8_t)((CID_Tab[1] & 0xFF000000) >> 24);
  cardinfo->SD_cid.ProdName1 |= tmp << 16;

  /*!< Byte 5 */
  tmp = (uint8_t)((CID_Tab[1] & 0x00FF0000) >> 16);
  cardinfo->SD_cid.ProdName1 |= tmp << 8;

  /*!< Byte 6 */
  tmp = (uint8_t)((CID_Tab[1] & 0x0000FF00) >> 8);
  cardinfo->SD_cid.ProdName1 |= tmp;

  /*!< Byte 7 */
  tmp = (uint8_t)(CID_Tab[1] & 0x000000FF);
  cardinfo->SD_cid.ProdName2 = tmp;

  /*!< Byte 8 */
  tmp = (uint8_t)((CID_Tab[2] & 0xFF000000) >> 24);
  cardinfo->SD_cid.ProdRev = tmp;

  /*!< Byte 9 */
  tmp = (uint8_t)((CID_Tab[2] & 0x00FF0000) >> 16);
  cardinfo->SD_cid.ProdSN = tmp << 24;

  /*!< Byte 10 */
  tmp = (uint8_t)((CID_Tab[2] & 0x0000FF00) >> 8);
  cardinfo->SD_cid.ProdSN |= tmp << 16;

  /*!< Byte 11 */
  tmp = (uint8_t)(CID_Tab[2] & 0x000000FF);
  cardinfo->SD_cid.ProdSN |= tmp << 8;

  /*!< Byte 12 */
  tmp = (uint8_t)((CID_Tab[3] & 0xFF000000) >> 24);
  cardinfo->SD_cid.ProdSN |= tmp;

  /*!< Byte 13 */
  tmp = (uint8_t)((CID_Tab[3] & 0x00FF0000) >> 16);
  cardinfo->SD_cid.Reserved1 |= (tmp & 0xF0) >> 4;
  cardinfo->SD_cid.ManufactDate = (tmp & 0x0F) << 8;

  /*!< Byte 14 */
  tmp = (uint8_t)((CID_Tab[3] & 0x0000FF00) >> 8);
  cardinfo->SD_cid.ManufactDate |= tmp;

  /*!< Byte 15 */
  tmp = (uint8_t)(CID_Tab[3] & 0x000000FF);
  cardinfo->SD_cid.CID_CRC = (tmp & 0xFE) >> 1;
  cardinfo->SD_cid.Reserved2 = 1;

  return (errorstatus);
}

/*
 * 函数名：SD_SelectDeselect
 * 描述  ：利用cmd7，选择卡相对地址为addr的卡，取消选择其它卡
 *      如果addr = 0,则取消选择所有的卡
 * 输入  ：-addr 选择卡的地址
 * 输出  ：-SD_Error SD卡错误代码
 *         成功时则为 SD_OK
 * 调用  ：外部调用
 */
static SD_Error SD_SelectDeselect(SDIO_TypeDef * SDIOx, uint32_t addr)
{
  SD_Error errorstatus = SD_OK;
  SDIO_CmdInitTypeDef SDIO_CmdInitStructure;

  /*!< Send CMD7 SDIO_SEL_DESEL_CARD */
  SDIO_CmdInitStructure.SDIO_Argument = addr;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_SEL_DESEL_CARD;
  SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R1;
  SDIO_SendCommand(SDIOx, &SDIO_CmdInitStructure, 0);

  errorstatus = CmdResp1Error(SDIOx, &SDIO_CmdInitStructure);

  return (errorstatus);
}

static SD_Error SD_SetBlockSize(SDIO_TypeDef * SDIOx, uint32_t BlockSize)
{
  SD_Error errorstatus = SD_OK;
  SDIO_CmdInitTypeDef SDIO_CmdInitStructure;

  SDIO_CmdInitStructure.SDIO_Argument = BlockSize;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_SET_BLOCKLEN;
  SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R1;
  SDIO_SendCommand(SDIOx, &SDIO_CmdInitStructure, 0);

  errorstatus = CmdResp1Error(SDIOx, &SDIO_CmdInitStructure);

  return (errorstatus);
}

/*
 * 函数名：SD_EnableWideBusOperation
 * 描述  ：配置卡的数据宽度(但得看卡是否支持)
 * 输入  ：-WideMode 指定SD卡的数据线宽
 *         具体可配置如下
 *         @arg MMCSD_BUS_WIDTH_8: 8-bit data transfer (Only for MMC)
 *         @arg MMCSD_BUS_WIDTH_4: 4-bit data transfer
 *         @arg MMCSD_BUS_WIDTH_1: 1-bit data transfer (默认)
 * 输出  ：-SD_Error SD卡错误代码
 *         成功时则为 SD_OK
 * 调用  ：外部调用
 */
static SD_Error SD_EnableWideBusOperation(SDIO_TypeDef * SDIOx, uint8_t WideMode)
{
  SD_Error errorstatus = SD_OK;

  /*!< MMC Card doesn't support this feature */
  if(SDIO_MULTIMEDIA_CARD == CardType)
  {
    errorstatus = SD_UNSUPPORTED_FEATURE;
    return (errorstatus);
  }
  else if((SDIO_STD_CAPACITY_SD_CARD_V1_1 == CardType) || (SDIO_STD_CAPACITY_SD_CARD_V2_0 == CardType) ||
          (SDIO_HIGH_CAPACITY_SD_CARD == CardType))
  {
    if(MMCSD_BUS_WIDTH_8 == WideMode)  // 2.0 sd不支持8bits
    {
      errorstatus = SD_UNSUPPORTED_FEATURE;
      return (errorstatus);
    }
    else if(MMCSD_BUS_WIDTH_4 == WideMode)  // 4数据线模式
    {
      errorstatus = SD_Enable_WideBus(SDIOx, ENABLE); // 使用acmd6设置总线宽度，设置卡的传输方式

      if(SD_OK == errorstatus)
      {
        SDIO_Set_Ios(SDIOx, 4000000, WideMode);
      }
    }
    else // 单数据线模式
    {
      errorstatus = SD_Enable_WideBus(SDIOx, DISABLE);

      if(SD_OK == errorstatus)
      {
        SDIO_Set_Ios(SDIOx, 4000000, WideMode);
      }
    }
  }

  return (errorstatus);
}

/*
 * 函数名：SD_Enable_WideBus
 * 描述  ：使能或关闭SDIO的4bit模式
 * 输入  ：新状态 ENABLE 或DISABLE
 * 输出  ：SD错误类型
 */
static SD_Error SD_Enable_WideBus(SDIO_TypeDef * SDIOx, FunctionalState NewState)
{
  SD_Error errorstatus = SD_OK;
  SDIO_CmdInitTypeDef SDIO_CmdInitStructure;

  /*!< If wide bus operation to be enabled */
  if(NewState == ENABLE)
  {
    /*!< Send CMD55 APP_CMD with argument as card's RCA.*/
    SDIO_CmdInitStructure.SDIO_Argument = (uint32_t)RCA << 16;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_APP_CMD;
    SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R1;
    SDIO_SendCommand(SDIOx, &SDIO_CmdInitStructure, 0);

    errorstatus = CmdResp1Error(SDIOx, &SDIO_CmdInitStructure);

    if(errorstatus != SD_OK)
    {
      return (errorstatus);
    }

    /*!< Send ACMD6 APP_CMD with argument as 2 for wide bus mode */
    /*开启4bit模式的命令acmd6*/
    SDIO_CmdInitStructure.SDIO_Argument = 0x2;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_APP_SD_SET_BUSWIDTH;
    SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R1;
    SDIO_SendCommand(SDIOx, &SDIO_CmdInitStructure, 0);

    errorstatus = CmdResp1Error(SDIOx, &SDIO_CmdInitStructure);

    if(errorstatus != SD_OK)
    {
      errorstatus = SD_REQUEST_NOT_APPLICABLE;
    }
    return errorstatus;
  } /*!< If wide bus operation to be disabled */
  else
  {
    /*!< Send CMD55 APP_CMD with argument as card's RCA.*/
    SDIO_CmdInitStructure.SDIO_Argument = (uint32_t)RCA << 16;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_APP_CMD;
    SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R1;
    SDIO_SendCommand(SDIOx, &SDIO_CmdInitStructure, 0);

    errorstatus = CmdResp1Error(SDIOx, &SDIO_CmdInitStructure);

    if(errorstatus != SD_OK)
    {
      return (errorstatus);
    }

    /*!< Send ACMD6 APP_CMD with argument as 0 for single bus mode */
    SDIO_CmdInitStructure.SDIO_Argument = 0x00;
    SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_APP_SD_SET_BUSWIDTH;
    SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R1;
    SDIO_SendCommand(SDIOx, &SDIO_CmdInitStructure, 0);

    errorstatus = CmdResp1Error(SDIOx, &SDIO_CmdInitStructure);

    if(errorstatus != SD_OK)
    {
      errorstatus = SD_REQUEST_NOT_APPLICABLE;
    }
    return errorstatus;
  }
}

static SD_Error CmdResp1Error(SDIO_TypeDef * SDIOx, SDIO_CmdInitTypeDef * SDIO_CmdInitStruct)
{
  uint32_t count = 0;
  uint8_t respIndex = 0;

  do
  {
    count++;
    respIndex = (SDIO_Get_STA(SDIOx) >> 11) & 0x3f;
    delay_us(80);
  } while((count < SD_TIMEOUT) && (respIndex != SDIO_CmdInitStruct->SDIO_CmdIndex));

  if(count >= SD_TIMEOUT)
  {
    return SD_CMD_RSP_TIMEOUT;
  }
  return SD_OK;
}

static SD_Error CmdResp2Error(SDIO_TypeDef * SDIOx, SDIO_CmdInitTypeDef * SDIO_CmdInitStruct)
{
  uint32_t count = 0;
  uint8_t respIndex = 0;

  do
  {
    count++;
    SDIO_SendCommand(SDIOx, SDIO_CmdInitStruct, 500);
    respIndex = (SDIO_Get_STA(SDIOx) >> 11) & 0x3f;
  } while((count < SD_TIMEOUT) && (respIndex != 63));
  if(count >= SD_TIMEOUT)
  {
    return SD_CMD_RSP_TIMEOUT;
  }
  return SD_OK;
}

static SD_Error CmdResp6Error(SDIO_TypeDef * SDIOx, SDIO_CmdInitTypeDef * SDIO_CmdInitStruct, uint16_t * prca)
{
  uint32_t count = 0;
  uint8_t respIndex = 0;
  uint32_t response_r0;
  do
  {
    count++;
    SDIO_SendCommand(SDIOx, SDIO_CmdInitStruct, 0);
    respIndex = (SDIO_Get_STA(SDIOx) >> 11) & 0x3f;
    if(respIndex == SDIO_CmdInitStruct->SDIO_CmdIndex)
    {
      response_r0 = SDIO_CmdInitStruct->SDIO_Resp[0];
      if(SD_ALLZERO == (response_r0 &
                        (SD_R6_GENERAL_UNKNOWN_ERROR |
                         SD_R6_ILLEGAL_CMD |
                         SD_R6_COM_CRC_FAILED)))
      {
        *prca = (uint16_t)(response_r0 >> 16); // 右移16位，就是接收到的返回rca
        break;
      }
    }
  } while((count < SD_TIMEOUT));

  if(count >= SD_TIMEOUT)
  {
    return SD_CMD_RSP_TIMEOUT;
  }
  return SD_OK;
}

static SD_Error CmdResp7Error(SDIO_TypeDef * SDIOx, SDIO_CmdInitTypeDef * SDIO_CmdInitStruct)
{
  uint32_t count = 0;
  uint32_t response = 0;
  uint32_t state = 0;
  uint8_t respIndex = 0;

  do
  {
    count++;
    SDIO_SendCommand(SDIOx, SDIO_CmdInitStruct, 0);
    response = SDIO_CmdInitStruct->SDIO_Resp[0] & 0xAA;
    state = SDIO_Get_STA(SDIOx);
    respIndex = (state >> 11) & 0x3f;
  } while((!response) && (count < SD_TIMEOUT) && (respIndex != 8));
  if(count >= SD_TIMEOUT)
  {
    return SD_CMD_RSP_TIMEOUT;
  }
  return SD_OK;
}

SD_Error SD_ReadBlock(SDIO_TypeDef * SDIOx,
                      uint8_t * ReadBuff,
                      uint32_t ReadAddr,
                      uint16_t BlockSize)
{
  SDIO_CmdInitTypeDef SDIO_CmdInitStructure;
  SDIO_DataInitTypeDef SDIO_DataInitStructure;
  SD_Error errorstatus = SD_OK;
  if(NULL == ReadBuff)
  {
    return SD_INVALID_PARAMETER;
  }
  if(CardType == SDIO_HIGH_CAPACITY_SD_CARD)  // 大容量卡
  {
    BlockSize = 512;
    ReadAddr >>= 9;
  }
  if((BlockSize > 0) && (BlockSize <= 2048) && ((BlockSize & (BlockSize - 1)) == 0))
  {
    errorstatus = SD_SetBlockSize(SDIOx, BlockSize);
    if(errorstatus != SD_OK)
    {
      return errorstatus;
    }
  }
  else
  {
    return SD_INVALID_PARAMETER;
  }

  SDIO_DataInitStructure.blksize = BlockSize;
  SDIO_DataInitStructure.blks = 1;
  SDIO_DataInitStructure.buf = ReadBuff;
  SDIO_DataInitStructure.flags = SDIO_DATA_DIR_READ;

  SDIO_CmdInitStructure.SDIO_Argument = ReadAddr;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_READ_SINGLE_BLOCK;
  SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R1;
  SDIO_SendCommand_and_Data(SDIOx, &SDIO_DataInitStructure, &SDIO_CmdInitStructure, 0);

  errorstatus = CmdResp1Error(SDIOx, &SDIO_CmdInitStructure);

  return errorstatus;
}

SD_Error SD_ReadMultiBlocks(SDIO_TypeDef * SDIOx,
                            uint8_t * ReadBuff,
                            uint32_t ReadAddr,
                            uint16_t BlockSize,
                            uint32_t NumberOfBlocks)
{

  SDIO_CmdInitTypeDef SDIO_CmdInitStructure;
  SDIO_DataInitTypeDef SDIO_DataInitStructure;
  SD_Error errorstatus = SD_OK;
  if(NULL == ReadBuff)
  {
    return SD_INVALID_PARAMETER;
  }
  if(CardType == SDIO_HIGH_CAPACITY_SD_CARD)  // 大容量卡
  {
    BlockSize = 512;
    ReadAddr >>= 9;
  }
  if((BlockSize > 0) && (BlockSize <= 2048) && ((BlockSize & (BlockSize - 1)) == 0))
  {
    errorstatus = SD_SetBlockSize(SDIOx, BlockSize);
    if(errorstatus != SD_OK)
    {
      return errorstatus;
    }
  }
  else
  {
    return SD_INVALID_PARAMETER;
  }

  SDIO_DataInitStructure.blksize = BlockSize;
  SDIO_DataInitStructure.blks = NumberOfBlocks;
  SDIO_DataInitStructure.buf = ReadBuff;
  SDIO_DataInitStructure.flags = SDIO_DATA_DIR_READ;

  SDIO_CmdInitStructure.SDIO_Argument = ReadAddr;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_READ_MULT_BLOCK;
  SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R1;
  SDIO_SendCommand_and_Data(SDIOx, &SDIO_DataInitStructure, &SDIO_CmdInitStructure, 0);

  errorstatus = CmdResp1Error(SDIOx, &SDIO_CmdInitStructure);

  if(errorstatus != SD_OK)
  {
    return errorstatus;
  }

  SDIO_CmdInitStructure.SDIO_Argument = 0;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_STOP_TRANSMISSION;
  SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R1B;
  SDIO_SendCommand(SDIOx, &SDIO_CmdInitStructure, 0);

  errorstatus = CmdResp1Error(SDIOx, &SDIO_CmdInitStructure);
  if(errorstatus != SD_OK)
  {
    return errorstatus;
  }

  return errorstatus;
}

SD_Error SD_WriteBlock(SDIO_TypeDef * SDIOx,
                       uint8_t * WriteBuff,
                       uint32_t WriteAddr,
                       uint16_t BlockSize)
{
  SDIO_CmdInitTypeDef SDIO_CmdInitStructure;
  SDIO_DataInitTypeDef SDIO_DataInitStructure;
  SD_Error errorstatus = SD_OK;
  if(NULL == WriteBuff)
  {
    return SD_INVALID_PARAMETER;
  }
  if(CardType == SDIO_HIGH_CAPACITY_SD_CARD)  // 大容量卡
  {
    BlockSize = 512;
    WriteAddr >>= 9;
  }
  if((BlockSize > 0) && (BlockSize <= 2048) && ((BlockSize & (BlockSize - 1)) == 0))
  {
    errorstatus = SD_SetBlockSize(SDIOx, BlockSize);
    if(errorstatus != SD_OK)
    {
      return errorstatus;
    }
  }
  else
  {
    return SD_INVALID_PARAMETER;
  }

  SDIO_DataInitStructure.blksize = BlockSize;
  SDIO_DataInitStructure.blks = 1;
  SDIO_DataInitStructure.buf = WriteBuff;
  SDIO_DataInitStructure.flags = SDIO_DATA_DIR_WRITE;

  SDIO_CmdInitStructure.SDIO_Argument = WriteAddr;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_WRITE_SINGLE_BLOCK;
  SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R1;
  SDIO_SendCommand_and_Data(SDIOx, &SDIO_DataInitStructure, &SDIO_CmdInitStructure, 0);

  errorstatus = CmdResp1Error(SDIOx, &SDIO_CmdInitStructure);

  return errorstatus;
}

SD_Error SD_WriteMultiBlocks(SDIO_TypeDef * SDIOx,
                             uint8_t * WriteBuff,
                             uint32_t WriteAddr,
                             uint16_t BlockSize,
                             uint32_t NumberOfBlocks)
{

  SDIO_CmdInitTypeDef SDIO_CmdInitStructure;
  SDIO_DataInitTypeDef SDIO_DataInitStructure;
  SD_Error errorstatus = SD_OK;
  if(NULL == WriteBuff)
  {
    return SD_INVALID_PARAMETER;
  }
  if(CardType == SDIO_HIGH_CAPACITY_SD_CARD)  // 大容量卡
  {
    BlockSize = 512;
    WriteAddr >>= 9;
  }
  if((BlockSize > 0) && (BlockSize <= 2048) && ((BlockSize & (BlockSize - 1)) == 0))
  {
    errorstatus = SD_SetBlockSize(SDIOx, BlockSize);
    if(errorstatus != SD_OK)
    {
      return errorstatus;
    }
  }
  else
  {
    return SD_INVALID_PARAMETER;
  }

  SDIO_DataInitStructure.blksize = BlockSize;
  SDIO_DataInitStructure.blks = NumberOfBlocks;
  SDIO_DataInitStructure.buf = WriteBuff;
  SDIO_DataInitStructure.flags = SDIO_DATA_DIR_WRITE;

  SDIO_CmdInitStructure.SDIO_Argument = WriteAddr;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_WRITE_MULT_BLOCK;
  SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R1;
  SDIO_SendCommand_and_Data(SDIOx, &SDIO_DataInitStructure, &SDIO_CmdInitStructure, 0);

  errorstatus = CmdResp1Error(SDIOx, &SDIO_CmdInitStructure);

  if(errorstatus != SD_OK)
  {
    return errorstatus;
  }

  SDIO_CmdInitStructure.SDIO_Argument = 0;
  SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_STOP_TRANSMISSION;
  SDIO_CmdInitStructure.SDIO_Flags = SDIO_RESP_R1B;
  SDIO_SendCommand(SDIOx, &SDIO_CmdInitStructure, 0);

  errorstatus = CmdResp1Error(SDIOx, &SDIO_CmdInitStructure);
  if(errorstatus != SD_OK)
  {
    return errorstatus;
  }

  return errorstatus;
}

// 读SD卡
// buf:读数据缓存区
// sector:扇区地址
// cnt:扇区个数
// 返回值:错误状态;0,正常;其他,错误代码;
SD_Error SD_ReadDisk(SDIO_TypeDef * SDIOx, uint8_t * buf, uint32_t sector, uint32_t cnt)
{
  SD_Error result = SD_OK;
  long long lsector = sector;
  uint32_t n;
  lsector <<= 9;
  if((uint32_t)buf % 4 != 0)
  {
    for(n = 0; n < cnt; n++)
    {
      result = SD_ReadBlock(SDIOx, buf, lsector + 512 * n, 512);
      buf += 512;
    }
  }
  else
  {
    if(cnt == 1)
    {
      result = SD_ReadBlock(SDIOx, buf, lsector, 512);
    }
    else
    {
      result = SD_ReadMultiBlocks(SDIOx, buf, lsector, 512, cnt);
    }
  }
  return result;
}

// 写SD卡
// buf:写数据缓存区
// sector:扇区地址
// cnt:扇区个数
// 返回值:错误状态;0,正常;其他,错误代码;
SD_Error SD_WriteDisk(SDIO_TypeDef * SDIOx, uint8_t * buf, uint32_t sector, uint32_t cnt)
{
  SD_Error result = SD_OK;
  long long lsector = sector;
  uint32_t n;
  lsector <<= 9;
  if((uint32_t)buf % 4 != 0)
  {
    for(n = 0; n < cnt; n++)
    {
      result = SD_WriteBlock(SDIOx, buf, lsector + 512 * n, 512);
      buf += 512;
    }
  }
  else
  {
    if(cnt == 1)
    {
      result = SD_WriteBlock(SDIOx, buf, lsector, 512);
    }
    else if(cnt > 1)
    {
      result = SD_WriteMultiBlocks(SDIOx, buf, lsector, 512, cnt);
    }
  }
  return result;
}
