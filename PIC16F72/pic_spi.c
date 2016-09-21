/*******************************************Copyright(c)**************************************************
**                        Guangzhou ZHIYUAN electronics Co.,LTD
**
**                           http://www.embedtools.com
**
**---------------File Info--------------------------------------------------------------------------------
** File Name:              pic_spi.c
** Lastest modified Date:  2014-08-27
** Latest Version:         V1.0
** Description:            SPI接口定义
**
**--------------------------------------------------------------------------------------------------------
** Created By:             Xie JieZhang
** Created date:           2014-08-27
** Version:                V1.0
** Description:            SPI，初始化，接口定义
**
**--------------------------------------------------------------------------------------------------------
** Modified By:            
** Modified date:          
** Version:                
** Description:            
**
*********************************************************************************************************/
#include <pic.h>
#include "pic_spi.h"
/*********************************************************************************************************
** Function name:      spiInit
** Descriptions:       SPI初始化，配置I2C波特率
** input parameters:   无
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void spiInit (void)
{
    /*
    *  SPI 引脚配置
    */
    
    TRISC |= 0x01<<MISO_BIT;                                            /* RC4: SDI           配置为输入*/
    TRISC &= ~( (0x01<<SCLK_BIT)|(0x01<<MOSI_BIT) );                    /* RC5: SDO  RC3:SCKL 配置为输出*/
    TRISC |= 0x01<<IRQ_BIT;                                             /* RC6: IRQ           配置为输入*/
    TRISC &= ~(0x01<<CSN_BIT);                                          /* RC7: CSn           配置为输出*/
    TRISA &= ~(0x01<<CE_BIT);                                           /* RA5: CE            配置为输出*/
    ADCON1 = 0x06;                                                      /* RA端口配置成数字I/O口        */

    CE_SET;                                                             /* 使能芯片                     */                                                    
    CSN_SET;                                                            /* SPI不是能                    */
    SCLK_CLR;                                                           /* 时钟信号初始化成高电平       */
//    /*
//    *  SPI通信配置
//    */
//    WCOL = 0;                                                           /* 冲突标志清零                 */
//    SSPEN = 1;                                                          /* 使用SPI模式                  */
//    CKP   = 1;                                                          /* 高电平空闲                   */
//    SSPCON &= ~(0x0f);                                                  /* SPI时钟频率为Fosc/4 = 2 MHz  */
//    SMP  = 1;                                                           /* 输入数据在数据输出的时钟后沿 */
 
}
/*********************************************************************************************************
** Function name:      spiUsDelay
** Descriptions:       SPI延时函数
** input parameters:   n: 延时周期数
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void spiUsDelay (uchar n)
{
	for (;n>0;n--) {
        NOP();    
    }
}

/*********************************************************************************************************
** Function name:      spiMOSI
** Descriptions:       SPI向数据输出线写入数据
** input parameters:   无
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
void spiMOSI (uchar ucBit)
{
    if (ucBit == 0) {
        PORTC &= ~(0x01 << MOSI_BIT);
    }
    else {
        PORTC |=  (0x01 << MOSI_BIT);
    }
}
/*********************************************************************************************************
** Function name:      spiMISO
** Descriptions:       SPI向数据输入线读取数据
** input parameters:   无
** output parameters:  无
** Returned value:     无
*********************************************************************************************************/
uchar spiMISO (void)
{
    if ((PORTC & (0x01 << MISO_BIT)) == 0) {
        return 0;
    }
    else {
        return 1;
    }     
}
/*********************************************************************************************************
** Function name:      spiByteRW
** Descriptions:       SPI字节通信，同时写入和读出一个字节
** input parameters:   ucByte：写入的字节
** output parameters:  无
** Returned value:     返回读出到的一个字节
*********************************************************************************************************/
uchar spiByteRW (uchar ucByte)
{
    uchar ucBit;
    
    for (ucBit = 0; ucBit < 8; ucBit++) {
        spiMOSI(ucByte & 0x80);                                         /* 写入数据                     */  
        ucByte <<= 1;
        SCLK_SET;
        ucByte |= spiMISO();                                            /* 读出数据                     */
        //dat <<= 1;
        SCLK_CLR;
    }
    return  ucByte;
}
/*********************************************************************************************************
** Function name:      spiRegRW
** Descriptions:       SPI读取寄存器并写入
** input parameters:   ucReg: 寄存器地址
**                     ucVal: 写入的值
** output parameters:  无
** Returned value:     写入时的状态
*********************************************************************************************************/
uchar spiRegRW (uchar ucReg, uchar ucVal)
{
    uchar ucStatus;
    
    CSN_CLR;
    ucStatus = spiByteRW(ucReg);
    spiByteRW(ucVal);
    CSN_SET;
    
    return ucStatus;
}
/*********************************************************************************************************
** Function name:      spiRegRead
** Descriptions:       SPI读取寄存器值
** input parameters:   ucReg: 寄存器地址
** output parameters:  无
** Returned value:     返回寄存器的值
*********************************************************************************************************/
uchar spiRegRead (uchar ucReg)
{
    uchar ucRes;

    CSN_CLR;
    ucRes = spiByteRW(ucReg);
    CSN_SET;
    
    return ucRes;
}
/*********************************************************************************************************
** Function name:      spiBufRead
** Descriptions:       SPI读取缓冲区的值
** input parameters:   ucReg: 缓冲区地址
**                     pucBuf: 存放首地址
**                     ucN:    读取的字节数
** output parameters:  无
** Returned value:     读取时的状态
*********************************************************************************************************/
uchar spiBufRead(uchar ucReg, uchar *pucBuf, uchar ucN)
{
    uchar ucStatus, n;
    CSN_CLR;
    ucStatus = spiByteRW(ucReg);
    
    for (n=0; n < ucN; n++) {
        pucBuf[n] = spiByteRW(0);
    }
    CSN_SET;

    return ucStatus;
}

/*********************************************************************************************************
** Function name:      spiBufWrite
** Descriptions:       SPI读取缓冲区的值
** input parameters:   ucReg: 缓冲区地址
**                     pucBuf: 存放首地址
**                     ucN:    读取的字节数
** output parameters:  无
** Returned value:     写入时的状态
*********************************************************************************************************/
uchar spiBufWrite(uchar ucReg, uchar *pucBuf, uchar ucN)
{
    uchar ucStatus, n;
    CSN_CLR;
    ucStatus = spiByteRW(ucReg);
    
    for (n=0; n < ucN; n++) {
        spiByteRW(*pucBuf);
        pucBuf++;
    }
    CSN_SET;

    return ucStatus;
}

/*********************************************************************************************************
   End File
*********************************************************************************************************/
