#include <Servo.h>

#include <Adafruit_NeoPixel.h>

 

Servo UvServo;

int pos = 0;

 

#define Pin1 10

 

#define Pin2 11

 

#define Pin3 12

 

#define uv 13

 

#define um 9

 

#define Num_um 13

 

#define UV_num 30

 

Adafruit_NeoPixel pixels1(3, Pin1, NEO_GRB + NEO_KHZ800); 

 

Adafruit_NeoPixel pixels2(3, Pin2, NEO_GRB + NEO_KHZ800); 

 

Adafruit_NeoPixel pixels3(3, Pin3, NEO_GRB + NEO_KHZ800); 

 

Adafruit_NeoPixel UV = Adafruit_NeoPixel(UV_num, uv, NEO_GRB + NEO_KHZ800);

 

Adafruit_NeoPixel Um = Adafruit_NeoPixel(Num_um, um, NEO_GRB + NEO_KHZ800);

 

 

#define PUL 7

 

#define DIR 6

 

#define ENA 5

 

#define echo 3

 

#define trig 4

 

char data; //data는 시리얼값저장, data1은 시리얼값 유지용

 

char result;

 

unsigned long millisTime = 0; //현재 시간

 

unsigned long countTime = 0;  //카운트 시작 시간

 

int distance;

 

void setup() {

 

  Serial.begin(9600);

 

  Serial1.begin(9600);

 

  UvServo.attach(2);

 

  pinMode(PUL, OUTPUT);

 

  pinMode(DIR, OUTPUT);

 

  pinMode(ENA, OUTPUT);

 

  pinMode(Pin1, OUTPUT);

 

  pinMode(Pin2, OUTPUT);

 

  pinMode(Pin3, OUTPUT);

 

  pinMode(uv, OUTPUT);

 

  pinMode(trig, OUTPUT);

 

  pinMode(echo, INPUT);

 

  pixels1.setBrightness(50);

 

  pixels1.begin();

 

  pixels2.setBrightness(50);

 

  pixels2.begin();

 

  pixels3.setBrightness(50);

 

  pixels3.begin();

 

  UV.setBrightness(50);

 

  UV.begin();

 

  Um.setBrightness(50);

 

  Um.begin();

}

 

void Neo1(int a){

  for(int i=0; i<pixels1.numPixels(); i++){

    pixels1.setPixelColor(i, pixels1.Color(a,0,0));

    pixels1.show();

  }

 //data = Serial1.read();

}

 

void Neo2(int a){

  for(int i=0; i<pixels2.numPixels(); i++){

    pixels2.setPixelColor(i, pixels2.Color(a,0,0));

    pixels2.show();

  }

 //data = Serial1.read();

}

 

void Neo3(int a){

  for(int i=0; i<pixels3.numPixels(); i++){

    pixels3.setPixelColor(i, pixels3.Color(a,0,0));

    pixels3.show();

  }

 //data = Serial1.read();

}

 

void UV_neo(int a){

  for(int i=0; i<UV.numPixels(); i++){

    UV.setPixelColor(i, UV.Color(0,a,a));

    UV.show();

  }

 //data = Serial1.read();

}

 

void Um_neo(int a){

  for(int i=0; i<Um.numPixels(); i++){

    Um.setPixelColor(i, Um.Color(a,a,0));

    Um.show();

  }

  //data = Serial1.read();

}

 

float Distance(){

  digitalWrite(trig, HIGH);

  delay(1);

  digitalWrite(trig, LOW);

  float dur = pulseIn(echo, HIGH) / 58.2;

  return dur;

}

 

void UVNEO(){

  distance = Distance();

  if(distance <= 10){ //거리 제어

    UV_neo(0);

    UvServo.write(180);

    countTime = millis();

  }

  else{  

    millisTime = (millis() - countTime) / 100;

    if(millisTime >= 50){

      UV_neo(255);

      UvServo.write(90);

    }

  }

}

 

void Teachable(){

  

  if(Serial.available()>0){

    result = Serial.read();

 

    if(result == '0'){

      Serial1.println('0');

    }

    if(result == '1'){

      Serial1.println('1');

    }

    if(result == '2'){

      Serial1.println('2');

    }

    if(result == '3'){

      Serial1.println('3');

    }

    if(result == '4'){

      Serial1.println('4');

    }

    if(result == '5'){

      Serial1.println('5');

    }

    if(result == '6'){

      Serial1.println('6');

    }

    if(result == '7'){

      Serial1.println('7');

    }

    if(result == '8'){

      Serial1.println('8');

    }

    delay(1000);

  }

}

 

 

 

void loop() {

    if(Serial.available()>0){

    result = Serial.read();

    UVNEO();

 

    if(Serial1.available()>0){

      data = Serial1.read(); // 시리얼값을 데이터로 대입

      //Serial.print(data);

      if(data == 'c'){Neo1(255);}

      if(data == 'd'){Neo2(255);}

      if(data == 'e'){Neo3(255);}

      if(data == 'z'){Um_neo(255);}

      if(data == 'f'){Neo1(0);Neo2(0);Neo3(0);}

      if(data == 'Z'){Um_neo(0);}

  // 왼쪽 

      

      while(data == 'a'){

 

        delay(500);

 

        Serial1.print('c');

 

        Teachable();     // 첫 값

 

     

 

        for(int i=0; i<17000; i++){

 

          digitalWrite(DIR,LOW);

 

          digitalWrite(ENA,HIGH);

 

          digitalWrite(PUL,HIGH);

 

          delayMicroseconds(50); 

 

          digitalWrite(PUL,LOW);

 

          delayMicroseconds(50);

 

        }

 

 

        //Serial1.print('C');

        Serial1.println('q');

        break;

        

      }

 

   

      while(data == 'q'){

 

        delay(3000);

  

        Serial1.print('d');   

  

        Teachable();           // 두 번째 값

 

 

 

        for(int i=0; i<17000; i++){

 

          digitalWrite(DIR,LOW);

 

          digitalWrite(ENA,HIGH);

 

          digitalWrite(PUL,HIGH);

 

          delayMicroseconds(50); 

 

          digitalWrite(PUL,LOW);

 

          delayMicroseconds(50);

 

        }

 

        //Serial1.print('D');

        Serial1.println('w');

      

        break;      

      }  

 

          

        

 

      while(data == 'w'){

 

        digitalWrite(DIR,LOW);

 

        digitalWrite(ENA,LOW);

 

        delay(3000);

 

        Serial1.print('e');

 

        Teachable();           // 세 번째 값

 

        //Serial1.println();

 

        break;

 

      }

  

 

  

 

  // 오른쪽

 

      while(data == 'b'){

 

        delay(500);

 

        Serial1.print('e');

 

        Teachable();     // 첫 값

 

        

 

        for(int i=0; i<17000; i++){

 

          digitalWrite(DIR,HIGH);

 

          digitalWrite(ENA,HIGH);

 

          digitalWrite(PUL,HIGH);

 

          delayMicroseconds(50); 

 

          digitalWrite(PUL,LOW);

 

          delayMicroseconds(50);

 

        }

 

        //Serial1.print('E');

        Serial1.println('r');

        break;

        

      }

 

      

 

      while(data == 'r'){

 

        delay(3000);

 

        Serial1.print('d');

 

        Teachable();     // 첫 값

 

 

        for(int i=0; i<17000; i++){

 

          digitalWrite(DIR,HIGH);

 

          digitalWrite(ENA,HIGH);

 

          digitalWrite(PUL,HIGH);

 

          delayMicroseconds(50); 

 

          digitalWrite(PUL,LOW);

 

          delayMicroseconds(50);

 

        }

        

        //Serial1.print('F');

        Serial1.println('t');

        break;

        

      }

 

      

 

      while(data == 't'){

 

        digitalWrite(DIR,LOW);

 

        digitalWrite(ENA,LOW);

 

        delay(3000);

 

        Serial1.print('c');   

 

        Teachable();           // 두 번째 값

 

        //Serial1.println();

 

        break;

 

      }

 

    }

 

  }

}
