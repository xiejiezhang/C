/*******************************************Copyright(c)**************************************************
**                        Guangzhou ZHIYUAN electronics Co.,LTD
**
**                           http://www.embedtools.com
**
**---------------File Info--------------------------------------------------------------------------------
** File Name:              gpio.h
** Lastest modified Date:  2014-08-26
** Latest Version:         V1.0
** Description:            GPIO configure,GPIO function
**
**--------------------------------------------------------------------------------------------------------
** Created By:             Xie JieZhang
** Created date:           2014-08-26
** Version:                V1.0
** Description:            define based driver and configure of GPIO
**
**--------------------------------------------------------------------------------------------------------
** Modified By:            
** Modified date:          
** Version:                
** Description:            
**
*********************************************************************************************************/

#ifndef _GPIO_H
#define _GPIO_H

/*
*  GPIO �����������
*/
#define GPIO_CONF_IN(POT,BIT)   (TRIS##POT |= (0x01<<BIT))              /* GPIO��������                 */
#define GPIO_CONF_OUT(POT,BIT)  (TRIS##POT &= ~(0x01<<BIT))             /* GPIO�������                 */

#define GPIO_TOG(POT,BIT)       (PORT##POT ^= (0x01<<BIT))              /* GPIO����ȡ��                 */
#define GPIO_SET(POT,BIT)       (PORT##POT |= (0x01<<BIT))              /* GPIO������λ                 */
#define GPIO_CLR(POT,BIT)       (PORT##POT &= ~(0x01<<BIT))             /* GPIO��������                 */
#define GPIO_ON(POT,BIT)        (PORT##POT |= (0x01<<BIT))              /* GPIO������λ                 */
#define GPIO_OFF(POT,BIT)       (PORT##POT &= ~(0x01<<BIT))             /* GPIO��������                 */

void gpioInit (void);
void ledAllClose (void);
void ledAllOpen (void);
/*********************************************************************************************************
  ��ɫLED����
*********************************************************************************************************/
void ledBlueOpen (void);
void ledBlueClose (void);
void ledBlueToggle (void);
/*********************************************************************************************************
  ��ɫLED����
*********************************************************************************************************/
void ledRedOpen (void);
void ledRedClose (void);
void ledRedToggle (void);
/*********************************************************************************************************
  ��ɫLED����
*********************************************************************************************************/
void ledYellowOpen (void);
void ledYellowClose (void);
void ledYellowToggle (void);
#endif
/*********************************************************************************************************
   End File
*********************************************************************************************************/
