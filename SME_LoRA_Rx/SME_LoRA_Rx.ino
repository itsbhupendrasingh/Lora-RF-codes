/*********
  Modified from the examples of the Arduino LoRa library by nuttyengieer.com 
  for more information write to nuttyengineeronline@gmail.com or info@nuttyengineer.com
*********/
#include<LiquidCrystal.h>
#include <SPI.h>
#include <LoRa.h>
LiquidCrystal lcd(A0,A1, A2, A3, A4, A5); // LCD pins
#define ss 10
#define rst 9
#define dio0 2

int counter = 0;

void setup() {
  //initialize Serial Monitor
  Serial.begin(9600);
  lcd.begin(20,4);
  lcd.clear();
  while (!Serial);
 Serial.println("LoRa Receiver Tested by SME Dehradun  ");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
 if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    lcd.setCursor(0,0);
    lcd.print("LoRa Error!     ");
    while (1);
  }
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
  lcd.setCursor(0,0);
  lcd.print("LoRa is OK!    ");
  delay(3000);
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");
    lcd.setCursor(0,0);
    lcd.print("Received packet");
    // read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
      lcd.setCursor(0,1);
      lcd.print(LoRaData);
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    lcd.setCursor(0,2);
    lcd.print(" with RSSI ");
    lcd.setCursor(0,3);
    lcd.print(LoRa.packetRssi());
    lcd.print(" ");
    
  }
}
