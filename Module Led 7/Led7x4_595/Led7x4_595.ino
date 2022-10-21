#define LED1        14
#define LED2        15
#define LED3        16
#define LED4        17

int MOSI__ = 5;
int RCK__  = 7;
int SCK__  = 6;


uint8_t data=0;

uint16_t LED7SEG[10]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void setup()
{
  pinMode(MOSI__,OUTPUT);
  pinMode(SCK__,OUTPUT);
  pinMode(RCK__,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
}
void myShiftOut(uint8_t data){
  for (int i = 0 ; i < 8; i++) {
    digitalWrite(MOSI__,!!(data & (1<<(7-i))));
    digitalWrite(SCK__,1);
    digitalWrite(SCK__,0);
  }
  export_data();
}

void export_data (){
  digitalWrite(RCK__,0);
  digitalWrite(RCK__,1);
//  digitalWrite(RCK__,0);
}

/*-----------------------------------------------------------------------------*/
void num1(int i){
  for(int j = 0; j < 24; j++){
  myShiftOut(LED7SEG[i]);
  digitalWrite(LED4,1);
  delay(5);
  }
}
void num2(int i){
  for(int j = 0; j < 24; j++){
   if(i<0 && i>-10) myShiftOut(0xbf);
   else myShiftOut(LED7SEG[i/10]);
   digitalWrite(LED3,1);  
   delay(10);
   digitalWrite(LED3,0); 
   if (i<0 && i>-10) myShiftOut(LED7SEG[i*-1]);
   else myShiftOut(LED7SEG[i%10]);
   digitalWrite(LED4,1); 
   delay(10);
   digitalWrite(LED4,0); 
   }
}
void num3(int i){
  for(int j = 0; j < 24; j++){
  int tmp = i;
  if(i<-9 && i>-100) myShiftOut(0xbf);
  else myShiftOut(LED7SEG[tmp/100]);
   digitalWrite(LED2,1);   
   delay(10);
   digitalWrite(LED2,0);
   tmp %= 100;
   
   if(i<-9 && i>-100) myShiftOut(LED7SEG[i*-1/10]);
   else myShiftOut(LED7SEG[tmp/10]);
   digitalWrite(LED3,1);  
   delay(10);
   digitalWrite(LED3,0); 
   
   if(i<-9 && i>-100) myShiftOut(LED7SEG[i*-1%10]);
   myShiftOut(LED7SEG[tmp%10]);
   digitalWrite(LED4,1);
   delay(10);
   digitalWrite(LED4,0); 
  }
}
void num4(int i){
  for(int j = 0; j < 24; j++){
    int tmp = i;
  if(i<-99 && i>-1000) myShiftOut(0xbf);
  else myShiftOut(LED7SEG[tmp/1000]);
   digitalWrite(LED1,1);  
   delay(10);
   digitalWrite(LED1,0); 
   tmp %= 1000;
   
   if(i<-99 && i>-1000) myShiftOut(LED7SEG[(i*-1/100)]);
   else myShiftOut(LED7SEG[tmp/100]);
   digitalWrite(LED2,1);  
   delay(10);
   digitalWrite(LED2,0); 
   tmp %= 100;
   
   if(i<-99 && i>-1000) myShiftOut(LED7SEG[(i*-1%100)/10]);
   else myShiftOut(LED7SEG[tmp/10]);
   digitalWrite(LED3,1);  
   delay(10);
   digitalWrite(LED3,0); 
   
   if(i<-99 && i>-1000) myShiftOut(LED7SEG[(i*-1%100)%10]);
   else myShiftOut(LED7SEG[tmp%10]);
   digitalWrite(LED4,1); 
   delay(10);
   digitalWrite(LED4,0);
  }
}

void LED_put(int i){
  if(i<-99 && i>-1000) num4(i);
  else if(i<-9 && i>-100) num3(i);
  else if(i<0 && i>-10) num2(i);
  else if(i>-1 && i<10) num1(i);
  else if(i>9 && i<100) num2(i);
  else if(i>99 && i<1000) num3(i);
  else if(i>999 && i<10000) num4(i);
  else num_full();
}

void num_full()
{
  for(int j = 0; j < 24; j++){
  myShiftOut(0x8e);//chu F
   digitalWrite(LED1,1); 
   delay(10);
   digitalWrite(LED1,0);
   myShiftOut(0xc1);//chu U
   digitalWrite(LED2,1); 
   delay(10);
   digitalWrite(LED2,0); 
   myShiftOut(0xc7);//chu U
   digitalWrite(LED3,1);  
   delay(10);
   digitalWrite(LED3,0); 
   myShiftOut(0xc7);//chu L
   digitalWrite(LED4,1); 
   delay(10);
   digitalWrite(LED4,0); 
  }
}

void LED_clr(){
  myShiftOut(0xff);
}

void loop(){
  for(int i=10;i<21;i++) {
    LED_put(i);
    delay(100);
  }
}
