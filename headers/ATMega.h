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

void affichagevariable(float (variable),const char* (unite), int (taille));
void texte(const char* text,int taille);
void affichage_gen();
void menu_buzzer();
void boutonmoinstest();
void boutonplustest();
void boutonvalidertest();
void activation_buzzer();
void testdesboutons();

