#include <Keypad.h>
#include <LiquidCrystal.h>

//definindo as constantes
const int FSR_PIN = A1; //Pino do sensor de força
const float VCC = 4.98;
const float R_DIV = 323.0;
int quantidade = 0;
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Definicao da quantidade de linhas e colunas
const byte LINHAS = 4;
const byte COLUNAS = 4;
//Definicao dos pinos das linhas
byte PinosLinhas[LINHAS] = {A2, A3, A4, A5};
// A0, A1, A2, A3, A4 e A5 são constantes pré-definidas
// No Arduino uno, elas valem 14(A0), 15, 16, 17, 18 e 19(A5)
//Definicao dos pinos das colunas
byte PinosColunas[COLUNAS] = {7, 6, 5};
//Matriz de caracteres
char matriz_teclas[LINHAS][COLUNAS] = 
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
int ColunaLCD = 0;

int peso = 0;

String stringdigitada = "";

void atualizaDisplay(){
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(peso);
  lcd.print(" kg  ");
  ColunaLCD=0;
  lcd.setCursor(0, 0);
}

//Inicializa o teclado
Keypad meu_teclado = Keypad( makeKeymap(matriz_teclas), 
                             PinosLinhas, PinosColunas, 
                             LINHAS, COLUNAS);


void setup() {
  Serial.begin(9600);
   pinMode(FSR_PIN, INPUT);
  
  // inicializando display 16x2
  lcd.begin(16, 2);  
  lcd.setCursor(ColunaLCD, 0);
  atualizaDisplay();
  
  // exibindo mensagem no display
  lcd.print("     Sabor");{
  lcd.setCursor(0, 1);
  lcd.print("   Solidario");
  lcd.setCursor(0, 2);
    delay(7000);
  lcd.clear();
    lcd.print("Digite o peso");{
      lcd.setCursor(0,1);
      lcd.print("da pessoa:");
      lcd.setCursor(0,2);
      delay(5000);
    lcd.clear();}}
  
  delay(1000);} // aguardando 1 segundos antes de iniciar a leitura


  void loop(){
  char tecla = meu_teclado.getKey();
  //if( (tecla=='0')||(tecla=='1')||(tecla=='2')||(tecla=='3')||
  //    (tecla=='4')||(tecla=='5')||(tecla=='6')||(tecla=='7')||
  //    (tecla=='8')||(tecla=='9') ){
  if((tecla!='*')&&(tecla!='#')&&(tecla!=NO_KEY)){
                                        // NO_KEY indica nada digitado!
    stringdigitada+=tecla;              // Concatena 'tecla' ao final de stringdigitada(tipo String!)
    
    lcd.print(tecla);                   // "mostra" tecla no display
    lcd.setCursor (++ColunaLCD, 0);     // Incrementa Coluna
    Serial.println(stringdigitada);     //debug
  }
  else
  if (tecla=='*') //* = Backspace
  {
    if(ColunaLCD>0) {                   // Testa se não chegou ao começo da string
      lcd.setCursor (--ColunaLCD, 0);   // Coluna - 1
      lcd.print("_");                   //Escreve '_'
      stringdigitada.remove(ColunaLCD); //Retira o ultimo
                                        //caractere da string
      lcd.setCursor(ColunaLCD, 0);      //Reposiciona
    }
  }
  else
  if (tecla=='#'){//# = Enter
    peso = stringdigitada.toInt();      // Converte string -> int
    if(peso>180) peso = 180;            // Limite superior
    stringdigitada="";                  // Zera stringdigitada
    Serial.print ("Peso da pessoa: ");  //escreve Texto 
    Serial.println (peso);              //escreve em uma nova linha (ln), 
  							            //o valor do peso
    quantidade = 30 * peso;
   	atualizaDisplay();
    delay(3000);
    lcd.clear();
    lcd.print("Sua porcao tera:");{
      lcd.setCursor(0,1);
      lcd.print(quantidade);
  		lcd.print(" gramas  ");
      lcd.setCursor(0,2);}
    delay(5000);
    lcd.clear();
       //Ativando sensor força 
        int fsrADC = analogRead(FSR_PIN);

        if(fsrADC != 0){
            float fsrV = fsrADC * VCC / 1023.0;
            float fsrR = R_DIV * (VCC / fsrV - 1.0);
            Serial.println("Resistance: " + String(fsrR) + "ohms");
            float force;
            float fsrG = 1.0 / fsrR;
            if(fsrR <= 600)
            force = (fsrG - 0.00075) / 0.00000032639;
        else
            force = fsrG / 0.000000642857;
            Serial.println("force: " + String(force) + "g");
            Serial.println();

        lcd.clear();
        lcd.print("Peso: " + String(force) + " g");
        if(force < 0.5) lcd.clear();
    
  delay(1500);
}}}