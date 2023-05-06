#include <LiquidCrystal.h>
//definindo as constantes
const int ldrPin = A1;  // pino do LDR
const int greenLedPin = 6; // pino do LED verde
const int yellowLedPin = 7; // pino do LED amarelo
const int redLedPin = 8; // pino do LED vermelho
const int buzzerPin = 9; // pino da buzina

const int analogIn = A0;
int humiditysensorOutput = 0;
int RawValue= 0;
double Voltage = 0;
double tempC = 0;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // definindo os pinos dos leds e da buzina como saídas
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);  
  Serial.begin(9600);
  pinMode(A2, INPUT);
  
  // inicializando display 16x2
  lcd.begin(16, 2);  
  
  // exibindo mensagem no display
  lcd.print("   A VINHERIA");{
  lcd.setCursor(0, 1);
  lcd.print("    AGNELLO");
  lcd.setCursor(0, 2);
    delay(500)	;}
  
  delay(1000);} // aguardando 1 segundos antes de iniciar a leitura do LDR


void loop() { 
  
  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 1023.0) * 5000; // 5000 to get millivots.
  tempC = (Voltage-500) * 0.1; // 500 is the offset
  Serial.print("Temperatura em C = ");
  Serial.print(tempC);
  humiditysensorOutput = analogRead(A2);
  Serial.print("\t Umidade: "); // Printing out Humidity Percentage
  Serial.print(map(humiditysensorOutput, 0, 1023, 10, 70));
  Serial.println("%");

    delay(2000);  //iterate every 2 seconds 
  
// SENSOR DE LUMINOSIDADE
  int leitura = analogRead(ldrPin);
  Serial.print("Luminosidade: ");
  Serial.println(leitura);

  if(analogRead(ldrPin) > 650){ 
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
 
  }else if (analogRead(ldrPin) < 350){ 
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    lcd.clear();
  	lcd.print("Ambiente muito"); {
  	lcd.setCursor(0, 1);
    lcd.print("claro");
    lcd.setCursor(0, 2);
      delay(5000);
    // ativando a buzina
      tone(buzzerPin, 2000, 5000);}
    
  }else{
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    lcd.clear();
  	lcd.print("Ambiente a meia"); {
  	lcd.setCursor(0, 1);
    lcd.print("luz");
    lcd.setCursor(0, 2);
      delay(5000);}
  }    
  
  	//SENSOR TEMPERATURA ºC
  if(tempC >= 15.1){
    digitalWrite(yellowLedPin, HIGH);
  	lcd.clear();
  	lcd.print("Temp. ALTA ");{
  	lcd.setCursor(0, 1);
  	lcd.print("Temp:");
  	lcd.print(tempC);
  	lcd.setCursor(0, 2);
  delay(5000);
    // ativando a buzina e ligando o LED amarelo
    tone(buzzerPin, 2000, 5000);}
 
  }else if (tempC <= 9.9){ 
    digitalWrite(yellowLedPin, HIGH);
  	lcd.clear();
  	lcd.print("Temp. BAIXA"); {
  	lcd.setCursor(0, 1);
  	lcd.print("Temp:");
  	lcd.print(tempC);
  	lcd.setCursor(0, 2);
  delay(5000);
    // ativando a buzina e ligando o LED amarelo
    tone(buzzerPin, 2000, 5000);}
      
  }else{
    lcd.clear();
  	lcd.print("Temp. OK"); {
  	lcd.setCursor(0, 1);
  	lcd.print("Temp:");
  	lcd.print(tempC);
  	lcd.setCursor(0, 2);
  delay(5000);}
}
  
      //SENSOR UMIDADE    
  if(map(humiditysensorOutput, 0, 1023, 10, 70) > 70){ 
  	digitalWrite(redLedPin, HIGH);
    lcd.clear();
  	lcd.print("Umid. ALTA ");{
  	lcd.setCursor(0, 1);
  	lcd.print("Umidade:");
  	lcd.print(map(humiditysensorOutput, 0, 1023, 10, 70));
  	lcd.print("%");
  	lcd.setCursor(0, 2);
      delay(1800);
    // ativando a buzina e ligando o LED vermelho
    tone(buzzerPin, 2000, 5000);}
 
  }else if(map(humiditysensorOutput, 0, 1023, 10, 70) < 49){ 
  	digitalWrite(redLedPin, HIGH);
    lcd.clear();
  	lcd.print("Umid. BAIXA"); {
  	lcd.setCursor(0, 1);
  	lcd.print("Umidade:");
  	lcd.print(map(humiditysensorOutput, 0, 1023, 10, 70));
  	lcd.print("%");
  	lcd.setCursor(0, 2);
      delay(1800);
    // ativando a buzina 
    tone(buzzerPin, 2000, 5000);}
      
  }else{
    lcd.clear();
  	lcd.print("Umid. OK"); {
  	lcd.setCursor(0, 1);
  	lcd.print("Umidade:");
  	lcd.print(map(humiditysensorOutput, 0, 1023, 10, 70));
    lcd.print("%");
  	lcd.setCursor(0, 2);
  	delay(1800);}}} 