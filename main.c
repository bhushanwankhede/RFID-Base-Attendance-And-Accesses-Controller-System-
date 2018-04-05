/*
 * File:   newmain.c
 * Author: Bhushan
 *
 * Created on 19 February, 2018, 2:29 AM
 */

#include <xc.h>
#include<stdio.h>
#include"header.h"

#define LCDDATA PORTD
#define RS PORTCbits.RC4
#define EN PORTCbits.RC5

//L293D

#define INPUT_A1  RA0
#define INPUT_A2  RA1
#define ENABLE_1  RA2
#define INPUT_B1  RA3
#define INPUT_B2  RA4
#define ENABLE_2  RA5
/*#define C_1 RB7
#define C_2 RB6
#define C_3 RB5
#define C_4 RB4

#define  R_4 RB3
#define  R_3 RB2
#define  R_2 RB1
#define  R_1 RB0*/
/*********************************************************************************************************
 *
 *
 *
*************************************************************************************************************/
// keypad input
#define c1 PORTBbits.RB3
#define c2 PORTBbits.RB2
#define c3 PORTBbits.RB1
#define c4 PORTBbits.RB0
#define r1 PORTBbits.RB7
#define r2 PORTBbits.RB6
#define r3 PORTBbits.RB5
#define r4 PORTBbits.RB4

/*****************************************************************************************************************/
void INIT_LCD(void);
void LCDClear(void);
void LCD_Write(unsigned char *a);
void LCDCmdInit( unsigned char cmd );
unsigned char LCDCmdDataWrite(unsigned char data);
/*****************************************************************************************************************/
unsigned char UART_Write(unsigned char *text);
void INIT_TIMER(unsigned char timer_name , volatile unsigned char timer_value );
unsigned char  READKEY();
void CHECK_KEY_STATUS(unsigned char STATUS);
/***************************************************************************************************************/
void DOOR_CLOSE();
void DOOR_OPEN();
void  interrupt InterruptHandlerHigh(void);
/**************************************************************************************************************/
void STRCAT(unsigned char * destination , unsigned char * source);
void CLEAR(unsigned char *array );
void delay(int a);
/****************************************************************************************************************/
void UARTGsmWrite(const unsigned char *text);
void ID_CHECK(unsigned int l);
unsigned char keypad(void);
unsigned int CheckInPass();
/*******************************************************************************************************************/
void INIT_GSM();
void enter();
void sendSms(/*unsigned char * msgnum_arr, const unsigned char *msg*/);
/*********************************************************************************************************************/
unsigned char 	RX_DATA[13]	=	'\0';
unsigned char 	FLAG		=	   0;
unsigned char 	STATUS_FLAG	=	 '0';
const unsigned char status_one[]	={"CHECK IN"};
const unsigned char status_two[]	={"CHECK OUT"};
//const unsigned char status_three[]	={"UNKNOWN IN"};
//const unsigned char status_four[]	={"UNKNOWN OUT"};
unsigned char 	InPassword[6]	=	'\0';
unsigned int	 PassCout 	=	    0;
unsigned int 	Not		=	     1;
unsigned int 	Match		=	     0;
const unsigned char PassDataBase[4][5]={"9542","1286","9174","2357"};
const unsigned char PassTwo[5]={""};
const unsigned char PassThree[5]={""};
const unsigned char PassFour[5]={""};
unsigned char MGS[100]=" ";
unsigned int C1=0 , C2=0,C3=0,C4=0;
unsigned int R1 = 0,R2=0,R3=0,R4=0;
unsigned int KeyIsPressFlag=0;
unsigned char _STATUS_[20]=" ";
int len=0;
unsigned int GetPass=0;
unsigned char LOCK=0 , CARD_DETECT=0; 
unsigned char keyflag;
/***************************************************************************************************************************/
#pragma code InterruptVectorHigh = 0x08  // for define interrunt location 
void dInterruptVectorHigh (void)
{
  #asm;
    goto InterruptHandlerHigh ;             //jump to interrupt routine
  #endasm;
}
/*void interrupt ISR_KEY()
{
   if(RBIF)
    {
      RBIF=0;
       STATUS_FLAG=READKEY();
    } 
}*/


void interrupt InterruptHandlerHigh(void)
{
	unsigned char recv_data;
	if (INTCONbits.TMR0IF)
	{ 
		INTCONbits.TMR0IF = 0;
    		TMR0H	 = 0x0B;
    		TMR0L	 = 0xDC;
   	 c1=0;c2=1;c3=1;c4=1;delay(1);
	if(r1==0){ Not=0;C1=1;R1 = 1 ;KeyIsPressFlag=1;/*while(r1==0);LCD_Write("1"); delay(10);return '1';*/}
	if(r2==0){ Not=0;C1=1;R2 = 1 ;KeyIsPressFlag=1;/*while(r2==0);	LCD_Write("4");delay(10);return '4';*/}
	if(r3==0){ Not=0;C1=1;R3 = 1 ;KeyIsPressFlag=1;/*while(r3==0);LCD_Write("7");delay(10);return '7';*/}
	if(r4==0){ Not=0;C1=1;R4 = 1 ;KeyIsPressFlag=1;/*while(r4==0);LCD_Write("*");delay(10);return '*';*/}
	
	c1=1;c2=0;c3=1;c4=1;delay(1);
	if(r1==0){ Not=0;C2=1;R1 = 1 ;KeyIsPressFlag=1;/*while(r1==0);LCD_Write("2");delay(10);return '2';*/}
	if(r2==0){ Not=0;C2=1;R2 = 1 ;KeyIsPressFlag=1;/*while(r2==0);LCD_Write("5");delay(10);return '5';*/}
	if(r3==0){ Not=0;C2=1;R3 = 1 ;KeyIsPressFlag=1;/*while(r3==0);LCD_Write("8");delay(10);return '8';*/}
	if(r4==0){ Not=0;C2=1;R4 = 1 ;KeyIsPressFlag=1;/*while(r4==0);LCD_Write("0");delay(10);return '0';*/}
	
	c1=1;c2=1;c3=0;c4=1;delay(1);
	if(r1==0){ Not=0;C3=1;R1 = 1 ;KeyIsPressFlag=1;/*while(r1==0);LCD_Write("3");delay(10);return '3';*/}
	if(r2==0){ Not=0;C3=1;R2 = 1 ;KeyIsPressFlag=1;/*while(r2==0);LCD_Write("6");delay(10);return '6';*/}
	if(r3==0){ Not=0;C3=1;R3 = 1 ;KeyIsPressFlag=1;/*while(r3==0);LCD_Write("9");delay(10);return '9';*/}
	if(r4==0){ Not=0;C3=1;R4 = 1 ;KeyIsPressFlag=1;/*while(r4==0);LCD_Write("#");delay(10);return '#';*/}
    
   	 c1=1;c2=1;c3=1;c4=0;delay(1);
	if(r1==0){ Not=0;C4=1;R1 = 1 ;KeyIsPressFlag=1;/*while(r1==0);LCD_Write("IN");delay(10);return '3';*/}
	if(r2==0){ Not=0;C4=1;R2 = 1 ;KeyIsPressFlag=1;/*while(r2==0);LCD_Write("OUT");delay(10);return '6';*/}
	if(r3==0){ Not=0;C4=1;R3 = 1 ;KeyIsPressFlag=1;/*while(r3==0);LCD_Write("C");delay(10);return '9';*/}
	if(r4==0){ Not=0;C4=1;R4 = 1 ;KeyIsPressFlag=1;/*while(r4==0);LCD_Write("D");delay(10);return '#';*/}
  	}   
   
  /** if(RBIF)
    {
      LCD_Write("IOC");
      
     STATUS_FLAG=READKEY();
     RBIF=0;
    } */
	if(PIR1bits.RCIF)  				  //serial interrupt // do we have uart rx interrupt request?
	{  
		PIR1bits.RCIF=0;
        recv_data= RCREG;
       
        if(recv_data)
        {
            RX_DATA[FLAG]=recv_data;
            FLAG+=1;
            len+=1;
            if(len == 12 ){CARD_DETECT=1;
             //UART_Write("_0_");
            }
            
        }
  }
        if(FLAG >= 12){FLAG=0;}
        
	}

/*************************************************************************************************************************/
void INIT_PORT()
{
    // oscilator controlle registor bit [OSCCON ] 
	  OSCCONbits.IRCF0=1;
	  OSCCONbits.IRCF1=1;      //8 mhz
	  OSCCONbits.IRCF2=1;
	  OSCCONbits.SCS1=1;      // internal osc
	  OSCCONbits.SCS0=0;
    ADCON1=0x0F;            // all DIGITAL 
    TRISA=0x00;             // as input 
    TRISC=0x80;             // 10000000 RC7 as input and anther as output
    TRISCbits.TRISC7=1;
    PORTC=0X00;             // clear portc 
    TRISE=0X05;             // 00000101 RE0, as input and  and anther as output 
    PORTE=0X00;               // clear porte
    TRISD=0X00;              // portd as output for lcd data line 
    PORTD=0X00;              // clear portd 
    TRISB=0XF0;             // 1111000 as input and anther as output
    TRISB=0b11110000;
    PORTB=0X00;             // clear portb
    //LATB=0x0F;        // Initial value for keypad port
  //  RBPU = 1;         // Enable Weak internal pull-ups in pin RB4 and RB5
    
}
/*****************************************************************************************************************************/
unsigned char Ready_to_Send(unsigned char Tx)
{
    while(!TRMT);
    TXREG =Tx ;delay(3);
}
/******************************************************************************************************************************/
void INIT_UART(long int Baudrate )
{
    unsigned int x=0;
    x = (_XTAL_FREQ/Baudrate)/16 - 1 ;
    SPBRG=x;             //  set value on the SPBRG  
    TXSTA=0b00100100;     //{ TXSTAbits.TXEN=1 : transmit enable , TXSTAbits.SYNC=0 : Asynchronous mode
                         //  TXSTAbits.BRGH=1; :  high speed transmission  } 
    RCSTA=0b10010000;   // Serial Port Enable  ,Continuous Receive Enable 
    //BAUDCON=0x00;
 }
/************************************************************************************************************************************/
void INIT_INTR(void)
{  
    //RCON=0x80; 
    RCONbits.IPEN=1;    // enable priority interrupt
    //RBIE = 1;        // Enable PORT B interrupt
    //RBIF = 0;  
    INTCON=0b11100000;  // GOLOBLE AND PERIPHERIAL ENABLE 
    INTCON2=0b00000101; //  All PORTB pull-ups are disabled 
    //INTCONbits.RBIE = 1; // Enable PORT B interrupt
    //INTCONbits.RBIF = 0;  //RB Port Change Interrupt Priority bit is high priorty 
    INTCON3=0x00;       // Disables all external interrupt 
    PIR1=0x00;        //  PERIPHERAL INTERRUPT REQUEST (FLAG) REGISTER 1
    PIR2=0x00;      // PERIPHERAL INTERRUPT REQUEST (FLAG) REGISTER 2
    PIE1 =0x20;  //PERIPHERAL INTERRUPT ENABLE REGISTER 1
    PIE1bits.RCIE=1;
    PIE2 =0x00;     // PERIPHERAL INTERRUPT ENABLE REGISTER 2 
    IPR1=0x20;  
    IPR1bits.RCIP=1;//PERIPHERAL INTERRUPT PRIORITY REGISTER 1
    //IPR2 =0x00;      // PERIPHERAL INTERRUPT PRIORITY REGISTER 2
}
/***********************************************************************************************************************************/
void PUT_DATA()
{
      LCDClear(); 
   //   LCD_Write("WEL-COME");
      //LCDCmdInit(0XC0);
      /*LCD_Write("     HOSTEL     ");
      delay(100);
      LCDClear();
      LCD_Write("A  -> CHECK IN");
      LCDCmdInit(0XC0);
      LCD_Write("B  -> CHECK OUT");
      delay(100);
      LCDClear();
      LCD_Write("C  -> UNKNOWN ");
      LCDCmdInit(0XC0);
      LCD_Write("   CHECK IN");
      delay(100);
      LCDClear();
      LCD_Write("D  -> UNKNOWN ");
      LCDCmdInit(0XC0);
      LCD_Write("    CHECK OUT");
      delay(100);*/
      LCDClear();
      LCD_Write("FIRST PRESS KEY....");
      LCDCmdInit(0XC0);
      LCD_Write("THAN SHOW CARD.....");
      delay(100);
      LCDClear();
      LCD_Write("   PRESS KEY........");
}
/*****************************************************************************************************************************/
void delay(int a){for(int i=0;i<a;i++){__delay_ms(10);} }
/******************************************************************************************************************************/
void main(void) 
 {
    /*unsigned char flag=1;
    unsigned int Key=1,CheckFlag=0;
    PassCout=0;
    CLEAR(MGS);
    CLEAR(_STATUS_);
    CLEAR(RX_DATA);*/
    INIT_PORT();
    //INIT_LCD();
   // INIT_INTR();
   // INIT_TIMER(0,0x82);
    INIT_UART(9600);
   /* LCDClear();
    LCD_Write("-> GIRL SECURITY");
    LCDCmdInit(0XC0);
    LCD_Write("-> SYSTEM......");
    delay(100);
    LCDClear();*/
     while(1)
     {
        if(Not){LCDCmdInit(0X80); LCD_Write("A : IN | B : OUT");}
       delay(10);
       if(KeyIsPressFlag){if(Key){Key=0; LCDClear();}KeyIsPressFlag=0;CheckFlag=1;STATUS_FLAG=keypad();}
       PUT_DATA();
       delay(110);
       //STATUS_FLAG=READKEY(); 
       if(CheckFlag){CheckFlag=0;CHECK_KEY_STATUS(STATUS_FLAG);}
      //delay(100);
       if(GetPass){GetPass=0;LCDClear();while(!KeyIsPressFlag){LCDCmdInit(0X80);LCD_Write("-> Password.....");}delay(10);Key=1;}
       if(PassCout == 4)
      	{
        		PassCout=0;
        		Not=1;
        		LCDClear();
        		//LCD_Write(InPassword);
        		delay(10);
        		LCDClear();
        		Match=CheckInPass();
        		if(Match)
        			{
          				Match=0;
          				LCDClear();
          				LCD_Write("SHOW YOUR CARD....");
          				while(!CARD_DETECT);
          				CARD_DETECT=0;
          				LOCK=1;
          				LCDClear();
        			}
        			else
        			{
            				LCDClear();
            				LCD_Write("MATCH NOT FOUND......");
             				CLEAR(InPassword);
            				delay(100);
           				 LCDClear();
        			}
      	}
      if(len == 12 && LOCK)
            {   
	unsigned int l =len;
          	LOCK=0;
          CLEAR(MGS);
          len=0; 
         STRCAT(MGS , "  ID : ");
         STRCAT(MGS , RX_DATA);
          LCDClear();
          STRCAT(MGS , "  NAME : ");
          ID_CHECK(l);
          STRCAT(MGS ,"  STATUS : ");
          STRCAT(MGS, _STATUS_);      
          __delay_ms(50);
          DOOR_OPEN(); 
          delay(150);
          DOOR_CLOSE();
          delay(10);
          sendSms();
          CLEAR(MGS);
          CLEAR(InPassword);
          CLEAR(RX_DATA);
          CLEAR(_STATUS_);
          LCDClear();
      }
    }
 }
/*/************************************************************************************************************************/*/
void DOOR_CLOSE()
{
  ENABLE_1=1;
  INPUT_A1=1;
  delay(300);
  INPUT_A1=0;
  ENABLE_1=0;
}
/*******************************************************************************************************************/
void DOOR_OPEN()
{
  ENABLE_1=1;
  INPUT_A2=1;
  delay(300);
  INPUT_A2=0;
  ENABLE_1=0;
}
/******************************************************************************************************************/
unsigned char UART_Write(unsigned char *text)
{
    for(int i=0;text[i]!='\0';++i)
    {
        Ready_to_Send(text[i]);
    }
}
/***************************************************************************************************************/
void UARTGsmWrite(const unsigned char *text)
{
  for (int i = 0; text[i]!='\0'; ++i)
  {
    Ready_to_Send(text[i]);
  }
}

void LCDCmdInit( unsigned char cmd )
{
    LCDDATA=cmd;
    RS = 0;
    EN=1;
    __delay_ms(50);
    EN=0;
}

unsigned char LCDCmdDataWrite(unsigned char data)
{
    LCDDATA= data ;
    RS=1;
    EN=1;
    __delay_ms(20);
    EN=0;   
}

void LCD_Write(unsigned char *a)
{
	for(int i=0;a[i]!='\0';i++)
    {
        LCDCmdDataWrite(a[i]);
    }
}

void LCDClear(void)
{
    LCDCmdInit(0x01);
    LCDCmdInit( 0x80);        
}

void INIT_LCD(void)
{
    LCDCmdInit(0x38);
    __delay_ms(20);
    LCDCmdInit(0x0c);
    __delay_ms(20);
    LCDCmdInit(0x01);
    __delay_ms(20);
    LCDCmdInit(0x06);
    __delay_ms(20);
    LCDCmdInit(0x0E);
    __delay_ms(20);
    LCDCmdInit(0x80);
    __delay_ms(20);
}
/*
unsigned char  READKEY()
{
  if(R_1 == 0  && R_2 == 1 && R_3 == 1 && R_4 == 1)
 {
     LCDClear();
     LOCK=1;
     LCD_Write("SHOW YOUR CARD....");
     while(!CARD_DETECT);
     CARD_DETECT=0;
     delay(1);
     while(! R_1){LCDClear();LCD_Write("    CHECK IN    ");}
     for(int i =0 ;i<100;i++){__delay_ms(10);}
     LCDClear();
     keyflag='1';
     return(keyflag);
 }
 else if (R_1 == 1  && R_2 == 0 && R_3 == 1 && R_4 == 1)
 {
     LCDClear();
     LCD_Write("SHOW YOUR CARD....");
     while(!CARD_DETECT);
     CARD_DETECT=0;
     delay(1);
     while( !R_2){LCDClear();LCD_Write("    CHECK OUT   ");}
     for(int i =0 ;i<100;i++){__delay_ms(10);}
     LCDClear();
       LOCK=1;
      keyflag='2';
      return(keyflag);
 }
 else if(R_1 == 1  && R_2 == 1 && R_3 == 0 && R_4 == 1)
 {
     LCDClear();
     delay(1);
      LOCK=1;
     while(!R_3){ LCDClear();LCD_Write( "UNKNOWN CHECK IN");}
     for(int i =0 ;i<100;i++){__delay_ms(10);}
     LCDClear();
    len=12;
    keyflag='3';
    return(keyflag);
 }
 else if(R_1 == 1  && R_2 == 1 && R_3 == 1 && R_4 == 0)
 {
      LCDClear();
      delay(1);
      LOCK=1;
     while(!R_4){LCDClear(); LCD_Write( " UNKNOWN CHECK ");
      LCDCmdInit(0XC0);
      LCD_Write("      OUT       ");}
      for(int i =0 ;i<100;i++){__delay_ms(10);}
     LCDClear();
      len=12;
      keyflag='4';
      return(keyflag);
 }
    
}*/

void CHECK_KEY_STATUS(unsigned char STATUS)
{
    
  switch(STATUS)
  {

    case 'A' : GetPass=1;STRCAT(_STATUS_ ,status_one); break;
    case 'B'
    : GetPass=1;;STRCAT(_STATUS_ ,status_two); break;
    case '1' : InPassword[PassCout]='1';PassCout+=1;break; //STRCAT(_STATUS_,status_three); break;
    case '2' : InPassword[PassCout]='2';PassCout+=1;break; //STRCAT(_STATUS_,status_four); break;
    case '3' : InPassword[PassCout]='3';PassCout+=1;break;
    case '4' : InPassword[PassCout]='4';PassCout+=1;break;
    case '5' : InPassword[PassCout]='5';PassCout+=1;break;
    case '6' : InPassword[PassCout]='6';PassCout+=1;break;
    case '7' : InPassword[PassCout]='7';PassCout+=1;break;
    case '8' : InPassword[PassCout]='8';PassCout+=1;break;
    case '9' : InPassword[PassCout]='9';PassCout+=1;break;
    case '0' : InPassword[PassCout]='0';PassCout+=1;break;
    default :  break;
  }
}

void STRCAT(unsigned char * destination , unsigned char * source)
{
  int len=0;
  for(int j=0 ; destination[j] !='\0';j++){len+=1;}
  for (int i = 0; source[i]!='\0'; ++i)
  {
    destination[len]=source[i];
    len+=1;
  }
}

void CLEAR(unsigned char *array )
{
  for (int i = 0;array[i]!='\0'; ++i)
  {
    array[i]='\0';
  }
}

void ID_CHECK(unsigned int l)
{
  switch(RX_DATA[l-1])
          {

            case '6' : LCD_Write("name ");LCDCmdInit(0XC0);LCD_Write(_STATUS_); STRCAT(MGS ," name"); break;

            case '1' : LCD_Write("name");LCDCmdInit(0XC0);LCD_Write(_STATUS_); STRCAT(MGS ," name"); break;

            case 'E' : LCD_Write("name");LCDCmdInit(0XC0);LCD_Write(_STATUS_); STRCAT(MGS ," name"); break;

            case '7' : LCD_Write("name");LCDCmdInit(0XC0);LCD_Write(_STATUS_); STRCAT(MGS ," name"); break;

            default  :/* LCD_Write("UNKNOWN ID");LCDCmdInit(0XC0);LCD_Write(_STATUS_);STRCAT(MGS ," UNKNOWN ID");  */     break;
          }
}

void enter()
{
   delay(10);
   Ready_to_Send(0X0D);
   delay(1);
   Ready_to_Send(0X0A);
   delay(1);
}

void sendSms(/*unsigned char *msgnum_arr, const unsigned char *msg*/)
{
    unsigned char i=0,j=0;
    UARTGsmWrite((const unsigned char*)"AT");delay(100);enter();
    UARTGsmWrite((const unsigned char*)"AT+CMGF=1");delay(400);enter();
    UARTGsmWrite((const unsigned char*)"AT+CMGS=\"numaber/"");enter();
    delay(500);
    for(int i=0;MGS[i]!='\0';i++){Ready_to_Send(MGS[i]);delay(1);if(j==0xff) goto down;j++;}
//    for(int i=0;MGS[i]!='\0';i++){Ready_to_Send(MGS[i]);delay(1);if(j==0xff) goto down;j++;}
down:   enter();delay(100);
        Ready_to_Send(0x1a);
        delay(100);
}

unsigned char keypad(void)
{
//	c1=0;c2=1;c3=1;c4=1;delay(20);
	if(/*r1==0*/R1 && C1){R1=0;C1=0;/*while(r1==0);*/LCD_Write("*"); delay(10);return '1';}
	if(/*r2==0*/R2 && C1){R1=0;C1=0;/*while(r2==0);*/LCD_Write("*"); delay(10);return '4';}	
	if(/*r3==0*/R3 && C1){R1=0;C1=0;/*while(r3==0);*/LCD_Write("*"); delay(10);return '7';}
	if(/*r4==0*/R4 && C1){R1=0;C1=0;/*while(r4==0);*/	LCD_Write("*"); delay(10);return '*';}
	
	//c1=1;c2=0;c3=1;c4=1;delay(20);
	if(/*r1==0*/R1 && C2){R1=0;C2=0;/*while(r1==0);*/LCD_Write("*");delay(10);return '2';}
	if(/*r2==0*/R2 && C2){R2=0;C2=0;/*while(r2==0);*/LCD_Write("*");delay(10);return '5';}
	if(/*r3==0*/R3 && C2){R3=0;C2=0;/*while(r3==0);*/LCD_Write("*");delay(10);return '8';}
	if(/*r4==0*/R4 && C2){R4=0;C2=0;/*while(r4==0);*/LCD_Write("*");delay(10);return '0';}
	
	//c1=1;c2=1;c3=0;c4=1;delay(20);
	if(/*r1==0*/R1 && C3){R1=0;C3=0;/*while(r1==0);*/LCD_Write("*");delay(10);return '3';}
	if(/*r2==0*/R2 && C3){R2=0;C3=0;/*while(r2==0);*/LCD_Write("*");delay(10);return '6';}
	if(/*r3==0*/R3 && C3){R3=0;C3=0;/*while(r3==0);*/LCD_Write("*");delay(10);return '9';}
	if(/*r4==0*/R4 && C3){R4=0;C3=0;/*while(r4==0);*/LCD_Write("#");delay(10);return '#';}
    
   // c1=1;c2=1;c3=1;c4=0;delay(20);
	if(/*r1==0*/R1 && C4){R1=0;C4=0;/*while(r1==0);*/LCD_Write("IN");delay(10);return 'A';}
	if(/*r2==0*/R2 && C4){R2=0;C4=0;/*while(r2==0);*/LCD_Write("OUT");delay(10);return 'B';}
	if(/*r3==0*/R3 && C4){R3=0;C4=0;/*while(r3==0);*/LCD_Write("C");delay(10);return 'C';}
	if(/*r4==0*/R4 && C4){R4=0;C4=0;/*while(r4==0);*/LCD_Write("D");delay(10);return 'D';}
	return 0;
}

void INIT_TIMER(unsigned char timer_name , volatile unsigned char timer_value )
{
	switch(timer_name)
	{
		case 0:T0CON=timer_value;break;
		case 1:T1CON=timer_value;break;
		case 2:T2CON=timer_value;break;
		case 3:T1CONbits.T1OSCEN=1;T3CON=timer_value;break;
	}
}

unsigned int CheckInPass()
{
  int Count=0;
  for(unsigned int i=0; i<= 4 ; ++i)
  {
    for(unsigned int j=0;PassDataBase[i][j]!='\0'&& InPassword[j]!='\0';++j)
    {
      if(InPassword[j] == PassDataBase[i][j])
      {
          Count+=1;
         
      }
    }
     if(Count == 4)
        {
              return 1;
        }
     else
        {
             Count=0;
        }
    }
  return 0;
}