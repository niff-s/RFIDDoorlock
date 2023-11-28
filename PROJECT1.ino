#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN         9
#define SS_PIN          10
#define LED_G           3
#define LED_R           2
#define servoPin          5
#define buzzer          6

MFRC522 mfrc522(SS_PIN, RST_PIN);

Servo Servo1;

void setup() {
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode (LED_G, OUTPUT);
  pinMode (LED_R, OUTPUT);
  pinMode (buzzer, OUTPUT);
  Servo1.attach (servoPin);
}


void loop() {
  // Servo1.write (0);
  // delay (100);

  if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

  if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

  String content = "";
  byte letter;
  for (byte i = 0;i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  content.toUpperCase();
  if (content == "32E6FF1E") {
    digitalWrite(LED_G, HIGH);
    delay(1000);
    digitalWrite(LED_G, LOW);
    Servo1.write (90);
    delay (1000);
    Servo1.write (0);
    delay(1000);
    Servo1.write (90);
    delay (1000);
  }

  else {
    digitalWrite(LED_R, HIGH);
    digitalWrite (buzzer, HIGH);
    delay(500);
    digitalWrite (buzzer, LOW);
    delay (2000);
    digitalWrite(LED_R, LOW);
    delay (2000);
    
  }

}
