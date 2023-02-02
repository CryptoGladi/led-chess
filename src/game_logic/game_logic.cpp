#include "game_logic/game_logic.h"

void Player::change() noexcept {
  if (this->type == NWhite)
    this->type = NBlack;
  else if (this->type == NBlack)
    this->type = NWhite;
}

GameLogic::GameLogic() {
  this->matrix = GetGeneratedMatrixFigure();
}

MatrixFigure& GameLogic::get_matrix() noexcept {
  return this->matrix;
}

StatusMove GameLogic::move(uint8_t height, uint8_t width, bool& is_successful) noexcept {
  // TODO Проверить на очередь хода

  bool found_new_queen = this->matrix.update_queen();

  this->who_make_next_move.change();
  StatusMove result;
  result.result_info = ResultForMove { .found_new_queen = found_new_queen };
  return result;
}

Player GameLogic::get_who_make_next_move() noexcept {
  return this->who_make_next_move;
}