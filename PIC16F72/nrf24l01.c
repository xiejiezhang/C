#include "pic.h"
#include "pic_spi.h"
#include "nrf24l01.h"


static uchar const TxAddr[TX_ADDR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};//TX address
static uchar const RxAddr[RX_ADDR_WIDTH] = {0};//;RX address

extern void usDelay(uint x);

uchar nrfInit(void)
{
	uchar sta = 0;
    uchar ret = 0;

    usDelay(20);//��ϵͳʲô������
	CE_CLR;     //����ģʽ1   
	CSN_SET;    //Ƭѡ��Ч 
	SCLK_SET;
    
    //spiRegRW(WRITE_REG+CONFIG, 0x0e);      // CRCʹ�ܣ�16λCRCУ�飬�ϵ� 
   
	//sta=spiRegRead(READ_REG+CONFIG);//�������ݺ��ȡ״̬�Ĵ���
	//if (sta != 0x0e) {
    //    ret  = 1;
    //}
    return ret;
    
}

/*****************NRF����Ϊ����ģʽ����������******************************/
void nrfSetTxMode(uchar *TxDate)
{//����ģʽ
    CE_CLR; 
   	spiBufWrite(WRITE_REG+TX_ADDR,TxAddr,TX_ADDR_WIDTH);//д�Ĵ���ָ��+���յ�ַʹ��ָ��+���յ�ַ+��ַ���
	spiBufWrite(WRITE_REG+RX_ADDR_P0,TxAddr,TX_ADDR_WIDTH);//Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ
	spiBufWrite(TX_PLOAD_WIDTH,TxDate,TX_PLOAD_WIDTH);//д������ 
	/******�����йؼĴ�������**************/
  	spiRegRW(WRITE_REG+EN_AA,0x01);       // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	spiRegRW(WRITE_REG+EN_RXADDR,0x01);   // ʹ�ܽ���ͨ��0
  	spiRegRW(WRITE_REG+SETUP_RETR,0x0a);  // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
  	spiRegRW(WRITE_REG+RF_CH,0x40);       // ѡ����Ƶͨ��0x40
  	spiRegRW(WRITE_REG+RF_SETUP,0x07);    // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
	spiRegRW(WRITE_REG+CONFIG,0x0e);      // CRCʹ�ܣ�16λCRCУ�飬�ϵ�  
	CE_SET;
	usDelay(10);//����10us������
}

/*****************NRF����Ϊ����ģʽ����������******************************/
//��Ҫ����ģʽ
void nrfRxModeSet()
{
    CE_CLR;   
  	spiBufWrite(WRITE_REG+RX_ADDR_P0,TxAddr,TX_ADDR_WIDTH);  // �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ
  	spiRegRW(WRITE_REG+EN_AA,0x01);               // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	spiRegRW(WRITE_REG+EN_RXADDR,0x01);           // ʹ�ܽ���ͨ��0
  	spiRegRW(WRITE_REG+RF_CH,0x40);                 // ѡ����Ƶͨ��0x40
  	spiRegRW(WRITE_REG+RX_PW_P0,TX_PLOAD_WIDTH);  // ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
  	spiRegRW(WRITE_REG+RF_SETUP,0x07);            // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������*/
  	spiRegRW(WRITE_REG+CONFIG,0x0f);              // CRCʹ�ܣ�16λCRCУ�飬�ϵ磬����ģʽ
  	CE_SET;
	usDelay(10);//����10us������     
}

/****************************���Ӧ���ź�******************************/
uchar checkACK()
{  //���ڷ���
	uchar sta = spiRegRead(READ_REG+STATUS);   // ����״̬�Ĵ���
	if((sta & (1 << 4)) || (sta & (1 << 5)))   //��������ж�
	{
	   spiRegRW(WRITE_REG+STATUS,0xff);    // ���TX_DS��MAX_RT�жϱ�־
	   CSN_CLR;
	   spiByteRW(FLUSH_TX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס����  
       CSN_SET; 
	   return(0);
	}
	else
	   return(1);
}


/******************�ж��Ƿ�����յ����ݣ��ӵ��ʹ�RXȡ��*********************/
//���ڽ���ģʽ
uchar nrfPacketRx(uchar *RevDate)
{
	 uchar sta;
   	 uchar RevFlags=0;
	 sta=spiRegRead(READ_REG+STATUS);//�������ݺ��ȡ״̬�Ĵ���
     if(sta & (1 << 6))			    // �ж��Ƿ���յ�����
	 {
	    CE_CLR; 			//SPIʹ��
		spiBufRead(RD_RX_PLOAD,RevDate,RX_PLOAD_WIDTH);// ��RXFIFO��ȡ����
		RevFlags=1;	   //��ȡ������ɱ�־
	  }
	  spiRegRW(WRITE_REG+STATUS,0xff); //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�
	 return(RevFlags);
}

