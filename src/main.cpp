#include <Arduino.h>
#include "game_logic/game_logic.h"

void setup() {
  Serial.begin(921600);

  auto game_logic = game_logic::GameLogic();
  auto matrix = game_logic.GetMatrix();
}

void loop() {
  auto game_logic = game_logic::GameLogic();
  auto matrix = game_logic.GetMatrix();

  delay(2313);
  matrix.Print();
}