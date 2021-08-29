#include<SoftwareSerial.h>
SoftwareSerial sim(2, 3);

int lampu = 4;
String pesan;
bool cek = false;

void setup() {
  Serial.begin(9600);
  pinMode(lampu, OUTPUT);
  sim.begin(9600);
  delay(100);
  sim.println("AT");
  sim.println("AT+CMGF=1");
  sim.println("AT+CNMI=1,2,0,0,0");
}

void loop() {
  if (Serial.available()) {
    sim.write(Serial.read());
  }
  if (sim.available() > 0) {
    pesan = sim.readStringUntil('\n');
    Serial.println(pesan);
    if (pesan == "On\r") {
      digitalWrite(lampu, HIGH);
      cek = true;
      eksekusi(1);
      Serial.println("lampu menyala");
    }
    if (pesan == "Off\r") {
      digitalWrite(lampu, LOW);
      cek = false;
      eksekusi(0);
      Serial.println("lampu padam");
    }
    if (pesan == "Status\r") {
      stat();
      Serial.println("status sedang di cek");
    }

  }
}

void eksekusi(bool tipe) {
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"082124047427\"\r");
  delay(1000);
  if (tipe == 1) {
    sim.println("lampu menyala");
  } else {
    sim.println("lampu padam");
  }
  delay(100);
  sim.println((char)26);
  delay(1000);
}

void stat () {
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"082124047427\"\r");
  delay(1000);
  if (cek == true) {
    sim.println("lampu sedang menyala");
  } else {
    sim.println("lampu sedang padam");
  }
  delay(100);
  sim.println((char)26);
  delay(1000);
}
