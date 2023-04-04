#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <SD.h>
#include <opencv2/opencv.hpp>
class afficheur
{
private:
    Adafruit_TFTLCD lcd(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
public:
    /// @brief Init afficheur with given params
    /// @param lcd_cs
    /// @param lcd_cd
    /// @param lcd_wr
    /// @param lcd_rd
    /// @param lcd_reset
    /// @param sd_cs 
    afficheur(String& lcd_cs, String& lcd_cd, String& lcd_wr, String& lcd_rd, String& lcd_reset, int sd_cs);
    
};






// Configuration de la carte SD
#define SD_CS 10

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

  // Chargement de la photo de l'élève
  cv::Mat photo = cv::imread("eleve.jpg");

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
  lcd.setAddrWindow(0, 0, photo.cols - 1, photo.rows - 1);
  for (int y = 0; y < photo.rows; y++) {
    lcd.pushColors(pixels[y], photo.cols, false);
  }

  // Affichage du nom de l'élève sous la photo
  String nomEleve = "Nom de l'élève";
  lcd.setCursor((lcd.width() - nomEleve.length() * 6) / 2, photo.rows + 10); // Centre le texte sous la photo
  lcd.setTextColor(WHITE);
  lcd.setTextSize(2);
  lcd.print(nomEleve);
}

void loop() {
  // Le code ne fait rien dans la boucle principale
}