#pragma once

#include <Arduino.h>
#include "detail.h"
#include "global.h"

/// @brief Типы фигур в шашек
enum TypeFigure : uint8_t {
  /// @brief Белая фигура
  FWhite,

  /// @brief Чёрная фигура
  FBlack,

  /// @brief Пустая ячейка
  Empty,

  /// @brief Это ячейка вообще не используется в игре
  NotUsed,
};

struct Figure {
  TypeFigure get_opposite() noexcept;

  /// @brief Тип нашей фигуры
  TypeFigure type;

  /// @brief Фигура королева?
  bool is_queen = false;
};

/// @brief Матрица шашек
struct MatrixFigure {
  /// @brief Конструктор, который везде ставит `Figure::NotUsed`
  MatrixFigure() {
    for (auto h = 0; h < detail::HEIGHT_MATRIX; ++h)
      for (auto w = 0; w < detail::WIDTH_MATRIX; ++w)
        this->figures[h][w] = Figure{.type = NotUsed};
  }

  /// @brief Напечать матрицу/figures в Serial
  void print() noexcept;

  /// @brief Обновить все королевы
  /// @warning Делать так каждый ход! Иначе королева может не появиться!
  /// @return Хотя бы одна НОВАЯ королева найдена?
  bool update_queen() noexcept;

  Figure& get_figure(uint8_t height, uint8_t width) noexcept;

  // @brief Сама наша матрица
  Figure figures[detail::HEIGHT_MATRIX][detail::WIDTH_MATRIX];

 private:
  /// @brief Установить статус королевы по высоте матрицы и типы нужной фигуры
  /// @param height Нужная высота матрицы для изменения
  /// @param type_figure Нужный тип фигуры для статуса королевы
  /// @return Хотя бы одна НОВАЯ королева найдена?
  bool set_queen_in_layer(uint8_t height, TypeFigure type_figure) noexcept;
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
                                TypeFigure type_figure) noexcept;
}  // namespace detail

/// @brief Получить уже генерированный (генерация происходит во время
/// компиляции) шашки
/// @return Сами наша матрица фигур. Типо вот так:
///
/// W - белые
/// B - Чёрные
/// E - пустые (использовать можно!)
/// N - их нельзя использовать
/// ! - фигура королева
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
MatrixFigure GetGeneratedMatrixFigure() noexcept;