#include <Servo.h>
Servo servo;
int TimurLDRPin = A0;
int BaratLDRPin = A1;
int TLDR = 0; //Variabel untuk menyimpan pembacaan LDR
int BLDR = 0;
int perbedaan = 0; //Variabel untuk membandingkan LDR timur dan LDR barat
int error = 10;  // Variabel jika ada perbedaan mencolok antara dua LDR tersebut
int servoSet = 130; //Variabel untuk posisi servo - akan berbeda untuk setiap servo
void setup() {
 servo.attach(9);   //menghubungkan objek servo ke pin PWM 9
 Serial.begin(9600);
}
void loop() {
 TLDR = analogRead(TimurLDRPin); //Baca nilai LDR
 BLDR = analogRead(BaratLDRPin);
 if (TLDR < 400 && BLDR < 400) {  //Periksa apakah ada cahaya redup pada dua LDR
   while (servoSet<=180 && servoSet>=80) {   // jika benar, loop ini kirim panel kembali ke timur untuk matahari terbit
  servoSet ++;
  servo.write(servoSet);
  delay(100);
   }
 }
 perbedaan = TLDR - BLDR ; //Cek perbedaan nilai antara dua LDR
 if (perbedaan > 10) {        //Kirim panel ke arah LDR dengan pembacaan yang lebih tinggi
   if (servoSet <= 180) {
  servoSet ++;
  servo.write(servoSet);
   }
 } else if (perbedaan < -10) {
   if (servoSet >= 80) {
  servoSet --;
  servo.write(servoSet);
   }
 }
 Serial.print(TLDR);    
 Serial.print("   -   ");   
 Serial.print(BLDR);   
 Serial.print("   -   ");
 Serial.print(perbedaan);   
 Serial.print("   -   ");
 Serial.print(servoSet);  
 Serial.print("   -   ");
 Serial.println(".");
 delay(100);}
