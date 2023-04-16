// Bluetooth bilgileri al Bağlantı tamam ise devam et.
// Kontrol bilgi yolla gel.
// Önce yüz tanıma bilgilerinin sl yüz tanındı ise siğer aşamaya geç yoksa bekle.
// Gaz sensörü bilgileri al
// Eğer sigara, alkol testi başarılı ise devam et.
// Yoksa bekle.
// Devam et ise: sıcaklık veri al yazdır.
// Gaz sensörü bilgi al yazdır.

#include <dht11.h> // dht11 kütüphanesini ekliyoruz.
#define DHT11PIN 5 // DHT11PIN olarak belirliyoruz.
dht11 DHT11;

int rolepin = 7;      //5v röle için pin ayarlandı.
int btbaglanti= 8;    //bluetooth modülü için pin ayarlandı.
int gaspin = A0;       //gaz sensör pini ayarlandı.
int dhtpin = 10;       //sıcaklık sensör pini ayarlandı.
int ledpin = 11;
int ledpin2 12;


int esikDegeri = 400;   //Gaz eşik değerini belirle    
int buzzerPin = 9;      //Buzzerın takılacağı pin
int deger;              //Sensörden okunan değer


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);           //bluetooth modülü için serial ayarlandı.Aynı zamanda dht11 içinde ayarlandı.
  pinMode(rolepin, OUTPUT);     // röle'nin pini çıkış olarak ayarlandı. 
  pinMode(buzzerPin, OUTPUT);   // buzzer pini ayarlandı.
  pinMode(dhtpin, OUTPUT);      //sıcaklık sensörüpini ayarlandı.
  pinMode(gaspin, OUTPUT);      //gaz sensörü pini ayarlandı.
  //pinMode(btbaglanti, OUTPUT);  //bluetooth modülü bağlantı ayarlarını kontrol et pin ayarlanmıyor.!!




}



void loop() {
  // put your main code here, to run repeatedly:

  bool kullanicigirdimi = false; //kullanıcı girdi mi bu değer ile kontrol ediliyor.
    
    char mesaj = Serial.read();
    Serial.println(mesaj);
    

  if(mesaj == '1'){
    kullanicigirdimi = true ;
    }
      else if(mesaj == '0'){
      kullanicigirdimi = false;
      //break     //!!!!!!!!BURADA BREAK İLE DÖNGÜ TAMAMEN KIRILMALI ONU KESİN KONTROLET. yoksa değişken ata bool olarak sonra her koşulun ilk kodu ile if ile kontorl et.!!!
      }

  if (kullanicigirdimi = true){   //if ile kullanıcı giriş yaptı mı yı kontrol ettik ve bütün kodlar bunun içinde çalışacaktır.

  if (mesaj == 'a'){  //yüz tanıma başarılı bu kod geldi şimdi gaz sensör kontrolü yap.
      deger = analogRead(A0); //Sensörden analog değer okundu
      
      if (deger > esikDegeri) { //Sensörden okunan değer eşik değerinden büyükse çalışır.
        Serial.print("");                 //verileri tekefona gönder uygulama devam ETMEMELİ durdur.
        Serial.print("d");                 //veri olarak aynı zamanda bir char gönder ki uygulama rahat anlasın durdur'u
        //DİKKAAAAT!!!! bu linki dene https://iremcorak.home.blog/2019/03/20/arduino-ve-app-invertor-uygulamasinin-bluetooth-uzerinden-seri-haberlesmesi/
        digitalWrite(buzzerPin, HIGH);    //poziitf tespit(olumsuz) şoför araç kullanamaz alarm çalıyor.
        digitalWrite(rolepin, LOW);       //röle marş kilidi kilitli hala 
        } 

        
      else { //Sensörden okunan değer eşik değerinin altındaysa çalışır.
          digitalWrite(buzzerPin, LOW);  //gaz negatif(olumlu) şoför araç kullanabilir. Alarm kapalı
          Serial.print("");   //Telefona gaz sensörü verlierini gönder ve devam et. GO! GO! seri biraz hadi yetiştir bu kodu
          
          //Gaz testi başarılı artık kontrol kısmı kodlarını yaz.!!!
         
            
            char mesaj2 = Serial.read();
            Serial.println(mesaj2);
            
            if(mesaj2 == 'm'){
                digitalWrite(rolepin, HIGH);   //kullanıcı marş aç değerine bastı
            }
            if(mesaj2 == 'n'){
                digitalWrite(rolepin, LOW);     //kullanıcı marş kilidi kapadı
            }
            //serial ile bluetooth ile sıcaklık nem verilerini gönder.
            //gaz değerini sürekli ölç.
            deger = analogRead(A0); //Sensörden analog değer okundu
      
            if (deger > esikDegeri) { //Sensörden okunan değer eşik değerinden büyükse çalışır.
                Serial.print("");     //verileri tekefona gönder araç durdurulmalı.
                Serial.print("o");    //tele gönder 
                digitalWrite(buzzerPin, LOW);   //belli düzen ile alarm ötüyor.
                delay(500);
                digitalWrite(buzzerPin, HIGH);  
                delay(500);
                digitalWrite(buzzerPin, LOW);   //belli düzen ile alarm ötüyor.
                delay(450);
                digitalWrite(buzzerPin, HIGH);  
                delay(400);
                digitalWrite(buzzerPin, LOW);    //belli düzen ile alarm ötüyor.
                delay(350);
                digitalWrite(buzzerPin, HIGH);  
                delay(300);
                digitalWrite(buzzerPin, LOW);    //belli düzen ile alarm ötüyor.
                delay(200);
                digitalWrite(buzzerPin, HIGH);  
                delay(100);
                digitalWrite(buzzerPin, LOW);    //belli düzen ile alarm ötüyor.
                delay(500);
                digitalWrite(buzzerPin, HIGH);  
                delay(500);
                digitalWrite(buzzerPin, LOW);   //belli düzen ile alarm ötüyor.
                delay(450);
                digitalWrite(buzzerPin, HIGH);  
                delay(400);
                digitalWrite(buzzerPin, LOW);    //belli düzen ile alarm ötüyor.
                delay(350);
                digitalWrite(buzzerPin, HIGH);  
                delay(300);
                digitalWrite(buzzerPin, LOW);    //belli düzen ile alarm ötüyor.
                delay(200);
                digitalWrite(buzzerPin, HIGH);  
                delay(100);
                digitalWrite(buzzerPin, LOW);    //belli düzen ile alarm ötüyor.
                
                char mesaj3 = Serial.read();
                Serial.println(mesaj3);
            
            if(mesaj3 == 'f'){
                digitalWrite(rolepin, LOW);   //araçta gaz tespit edildi süre doldu. MArş kapatılıyor.
            }


                } 









          }          
      }
    else if(mesaj == 'b'){
      //yüz tanıma yanlış alarm öt yanlış kişi
      pinMode(rolepin, LOW);           // röle ile marş kilitli
      digitalWrite(buzzerPin, LOW);   //belli düzen ile alarm ötüyor.
      delay(500);
      digitalWrite(buzzerPin, HIGH);  
      delay(500);
      digitalWrite(buzzerPin, LOW);   //belli düzen ile alarm ötüyor.
      delay(450);
      digitalWrite(buzzerPin, HIGH);  
      delay(400);
      digitalWrite(buzzerPin, LOW);    //belli düzen ile alarm ötüyor.
      delay(350);
      digitalWrite(buzzerPin, HIGH);  
      delay(300);
      digitalWrite(buzzerPin, LOW);    //belli düzen ile alarm ötüyor.
      delay(200);
      digitalWrite(buzzerPin, HIGH);  
      delay(100);
      digitalWrite(buzzerPin, LOW);    //belli düzen ile alarm ötüyor.
      delay(500);
      digitalWrite(buzzerPin, HIGH);  
      delay(500);
      digitalWrite(buzzerPin, LOW);   //belli düzen ile alarm ötüyor.
      delay(450);
      digitalWrite(buzzerPin, HIGH);  
      delay(400);
      digitalWrite(buzzerPin, LOW);    //belli düzen ile alarm ötüyor.
      delay(350);
      digitalWrite(buzzerPin, HIGH);  
      delay(300);
      digitalWrite(buzzerPin, LOW);    //belli düzen ile alarm ötüyor.
      delay(200);
      digitalWrite(buzzerPin, HIGH);  
      delay(100);
      digitalWrite(buzzerPin, LOW);    //belli düzen ile alarm ötüyor.
      }

      
    else {
      digitalWrite(buzzerPin, HIGH);   //yüz tanıma yapılmadı beklemede. buaryı loop'a al tekrar et!!
      delay(1000);
      digitalWrite(buzzerPin, LOW);   
      delay(1000);
      digitalWrite(buzzerPin, HIGH);  
      delay(1000);
      digitalWrite(buzzerPin, LOW);  
      }  
    }    
    //kullanıcı girdimi = true ise kodunun bitiş noktası
  else{
    digitalWrite(rolepin, LOW);   //LOW ile röle'yi kapalı konumda tutuyoruz çünkü kullanıcı giriş yapmadı.
    }

  
  //digitalWrite(rolepin, HIGH); // röle pini elektrik verildi ve röle açıldı.
  //delay(2000);                 // röle arası süre kondu. Bunu kaldır ve if koşulu ile denemelerin sonuna gelindiğinde röleyi aç ve marş kilidi aç diyince kilitle if ile.
  //digitalWrite(rolepin, LOW);  // röle pini elektrik kesildi ve röle kapandı.
  





}
