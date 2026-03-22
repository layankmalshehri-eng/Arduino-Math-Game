#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int buzzer = 10;

int score = 0;
int maxNumber = 10;
int level = 1;

void setup(){

lcd.init();
lcd.backlight();

pinMode(buzzer,OUTPUT);

randomSeed(analogRead(0));

startScreen();

}

void loop(){}

void startScreen(){

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Math Game");

lcd.setCursor(0,1);
lcd.print("Press A Start");

while(true){

char key = keypad.getKey();

if(key=='A'){
selectLevel();
break;
}

}

}

void selectLevel(){

lcd.clear();

lcd.setCursor(0,0);
lcd.print("B Easy");

lcd.setCursor(0,1);
lcd.print("C Med D Hard");

while(true){

char key = keypad.getKey();

if(key=='B'){
maxNumber = 10;
level = 1;
break;
}

if(key=='C'){
maxNumber = 50;
level = 2;
break;
}

if(key=='D'){
maxNumber = 20;
level = 3;
break;
}

}

startGame();

}

void startGame(){

score = 0;

for(int i=1;i<=10;i++){

askQuestion(i);

}

showScore();

}

void askQuestion(int q){

int a = random(1,maxNumber);
int b = random(1,maxNumber);

int correct;
char op;

if(level==1 || level==2){

if(random(0,2)==0){

op='+';
correct = a + b;

}else{

op='-';

if(a<b){
int t=a;
a=b;
b=t;
}

correct = a - b;

}

}else{

if(random(0,2)==0){

op='*';
correct = a * b;

}else{

op='/';

a = a * b;
correct = a / b;

}

}

lcd.clear();

lcd.setCursor(0,0);
lcd.print("Q");
lcd.print(q);
lcd.print(": ");
lcd.print(a);
lcd.print(op);
lcd.print(b);

String answer="";

unsigned long startTime = millis();
int timeLimit = 40;

while(true){

int timeLeft = timeLimit - (millis() - startTime)/1000;

lcd.setCursor(0,1);
lcd.print("T:");
lcd.print(timeLeft);
lcd.print(" Ans:");
lcd.print(answer);
lcd.print("   ");

if(timeLeft <= 0){
loseSound();
delay(500);
return;
}

char key = keypad.getKey();

if(key){

if(key>='0' && key<='9'){
answer += key;
}

if(key=='*'){

if(answer.length()>0){
answer.remove(answer.length()-1);
}

}

if(key=='#'){

int user = answer.toInt();

if(user==correct){

score +=10;
winSound();

}else{

loseSound();

}

delay(500);
return;

}

}

}

}

void showScore(){

lcd.clear();

lcd.setCursor(0,0);
lcd.print("Game Over");

lcd.setCursor(0,1);
lcd.print("Score:");
lcd.print(score);

delay(5000);

startScreen();

}

void winSound(){

tone(buzzer,900,120);
delay(150);

tone(buzzer,1200,150);
delay(150);

tone(buzzer,1500,200);

}

void loseSound(){

tone(buzzer,400,300);
delay(300);

tone(buzzer,250,400);

}
