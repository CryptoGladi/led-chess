#include "game_logic/game_logic.h"

void Player::change() noexcept {
  if (this->type == NWhite)
    this->type = NBlack;
  else if (this->type == NBlack)
    this->type = NWhite;
}

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
  }
  else {
    Serial.print("Error");
  }

  Serial.printf(" ");
}

GameLogic::GameLogic() {
  this->matrix = GetGeneratedMatrixFigure();
}

MatrixFigure& GameLogic::get_matrix() noexcept {
  return this->matrix;
}

StatusMove GameLogic::move(uint8_t to_height, uint8_t to_width, uint8_t from_height, uint8_t from_width,
                           bool& is_successful) noexcept {
  auto type_figure = this->matrix.figures[to_height][to_width].type;
  if ((type_figure != FWhite && this->player.type == NWhite) ||
      (type_figure != FBlack && this->player.type == NBlack))
      return detail::ReturnErrorMove(FigureNotObeyThePlayer, is_successful);

  // TODO Сам движок изменений
  this->matrix.figures[to_height][to_width].type = FBlack; 

  bool found_new_queen = this->matrix.update_queen();

  this->player.change();
  return detail::ReturnResultMove(
      ResultForMove{.found_new_queen = found_new_queen}, is_successful);
}

Player GameLogic::get_who_make_next_move() noexcept {
  return this->player;
}