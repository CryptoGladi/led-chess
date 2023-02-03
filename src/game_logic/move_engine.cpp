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

    if (status.error == FigureGoesOutOfBounds) {
      Serial.print("FigureGoesOutOfBounds");
    } else if (status.error == FigureNotObeyThePlayer) {
      Serial.print("FigureNotObeyThePlayer");
    }
  }

  Serial.println("");
}

StatusMove detail::MoveEngine::move() noexcept {
  if (!check_not_used_matrix())
    return ReturnErrorMove(TypeErrorForMove::FigureGoesOutOfBounds,
                           this->is_successful);

  auto new_figure = this->matrix.figures[to_height][to_width];
  this->matrix.figures[to_height][to_width] =
      Figure{.type = Empty, .is_queen = false};
  this->matrix.figures[from_height][from_width] = new_figure;

  Serial.println("Done detail::MoveEngine::move");
  bool found_new_queen = this->matrix.update_queen();
  return ReturnResultMove(ResultForMove{.found_new_queen = found_new_queen},
                          this->is_successful);
}

bool detail::MoveEngine::check_not_used_matrix() noexcept {
  if (this->matrix.figures[this->from_height][this->from_width].type == NotUsed)
    return false;

  return true;
}