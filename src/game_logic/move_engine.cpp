#include "game_logic/move_engine.h"

StatusMove detail::ReturnResultMove(ResultForMove result,
                                    bool& is_successful) noexcept {
  is_successful = true;
  StatusMove status;
  status.result = result;

  return status;
}

StatusMove detail::ReturnErrorMove(TypeErrorForMove error,
                                   bool& is_successful) noexcept {
  is_successful = false;
  StatusMove status;
  status.error = error;

  return status;
}

void detail::PrintStatusMove(StatusMove status, bool is_successful) noexcept {
  Serial.print("PrintStatusMove: ");

  if (is_successful) {
    Serial.print("Successful");
  } else {
    Serial.print("Error = ");

    if (status.error == FigureGoToNotUsed) {
      Serial.print("FigureGoToNotUsed");
    } else if (status.error == FigureNotObeyThePlayer) {
      Serial.print("FigureNotObeyThePlayer");
    }
  }

  Serial.println("");
}

StatusMove detail::MoveEngine::move() noexcept {
  if (!check_buffer_overflow())
    return ReturnErrorMove(BufferOverflow, this->is_successful);

  if (!check_not_used_matrix())
    return ReturnErrorMove(FigureGoToNotUsed, this->is_successful);

  auto new_figure = this->matrix.figures[to_height][to_width];
  this->matrix.figures[to_height][to_width] =
      Figure{.type = Empty, .is_queen = false};
  this->matrix.figures[from_height][from_width] = new_figure;

  Serial.println("Done detail::MoveEngine::move");
  bool found_new_queen = this->matrix.update_queen();
  return ReturnResultMove(ResultForMove{.found_new_queen = found_new_queen},
                          this->is_successful);
}

bool detail::MoveEngine::check_buffer_overflow() noexcept {
  if (this->to_height > HEIGHT_MATRIX || this->from_height > HEIGHT_MATRIX)
    return false;
  if (this->to_width > WIDTH_MATRIX || this->from_width > WIDTH_MATRIX)
    return false;

  return true;
}

bool detail::MoveEngine::check_not_used_matrix() noexcept {
  if (this->matrix.figures[this->from_height][this->from_width].type == NotUsed)
    return false;

  return true;
}

bool detail::MoveEngine::check_possibility() noexcept {
  auto figure_for_check = matrix.figures[this->to_height][this->to_width];
  uint8_t maximum_stroke_length =
      figure_for_check.is_queen ? macro::MAX(HEIGHT_MATRIX, WIDTH_MATRIX) : 1;

  // TODO сделать рейдинг линий (чтобы проверять возможность хода) и узнать
  // расстояние от начального положение нашей фигуры.
  // if ((this->to_height - 1) == this->from_height || ((this->to_height - 1) ==
  // this->from_height))

  return true;
}