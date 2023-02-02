#include <Arduino.h>
#include "game_logic/game_logic.h"

void setup() {
  Serial.begin(921600);
}

void loop() {
  auto game_logic = GameLogic();
  auto matrix = game_logic.get_matrix();

  delay(2313);
  Serial.println("Без проверки королевы");
  matrix.print();

  Serial.println("С проверкой королевы");
  
  matrix.print();
}