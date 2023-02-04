#pragma once

#include "macro.h"
#include "matrix_figure.h"

/// @brief Тип ошибки при ходе
enum TypeErrorForMove : uint8_t {
  /// @brief Фигура не подчиниется игроку. Значит сейчас ходит другой игрок!
  /// @warning Реализация этой ошибки только в game_logic.cpp
  FigureNotObeyThePlayer,

  /// @brief Фигура захотела пойти в неиспользуемую клетку
  FigureGoToNotUsed,

  /// @brief
  BufferOverflow
};

/// @brief Результат (всё успешно) при ходе
struct ResultForMove {
  /// @brief Была найдена новая королева
  bool found_new_queen;
};

/// @brief Статус хода
union StatusMove {
  /// @brief Тип ошибки
  TypeErrorForMove error;

  /// @brief Результат (если нет ошибок)
  ResultForMove result;
};

namespace detail {
StatusMove ReturnResultMove(ResultForMove result, bool& is_successful) noexcept;

StatusMove ReturnErrorMove(TypeErrorForMove error,
                           bool& is_successful) noexcept;

void PrintStatusMove(StatusMove status_move, bool is_successful) noexcept;

struct MoveEngine {
  MoveEngine(MatrixFigure& matrix,
             uint8_t to_height,
             uint8_t to_width,
             uint8_t from_height,
             uint8_t from_width,
             bool& is_successful)
      : matrix(matrix),
        to_height(to_height),
        to_width(to_width),
        from_height(from_height),
        from_width(from_width),
        is_successful(is_successful){};

  StatusMove move() noexcept;

 private:
  bool check_buffer_overflow() noexcept;

  bool check_not_used_matrix() noexcept;

  bool check_possibility() noexcept;

  MatrixFigure& matrix;
  uint8_t to_height;
  uint8_t to_width;
  uint8_t from_height;
  uint8_t from_width;
  bool& is_successful;
};
}  // namespace detail