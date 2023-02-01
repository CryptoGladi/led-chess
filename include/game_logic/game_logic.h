#pragma once

#include <Arduino.h>
#include "detail.h"
#include "matrix_figure.h"

namespace game_logic {

using namespace game_logic::matrix_figure;

/// @brief Вся логика игры в шашках
class GameLogic {
 public:
  /// @brief Констуктор
  GameLogic();

  matrix_figure::MatrixFigure& GetMatrix() noexcept;

 private:
  matrix_figure::MatrixFigure matrix;
};
}  // namespace game_logic