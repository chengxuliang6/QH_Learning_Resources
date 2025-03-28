/*          
//数字锁相环（MB1504）驱动程序  
//针对晶体 采用 12M 步进采用 10 KHz 的驱动程序  
//        12M / 10K = 1200 = 0x04b0  
//        Refer counter          = ( 0x04b0 << 1 ) | 0x8001          SW = 32  
//        Refer counter          = ( 0x0960 ) | 0x8001  
// Refer counter          = 0x8961 ;  
  
*/   
#include < reg52.h >   
#include < intrins.h >   
   
sbit CLK  = P1^0;        //// 9 脚   
sbit DATA = P1^1;        //// 10脚   
sbit LE   = P1^2;        //// 11脚   
   
void Send16Bit( unsigned int SendData )   
{   
  unsigned char i;   
  unsigned int SendMiddle;    
   
  SendMiddle = SendData;   
   LE = 0;         
   CLK = 0;   
  for( i = 0; i < 16; i ++ )   
          {   
                DATA = ( SendMiddle & 0x8000 );   
                _nop_( );        CLK = 1;   
                _nop_( );        CLK = 0;   
                SendMiddle = SendMiddle << 1;   
          }   
  LE = 1;          _nop_( );          LE = 0;   
}   
   
void Send11Bit( unsigned int SendData )   
{   
  unsigned char i;   
  unsigned int  SendMiddle;   
     
  SendMiddle = SendData;   
  LE = 0;        CLK = 0;   
  for( i = 0; i < 11; i ++ )   
          {   
         DATA = ( SendData & 0x8000 );   
         _nop_( );        CLK = 1;   
         _nop_( );        CLK = 0;   
         SendData = SendData << 1;   
        }   
}   
   
void Send8Bit( unsigned char SendData )   
{   
  unsigned char i;   
  unsigned char SendMiddle;   
   
  SendMiddle = SendData;   
  for( i = 0; i < 8; i ++ )   
          {   
         DATA = ( SendData & 0x80 );   
         _nop_( );        CLK = 1;   
         _nop_( );        CLK = 0;   
         SendData = SendData << 1;   
        }   
  LE = 1;        _nop_( );        LE = 0;   
}   
   
void SendReferF( void )   
{ //针对晶体 采用 12M    
  Send16Bit( 0x8961 ); // 12M Crystal   
}   
   
void FrequenceToSend( unsigned int FrequenceD )   
{   
  unsigned char AD = 0,        i  = 0;   
  unsigned int  ND = 0,          
   
          MiddleF = FrequenceD;   
          ND = ( unsigned int  ) ( MiddleF / 128 );   
          AD = ( unsigned char ) ( MiddleF % 128 );   
          ND = ND <<7;                AD = AD << 1;        AD = AD & 0xfe;//////////   
          Send11Bit( ND );        Send8Bit( AD );   
 //  }   
}   
   
void main( void )   
{   
SendReferF( );           ////MB1504   送基准数 // 初始化   
FrequenceToSend( 4000 );  ////MB1504        送30 M    
while( 1 )   
        {   
        }   
}  