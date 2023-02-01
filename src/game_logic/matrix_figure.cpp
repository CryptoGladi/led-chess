#include "game_logic/matrix_figure.h"

using namespace game_logic;
using namespace game_logic::matrix_figure;

void matrix_figure::MatrixFigure::Print() noexcept {
  Serial.println("matrix_figure::MatrixFigure::Print");

  for (int h = 0; h < HEIGHT_MATRIX; h++) {
    for (int w = 0; w < WIDTH_MATRIX; w++) {
      switch (this->figures[h][w]) {
        case White:
          Serial.print("W");
          break;
        case Black:
          Serial.print("B");
          break;
        case Empty:
          Serial.print("E");
          break;
        case NotUsed:
          Serial.print("N");
          break;
      }

      Serial.print(" ");
    }

    Serial.println("");
  }
}

void InsertLayerForMatrixFigure(MatrixFigure& matrix,
                                bool is_even,
                                uint8_t height,
                                Figure type_figure) noexcept {
  for (auto w = 0; w < WIDTH_MATRIX; ++w)
    if (!is_even && w % 2 != 0)
      matrix.figures[height][w] = type_figure;
    else if (is_even && w % 2 == 0)
      matrix.figures[height][w] = type_figure;
}

MatrixFigure game_logic::matrix_figure::GetGeneratedMatrixFigure() {
  MatrixFigure matrix_figure;

  InsertLayerForMatrixFigure(matrix_figure, false, 0, Figure::Black);
  InsertLayerForMatrixFigure(matrix_figure, true, 1, Figure::Black);
  InsertLayerForMatrixFigure(matrix_figure, false, 2, Figure::Black);

  InsertLayerForMatrixFigure(matrix_figure, true, 3, Figure::Empty);
  InsertLayerForMatrixFigure(matrix_figure, false, 4, Figure::Empty);

  InsertLayerForMatrixFigure(matrix_figure, true, 5, Figure::White);
  InsertLayerForMatrixFigure(matrix_figure, false, 6, Figure::White);
  InsertLayerForMatrixFigure(matrix_figure, true, 7, Figure::White);

  return matrix_figure;
}
