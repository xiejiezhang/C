/*******************************************Copyright(c)**************************************************
**                        Guangzhou ZHIYUAN electronics Co.,LTD
**
**                           http://www.embedtools.com
**
**---------------File Info--------------------------------------------------------------------------------
** File Name:              pic_spi.h
** Lastest modified Date:  2014-08-26
** Latest Version:         V1.0
** Description:            SPI接口的声明
**
**--------------------------------------------------------------------------------------------------------
** Created By:             Xie JieZhang
** Created date:           2014-08-26
** Version:                V1.0
** Description:            SPI接口声明
**
**--------------------------------------------------------------------------------------------------------
** Modified By:            
** Modified date:          
** Version:                
** Description:            
**
*********************************************************************************************************/
#ifndef _PIC_SPI_H
#define _PIC_SPI_H

#define uchar unsigned char
#define uint unsigned int

#define CE_BIT   5
#define CSN_BIT  7
#define SCLK_BIT 3
#define MOSI_BIT 4
#define MISO_BIT 5
#define IRQ_BIT  6

#define CE_CLR  (PORTA &= ~(0x01<<CE_BIT))
#define CE_SET  (PORTA |=   0x01<<CE_BIT)

#define CSN_CLR  (PORTC &= ~(0x01<<CSN_BIT))
#define CSN_SET   (PORTC |=   0x01<<CSN_BIT)

#define SCLK_CLR  (PORTC &= ~(0x01<<SCLK_BIT))
#define SCLK_SET   (PORTC |=   0x01<<SCLK_BIT)

#define MOSI_CLR  (PORTC &= ~(0x01<<MOSI_BIT))
#define MOSI_SET   (PORTC |=   0x01<<MOSI_BIT)

#define MISO_CLR  (PORTC &= ~(0x01<<MISO_BIT))
#define MISO_SET   (PORTC |=   0x01<<MISO_BIT)

#define IRQ_VAL ((PORTC & (0x01 << IRQ_BIT)) ? 1 : 0 )
uchar spiBufWrite(uchar ucReg, uchar *pucBuf, uchar ucN);
uchar spiBufRead(uchar ucReg, uchar *pucBuf, uchar ucN);
uchar spiRegRead (uchar ucReg);
uchar spiRegRW (uchar ucReg, uchar ucVal);
uchar spiByteRW (uchar ucByte);
void spiInit (void);

void spiUsDelay (uchar n);

#endif
/*********************************************************************************************************
   End File
*********************************************************************************************************/
