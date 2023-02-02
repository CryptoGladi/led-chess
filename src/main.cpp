#include <Arduino.h>
#include "game_logic/game_logic.h"

void setup() {
  Serial.begin(921600);
}

void loop() {
  auto game_logic = GameLogic();

  delay(2313);
  //Serial.println("Без проверки королевы");
  //matrix.print();

  Serial.println("С проверкой королевы");
  bool is_successful = false;
  auto status = game_logic.move(7, 0, NULL, NULL, is_successful);

  if (status.result.found_new_queen) {
    Serial.println("Всё работает!");
  }
  else {
    Serial.println("Не работает!");
  }

  detail::PrintStatusMove(status, is_successful);
  game_logic.get_matrix().print();
}