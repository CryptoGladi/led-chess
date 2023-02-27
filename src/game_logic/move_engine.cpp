#include "game_logic/move_engine.h"

using namespace utilities;

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
  ss << "PrintStatusMove: ";

  if (is_successful)
    ss << "Successful";
  else
    ss << "Error = " << status.error;

  ss << ssEndl;
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

  ss << "Done detail::MoveEngine::move" << ssEndl;
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

  ss << "all_possible_moves.size() = " << all_possible_moves.size() << ssEndl;

  auto index = all_possible_moves.find(
      Coordinate{.height = from_height, .width = from_width},
      [](Coordinate& a, Coordinate& b) -> bool {
        return a.height == b.height && a.width == b.width;
      });

  return !(index == -1);
}

detail::coordinates_t detail::MoveEngine::get_all_possible_moves() noexcept {
  coordinates_t result;
  auto currect_figure =
      this->matrix.get_figure(this->to_height, this->to_width);

  //if (currect_figure.is_queen || currect_figure.type == FBlack)
  //  get_possible_moves(+1, -1, result);

  //if (currect_figure.is_queen || currect_figure.type == FBlack)
  //  get_possible_moves(+1, +1, result);

  //if (currect_figure.is_queen || currect_figure.type == FWhite)
  //  get_possible_moves(-1, -1, result);

  if (currect_figure.is_queen || currect_figure.type == FWhite)
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
    if ((last_coordinate.height == -1 ||
         last_coordinate.height == HEIGHT_MATRIX + 1) ||
        (last_coordinate.width == -1 || last_coordinate.width == WIDTH_MATRIX + 1)) {
      // TODO Переработать условия колизии! (неверно last_coordinate.width <
      // abs(change_width))

      ss << "done break!" << ssEndl;

      ss << "info:" << ssEndl;
      ss << "change_height = " << change_height << ssEndl;
      ss << "change_width = " << change_width << ssEndl;
      ss << "last_coordinate.height = " << last_coordinate.height << ssEndl;
      ss << "last_coordinate.width = " << last_coordinate.width << ssEndl;

      break;
    }

    uint8_t new_height = last_coordinate.height + change_height;
    uint8_t new_width = last_coordinate.width + change_width;
    auto new_coordinate = Coordinate{.height = new_height, .width = new_width};

    last_coordinate = new_coordinate;

    ss << "new coordinate: height=" << new_height << "; width=" << new_width
       << ";" << ssEndl;

    moves.insertBack(&new_coordinate);
    ++i;
  }

  ss << "moves for one = " << moves.size() << ssEndl;
}