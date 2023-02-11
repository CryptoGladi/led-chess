#include <Arduino.h>
#include <ArduinoLog.h>
#include "game_logic/game_logic.h"

void setup() {
  Serial.begin(921600);
  Log.begin(LOG_LEVEL_TRACE, &Serial);
}

void loop() {
  auto game_logic = GameLogic();

  delay(2313);

  bool is_successful = false;
  auto status = game_logic.move(7, 0, 0, 3, is_successful);

  detail::PrintStatusMove(status, is_successful);
  game_logic.get_matrix().print();
}