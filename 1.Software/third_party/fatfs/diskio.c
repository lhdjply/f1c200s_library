#include "diskio.h" /* Declarations of disk functions */
#include "common.h"

extern DATA mydata;
extern SD_CardInfo SDCardInfo;
extern USB_NOCACHE_RAM_SECTION struct usbh_msc *active_msc_class;

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status(
		BYTE pdrv /* Physical drive nmuber to identify the drive */
)
{
	DSTATUS status = STA_NOINIT;

	switch (pdrv)
	{
	case SD_CARD: /* SD CARD */
		status &= ~STA_NOINIT;
		break;
	case USB:
		if (active_msc_class == NULL)
		{
			status = STA_NOINIT;
		}
		else
		{
			status = RES_OK;
		}
		break;
	default:
		status = STA_NOINIT;
	}
	return status;
}

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize(
		BYTE pdrv /* Physical drive nmuber to identify the drive */
)
{
	DSTATUS status = STA_NOINIT;
	switch (pdrv)
	{
	case SD_CARD: /* SD CARD */
		if (SD_Init(SDIO0) == SD_OK)
		{
			status &= ~STA_NOINIT;
		}
		status &= ~STA_NOINIT;
		break;
	case USB:
		if (active_msc_class == NULL)
		{
			status = STA_NOINIT;
		}
		else
		{
			status = RES_OK;
		}
		break;
	default:
		status = STA_NOINIT;
	}
	return status;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read(
		BYTE pdrv,		/* Physical drive nmuber to identify the drive */
		BYTE *buff,		/* Data buffer to store read data */
		LBA_t sector, /* Start sector in LBA */
		UINT count		/* Number of sectors to read */
)
{
	DRESULT status;
	switch (pdrv)
	{
	case SD_CARD:
		status = SD_ReadDisk(SDIO0, buff, sector, count);
		break;
	case USB:
		status = usbh_msc_scsi_read10(active_msc_class, sector, buff, count);
		break;
	default:
		status = RES_PARERR;
	}
	return status;
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write(
		BYTE pdrv,				/* Physical drive nmuber to identify the drive */
		const BYTE *buff, /* Data to be written */
		LBA_t sector,			/* Start sector in LBA */
		UINT count				/* Number of sectors to write */
)
{
	DRESULT status;
	if (!count)
	{
		return RES_PARERR; /* Check parameter */
	}
	switch (pdrv)
	{
	case SD_CARD:
		status = SD_WriteDisk(SDIO0, (uint8_t *)buff, sector, count);
		break;
	case USB:
		status = usbh_msc_scsi_write10(active_msc_class, sector, buff, count);
		break;
	default:
		status = RES_PARERR;
	}
	return status;
}
#endif

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl(
		BYTE pdrv, /* Physical drive nmuber (0..) */
		BYTE cmd,	 /* Control code */
		void *buff /* Buffer to send/receive control data */
)
{
	DRESULT status = RES_PARERR;
	switch (pdrv)
	{
	case SD_CARD:
		if (status & STA_NOINIT)
			return RES_NOTRDY;
		switch (cmd)
		{
		case CTRL_SYNC:
			status = RES_OK;
			break;
		case GET_SECTOR_SIZE:
			*(DWORD *)buff = 512;
			status = RES_OK;
			break;
		case GET_SECTOR_COUNT:
			*(DWORD *)buff = SDCardInfo.CardCapacity / 512;
			status = RES_OK;
			break;
		case GET_BLOCK_SIZE:
			*(DWORD *)buff = SDCardInfo.CardBlockSize;
			status = RES_OK;
			break;
		default:
			status = RES_PARERR;
			break;
		}
		break;
	case USB:
		switch (cmd)
		{
		case CTRL_SYNC:
			status = RES_OK;
			break;
		case GET_SECTOR_SIZE:
			*(WORD *)buff = active_msc_class->blocksize;
			status = RES_OK;
			break;
		case GET_BLOCK_SIZE:
			*(DWORD *)buff = 1;
			status = RES_OK;
			break;
		case GET_SECTOR_COUNT:
			*(DWORD *)buff = active_msc_class->blocknum;
			status = RES_OK;
			break;
		default:
			status = RES_PARERR;
			break;
		}
		break;
	default:
		status = RES_PARERR;
	}
	return status;
}

// 获得时间
// User defined function to give a current time to fatfs module      */
// 31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */
// 15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */
DWORD get_fattime(void)
{
	DWORD time_buff = 0;

	// 按照FatFs的时间格式组合
	time_buff |= ((mydata.real_time.year - 1980) << 25); // 年
	time_buff |= (mydata.real_time.month << 21);				 // 月
	time_buff |= (mydata.real_time.day << 16);					 // 日

	time_buff |= (mydata.real_time.hour << 11);	 // 时
	time_buff |= (mydata.real_time.minute << 5); // 分
	time_buff |= (mydata.real_time.second / 2);	 // 秒

	return time_buff;
}
