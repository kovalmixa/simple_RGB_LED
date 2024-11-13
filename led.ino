const int redPin = 6, greenPin = 5, bluePin = 3, analogPin = A0;
int red = 0, green = 0, blue = 0; 
int analog = 0;
void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(analogPin, INPUT);
}

void rgb(int _x){
  double x = double(_x) / 1023 * 3 * PI / 2;
  if (x <= PI) red = int(sin(x + PI / 2) * 255);
  else red = int(sin(x + PI) * 255);
  green = int(sin(x) * 255);
  blue = int(sin(x + 3 * PI / 2) * 255);
  if(red < 0) red = 0;
  if(green < 0) green = 0;
  if(blue < 0) blue = 0;
  char msg[30];
  Serial.print(x);
  sprintf(msg, "\t%d\t%d\t%d", red, green, blue);
  Serial.println(msg);
  
}

void led(){
  analogWrite(redPin, 255 - red);
  analogWrite(greenPin, 255 - green);
  analogWrite(bluePin, 255 - blue);
}

void signal(bool isAuto){
  if(isAuto){
    if (analog >= 1023) analog = 0;
    analog += 5; 
    delay(2);
  }
  else{
    analog = double(analogRead(analogPin)) ;
  }
}

void loop() {
  signal(true);
  rgb(analog);
  led();
}
