#include <LiquidCrystal.h>

int botaoPressionado = 0;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int getTime[2];
int horas = 0, minutos = 0, segundos = 0;

#define btnRIGHT  1 
#define btnUP     2 
#define btnDOWN   3 
#define btnLEFT   4 
#define btnSELECT 5 
#define btnNONE   0 

void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2); 
    lcd.setCursor(0,0);
    ajustar_hora();
}

void loop () {
    for(int ciclo; ciclo<=10; ciclo++) {
        
    
        botaoPressionado = verificar_btn_pressionado();
        lcd.setCursor(0,0);
        switch (botaoPressionado) {
            case btnNONE: {
                //Nenhuma ação
                break;
            }

            case btnLEFT: {
                lcd.print("Esquerda        ");            
                break;
            }

            case btnRIGHT: {
                lcd.print("Direita         ");
                break;
            }
            case btnUP: {
                lcd.print("Cima            ");            
                break;
            }

            case btnDOWN: {
                lcd.print("Baixo           ");
                break;
            }

            case btnSELECT: {
                lcd.print("Select          ");
                break;
            }
        }

        lcd.setCursor(0,1);
        if(horas<10){lcd.print("0");}
        lcd.print(horas);
        lcd.print(":");
        if(minutos<10){lcd.print("0");}
        lcd.print(minutos);
        lcd.print(":");
        if(segundos<10){lcd.print("0");}
        lcd.print(segundos);
    
        //ciclo++;
        delay(100);
    }
    relogioLoop();
    
}

void acender (int Pino) {
    digitalWrite(Pino, HIGH);
}

void apagar (int Pino) {
    digitalWrite(Pino, LOW);
}

int verificar_btn_pressionado () { 
    botaoPressionado = analogRead(0); 
    
    if (botaoPressionado > 1000) return btnNONE;   //0
    if (botaoPressionado < 50)   return btnRIGHT;  //1 
    if (botaoPressionado < 150)  return btnUP;     //2  
    if (botaoPressionado < 350)  return btnDOWN;   //3
    if (botaoPressionado < 500)  return btnLEFT;   //4
    if (botaoPressionado < 750)  return btnSELECT; //5
    
    return btnNONE; 
}


void ajustar_hora() {
    Serial.println("Digite a Hora:");
    int i = 0;
    int ii = 0;
    while (i == 0) {
        while(Serial.available()) {
            getTime[ii] = Serial.read()-48;
            ii++;
            if(ii == 2) {
                horas = getTime[0]*10+getTime[1];
                i++;
                break;
            }
        }
    }
    Serial.println("Recebeu");
    
    Serial.println("Digite os minutos:");
    i = 0;
    ii = 0;
    while (i == 0) {
        while(Serial.available()) {
            getTime[ii] = Serial.read()-48;
            ii++;
            if(ii == 2) {
                minutos = getTime[0]*10+getTime[1];
                i++;
                break;
            }
        }
    }
    Serial.println("Recebeu");
    
    Serial.println("Digite os segundos:");
    i = 0;
    ii = 0;
    while (i == 0) {
        while(Serial.available()) {
            getTime[ii] = Serial.read()-48;
            ii++;
            if(ii == 2) {
                segundos = getTime[0]*10+getTime[1];
                i++;
                break;
            }
        }
    }
    Serial.println("Recebeu");
}

void relogioLoop() {
    segundos++;
    
    if(segundos >= 60){
        minutos++;
        segundos = 0;
    }
      if(minutos >= 60){
          horas++;
          minutos = 0;
      }
      if(horas >= 24){
          //dia = dia + 1;
          horas = 0;
      }
      /*
      if(dia >= 32){
        mes = mes + 1;
        dia = 1;
      }
      if(mes >= 13){
        ano = ano + 1;
        mes = 1;
      }
      if(dia >= 32){
        mes = mes + 1;
        dia = 1;
      }

      if(hora >= 24){
        dia = dia + 1;
        hora = 0;
      }
      if(hora < 0){
        hora = 0;
      }
      if(minuto < 0){
        minuto = 0;
      }
      */
}
