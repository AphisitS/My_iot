// Libraly
#include <FirebaseESP8266.h>
#include <TridentTD_LineNotify.h>
#include <ESP8266WiFi.h>
#include<DHT.h>


#define LINE_TOKEN  "lzUBVRj5OQJl1sqk60le75YjTgcTTeVwkrpD5KX9gnB" //Line TOken                      
#define FIREBASE_HOST "myhome-5ed54.firebaseio.com"                          // database URL 
#define FIREBASE_KEY "WyEUSLlJBztVMNGw8p6EPUJPbMQZeIHKuCAotGUY"             // secret key
#define WIFI_SSID "Naliel"
#define WIFI_PASSWORD "357935799"
//#define DHTPIN 13  //D7 
//#define DHTTYPE DHT11 //specifying the type of sensor
const int sensor_pin = A0;

//DHT dht(DHTPIN, DHTTYPE);
bool ligh, ligh1, ligh2, ligh3;
int cout=0;

FirebaseData firebaseData;
void setup() {
  connectWifi();
  Serial.println(LINE.getVersion());
  pinMode(5, OUTPUT); //D1
  pinMode(4, OUTPUT); //D2
  pinMode(0, OUTPUT); //D3
  pinMode(2, OUTPUT); //D4
  Serial.begin(115200);
  Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);
  //dht.begin();
 /* LINE.setToken(LINE_TOKEN);
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
  // Do something*/
}

void loop() {
  /*double sM, sm;

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
  Firebase.setFloat(firebaseData, "Data/Moisture:", (sm + 0.001));*/
  Ligh();
  
  Serial.println("...........");

}

void connectWifi() {
  Serial.begin(9600);
  Serial.println(WiFi.localIP());
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
}

void Ligh() {
  Firebase.getBool(firebaseData, "LightState/switch", ligh);
  Firebase.getBool(firebaseData, "LightState1/switch1", ligh1);
  Firebase.getBool(firebaseData, "LightState2/switch2", ligh2);
  Firebase.getBool(firebaseData, "LightState3/switch3", ligh3);
  Serial.println(ligh);
  if (ligh == true) {
    digitalWrite(5, HIGH);
    Serial.println("true");
  }
  else if (ligh == false) {
    digitalWrite(5, LOW);
    Serial.println("false");
  }
  if (ligh1 == true) {
    digitalWrite(4, HIGH);
    Serial.println("true");
  }
  else if (ligh1 == false) {
    digitalWrite(4, LOW);
    Serial.println("false");
  }
  if (ligh2 == true) {
    digitalWrite(0, HIGH);
    Serial.println("true");
  }
  else if (ligh2 == false) {
    digitalWrite(0, LOW);
    Serial.println("false");
  }
  if (ligh3 == true) {
    digitalWrite(2, HIGH);
    Serial.println("true");
  }
  else if (ligh3 == false) {
    digitalWrite(2, LOW);
    Serial.println("false");
  }
  if (ligh == true || ligh == false) {
    Firebase.setBool(firebaseData, "Data/switch", ligh);
  }
  if (ligh1 == true || ligh1 == false) {
    Firebase.setBool(firebaseData, "Data/switch1", ligh1);
  }
  if (ligh2 == true || ligh2 == false) {
    Firebase.setBool(firebaseData, "Data/switch2", ligh2);
  }
  if (ligh3 == true || ligh3 == false) {
    Firebase.setBool(firebaseData, "Data/switch3", ligh3);
  }
}

void dryH(float sn){

    LINE.notify("ความชื้นในดินอยู่ที่ :");          // จำนวนเต็ม
    LINE.notify(sn);
    LINE.notify("กรุณารดน้ำต้นไม้ เพื่อสวนที่สวยงามของท่าน :");  
    
  }

 
