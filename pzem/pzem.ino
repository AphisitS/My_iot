git commit -m "Add all my files"#include <PZEM004Tv30.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>
#include<DHT.h>



#define LINE_TOKEN  "lzUBVRj5OQJl1sqk60le75YjTgcTTeVwkrpD5KX9gnB" //Line TOken    
#define FIREBASE_HOST "myhome-5ed54.firebaseio.com"                          // database URL 
#define FIREBASE_KEY "WyEUSLlJBztVMNGw8p6EPUJPbMQZeIHKuCAotGUY"             // secret key        // secret key
#define WIFI_SSID "Naliel"
#define WIFI_PASSWORD "357935799"
#define DHTPIN D5  //D7 
#define DHTTYPE DHT11 //specifying the type of sensor
#define reray D3
#define fan D4
#define ligh D7
const int sensor_pin = A0;
float f;
int cout=0;
bool l2,cutpow;
FirebaseData firebaseData;
PZEM004Tv30 pzem(4, 5); //D1->Rx,D2->Tx
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  
  connectWifi();
   dht.begin();
  pinMode(reray, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(ligh, OUTPUT);
  Serial.begin(115200);
  Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);


  digitalWrite(fan, 1);
  digitalWrite(ligh, 1);
  digitalWrite(reray, 0);
   LINE.setToken(LINE_TOKEN);
  // ตัวอย่างส่งข้อความ
  LINE.notify("สวัสดีครับ\nตอนนี้Sensorตัวที่1 กำลังทำงานอยู่");
  /*
  LINE.notify("myarduino.net");
  // ตัวอย่างส่งข้อมูล ตัวเลข
  LINE.notify(2342);          // จำนวนเต็ม
  LINE.notify(212.43434, 5);  // จำนวนจริง แสดง 5 หลัก

  // เลือก Line Sticker ได้จาก https://devdocs.line.me/files/sticker_list.pdf
  LINE.notifySticker(3, 240);       // ส่ง Line Sticker ด้วย PackageID 3 , StickerID 240
  LINE.notifySticker("Hello", 1, 2); // ส่ง Line Sticker ด้วย PackageID 1 , StickerID 2  พร้อมข้อความ*/
  // ตัวอย่างส่ง รูปภาพ ด้วย url
  LINE.notifyPicture("https://upload.wikimedia.org/wikipedia/commons/a/a2/Kim_Yeri_at_Trans_Korean_Wave_in_Jakarta_on_April_27%2C_2019.jpg");
  // Do something
}

void loop() {
  Firebase.getFloat(firebaseData, "Data/Temperature:", f);
  Firebase.getBool(firebaseData, "Plantstate/switch", l2);
   Firebase.getBool(firebaseData, "CutPower/value", cutpow);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("temp =");
  Serial.println(t);
  Serial.print("humd =");
  Serial.println(h + .001);
  Firebase.setFloat(firebaseData, "Data/Temperature:", (t + 0.001));
  Firebase.setFloat(firebaseData, "Data/Humidity:", (h + 0.001));
  Serial.print("f =  ");
  Serial.println(f);
  Serial.print("l2 = ");
  Serial.println(l2);
   double sM, sm;

  sM = analogRead(sensor_pin);
  Serial.println(sM);
  sM = 100 - (sM / 10.24);
  sm = sM * 1.52;

  Serial.println(sM);
  Serial.println(sm);
  //float h = dht.readHumidity();
 // float t = dht.readTemperature();
  
 
 
  if(sm<50){
    if(cout==0){
      
   dryH(sm);

    }
    cout++;
    if(cout==1000){
      cout=0;
      }
      
   
    }
    
//  Serial.println(t);
  //Serial.println(h + .001); 
 // Firebase.setFloat(firebaseData, "Data/Temperature:", (t + 0.001));
 // Firebase.setFloat(firebaseData, "Data/Humidity:", (h + 0.001));
  Firebase.setFloat(firebaseData, "Data/Moisture:", (sm + 0.001));
  Fan(f);
  Ligh(l2);
  cut(cutpow);


  double voltage = pzem.voltage();
  if (voltage = NAN) {
    Serial.print("Voltage: "); Serial.print(voltage); Serial.println("V");
  } else {
    Serial.println("Error reading voltage");
  }

  double current = pzem.current();
  if (current != NAN) {
    Serial.print("Current: "); Serial.print(current); Serial.println("A");
  } else {
    Serial.println("Error reading current");
  }

  double power = pzem.power();
  if (current != NAN) {
    Serial.print("Power: "); Serial.print(power); Serial.println("W");
  } else {
    Serial.println("Error reading power");
  }

  double energy = pzem.energy();
  if (current != NAN) {
    Serial.print("Energy: "); Serial.print(energy, 3); Serial.println("kWh");
  } else {
    Serial.println("Error reading energy");
  }

  double frequency = pzem.frequency();
  if (current != NAN) {
    Serial.print("Frequency: "); Serial.print(frequency, 1); Serial.println("Hz");
  } else {
    Serial.println("Error reading frequency");
  }

  double pf = pzem.pf();
  if (current != NAN) {
    Serial.print("PF: "); Serial.println(pf);
  } else {
    Serial.println("Error reading power factor");
  }
  double v = pzem.voltage();
  double  c = pzem.current();
  double  p = pzem.power();
  double  e = pzem.energy();
  double  f = pzem.frequency();

  Firebase.setFloat(firebaseData, "Data/Voltage:", v + 0.01);
  Firebase.setFloat(firebaseData, "Data/Current:", c + 0.01);
  Firebase.setFloat(firebaseData, "Data/Power:", p + 0.01);
  Firebase.setFloat(firebaseData, "Data/Energy:", e + 0.01);
  Firebase.setFloat(firebaseData, "Data/Frequency:", f + 0.01);

  Serial.println();
  delay(2000);
}
void connectWifi() {

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);


}
void Fan(float t2) {
  Serial.print("ff =  ");
  Serial.println(fan);
  
  Serial.print("t2 =  ");
  Serial.println(t2);

  
  if (t2 > 27) {
   
    digitalWrite(fan, 0);
  }
  else {
    
    
    digitalWrite(fan, 1);
  }

}

void Ligh(bool li) {
  if (li == true) {
    digitalWrite(ligh, 0);
   
    
  }
  else {
    digitalWrite(ligh, 1);
  
  }
  delay(1000);
}




  void cut (bool ct){
    if(ct==true){
      digitalWrite(reray, 0);
      }
      else{
        digitalWrite(reray, 1);
        }
    
    }
    void dryH(float sn){

    LINE.notify("ความชื้นในดินอยู่ที่ :");          // จำนวนเต็ม
    LINE.notify(sn);
    LINE.notify("กรุณารดน้ำต้นไม้ เพื่อสวนที่สวยงามของท่าน :");  
    
  }
