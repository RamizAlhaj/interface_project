#define in1 2  //Right motor pole 1
#define in2 3  //Right motor pole 2
#define in3 4  //left motor pole 1
#define in4 7  //left motor pole 1
#define ena 5  //Right motor speed
#define enb 6  //Right motor speed

const int trigPinCenter = 11;//Trigger Pin of Ultrasonic
const int echoPinCenter = 12;//Echo Pin of Ultrasonic
const int trigPinRight = 11;//Trigger Pin of Ultrasonic
const int echoPinRight = 12;//Echo Pin of Ultrasonic
const int trigPinLeft = 11;//Trigger Pin of Ultrasonic
const int echoPinLeft = 12;//Echo Pin of Ultrasonic

long duration;//used by ultrasonic Function
int distance,Cdistance,Rdistance,Ldistance;
void setup() {
  // put your setup code here, to run once:
    pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);

  pinMode(trigPinCenter, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinCenter, INPUT); // Sets the echoPin as an Input

  pinMode(trigPinRight, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinRight, INPUT); // Sets the echoPin as an Input

  pinMode(trigPinLeft, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinLeft, INPUT); // Sets the echoPin as an Input
}


void loop() {
  //اذا الفرق بين سنسر اليمين ولشمالل اكبر من 3 سم اعمل سنتر
  //اقرا اليمين واقرا لشمال 
    
    Rdistance=ultrasonic(trigPinRight,echoPinRight);
    delay(100);
    Ldistance=ultrasonic(trigPinLeft,echoPinLeft);
    delay(100);
    if(abs(Rdistance - Ldistance)>2){
      if(Rdistance > Ldistance){
        Tright10();
      }
      else{
        Tleft10();
      }
    }
    else{
      Cdistance=ultrasonic(trigPinCenter,echoPinCenter);//take ultrasonic distance value
      if(Cdistance>30)//if greater than 30 Cm
       {
      forward();//go to forward
        }
      else 
        {
      if(Cdistance<=10&&Cdistance>2)reverse();// if close to object reverse to get more space to change orientation
      off();                   //stop robot
      delay(300); // قللها شوي 
      Rdistance=ultrasonic(trigPinRight,echoPinRight);  //get ultrasonic value at right
      delay(300);
      Ldistance=ultrasonic(trigPinLeft,echoPinLeft);  //get ultrasonic value at left
      delay(300);
      comparison(Rdistance, Ldistance); //go to Comparasion function
      off();                    // stop after execute Comparison function action
      delay(150);
  }
}
}

int ultrasonic(int TrigPin , int EchoPin)//get distance captured by ultrasonic sensor
{
  distance=0;
  // Clears the trigPin
digitalWrite(TrigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(TrigPin, HIGH);
delayMicroseconds(10);
digitalWrite(TrigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(EchoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
return distance;
}

void comparison(int r, int l)//compare values of right and left Servo Pos 
{
  if(r>25||l>25)
  {
   if(r>l||r==l)
   {
     Tright90();
   }else if(l>r)
   {
     Tleft90();
   }
  }else if(r<25&&l<25)
  {
    Tleft180();
  }
}

void forward()
{
  analogWrite(ena,130);
  analogWrite(enb,130);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
void off()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
void Tleft90()
{
  analogWrite(ena,160);
  analogWrite(enb,150);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(650);
}
void Tright90()
{
  analogWrite(ena,150);
  analogWrite(enb,160);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(750);  
}

void Tleft10()
{ //هان يجب تقليل سرعة المطورات الي على لشمال ونقلل الديليه شوي صغيرة
  analogWrite(ena,160);
  analogWrite(enb,150);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(75); // بنقلل الديليه عشان ما يلف 90 يصير يلف 10د

  // الزاوية 10 =83
}
void Tright10()
{ //وهان بدنا نقلل سرعة المطور الي ع اليمينونقلل الديليه شوي 
  analogWrite(ena,150);
  analogWrite(enb,160);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(85);  
}

void Tleft180()
{
  analogWrite(ena,150);
  analogWrite(enb,150);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(1500);
}
void reverse()
{
  analogWrite(ena,140);
  analogWrite(enb,140);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(450);
}
