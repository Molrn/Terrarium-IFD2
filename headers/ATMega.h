#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SPIDevice.h>
#include <SimpleDHT.h>
#include <Arduino.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
#define ventil_set 7
#define ventil_unset 12
#define buzzer 11


//Affiche une variable sur l'ecran OLED
void affichagevariable(float (variable),const char* (unite), int (taille));

//Affiche une chaine de characteres sur l'ecran OLED
void texte(const char* text,int taille);

//Affiche le menu general sur l'ecran OLED
void affichage_gen();

//affiche le message annoncant comment désactiver le buzzer
void menu_buzzer();

//actualise les variables en fonction du contenu affiché sur l'ecran OLED lorsqu'il y a appui sur le bouton moins 
void boutonmoinstest();

//actualise les variables en fonction du contenu affiché sur l'ecran OLED lorsqu'il y a appui sur le bouton plus
void boutonplustest();

//actualise les variables en fonction du contenu affiché sur l'ecran OLED lorsqu'il y a appui sur le bouton valider
void boutonvalidertest();

//Active le buzzer 
void activation_buzzer();

//verifie constamment si les boutons sont appuyés ou non
void testdesboutons();

