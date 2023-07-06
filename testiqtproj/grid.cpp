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
    constexpr int cell_size = 4;
    constexpr int spacing = 1;

    for (size_t row = 0; row < grid.size(); ++row) {
        for (size_t col = 0; col < grid[row].size(); ++col) {
                QColor color = grid[row][col].current_state == 1 ? Qt::black : Qt::white;
                scene->addRect(col * (cell_size + spacing),
                               row * (cell_size + spacing),
                               cell_size,
                               cell_size,
                               QPen(Qt::NoPen),
                               QBrush(color));
        }
    }
    grid_view->setScene(scene);

}

// bool validate_grid_size(int height, int width, Pattern start_pattern) {}

/*
**  Initializes grid with given size and selected pattern
*/
Grid init_grid(Subgrid& active_grid, int height, int width, Pattern& start_pattern) {
  int start_row = (height / 2) - (start_pattern.height / 2);
  int start_col = (width / 2) - (start_pattern.width / 2);

  Grid grid{};
  for (int row = 0; row < height; ++row) {
    std::vector<Cell> new_row;
    for (int col = 0; col < width; ++col) {
      //Cell new_cell{};
        new_row.push_back({});
    }
    grid.push_back(new_row);
  }
  for (Coord c : start_pattern.coords) {
    active_grid.push_back({start_row + c.row, start_col + c.col});
    grid[start_row + c.row][start_col + c.col].current_state = ALIVE;
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
 * @brief coord_found
 * @param coords
 * @param targetCoord
 * @return
 */
bool coord_found(const std::vector<Coord>& coords, const Coord& targetCoord) {
  for (const Coord& coord : coords) {
    if (coord.row == targetCoord.row && coord.col == targetCoord.col) {
      return true;
    }
  }
  return false;
}

/**
 * @brief next_generation
 * Changes the state of cells if needed.
 * @param grid
 */
bool next_generation(Grid &grid, Subgrid& active_grid) {
  Subgrid temp_grid {};
  bool is_changed = false;
  for (Coord c : active_grid) {
    for (int x = c.row - 1; x <= c.row + 1; x++) { // loop the neightbors of alive cells
      for (int y = c.col - 1; y <= c.col + 1; y++) {
        if (x < 0 || static_cast<size_t>(x) >= grid.size() || y < 0 || static_cast<size_t>(y) >= grid[0].size())
          continue;
        if (coord_found(temp_grid, {x, y})) // check if current coord is already in temp grid
          continue;
        int neighbors_count = get_alive_neighbour(grid, x, y); // if not, get its neighbors
        if (neighbors_count == 3)
        {
          temp_grid.push_back({x, y});
        }
        else if (neighbors_count == 2 && x == c.row && y == c.col)
        {
          temp_grid.push_back({x, y});
        }
      }
    }
  }
  for (size_t i = 0; i < active_grid.size(); i++)
  {
    if (active_grid[i].col == temp_grid[i].col && active_grid[i].row == temp_grid[i].row)
      continue ;
    is_changed = true;
  }
  active_grid = temp_grid;
  return is_changed;
}
/**
 * @brief update_grid
 * loops the grid and updates
 * every columns state to next state
 * @param grid
 */
void update_grid(Grid &grid, Subgrid& active_grid) {
  for (auto& row : grid) {
    for (auto& col : row)
    {
      col.current_state = DEAD;
    }
  }
  for (Coord c : active_grid) {
    grid[c.row][c.col].current_state = ALIVE;
  }
}

