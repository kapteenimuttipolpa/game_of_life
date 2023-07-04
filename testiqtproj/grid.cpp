#include "grid.h"
#include "patterns.h"
#include "mainwindow.h"
#include <cstddef>
#include <iostream>
#include <vector>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QApplication>

/**
 * @brief print_grid
 * prints the current state of grid
 * @param grid
 */
void print_grid(const Grid &grid, QGraphicsView* grid_view, QGraphicsScene* scene) {
    const int cell_size = 20;
    const int spacing = 2;

    for (size_t row = 0; row < grid.size(); ++row) {
        for (size_t col = 0; col < grid[row].size(); ++col) {
            QColor color = grid[row][col].color;
            QGraphicsRectItem* rect_item = scene->addRect(col * (cell_size + spacing),
                                                         row * (cell_size + spacing),
                                                         cell_size,
                                                         cell_size,
                                                         QPen(Qt::NoPen),
                                                         QBrush(color));
        }
    }

    int scene_width = grid[0].size() * (cell_size + spacing);
    int scene_height = grid.size() * (cell_size + spacing);
    scene->setSceneRect(0, 0, scene_width, scene_height);

    grid_view->setScene(scene);
}

// bool validate_grid_size(int height, int width, Pattern start_pattern) {}

/*
**  Initializes grid with given size and selected pattern
*/
Grid init_grid(int height, int width, Pattern start_pattern) {
  int start_row = (height / 2) - (start_pattern.height / 2);
  int start_col = (width / 2) - (start_pattern.width / 2);

  Grid grid{};
  for (int row = 0; row < height; ++row) {
    std::vector<Cell> new_row;
    for (int col = 0; col < width; ++col) {
      Cell new_cell{};
      new_row.push_back(new_cell);

    }
    grid.push_back(new_row);
  }
  for (Coord c : start_pattern.coords) {
    grid[start_row + c.row][start_col + c.col].current_state = ALIVE;
    grid[start_row + c.row][start_col + c.col].next_state = ALIVE;
    grid[start_row + c.row][start_col + c.col].color = Qt::black;
  }

  return grid;
}

/**
 * @brief get_alive_neighbour
 * gets the count of alive neighbors
 * adjacent to current Cell
 *
 * @param grid
 * @param row
 * @param column
 * @return int
 */
int get_alive_neighbour(const Grid &grid, const int row, const int column) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    for (int x = row - 1; x <= row + 1; x++) {
        for (int y = column - 1; y <= column + 1; y++) {
            if (x == row && y == column) {
                continue; // Skip the center cell (current cell)
            }

            if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y].current_state == ALIVE) {
                count++;
            }
        }
    }

    return count;
}

/**
 * @brief next_generation
 * Changes the state of cells if needed.
 * @param grid
 */
void next_generation(Grid &grid) {
  for (size_t row = 0; row < grid.size(); row++) {
    for (size_t col = 0; col < grid.at(row).size(); col++) {
      int neighbors_count = get_alive_neighbour(grid, row, col);

      if (neighbors_count == 3) {
        grid.at(row).at(col).next_state = ALIVE;
      }

      else if ((neighbors_count <= 1 || neighbors_count >= 4) &&
               (grid.at(row).at(col).current_state == ALIVE)) {
        grid.at(row).at(col).next_state = DEAD;
      }
    }
  }
}
/**
 * @brief update_grid
 * loops the grid and updates
 * every columns state to next state
 * @param grid
 */
bool update_grid(Grid &grid) {
  bool is_changed = false;
  for (auto &row : grid) {
    for (auto &col : row) {
      if (col.current_state != col.next_state) {
        is_changed = true;
      }

      col.current_state = col.next_state;
      col.color = (col.current_state == 1) ? Qt::black : Qt::white;
    }
  }
  return is_changed;
}
