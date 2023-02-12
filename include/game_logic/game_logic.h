#pragma once

#include <Arduino.h>
#include "detail.h"
#include "matrix_figure.h"
#include "move_engine.h"

/// @brief Тип игрок
enum TypePlayer : uint8_t {
  /// @brief Сейчас ходят белые
  NWhite,

  /// @brief Сейчас ходят чёрные
  NBlack,
};

/// @brief Игрок
struct Player {
  explicit Player(TypePlayer type) : type(type){};

  /// @brief Изменить игрока на противоложный
  void change() noexcept;

  /// @brief Cам тип игрока
  TypePlayer type;
};

/// @brief Вся логика игры в шашках
class GameLogic {
 public:
  /// @brief Констуктор
  GameLogic();

  /// @brief Получить матрицу фигур
  MatrixFigure& get_matrix() noexcept;

  /// @brief Совершить ход
  /// @param to_height Высота фигуры в матрице КОТОРАЯ БУДЕТ ХОДИТЬ
  /// @param to_width Ширина фигуры в матрице КОТОРАЯ БУДЕТ ХОДИТЬ
  /// @param from_height Высота фигуры в матрице НА КОТОРОЙ ОНА ДОЛЖНА БЫТЬ
  /// @param from_width Ширина фигуры в матрице НА КОТОРОЙ ОНА ДОЛЖНА БЫТЬ
  /// @param is_successful Всё совершилось успешно?
  /// @return Статус
  StatusMove move(uint8_t to_height,
                  uint8_t to_width,
                  uint8_t from_height,
                  uint8_t from_width,
                  bool& is_successful) noexcept;

  /// @brief Кто сейчас делает ход?
  Player get_who_make_next_move() noexcept;

 private:
  /// @brief Матрица
  MatrixFigure matrix;

  /// @brief Текущий игрок
  Player currect_player = Player(TypePlayer::NWhite);
};