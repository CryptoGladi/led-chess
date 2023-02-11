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

  if (!check_possibility())
    return ReturnErrorMove(NoMovePossible, this->is_successful);

  auto new_figure = this->matrix.get_figure(to_height, to_width);
  this->matrix.get_figure(to_height, to_width) =
      Figure{.type = Empty, .is_queen = false};
  this->matrix.get_figure(from_height, from_width) = new_figure;

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
  if (this->matrix.get_figure(to_height, to_width).type == NotUsed)
    return false;

  if (this->matrix.get_figure(from_height, from_width).type == NotUsed)
    return false;

  return true;
}

bool detail::MoveEngine::check_possibility() noexcept {
  auto all_possible_moves = get_all_possible_moves();

  //if (all_possible_moves.find(Coordinate {.height = 1, .width = 1}, [a, n]){
  //  return true
  //}) {
  //}

  return true;
}

detail::coordinates_t detail::MoveEngine::get_all_possible_moves() noexcept {
  coordinates_t result;

  // TODO проверка на тип фигуры
  get_possible_moves(+1, -1, result);
  get_possible_moves(+1, +1, result);
  get_possible_moves(-1, -1, result);
  get_possible_moves(-1, +1, result);

  return result;
}

void detail::MoveEngine::get_possible_moves(
    int16_t change_height,
    int16_t change_width,
    coordinates_t& moves) noexcept {
  Coordinate last_coordinate = {.height = this->to_height,
                                .width = this->to_width};
  auto figure_for_check = matrix.get_figure(this->to_height, this->to_width);
  uint8_t maximum_stroke_length =
      figure_for_check.is_queen ? macro::MAX(HEIGHT_MATRIX, WIDTH_MATRIX) : 1;

  uint8_t i = 0;
  for (;;) {
    if (last_coordinate.height < abs(change_height) ||
        last_coordinate.width < abs(change_width) || maximum_stroke_length == i)
      break;

    uint8_t new_height = last_coordinate.height + change_height;
    uint8_t new_width = last_coordinate.width + change_width;
    auto new_coordinate = Coordinate{.height = new_height, .width = new_width};

    last_coordinate = new_coordinate;
    moves.insertBack(&new_coordinate);
    ++i;
  }
}