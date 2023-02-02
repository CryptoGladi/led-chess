#pragma once

#include <Arduino.h>
#include "detail.h"
#include "matrix_figure.h"

/// @brief Тип игрок
enum TypePlayer : uint8_t {
  /// @brief Сейчас ходят белые
  NWhite,

  /// @brief Сейчас ходят чёрные
  NBlack,
};

/// @brief Игрок
struct Player
{
  Player(TypePlayer type) : type(type) {};

  void change() noexcept;

  private:
  TypePlayer type;
};


/// @brief Тип ошибки при ходе
enum TypeErrorForMove : uint8_t {
  /// @brief Фигура не подчиниется игроку. Значит сейчас ходит другой игрок!
  FigureNotObeyThePlayer,
};

/// @brief Результат (всё успешно) при ходе
struct ResultForMove
{
  /// @brief Была найдена новая королева
  bool found_new_queen;
};

/// @brief Статус хода
union StatusMove
{
  /// @brief Тип ошибки
  TypeErrorForMove type_error;

  /// @brief Результат (если нет ошибок)
  ResultForMove result_info;
};


/// @brief Вся логика игры в шашках
class GameLogic {
 public:
  /// @brief Констуктор
  GameLogic();

  /// @brief Получить матрицу фигур
  MatrixFigure& get_matrix() noexcept;

  /// @brief Совершить ход
  /// @param height Высота фигуры в матрице
  /// @param width Ширина фигуры в матрице
  /// @param is_successful Всё совершилось успешно?
  /// @return Статус
  StatusMove move(uint8_t height, uint8_t width, bool& is_successful) noexcept;

  /// @brief Кто сейчас делает ход?
  Player get_who_make_next_move() noexcept;

 private:
  MatrixFigure matrix;
  Player who_make_next_move = Player(TypePlayer::NWhite);
};