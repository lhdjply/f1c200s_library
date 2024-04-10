#include "w25nxx.h"

static uint8_t W25NXX_ReadWriteByte(uint8_t TxData);
static void W25NXX_Write_Enable(void);
static void W25NXX_Wait_WriteEnd(void);
static void W25NXX_Read_Page(uint8_t * pBuffer, uint16_t ReadRowAddr, uint16_t ReadColumnAddr,
                             uint16_t NumByteToRead);
static void W25NXX_Write_Page(uint8_t * pBuffer, uint16_t WriteRowAddr, uint16_t WriteColumnAddr,
                              uint16_t NumByteToWrite);

void W25NXX_Init(void)
{
  SPI_InitTypeDef SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  CCU_BUS0_GatingClockCmd(CCU_BUS0Gating_SPI0, ENABLE);
  CCU_BUS0_GatingResetCmd(CCU_BUS0Gating_SPI0, ENABLE);

  GPIO_AF_Remap(GPIOC, GPIO_PinSource0, GPIO_AF_PC0_SPI0_CLK);
  GPIO_AF_Remap(GPIOC, GPIO_PinSource2, GPIO_AF_PC2_SPI0_MISO);
  GPIO_AF_Remap(GPIOC, GPIO_PinSource3, GPIO_AF_PC3_SPI0_MOSI);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /*W25NXX_CS*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_DriveCurrent = GPIO_DriveCurrent_Level3;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  W25NXX_CS = 1;

  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_Init(W25NXX_SPI, &SPI_InitStructure);

  SPI_Cmd(W25NXX_SPI, ENABLE); // 使能SPI外设
}

// SPIx 读写一个字节
// TxData:要写入的字节
// 返回值:读取到的字节
static uint8_t W25NXX_ReadWriteByte(uint8_t TxData)
{
  SPI_TransmitData8(W25NXX_SPI, TxData);
  while((W25NXX_SPI->FSR & 0xff) < 1)
  {
  }
  return SPI_ReceiveData8(W25NXX_SPI);
}

static void W25NXX_Write_Enable(void)
{
  W25NXX_CS = 0;                          // 使能器件
  W25NXX_ReadWriteByte(W25N_WriteEnable); // 发送写使能
  W25NXX_CS = 1;                          // 取消片选
}

static void W25NXX_Wait_WriteEnd(void)
{
  uint8_t ucFlash_Status = 0;

  do
  {
    W25NXX_CS = 0;
    W25NXX_ReadWriteByte(W25N_ReadStatusReg);
    W25NXX_ReadWriteByte(0xc0);
    ucFlash_Status = W25NXX_ReadWriteByte(0xff);
    W25NXX_CS = 1;
  } while((0x01 & ucFlash_Status) == SET);
}

uint16_t W25NXX_ReadID(void)
{
  uint16_t Temp = 0;
  W25NXX_CS = 0;
  W25NXX_ReadWriteByte(W25N_JedecDeviceID); // 发送读取ID命令
  W25NXX_ReadWriteByte(0x00);
  W25NXX_ReadWriteByte(0x00);
  Temp |= W25NXX_ReadWriteByte(0xFF) << 8;
  Temp |= W25NXX_ReadWriteByte(0xFF);
  W25NXX_CS = 1;
  return Temp;
}

/* flash读 */
static void W25NXX_Read_Page(uint8_t * pBuffer, uint16_t ReadRowAddr, uint16_t ReadColumnAddr, uint16_t NumByteToRead)
{
  /* 片选拉低 */
  if(NumByteToRead + ReadColumnAddr > W25NXX_PAGE_SIZE)
  {
    NumByteToRead = W25NXX_PAGE_SIZE;
    //SPI_FLASH_PageWrite too large
    return;
  }

  W25NXX_CS = 0;
  /* 读page指令，将数据从存储矩阵读取到cache中 */
  W25NXX_ReadWriteByte(W25N_ReadPage);
  W25NXX_ReadWriteByte(0x00);
  W25NXX_ReadWriteByte((ReadRowAddr & 0xFF00) >> 8);
  W25NXX_ReadWriteByte((ReadRowAddr & 0xFF));

  W25NXX_CS = 1;

  /* 等待flash操作完成 */
  W25NXX_Wait_WriteEnd();

  W25NXX_CS = 0;

  /* 发送读cache指令，从cache中读取数据 */
  W25NXX_ReadWriteByte(W25N_ReadData);
  W25NXX_ReadWriteByte((ReadColumnAddr & 0xFF00) >> 8);
  W25NXX_ReadWriteByte((ReadColumnAddr & 0xFF));
  W25NXX_ReadWriteByte(0x00);

  /* 取出数据 */
  while(NumByteToRead--)
  {
    *pBuffer = W25NXX_ReadWriteByte(0xff);
    pBuffer++;
  }
  W25NXX_CS = 1;

  /* 等待操作完成 */
  W25NXX_Wait_WriteEnd();
}

/* 页写入 */
static void W25NXX_Write_Page(uint8_t * pBuffer, uint16_t WriteRowAddr, uint16_t WriteColumnAddr,
                              uint16_t NumByteToWrite)
{
  if(NumByteToWrite + WriteColumnAddr > W25NXX_PAGE_SIZE)
  {
    NumByteToWrite = W25NXX_PAGE_SIZE;
    // SPI_FLASH_PageWrite too large
    return;
  }

  /* 写使能 */
  W25NXX_Write_Enable();

  /* 等待操作完成 */
  W25NXX_Wait_WriteEnd();

  W25NXX_CS = 0;

  /* 页写入指令 */
  W25NXX_ReadWriteByte(W25N_PageProgram_Load);
  W25NXX_ReadWriteByte((WriteColumnAddr & 0xFF00) >> 8);
  W25NXX_ReadWriteByte((WriteColumnAddr & 0xFF));

  /* 发送数据 */
  while(NumByteToWrite--)
  {
    W25NXX_ReadWriteByte(*pBuffer);
    pBuffer++;
  }
  W25NXX_CS = 1;

  /* 写使能 */
  W25NXX_Write_Enable();

  /* 等待操作完成 */
  W25NXX_Wait_WriteEnd();

  W25NXX_CS = 0;

  /* 写入PROGRAM_EXECUTE命令，将数据从缓存中写入存储矩阵 */
  W25NXX_ReadWriteByte(W25N_Program_Execute);
  W25NXX_ReadWriteByte((WriteRowAddr & 0xFF0000) >> 16); //无意义
  W25NXX_ReadWriteByte((WriteRowAddr & 0xFF00) >> 8);
  W25NXX_ReadWriteByte((WriteRowAddr & 0xFF));
  W25NXX_CS = 1;

  /* 等待操作完成 */
  W25NXX_Wait_WriteEnd();
}

/* 任意大小量读 */
void W25NXX_Read_Buffer(uint8_t * pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
  uint16_t ReadRowAddr = 0;
  uint16_t ReadColumnAddr = 0;
  uint8_t NumOfPage = 0;
  uint16_t ReadPageLen = 0;

  /* 地址转换 */
  ReadColumnAddr = ReadAddr % W25NXX_PAGE_SIZE;
  ReadRowAddr = ReadAddr / W25NXX_PAGE_SIZE;

  //判断读数据量是否会超过第一页
  if(NumByteToRead <= W25NXX_PAGE_SIZE - ReadColumnAddr)
  {
    ReadPageLen = NumByteToRead;
    NumOfPage = 0;

    W25NXX_Read_Page(pBuffer, ReadRowAddr, ReadColumnAddr, ReadPageLen);
  }
  else
  {
    //计算需要读出的页数
    NumOfPage = (NumByteToRead - (W25NXX_PAGE_SIZE - ReadColumnAddr)) / W25NXX_PAGE_SIZE;

    //超过第一页，但不超过第二页，需要从第一页和第二页读
    if(NumOfPage <= 0)
    {
      //第一页
      ReadPageLen = W25NXX_PAGE_SIZE - ReadColumnAddr;
      W25NXX_Read_Page(pBuffer, ReadRowAddr, ReadColumnAddr, ReadPageLen);

      //第二页
      pBuffer = pBuffer + ReadPageLen;
      ReadPageLen = NumByteToRead - ReadPageLen;
      ReadRowAddr++;
      ReadColumnAddr = 0;
      W25NXX_Read_Page(pBuffer, ReadRowAddr, ReadColumnAddr, ReadPageLen);
    }
    else //超过第一页，且数据量大于一页
    {
      //第一页
      ReadPageLen = W25NXX_PAGE_SIZE - ReadColumnAddr;
      W25NXX_Read_Page(pBuffer, ReadRowAddr, ReadColumnAddr, ReadPageLen);

      //中间页
      while(NumOfPage--)
      {
        pBuffer = pBuffer + ReadPageLen;
        ReadPageLen = W25NXX_PAGE_SIZE;
        ReadRowAddr++;
        ReadColumnAddr = 0;
        W25NXX_Read_Page(pBuffer, ReadRowAddr, ReadColumnAddr, ReadPageLen);
      }

      //最后一页,最后一页读的数据量 = (总数据量 - 第一页写入的数据) % 页大小
      pBuffer = pBuffer + ReadPageLen;
      ReadPageLen = (NumByteToRead - (W25NXX_PAGE_SIZE - ReadColumnAddr)) % W25NXX_PAGE_SIZE;
      ReadRowAddr++;
      ReadColumnAddr = 0;
      W25NXX_Read_Page(pBuffer, ReadRowAddr, ReadColumnAddr, ReadPageLen);
    }
  }
}

/* 任意大小量写入 */
void W25NXX_Write_Buffer(uint8_t * pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  uint16_t WriteRowAddr = 0;
  uint16_t WriteColumnAddr = 0;
  uint8_t NumOfPage = 0;
  uint16_t WritePageLen = 0;

  /* 地址转换 */
  WriteColumnAddr = WriteAddr % W25NXX_PAGE_SIZE;
  WriteRowAddr = WriteAddr / W25NXX_PAGE_SIZE;

  //    /* 计算写入的页数 */
  //    NumOfPage = NumByteToWrite / W25NXX_PAGE_SIZE;
  //    /*mod 运算求余，计算出剩余不满一页的字节数*/
  //    NumOfSingle = NumByteToWrite % W25NXX_PAGE_SIZE;

  //判断写入数据是否会超过第一页
  if(NumByteToWrite <= W25NXX_PAGE_SIZE - WriteColumnAddr)
  {
    WritePageLen = NumByteToWrite;
    NumOfPage = 0;
    W25NXX_FLASH_BlockErase(WriteRowAddr);
    W25NXX_Write_Page(pBuffer, WriteRowAddr, WriteColumnAddr, WritePageLen);
  }
  else //超过第一页
  {
    /* 计算写入的页数 */
    NumOfPage = (NumByteToWrite - (W25NXX_PAGE_SIZE - WriteColumnAddr)) / W25NXX_PAGE_SIZE;

    //超过第一页，但不超过第二页，需要在第一页和第二页写入
    if(NumOfPage <= 0)
    {
      //第一页
      WritePageLen = W25NXX_PAGE_SIZE - WriteColumnAddr;
      W25NXX_FLASH_BlockErase(WriteRowAddr);
      W25NXX_Write_Page(pBuffer, WriteRowAddr, WriteColumnAddr, WritePageLen);

      //第二页
      pBuffer = pBuffer + WritePageLen;
      WritePageLen = NumByteToWrite - WritePageLen;
      WriteRowAddr++;
      WriteColumnAddr = 0;
      W25NXX_FLASH_BlockErase(WriteRowAddr);
      W25NXX_Write_Page(pBuffer, WriteRowAddr, WriteColumnAddr, WritePageLen);
    }
    else //超过第一页，且数据量大于一页
    {
      //第一页
      WritePageLen = W25NXX_PAGE_SIZE - WriteColumnAddr;
      W25NXX_FLASH_BlockErase(WriteRowAddr);
      W25NXX_Write_Page(pBuffer, WriteRowAddr, WriteColumnAddr, WritePageLen);

      //中间页，每一页都正好写满
      while(NumOfPage--)
      {
        pBuffer = pBuffer + WritePageLen;
        WritePageLen = W25NXX_PAGE_SIZE;
        WriteRowAddr++;
        WriteColumnAddr = 0;
        W25NXX_FLASH_BlockErase(WriteRowAddr);
        W25NXX_Write_Page(pBuffer, WriteRowAddr, WriteColumnAddr, WritePageLen);
      }

      //最后一页,最后一页写入的数据量 = (总数据量 - 第一页写入的数据) % 页大小
      pBuffer = pBuffer + WritePageLen;
      WritePageLen = (NumByteToWrite - (W25NXX_PAGE_SIZE - WriteColumnAddr)) % W25NXX_PAGE_SIZE;
      WriteRowAddr++;
      WriteColumnAddr = 0;
      W25NXX_FLASH_BlockErase(WriteRowAddr);
      W25NXX_Write_Page(pBuffer, WriteRowAddr, WriteColumnAddr, WritePageLen);
    }
  }
}

void W25NXX_FLASH_BlockErase(uint32_t BlockAddr)
{
  /* 写使能 */
  W25NXX_Write_Enable();

  /* 等待操作完成 */
  W25NXX_Wait_WriteEnd();

  W25NXX_CS = 0;

  /* 发送块擦除命令 */
  W25NXX_ReadWriteByte(W25N_BlockErase);
  W25NXX_ReadWriteByte((uint8_t)((BlockAddr) >> 16));
  W25NXX_ReadWriteByte((uint8_t)((BlockAddr) >> 8));
  W25NXX_ReadWriteByte((uint8_t)BlockAddr);
  W25NXX_CS = 1;

  /* 等待操作完成 */
  W25NXX_Wait_WriteEnd();
}
