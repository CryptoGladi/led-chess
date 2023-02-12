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

StatusMove GameLogic::move(uint8_t to_height,
                           uint8_t to_width,
                           uint8_t from_height,
                           uint8_t from_width,
                           bool& is_successful) noexcept {
  auto type_figure = this->matrix.figures[to_height][to_width].type;
  if ((type_figure != FWhite && this->currect_player.type == NWhite) ||
      (type_figure != FBlack && this->currect_player.type == NBlack))
    return detail::ReturnErrorMove(FigureNotObeyThePlayer, is_successful);

  auto engine = detail::MoveEngine(this->matrix, to_height, to_width,
                                   from_height, from_width, is_successful);
  auto status = engine.move();

  this->currect_player.change();
  return status;
}

Player GameLogic::get_who_make_next_move() noexcept {
  return this->currect_player;
}