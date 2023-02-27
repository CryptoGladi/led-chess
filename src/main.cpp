#include <Arduino.h>
#include <SmartSerial.hpp>
#include "game_logic/game_logic.h"

void setup() {
  Serial.begin(HUZZAH_MONITOR_SPEED);
}

void loop() {
  auto game_logic = GameLogic();

  delay(2313);

  game_logic.get_matrix().print();

  bool is_successful = false; // -1 +1
  auto status = game_logic.move(5, 0, 4, 1, is_successful);

  detail::PrintStatusMove(status, is_successful);
  game_logic.get_matrix().print();
}