#pragma once

#include <Arduino.h>
#include "detail.h"

namespace game_logic {
namespace matrix_figure {
using namespace game_logic::detail::constant;

/// @brief Типы фигур в шашек
enum Figure : uint8_t {
  /// @brief Белая фигура
  White,

  /// @brief Чёрная фигура
  Black,

  /// @brief Пустая ячейка
  Empty,

  /// @brief Это ячейка вообще не используется в игре
  NotUsed,
};

/// @brief Матрица шашек
struct MatrixFigure {
  /// @brief Конструктор, который везде ставит `Figure::NotUsed`
  MatrixFigure() : figures{Figure::NotUsed} {
    for (auto h = 0; h < HEIGHT_MATRIX; ++h)
      for (auto w = 0; w < WIDTH_MATRIX; ++w)
        this->figures[h][w] = Figure::NotUsed;
  }

  /// @brief Напечать их в Serial
  void Print() noexcept;

  /// @brief Сама наша матрица
  Figure figures[HEIGHT_MATRIX][WIDTH_MATRIX];
};

namespace detail {
/// @brief Вставить один слой в матрице
/// @param is_even Номер ячейки должны быть чётными
/// @param height Координата высоты матрицы
/// @param type_figure Сам тип фигуры для вставки
/// @warning Вам нужно использовать его вместе с объектом (из-за this)
void InsertLayerForMatrixFigure(MatrixFigure& matrix,
                                bool is_even,
                                uint8_t height,
                                Figure type_figure) noexcept;
}  // namespace detail

/// @brief Получить уже генерированный (генерация происходит во время
/// компиляции) шашки
/// @return Сами наша матрица фигур. Типо вот так:
///
/// W - белые
/// B - Чёрные
/// E - пустые
/// N - их нельзя использовать
///
/// N B N B N B N B
/// B N B N B N B N
/// N B N B N B N B
/// E N E N E N E N
/// N E N E N E N E
/// W N W N W N W N
/// N W N W N W N W
/// W N W N W N W N
///
/// В картике https://shashki-online.com/images/game_board_64_populated.png
MatrixFigure GetGeneratedMatrixFigure();
};  // namespace matrix_figure
}  // namespace game_logic