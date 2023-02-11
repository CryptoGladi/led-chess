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
  Log.info("PrintStatusMove: ");

  if (is_successful) {
    Log.info("Successful");
  } else {
    Log.info("Error = ");

    if (status.error == FigureGoToNotUsed) {
      Log.info("FigureGoToNotUsed");
    } else if (status.error == FigureNotObeyThePlayer) {
      Log.info("FigureNotObeyThePlayer");
    }
  }

  Log.infoln("");
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

  Log.infoln("Done detail::MoveEngine::move");
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

  auto index = all_possible_moves.find(
      Coordinate{.height = from_height, .width = from_width},
      [](Coordinate& a, Coordinate& b) -> bool {
        return a.height == b.height && a.width == b.width;
      });

  return index != -1;
}

detail::coordinates_t detail::MoveEngine::get_all_possible_moves() noexcept {
  coordinates_t result;
  auto currect_figure =
      this->matrix.get_figure(this->to_height, this->to_width);

  if (currect_figure.is_queen || currect_figure.type == FWhite)
    get_possible_moves(+1, -1, result);

  if (currect_figure.is_queen || currect_figure.type == FWhite)
    get_possible_moves(+1, +1, result);

  if (currect_figure.is_queen || currect_figure.type == FBlack)
    get_possible_moves(-1, -1, result);

  if (currect_figure.is_queen || currect_figure.type == FBlack)
    get_possible_moves(-1, +1, result);

  return result;
}

void detail::MoveEngine::get_possible_moves(int16_t change_height,
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
        last_coordinate.width < abs(change_width) ||
        maximum_stroke_length == i ||
        matrix.get_figure(last_coordinate.height, last_coordinate.width).type !=
            Empty)
      break;

    uint8_t new_height = last_coordinate.height + change_height;
    uint8_t new_width = last_coordinate.width + change_width;
    auto new_coordinate = Coordinate{.height = new_height, .width = new_width};

    last_coordinate = new_coordinate;
    moves.insertBack(&new_coordinate);
    ++i;
  }
}