#include "ATMega.h"

byte variable_menu=0,boutonplusavant=1,boutonmoinsavant=1,boutonvalideravant=1,buzzer_actif=0,variableok=0;
byte mode=1, light=0;
int temperature2,humidity2,arrosage = 3;
float luminosite;
float degreseuilmin=23.5;
byte boutonvalider, boutonplus,boutonmoins;
String inString;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int pinDHT11 = 5;
SimpleDHT11 dht11(pinDHT11);

void setup() {
    Serial.begin(9600);
    Serial3.begin(115200);//vers l'esp8266
    Serial.println("=================================");
    pinMode(2,INPUT_PULLUP);
    pinMode(8,INPUT_PULLUP);
    pinMode(4,INPUT_PULLUP);
    pinMode(ventil_set,OUTPUT);
    pinMode(ventil_unset,OUTPUT);
    pinMode(buzzer,OUTPUT);
    pinMode(A15,OUTPUT);
    pinMode(A14,INPUT);
    pinMode(A10,OUTPUT);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); 
    }
    delay(1500);
    display.display();
    delay(1000); 
    display.clearDisplay();
    display.display();
    delay(1000);
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(5);
    display.println("GO !");
    display.display();
}

void affichagevariable(float (variable),const char* (unite), int (taille)){
    display.setTextSize(taille);
    display.setTextColor(WHITE);
    display.print(int(variable));
    display.print('.');
    display.print(int((variable-int(variable))*10));
    display.println(unite);
}

void texte(const char* text,int taille){
    display.setTextSize(taille);
    display.setTextColor(WHITE);
    display.println(text);
}

void affichage_gen(){
    display.clearDisplay();
    display.setCursor(0,0);
    switch (variable_menu){
          case 0 : texte("seuil de  chaleur dedepart\nventilo",2);
          break;
          case 1 : texte("mode \nallumage",2);
          break;
          case 2 : texte("arrosage",2);
          break;
          case 3 : texte("tempera-\nture\nhumidite",2);
          break;
    }
    display.display();
}

void menu_buzzer(){
    display.clearDisplay();
    display.setCursor(0,0);
    texte("Maintenez blanc pourdesactiverl'alarme!",2);
    display.display();
    boutonvalider=digitalRead(2);
    if(boutonvalider==0){
        buzzer_actif=0;
    }
}

void boutonmoinstest(){
    boutonmoins=digitalRead(4);
    delay(10);
    if(boutonmoins==0 && boutonmoinsavant==1){
        Serial.println("bouton moins pressé");
        if(variableok==0){
            variable_menu=((variable_menu-1)+4)%4;
            affichage_gen();
        }else{
            display.clearDisplay();
            display.setCursor(0,0);
            switch (variable_menu){
                case 0 :
                    degreseuilmin=degreseuilmin-0.5;
                    affichagevariable(degreseuilmin,"C",3);
                break;

                case 1 :
                        light = (light + 1)%2; 
                        if (light == 1) {
                            if (mode==1){
                                texte("mode : \nauto\nLED :\nON",2);
                            }else{
                                texte("mode : \nmanuel \nLED :\nON",2);
                            }
                        }else{
                            if (mode==1){
                                texte("mode : \nauto\nLED :\nOFF",2);
                            }else{
                                texte("mode : \nmanuel \nLED :\nOFF",2);
                            }
                        }
                break;

                case 2 :
                    arrosage = 0;
                    affichagevariable(arrosage,"J",4);
                break;

                case 3 :
                    affichagevariable(temperature2,"C",3);
                    affichagevariable(humidity2,"%",3);
                break;
            }
            display.display();
        }
    }
    boutonmoinsavant=boutonmoins;
}

void boutonplustest(){
    boutonplus=digitalRead(8);
    delay(10);
    if(boutonplus==0 && boutonplusavant==1){
        Serial.println("bouton plus pressé");
        if(variableok==0){
            variable_menu = (variable_menu+1)%4;
            affichage_gen();
        }else{
            display.clearDisplay();
            display.setCursor(0,0);
            switch (variable_menu){
                case 0 :
                    degreseuilmin=degreseuilmin+0.5;
                    affichagevariable(degreseuilmin,"C",3);
                break;

                case 1 :
                    mode = (mode + 1)%2  ; 
                    if  (light == 1) {
                        if (mode==1){
                            texte("mode : \nauto\nLED :\nON",2);
                        }else{
                            texte("mode : \nmanuel \nLED :\nON",2);
                        }
                    }else{
                        if (mode==1){
                            texte("mode : \nauto\nLED :\nOFF",2);
                        }else{
                            texte("mode : \nmanuel \nLED :\nOFF",2);
                        }                    
                    }
                break;
                case 2 :
                    arrosage = 0;
                    affichagevariable(arrosage,"J",4);
                break;
                case 3 :
                    affichagevariable(temperature2,"C",3);
                    affichagevariable(humidity2,"%",3);
                break;
            }
            display.display();
        }
    }
    boutonplusavant=boutonplus;
}

void boutonvalidertest(){
    boutonvalider=digitalRead(2);
    delay(10);
    if(boutonvalider==0 && boutonvalideravant==1){
        Serial.println("bouton valider pressé");
        variableok=(variableok+1)%2;
    }
    if(variableok==0){
        affichage_gen();
    }else{
        display.clearDisplay();
        display.setCursor(0,0);
        switch (variable_menu){
            case 0 : affichagevariable(degreseuilmin,"C",4);
            break;
            case 1 :
                if  (mode == 1) {
                    if(light==1){
                        texte("mode : \nauto\nLED :\nON",2);
                    }else{
                        texte("mode : \nauto\nLED :\nOFF",2);
                    }

                }else{
                    if(light==1){
                        texte("mode : \nmanuel\nLED :\nON",2);
                    }else{
                        texte("mode : \nmanuel\nLED :\nOFF",2);
                    }
                }
            break;

            case 2 : affichagevariable(arrosage,"J",4);
            break;

            case 3 :
                affichagevariable(temperature2,"C",3);
                affichagevariable(humidity2,"%",3);
            
            break;
        }
        display.display();
    }
    boutonvalideravant=boutonvalider;
}

void activation_buzzer() {
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
}

void testdesboutons(){
    boutonmoinstest();
    boutonplustest();
    boutonvalidertest(); 
}

void loop(){
    byte temperature = 0;
    byte humidity = 0;
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
        return;
    }
    display.clearDisplay();
    boutonplus=digitalRead(3);
    boutonmoins=digitalRead(4);
    boutonvalider=digitalRead(2);
    luminosite=analogRead(A14);
    texte("Maintenez blanc pourdesactiverl'alarme!",2);
    analogWrite(A10,1022);
    testdesboutons();
    temperature2=temperature;
    humidity2=humidity;
    if(temperature2>degreseuilmin){
        digitalWrite(ventil_set,true);
        delay(50);
        digitalWrite(ventil_set,false);
    }
    if(temperature2<degreseuilmin-1){
        digitalWrite(ventil_unset,true);
        delay(50);
        digitalWrite(ventil_unset,false);
    }
    Serial3.print("[SEU#");
    Serial3.print(degreseuilmin);
    Serial3.println("]");

    Serial3.print("[LED#");
    Serial3.print(light);
    Serial3.println("]");
    
    Serial3.print("[MOD#");
    Serial3.print(mode);
    Serial3.println("]");

    Serial3.print("[TMP#");
    Serial3.print(temperature2);
    Serial3.println("]");
    Serial3.print("[HUM#");
    Serial3.print(humidity2);
    Serial3.println("]");

    if(mode==1){
        if(luminosite<=20){
            analogWrite(A15,1022);
            delay(10);
        }else{
            analogWrite(A15,1);
            delay(10);
        }
    }else{
        if(light==1){
            analogWrite(A15,1022);
            delay(10);
        }else{
            analogWrite(A15,1);
            delay(10);
        }
    }
    testdesboutons();
    while (buzzer_actif==1){
        activation_buzzer();
        menu_buzzer();
    } 
}
