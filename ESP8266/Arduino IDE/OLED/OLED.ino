/**

  OLED - mostra setas
 
   The MIT License (MIT)

   Copyright (c) 2018 by ThingPulse, Daniel Eichhorn
   Copyright (c) 2018 by Fabrice Weinberg

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.

   ThingPulse invests considerable time and money to develop these open source libraries.
   Please support us by buying our products (and not the clones) from
   https://thingpulse.com

*/

// Incluir a biblioteca de exibicao correta
// Para uma conexão via I2C usando biblioteca Wire do SSD130611
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
// Possue as definicoes binarias das imagens a serem mostradas
#include "images.h"

#define SDA_PIN 5
#define SCL_PIN 4
#define ENDERECO_I2C 0x3C

SSD1306Wire  display(ENDERECO_I2C, SDA_PIN, SCL_PIN); // SDA, SCL

void desenhaSetaHorizontal(char o) {
  display.resetDisplay();
  //display.resetOrientation();
  //if (o == 'd') display.flipScreenVertically();
  display.drawXbm((128 - setaHorizontalWidth) / 2 , 0 , setaHorizontalWidth, setaHorizontalHeight, setaHorizontal);
  display.display();
  //display.resetOrientation();
}

void desenhaSetaVertical(char o) {
  display.resetDisplay();
  display.resetOrientation();
  if (o == 'b') display.mirrorScreen();
  display.drawXbm((128 - setaVerticalWidth) / 2 , 0 , setaVerticalWidth, setaVerticalHeight, setaVertical);
  display.display();
}

void desenhaSetaCima(char o) {
  display.resetDisplay();
  display.resetOrientation();
  if (o == 'd') display.flipScreenVertically();
  display.drawXbm((128 - setaCimaWidth) / 2 , 0 , setaCimaWidth, setaCimaHeight, setaCima);
  display.display();
  display.resetOrientation();
}

void desenhaSetaBaixo(char o) {
  display.resetDisplay();
  display.resetOrientation();
  if (o == 'd') display.flipScreenVertically();
  display.drawXbm((128 - setaBaixoWidth) / 2 , 0 , setaBaixoWidth, setaBaixoHeight, setaBaixo);
  display.display();
  display.resetOrientation();
}

void setup() {
  // Inverte os bytes para correta visualizacao do mapa de bits
  
  for (int i = 0; i < setaHorizontalWidth * setaHorizontalHeight / 8 ; i++) {
    setaHorizontal[i] = flipByte(setaHorizontal[i]);
  }
  for (int i = 0; i < setaVerticalWidth * setaVerticalHeight / 8 ; i++) {
    setaVertical[i] = flipByte(setaVertical[i]);
  }
  for (int i = 0; i < setaBaixoWidth * setaBaixoHeight / 8 ; i++) {
    setaBaixo[i] = flipByte(setaBaixo[i]);
  }
  for (int i = 0; i < setaCimaWidth * setaCimaHeight / 8 ; i++) {
    setaCima[i] = flipByte(setaCima[i]);
  }
  display.init();

}

void loop() {
  // Desenha setas em intervalos regulares
  int tempo = 10000;
  desenhaSetaHorizontal('d');
  delay(tempo);
  //desenhaSetaBaixo('d');
  //delay(tempo);
  //desenhaSetaVertical('b');
  //delay(tempo);
  //desenhaSetaBaixo('e');
  //delay(tempo);
  desenhaSetaHorizontal('e');
  delay(tempo);
  //desenhaSetaCima('e');
  //delay(tempo);
  //desenhaSetaVertical('c');
  //delay(tempo);
  //desenhaSetaCima('d');
  //delay(tempo);
}
