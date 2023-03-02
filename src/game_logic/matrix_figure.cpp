#include "game_logic/matrix_figure.h"

using namespace game_logic;

void matrix_figure::MatrixFigure::Print() noexcept {
  Serial.println("matrix_figure::MatrixFigure::Print");

  for (int h = 0; h < HEIGHT_MATRIX; h++) {
    for (int w = 0; h < WIDTH_MATRIX; h++) {
      switch (this->figures[h][w]) {
        case White:
          Serial.print("W");
          break;
        case Black:
          Serial.print("B");
          break;
        case Empty:
          Serial.print("E");
          break;
        case NotUsed:
          Serial.print("N");
          break;
      }
    }

    Serial.println("height: " + static_cast<char>(h));
  }
}