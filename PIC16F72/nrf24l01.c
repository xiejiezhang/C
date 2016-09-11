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

    usDelay(20);//让系统什么都不干
	CE_CLR;     //待机模式1   
	CSN_SET;    //片选无效 
	SCLK_SET;
    
    //spiRegRW(WRITE_REG+CONFIG, 0x0e);      // CRC使能，16位CRC校验，上电 
   
	//sta=spiRegRead(READ_REG+CONFIG);//发送数据后读取状态寄存器
	//if (sta != 0x0e) {
    //    ret  = 1;
    //}
    return ret;
    
}

/*****************NRF设置为发送模式并发送数据******************************/
void nrfSetTxMode(uchar *TxDate)
{//发送模式
    CE_CLR; 
   	spiBufWrite(WRITE_REG+TX_ADDR,TxAddr,TX_ADDR_WIDTH);//写寄存器指令+接收地址使能指令+接收地址+地址宽度
	spiBufWrite(WRITE_REG+RX_ADDR_P0,TxAddr,TX_ADDR_WIDTH);//为了应答接收设备，接收通道0地址和发送地址相同
	spiBufWrite(TX_PLOAD_WIDTH,TxDate,TX_PLOAD_WIDTH);//写入数据 
	/******下面有关寄存器配置**************/
  	spiRegRW(WRITE_REG+EN_AA,0x01);       // 使能接收通道0自动应答
  	spiRegRW(WRITE_REG+EN_RXADDR,0x01);   // 使能接收通道0
  	spiRegRW(WRITE_REG+SETUP_RETR,0x0a);  // 自动重发延时等待250us+86us，自动重发10次
  	spiRegRW(WRITE_REG+RF_CH,0x40);       // 选择射频通道0x40
  	spiRegRW(WRITE_REG+RF_SETUP,0x07);    // 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益
	spiRegRW(WRITE_REG+CONFIG,0x0e);      // CRC使能，16位CRC校验，上电  
	CE_SET;
	usDelay(10);//保持10us秒以上
}

/*****************NRF设置为接收模式并接收数据******************************/
//主要接收模式
void nrfRxModeSet()
{
    CE_CLR;   
  	spiBufWrite(WRITE_REG+RX_ADDR_P0,TxAddr,TX_ADDR_WIDTH);  // 接收设备接收通道0使用和发送设备相同的发送地址
  	spiRegRW(WRITE_REG+EN_AA,0x01);               // 使能接收通道0自动应答
  	spiRegRW(WRITE_REG+EN_RXADDR,0x01);           // 使能接收通道0
  	spiRegRW(WRITE_REG+RF_CH,0x40);                 // 选择射频通道0x40
  	spiRegRW(WRITE_REG+RX_PW_P0,TX_PLOAD_WIDTH);  // 接收通道0选择和发送通道相同有效数据宽度
  	spiRegRW(WRITE_REG+RF_SETUP,0x07);            // 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益*/
  	spiRegRW(WRITE_REG+CONFIG,0x0f);              // CRC使能，16位CRC校验，上电，接收模式
  	CE_SET;
	usDelay(10);//保持10us秒以上     
}

/****************************检测应答信号******************************/
uchar checkACK()
{  //用于发射
	uchar sta = spiRegRead(READ_REG+STATUS);   // 返回状态寄存器
	if((sta & (1 << 4)) || (sta & (1 << 5)))   //发送完毕中断
	{
	   spiRegRW(WRITE_REG+STATUS,0xff);    // 清除TX_DS或MAX_RT中断标志
	   CSN_CLR;
	   spiByteRW(FLUSH_TX);//用于清空FIFO ！！关键！！不然会出现意想不到的后果！！！大家记住！！  
       CSN_SET; 
	   return(0);
	}
	else
	   return(1);
}


/******************判断是否接收收到数据，接到就从RX取出*********************/
//用于接收模式
uchar nrfPacketRx(uchar *RevDate)
{
	 uchar sta;
   	 uchar RevFlags=0;
	 sta=spiRegRead(READ_REG+STATUS);//发送数据后读取状态寄存器
     if(sta & (1 << 6))			    // 判断是否接收到数据
	 {
	    CE_CLR; 			//SPI使能
		spiBufRead(RD_RX_PLOAD,RevDate,RX_PLOAD_WIDTH);// 从RXFIFO读取数据
		RevFlags=1;	   //读取数据完成标志
	  }
	  spiRegRW(WRITE_REG+STATUS,0xff); //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标
	 return(RevFlags);
}

