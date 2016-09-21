/*******************************************Copyright(c)**************************************************
**                        Guangzhou ZHIYUAN electronics Co.,LTD
**
**                           http://www.embedtools.com
**
**---------------File Info--------------------------------------------------------------------------------
** File Name:              pic_spi.c
** Lastest modified Date:  2014-08-27
** Latest Version:         V1.0
** Description:            SPI�ӿڶ���
**
**--------------------------------------------------------------------------------------------------------
** Created By:             Xie JieZhang
** Created date:           2014-08-27
** Version:                V1.0
** Description:            SPI����ʼ�����ӿڶ���
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
** Descriptions:       SPI��ʼ��������I2C������
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
*********************************************************************************************************/
void spiInit (void)
{
    /*
    *  SPI ��������
    */
    
    TRISC |= 0x01<<MISO_BIT;                                            /* RC4: SDI           ����Ϊ����*/
    TRISC &= ~( (0x01<<SCLK_BIT)|(0x01<<MOSI_BIT) );                    /* RC5: SDO  RC3:SCKL ����Ϊ���*/
    TRISC |= 0x01<<IRQ_BIT;                                             /* RC6: IRQ           ����Ϊ����*/
    TRISC &= ~(0x01<<CSN_BIT);                                          /* RC7: CSn           ����Ϊ���*/
    TRISA &= ~(0x01<<CE_BIT);                                           /* RA5: CE            ����Ϊ���*/
    ADCON1 = 0x06;                                                      /* RA�˿����ó�����I/O��        */

    CE_SET;                                                             /* ʹ��оƬ                     */                                                    
    CSN_SET;                                                            /* SPI������                    */
    SCLK_CLR;                                                           /* ʱ���źų�ʼ���ɸߵ�ƽ       */
//    /*
//    *  SPIͨ������
//    */
//    WCOL = 0;                                                           /* ��ͻ��־����                 */
//    SSPEN = 1;                                                          /* ʹ��SPIģʽ                  */
//    CKP   = 1;                                                          /* �ߵ�ƽ����                   */
//    SSPCON &= ~(0x0f);                                                  /* SPIʱ��Ƶ��ΪFosc/4 = 2 MHz  */
//    SMP  = 1;                                                           /* �������������������ʱ�Ӻ��� */
 
}
/*********************************************************************************************************
** Function name:      spiUsDelay
** Descriptions:       SPI��ʱ����
** input parameters:   n: ��ʱ������
** output parameters:  ��
** Returned value:     ��
*********************************************************************************************************/
void spiUsDelay (uchar n)
{
	for (;n>0;n--) {
        NOP();    
    }
}

/*********************************************************************************************************
** Function name:      spiMOSI
** Descriptions:       SPI�����������д������
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
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
** Descriptions:       SPI�����������߶�ȡ����
** input parameters:   ��
** output parameters:  ��
** Returned value:     ��
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
** Descriptions:       SPI�ֽ�ͨ�ţ�ͬʱд��Ͷ���һ���ֽ�
** input parameters:   ucByte��д����ֽ�
** output parameters:  ��
** Returned value:     ���ض�������һ���ֽ�
*********************************************************************************************************/
uchar spiByteRW (uchar ucByte)
{
    uchar ucBit;
    
    for (ucBit = 0; ucBit < 8; ucBit++) {
        spiMOSI(ucByte & 0x80);                                         /* д������                     */  
        ucByte <<= 1;
        SCLK_SET;
        ucByte |= spiMISO();                                            /* ��������                     */
        //dat <<= 1;
        SCLK_CLR;
    }
    return  ucByte;
}
/*********************************************************************************************************
** Function name:      spiRegRW
** Descriptions:       SPI��ȡ�Ĵ�����д��
** input parameters:   ucReg: �Ĵ�����ַ
**                     ucVal: д���ֵ
** output parameters:  ��
** Returned value:     д��ʱ��״̬
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
** Descriptions:       SPI��ȡ�Ĵ���ֵ
** input parameters:   ucReg: �Ĵ�����ַ
** output parameters:  ��
** Returned value:     ���ؼĴ�����ֵ
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
** Descriptions:       SPI��ȡ��������ֵ
** input parameters:   ucReg: ��������ַ
**                     pucBuf: ����׵�ַ
**                     ucN:    ��ȡ���ֽ���
** output parameters:  ��
** Returned value:     ��ȡʱ��״̬
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
** Descriptions:       SPI��ȡ��������ֵ
** input parameters:   ucReg: ��������ַ
**                     pucBuf: ����׵�ַ
**                     ucN:    ��ȡ���ֽ���
** output parameters:  ��
** Returned value:     д��ʱ��״̬
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
