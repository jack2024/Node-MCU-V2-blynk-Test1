#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define D0 16
#define D1 5 // I2C Bus SCL (clock)
#define D2 4 // I2C Bus SDA (data)
#define D3 0
#define D4 2 // Same as “LED_BUILTIN”, but inverted logic
#define D5 14 // SPI Bus SCK (clock)
#define D6 12 // SPI Bus MISO
#define D7 13 // SPI Bus MOSI
#define D8 15 // SPI Bus SS (CS)
#define D9 3 // RX0 (Serial console)
#define D10 1 // TX0 (Serial console)

char auth[] = "BdPtjWuNog720sAcBrWYx-XauMj-PcSU";  //token
//char ssid[] = "            JACK";  //ชื่อไวไฟ
char ssid[] = "ESP-Guest";  //ชื่อไวไฟ
char pass[] = "123456789";  //รหัสไวไฟ

//กำหนดขาrelay
#define lamp1 D0
#define lamp2 D3

#define BLYNK_Green     "#23C48E"
#define BLYNK_Blue      "#04C0F8"
#define BLYNK_Red       "#D3435C"
#define BLYNK_White     "#ffffff"

BlynkTimer timer;

WidgetLED led1(V10);
WidgetLED led2(V11);
WidgetLED led3(V12);

BLYNK_CONNECTED() {
  Blynk.syncAll();
}

BLYNK_WRITE(V1)
{
  int statuslamp = 0;
  statuslamp = param.asInt();
  Serial.println("ST1="+String(statuslamp));
  if(statuslamp==true){
    led1.on();
    pinMode(lamp1,HIGH);
  }
  else{
    led1.off();
    pinMode(lamp1,LOW);
  }
}
BLYNK_WRITE(V2)
{
  int statuslamp = 0;
  statuslamp = param.asInt();
  Serial.println("ST2="+String(statuslamp));
  if(statuslamp==true){
    led2.on();
    pinMode(lamp2,HIGH);
  }
  else{
    led2.off();
    pinMode(lamp2,LOW);
  }
}

void led_blink() {
  digitalWrite(D4,!digitalRead(D4));
  if(digitalRead(D4)){
    led3.off();
  }
  else{
    led3.on();
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(D0,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, led_blink);
  Serial.println();
  pinMode(lamp1,OUTPUT);
  pinMode(lamp2,OUTPUT);
  pinMode(D8,OUTPUT);
  pinMode(lamp1,HIGH);
  pinMode(lamp2,HIGH);
}

void loop() {
  Blynk.run();
  timer.run();
}
