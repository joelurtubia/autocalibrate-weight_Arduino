#include "HX711.h"
#include <EEPROM.h>
#include <Servo.h>


HX711 cell(A0, A1);
#define sw 11
#define CheckStep 10

// Declaramos la variable para controlar el servo
Servo servoMotor;

int LED = 12; //the pin we connect the LED
int LED2 = 7; //the pin we connect the LED
float results;
long sample=0;
float val=0;
long value=0;
long count=0;
float contador = 0;
float sample50g =0;
int contadorLoop = 0;

struct MyObject {
  long  field1;
  float field2;
};


void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  pinMode(CheckStep, INPUT_PULLUP);
    // Iniciamos el servo para que empiece a trabajar con el pin 8
  servoMotor.attach(8);
  
  int eeAddress = 0; //EEPROM address to start reading from
  MyObject customVar; //Variable to store custom object read from EEPROM.
  EEPROM.get( eeAddress, customVar );

  Serial.println( "Read custom object from EEPROM: " );
  Serial.println( customVar.field1 );
  Serial.println( customVar.field2 );
  if (customVar.field1 > 100){
    sample = customVar.field1;
    val = customVar.field2;
  }
}

void loop() {
  
  
    
  // Inicializamos al ángulo 0 el servomotor
  servoMotor.write(0);
  
  // comenzamos a leer los datos de la pesa
  
  count= cell.read();
  //int w=(((count-sample)/val)-2*((count-sample)/val));
  
  float w=((count-sample)/val);
  Serial.println(" Esperando una lectura de peso valida....");
  delay(500);
 while ((int)w > 10){
      Serial.println(" Primera lectura, puede estar errada....");
      Serial.print("weight:");
      Serial.print((int)w);
      Serial.println("g");
      
      delay(3500);
      count= cell.read();
      //int w=(((count-sample)/val)-2*((count-sample)/val));
      
      w=((count-sample)/val);      
      if ((int)w > 10){
      Serial.println(" Es un peso valido, este es el peso");
      Serial.print("weight:");
      Serial.print((int)w);
      Serial.println("g");
    
     Serial.println(" Presiona el boton si necesitas calibrar el equipo...");
     delay(500);

      /***
       * 
       * Need a carrier of signal to start
       * check if weight stay for more that 2 second in load cell
       * genearte a carrier to start use and for finish
      ***/      
     
      /***
       *Check if was weigth and  
       *contadorLoop =1 means that range of egg should be between 30gr. and 40 gr.
       *contadorLoop =2 means that range of egg should be between 50gr. and 60 gr.
       *contadorLoop =3 means that range of egg should be between 70gr. and 80 gr.
       ***/

      //Serial.println("Entrando al cliclo While ");
      contadorLoop = 0; 
      //count until 3 times
      while (4 > contadorLoop > 0){
            
            digitalWrite(LED, HIGH);
            digitalWrite(LED2, HIGH);
            
            if(digitalRead(CheckStep)==0) {
              
                contadorLoop = contadorLoop + 1;              
                Serial.println("Detectado Pin 10 a tierra...... ");  
                Serial.println("Contador Loop = ");
                Serial.println(contadorLoop);
                Serial.println("Peso = ");
                Serial.println((int)w);
                
   
                delay(2000);
                
                if (contadorLoop == 1 && 30 < w  && w <= 45){
                
                Serial.println(" pasando por la primera comparacion contadorLoop == 1 && (30 < w < 45) ");  
                  
                /***
                 * Move servo motor en 90 °
                 * Desplazamos al ángulo correspondiente
                  
                ***/
                for (int i = 0; i <= 90; i++)
                  {
                      // Desplazamos al ángulo correspondiente
                      servoMotor.write(i);
                      
                        digitalWrite(LED, HIGH);
                        delay(10);
                        digitalWrite(LED, LOW);
                        delay(10);
                        digitalWrite(LED2, HIGH);
                        delay(10);
                        digitalWrite(LED2, LOW);
                        delay(10);
                      // Hacemos una pausa de 25ms
                      delay(25);
                  }
                  

                  // Volvemos al inicio
                  delay(500);
                  servoMotor.write(0);
                  w = 0;
                  break;
                }
                else if(contadorLoop == 2 && (w > 46  && w <= 52)){
                Serial.println(" pasando por la segunda comparacion contadorLoop == 2 && (46 < w < 52) ");    
                  /***
                 * Move servo motor en 90 °
                 * Desplazamos al ángulo correspondiente
                  
                ***/
                for (int i = 0; i <= 90; i++)
                  {
                      // Desplazamos al ángulo correspondiente
                      servoMotor.write(i);
                        digitalWrite(LED, HIGH);
                        delay(10);
                        digitalWrite(LED, LOW);
                        delay(10);
                        digitalWrite(LED2, HIGH);
                        delay(10);
                        digitalWrite(LED2, LOW);
                        delay(10);    
                      // Hacemos una pausa de 25ms
                      delay(25);
                  }
                  // Volvemos al inicio
                  delay(500);
                  servoMotor.write(0);
                  w = 0;
                  break;
                  
                }
                else if(contadorLoop == 3 && 53 < w  && w < 70){
                Serial.println(" pasando por la tercera comparacion contadorLoop == 3 && (53 < w < 70) ");  
                  /***
                 * Move servo motor en 90 °
                 * Desplazamos al ángulo correspondiente
                  
                ***/
                for (int i = 0; i <= 90; i++)
                  {
                      // Desplazamos al ángulo correspondiente
                      servoMotor.write(i);
                        digitalWrite(LED, HIGH);
                        delay(10);
                        digitalWrite(LED, LOW);
                        delay(10);
                        digitalWrite(LED2, HIGH);
                        delay(10);
                        digitalWrite(LED2, LOW);
                        delay(10);      
                      // Hacemos una pausa de 25ms
                      delay(25);
                  }
                  // Volvemos al inicio
                  delay(500);
                  servoMotor.write(0);
                  w = 0;
                  break;
                  
                }
                
              }
        
            /***
           * Forzar calibracion???
            ***/      
            else if (digitalRead(sw)==0){
                  val=0;
                  sample=0;
                  w=0;
                  count=0;
                  calibrate();
                  for(int i=0;i<20;i++)
                    {
                        digitalWrite(LED, HIGH);
                        delay(50);
                        digitalWrite(LED, LOW);
                        delay(50);
                        digitalWrite(LED2, HIGH);
                        delay(50);
                        digitalWrite(LED2, LOW);
                        delay(50);
                    }
                  break;
                      
                  }     
        
      }
      
  
    }
    
    // read the latest value of W
  
  Serial.println(" Sleep for read again "); 
  delay(500);
  w = 0;
  count= cell.read();
  //int w=(((count-sample)/val)-2*((count-sample)/val));
  
  float w=((count-sample)/val);
  Serial.println(" Reading again "); 
  
  for(int i=0;i<20;i++)
  {
      digitalWrite(LED, HIGH);
      delay(100);
      digitalWrite(LED, LOW);
      delay(100);
      digitalWrite(LED2, HIGH);
      delay(100);
      digitalWrite(LED2, LOW);
      delay(100);
  }
  
 }
}


void calibrate()
{
//    lcd.clear();
 // lcd.print("Calibrating..."); 
  //lcd.setCursor(0,1);
  //lcd.print("Please Wait...");
  Serial.println(" #################################### ");
  Serial.println(" #################################### ");
  Serial.println(" pasando a modo calibracion ...... ");  
  Serial.println(" Por favor espere.... ");    
  for(int i=0;i<100;i++)
  {
    contador = contador + 1;    
    value=((contador-1)/contador) * value + (1/contador) * cell.read();
    //val = cell.read();
    sample+=value;
    //Serial.println(value); 
    if (i==30){
    
      Serial.println("30 % del proceso terminado"); 
     Serial.println("....");
    }else if (i==50){
    
      Serial.println("50 % del proceso terminado"); 
      Serial.println("........"); 
    }
    else if (i==90){
    
     Serial.println("90 % del proceso terminado"); 
     Serial.println(".............");
    
    }   
    
  }

  sample/=100;
  Serial.println("Llego a 100 la muestra");
  Serial.print("Este es el promedio de la muestra sin peso:");
  Serial.println(sample);
  
//  lcd.clear();
//  lcd.print("Put 100g & wait");
  Serial.println(" Coloque 50 gr y espere por favor ");
  delay(5000);

 //Serial.println(" Quite el peso por favor.... ");
 //Serial.println(" Por favor espere.... ");
  //delay(2000);
  
// Extraer valor con peso 50g  
  for(int i=0;i<200;i++)
  {
    count=cell.read();
    sample50g+=count-sample;
    //Serial.println(count); 
    if (i==60){
    
      Serial.println("30 % del proceso terminado"); 
     Serial.println("....");
    }else if (i==100){
    
      Serial.println("50 % del proceso terminado"); 
      Serial.println("........");
      //Serial.println(".............");   
    }
    else if (i==180){
    
     Serial.println("90 % del proceso terminado"); 
     Serial.println(".............");
    
    }  
    
    
  }
  
  // extrae el promedio de val
  
  sample50g/=200;

  Serial.println("Llego a 100 la muestra con el peso ");
  //Serial.print("Este es el promedio de la muestra :");
  //Serial.println(sample50g);
  delay(500);
  
  val=sample50g/50.0;        // put here your calibrating weight
  Serial.print("Este es el valor a guardar:");
  Serial.println(val);
  
   delay(2000);
   Serial.println(" Quite el peso por favor.... ");
   Serial.println(" ########################### ");


  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }

  Serial.println(" Borrando EEPROM .... ");
  // turn the LED on when we're done
  
   for(int i=0;i<20;i++)
  {
      digitalWrite(LED, HIGH);
      delay(50);
      digitalWrite(LED, LOW);
      delay(50);
  }
  
  //Data to store.
  MyObject customVar = {
    sample,
    val
  };
  
  Serial.println(" Store values::");
  Serial.println( customVar.field1 );
  Serial.println( customVar.field2 );

  int eeAddress = 0;   //Location we want the data to be put.
  EEPROM.put( eeAddress, customVar );
  
  Serial.print("Epprom escrita con los valores extraidos");
  
  //lcd.clear();
}
