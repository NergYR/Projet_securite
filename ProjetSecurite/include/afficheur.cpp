#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <SD.h>
#include <opencv2/opencv.hpp>

// Configuration de l'écran TFT LCD shield
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
Adafruit_TFTLCD lcd(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Configuration de la carte SD
#define SD_CS 10

// Classe Afficheur pour afficher la photo et le nom de l'élève
class Afficheur {
  public:
    Afficheur(String nomFichier, int posX, int posY) {
      _nomFichier = nomFichier;
      _posX = posX;
      _posY = posY;
    }
    void afficher() {
      // Chargement de la photo de l'élève
      cv::Mat photo = cv::imread(_nomFichier.c_str());

      // Conversion de la photo en un tableau de pixels
      uint16_t pixels[photo.rows][photo.cols];
      for (int y = 0; y < photo.rows; y++) {
        for (int x = 0; x < photo.cols; x++) {
          cv::Vec3b pixel = photo.at<cv::Vec3b>(y, x);
          uint16_t color = lcd.color565(pixel[2], pixel[1], pixel[0]); // Convertit la couleur en un format compatible avec l'écran
          pixels[y][x] = color;
        }
      }
      // Affichage de la photo sur l'écran TFT LCD shield
      lcd.setAddrWindow(_posX, _posY, _posX + photo.cols - 1, _posY + photo.rows - 1);
      for (int y = 0; y < photo.rows; y++) {
        lcd.pushColors(pixels[y], photo.cols, false);
      }
      // Affichage du nom de l'élève sous la photo
      String nomEleve = _nomFichier.substring(0, _nomFichier.indexOf('.'));
      lcd.setCursor(_posX + (lcd.width() - nomEleve.length() * 6) / 2, _posY + photo.rows + 10); // Centre le texte sous la photo
      lcd.setTextColor(WHITE);
      lcd.setTextSize(2);
      lcd.print(nomEleve);
    }

  private:
    String _nomFichier;
    int _posX;
    int _posY;
    void setup() {
   // Initialisation de l'écran TFT LCD shield
   lcd.begin(0x9341);
   lcd.setRotation(1); // Rotation de l'écran
   lcd.fillScreen(BLACK); // Fond noir

   // Initialisation de la carte SD
   if (!SD.begin(SD_CS)) {
     Serial.println("Erreur de carte SD");
     while (1);
   }

   // Affichage de la photo et du nom de l'élève
   afficheur("eleve.jpg", 20, 20);
   afficheur.afficher();
  }
};


void loop() {
  // Le code ne fait rien dans la boucle principale
}
