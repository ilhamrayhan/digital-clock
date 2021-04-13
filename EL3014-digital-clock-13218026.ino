//Tugas 2 EL3014 Sistem Mikroprosessor
//Ilham Rayhan 13218026
#include <TimerOne.h>
#include <ezButton.h>

//Button and LED
#define Button_Pin1  A4
#define Button_Pin2  A5
#define Button_Pin3  5
#define LED1        13
#define LED2        A3
#define LED3        0
#define LED4        1

// segment pins definitions
#define SegA1   12
#define SegB1   11
#define SegC1   10
#define SegD1    9
#define SegE1    8
#define SegF1    7
#define SegG1    6

// common pins of the three digits definitions
#define Dig1    4
#define Dig2    3
#define Dig3    2
#define Dig6    A2
#define Dig5    A1
#define Dig4    A0

//Global Variable
long clocks = 0;
long alarms = 0;
long stopwatchs = 0;
int stopwatch_flag = 0;
int alarm_flag = 0;
int sets = 0;
int modes = 0;
int blinks = 0;

//Button Initiation
ezButton mode(Button_Pin1);
ezButton set(Button_Pin2);
ezButton inc(Button_Pin3);

void setup() {
  pinMode(SegA1, OUTPUT);
  pinMode(SegB1, OUTPUT);
  pinMode(SegC1, OUTPUT);
  pinMode(SegD1, OUTPUT);
  pinMode(SegE1, OUTPUT);
  pinMode(SegF1, OUTPUT);
  pinMode(SegG1, OUTPUT);
  pinMode(Dig1, OUTPUT);
  pinMode(Dig2, OUTPUT);
  pinMode(Dig3, OUTPUT);
  pinMode(Dig4, OUTPUT);
  pinMode(Dig5, OUTPUT);
  pinMode(Dig6, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(Button_Pin1, INPUT);
  pinMode(Button_Pin2, INPUT);
  pinMode(Button_Pin3, INPUT);
  mode.setDebounceTime(50);
  set.setDebounceTime(50);
  inc.setDebounceTime(50);
  noInterrupts();
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(count);
  interrupts();
}


void count(void)
{ 
  clocks+=1;
  if (clocks == 86400){
    clocks = 0;
    }
  if ((alarm_flag == 1)&&(clocks == alarms)){
    digitalWrite(LED1, HIGH);
    }
  if (alarm_flag == 1){
    if(set.isPressed()) {
      alarm_flag = 0;
      digitalWrite(LED1, LOW);
      }
    }
  if ((stopwatch_flag == 1)){
    stopwatchs +=1;
    if (stopwatchs == 86400){
    stopwatchs = 0;
    }
    }
}

void sevseg(byte number)
{
  switch (number)
  {
    case 0:  // print 0
      digitalWrite(SegA1, LOW);
      digitalWrite(SegB1, LOW);
      digitalWrite(SegC1, LOW);
      digitalWrite(SegD1, LOW);
      digitalWrite(SegE1, LOW);
      digitalWrite(SegF1, LOW);
      digitalWrite(SegG1, HIGH);
      break;
 
    case 1:  // print 1
      digitalWrite(SegA1, HIGH);
      digitalWrite(SegB1, LOW);
      digitalWrite(SegC1, LOW);
      digitalWrite(SegD1, HIGH);
      digitalWrite(SegE1, HIGH);
      digitalWrite(SegF1, HIGH);
      digitalWrite(SegG1, HIGH);
      break;
 
    case 2:  // print 2
      digitalWrite(SegA1, LOW);
      digitalWrite(SegB1, LOW);
      digitalWrite(SegC1, HIGH);
      digitalWrite(SegD1, LOW);
      digitalWrite(SegE1, LOW);
      digitalWrite(SegF1, HIGH);
      digitalWrite(SegG1, LOW);
      break;
 
    case 3:  // print 3
      digitalWrite(SegA1, LOW);
      digitalWrite(SegB1, LOW);
      digitalWrite(SegC1, LOW);
      digitalWrite(SegD1, LOW);
      digitalWrite(SegE1, HIGH);
      digitalWrite(SegF1, HIGH);
      digitalWrite(SegG1, LOW);
      break;
 
    case 4:  // print 4
      digitalWrite(SegA1, HIGH);
      digitalWrite(SegB1, LOW);
      digitalWrite(SegC1, LOW);
      digitalWrite(SegD1, HIGH);
      digitalWrite(SegE1, HIGH);
      digitalWrite(SegF1, LOW);
      digitalWrite(SegG1, LOW);
      break;
 
    case 5:  // print 5
      digitalWrite(SegA1, LOW);
      digitalWrite(SegB1, HIGH);
      digitalWrite(SegC1, LOW);
      digitalWrite(SegD1, LOW);
      digitalWrite(SegE1, HIGH);
      digitalWrite(SegF1, LOW);
      digitalWrite(SegG1, LOW);
      break;
 
    case 6:  // print 6
      digitalWrite(SegA1, LOW);
      digitalWrite(SegB1, HIGH);
      digitalWrite(SegC1, LOW);
      digitalWrite(SegD1, LOW);
      digitalWrite(SegE1, LOW);
      digitalWrite(SegF1, LOW);
      digitalWrite(SegG1, LOW);
      break;
    
    case 7:  // print 7
      digitalWrite(SegA1, LOW);
      digitalWrite(SegB1, LOW);
      digitalWrite(SegC1, LOW);
      digitalWrite(SegD1, HIGH);
      digitalWrite(SegE1, HIGH);
      digitalWrite(SegF1, HIGH);
      digitalWrite(SegG1, HIGH);
      break;
 
    case 8:  // print 8
      digitalWrite(SegA1, LOW);
      digitalWrite(SegB1, LOW);
      digitalWrite(SegC1, LOW);
      digitalWrite(SegD1, LOW);
      digitalWrite(SegE1, LOW);
      digitalWrite(SegF1, LOW);
      digitalWrite(SegG1, LOW);
      break;
 
    case 9:  // print 9
      digitalWrite(SegA1, LOW);
      digitalWrite(SegB1, LOW);
      digitalWrite(SegC1, LOW);
      digitalWrite(SegD1, LOW);
      digitalWrite(SegE1, HIGH);
      digitalWrite(SegF1, LOW);
      digitalWrite(SegG1, LOW);
      break;
 
    case 10:  // print -
      digitalWrite(SegA1, HIGH);
      digitalWrite(SegB1, HIGH);
      digitalWrite(SegC1, HIGH);
      digitalWrite(SegD1, HIGH);
      digitalWrite(SegE1, HIGH);
      digitalWrite(SegF1, HIGH);
      digitalWrite(SegG1, LOW);
  }
}

void disp(long number){
  digitalWrite(Dig6, LOW);
  sevseg(number%10);  
  digitalWrite(Dig1, HIGH);
  delay(1);
  digitalWrite(Dig1, LOW);
  sevseg((number%60)/10);   
  digitalWrite(Dig2, HIGH);     
  delay(1);
  digitalWrite(Dig2, LOW);
  sevseg((number/60)%10);   
  digitalWrite(Dig3, HIGH);
  delay(1);
  digitalWrite(Dig3, LOW);
  sevseg((number/600)%6);  
  digitalWrite(Dig4, HIGH);
  delay(1);
  digitalWrite(Dig4, LOW);
  sevseg((number/3600)%10);   
  digitalWrite(Dig5, HIGH);     
  delay(1);
  digitalWrite(Dig5, LOW);
  sevseg(number/36000);   
  digitalWrite(Dig6, HIGH);
  delay(1);
  }

void setclock(){
  static long number = 0;
  static int hour = 0;
  static int minute = 0;
  number = (long(hour)*3600)+(minute*60);
  disp(number);
  if((inc.isPressed()) && (sets == 0)){
    hour += 1;
    if(hour>23) hour = 0;
  }
  if((inc.isPressed()) && (sets == 1)){
    minute += 1;  
    if (minute>59) minute =0;
  }
  if ((set.isPressed())){
    sets += 1;
    if (sets>2){
      sets = 0;
      modes = 0;
      }
  }
  if(sets ==2 ){
    clocks = number;
  }
 }

void setalarm(){
  static long number = 0;
  static int hour = 0;
  static int minute = 0;
  number = (long(hour)*3600)+(minute*60);
  disp(number);
  if((inc.isPressed()) && (sets == 0)){
    hour += 1;
    if(hour>23) hour = 0;
  }
  if((inc.isPressed()) && (sets == 1)){
    minute += 1;  
    if (minute>59) minute =0;  
  }
  if ((set.isPressed())){
    sets += 1;
    if (sets>2){
      sets = 0;
      modes = 0;
      }
  }
  if(sets ==2){
    alarms = number;
    alarm_flag = 1;
  }
  }

void stopwatch(){
  disp(stopwatchs);
  if (set.isPressed()){
    sets += 1;
    }
  if (sets>3){
    sets = 1;
    }
  switch(sets){
    case 1:
      stopwatch_flag = 1;
      break;
    case 2:
      stopwatch_flag = 0;
      break;
    case 3: 
      stopwatchs = 0;
    }
  }

void loop() {
  mode.loop();
  set.loop();
  inc.loop();
  if (mode.isPressed()){
      modes += 1;
      if (modes>3){
          modes = 0;
        }
    }
  switch (modes){
    case 0:
      disp(clocks);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;
    case 1:
      setclock();
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
      break; 
    case 2:
      setalarm();
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;
    case 3:
      stopwatch();
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
    }
} 
