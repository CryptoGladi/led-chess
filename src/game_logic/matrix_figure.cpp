#include "game_logic/matrix_figure.h"

using namespace utilities;

TypeFigure Figure::get_opposite() noexcept {
  switch(this->type)
  {
  case FWhite:
    return FBlack;
  case FBlack:
    return FWhite;
  default:
    return this->type;
  }
}

void MatrixFigure::print() noexcept {
  ss << "matrix_figure::MatrixFigure::Print" << ssEndl;

  for (int h = 0; h < detail::HEIGHT_MATRIX; h++) {
    for (int w = 0; w < detail::WIDTH_MATRIX; w++) {
      switch (this->figures[h][w].type) {
        case FWhite:
          ss << "W";
          break;
        case FBlack:
          ss << "B";
          break;
        case Empty:
          ss << "E";
          break;
        case NotUsed:
          ss << "N";
          break;
      }

      ss << (this->figures[h][w].is_queen ? "! " : " ");
    }

    ss << ssEndl;
  }
}

bool MatrixFigure::update_queen() noexcept {
  bool is_changed_for_white = set_queen_in_layer(0, TypeFigure::FWhite);
  bool is_changed_for_black = set_queen_in_layer(7, TypeFigure::FBlack);

  return is_changed_for_white || is_changed_for_black;
}

Figure& MatrixFigure::get_figure(uint8_t height, uint8_t width) noexcept {
  return this->figures[height][width];
}

void detail::InsertLayerForMatrixFigure(MatrixFigure& matrix,
                                        bool is_even,
                                        uint8_t height,
                                        TypeFigure type_figure) noexcept {
  for (size_t w = 0; w < detail::WIDTH_MATRIX; ++w)
    if (!is_even && w % 2 != 0)
      matrix.figures[height][w].type = type_figure;
    else if (is_even && w % 2 == 0)
      matrix.figures[height][w].type = type_figure;
}

bool MatrixFigure::set_queen_in_layer(uint8_t height,
                                      TypeFigure type_figure) noexcept {
  bool is_changed = false;

  for (size_t w = 0; w < detail::WIDTH_MATRIX; ++w)
    if (this->figures[height][w].type == type_figure &&
        this->figures[height][w].is_queen == false) {
      this->figures[height][w].is_queen = true;
      is_changed = true;
    }

  return is_changed;
}

MatrixFigure GetGeneratedMatrixFigure() noexcept {
  MatrixFigure matrix_figure;

  detail::InsertLayerForMatrixFigure(matrix_figure, false, 0,
                                     TypeFigure::FBlack);
  detail::InsertLayerForMatrixFigure(matrix_figure, true, 1,
                                     TypeFigure::FBlack);
  detail::InsertLayerForMatrixFigure(matrix_figure, false, 2,
                                     TypeFigure::FBlack);

  detail::InsertLayerForMatrixFigure(matrix_figure, true, 3, TypeFigure::Empty);
  detail::InsertLayerForMatrixFigure(matrix_figure, false, 4,
                                     TypeFigure::Empty);

  detail::InsertLayerForMatrixFigure(matrix_figure, true, 5,
                                     TypeFigure::FWhite);
  detail::InsertLayerForMatrixFigure(matrix_figure, false, 6,
                                     TypeFigure::FWhite);
  detail::InsertLayerForMatrixFigure(matrix_figure, true, 7,
                                     TypeFigure::FWhite);

  return matrix_figure;
}
