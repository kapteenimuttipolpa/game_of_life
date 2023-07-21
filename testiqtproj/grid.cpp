#include "grid.h"
#include "patterns.h"
#include <cstddef>
#include <iostream>
#include <vector>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QApplication>
#include <unordered_set>


/**
 * @brief print_grid
 * prints the current state of grid
 * @param grid
 */
void print_grid(const CoordVect& alive_cells, QGraphicsView* grid_view, QGraphicsScene* scene) {
    scene->setForegroundBrush(Qt::NoBrush); // sets the bg color as white/nothing
    // so we dont need to print empty cells all the time

    for(const Coord& c : alive_cells){ // loop coords in active_grid and draw squares
        scene->addRect(c.col * (cell_size + spacing),
                       c.row * (cell_size + spacing),
                       cell_size,
                       cell_size,
                       QPen(Qt::NoPen),
                       QBrush(Qt::black));
    }
    grid_view->setScene(scene); // set the current scene to what we drew
}

/*
**  Initializes grid with given size and selected pattern
*/
Grid init_grid(CoordVect& alive_cells, int height, int width, Pattern& start_pattern) {
  int start_row = (height / 2) - (start_pattern.height / 2);
  int start_col = (width / 2) - (start_pattern.width / 2);
  //Grid grid(height, std::vector<bool>(width));
  Grid grid(height, std::vector<bool>(width));
  for (Coord c : start_pattern.coords) { // loop the start pattern coords
      // and push them to active grid and set the cells at coord ALIVE
    alive_cells.push_back({start_row + c.row, start_col + c.col});
    grid[start_row + c.row][start_col + c.col].flip(); // flip to alive
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
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    //loops trough the neighbors of given cell (row , column)
    for (int x = row - 1; x <= row + 1; x++) {
        for (int y = column - 1; y <= column + 1; y++) {
            if (x == row && y == column) {
                continue; // Skip the center cell (current cell)
            }

            if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == ALIVE) { // flip to alive
                count++; //Check boundaries of grid and if neighbor is alive
            }
        }
    }
    return count;
}

/**
 * @brief coord_found
 * loops coordinates vector and checks if coord is found
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
bool next_generation(Grid &grid, CoordVect& alive_cells) {
  CoordVect temp_grid {};
  bool is_changed = false;
  const int g_size = static_cast<int>(grid.size());
  const int row_size = static_cast<int>(grid[0].size());

  for (Coord c : alive_cells) { // O(8N)
    for (int x = c.row - 1; x <= c.row + 1; x++) { // loop the neighbors of alive cells
      for (int y = c.col - 1; y <= c.col + 1; y++) {
        if (x < 0 || x >= g_size|| y < 0 || y >= row_size)
          continue;


        if (coord_found(temp_grid, {x, y})) // check if current coord is already in temp grid
            continue; //O(N)
        int neighbors_count = get_alive_neighbour(grid, x, y); // if not, get its neighbors O(8N)
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
  //Checks if terminal state was reached
  if (alive_cells.size() != temp_grid.size())
      is_changed = true;
    else
    {
      for (size_t i = 0; i < alive_cells.size(); i++)
      {
        if (alive_cells[i].col == temp_grid[i].col && alive_cells[i].row == temp_grid[i].row)
          continue;
        is_changed = true;
        break;
      }
    }
    for(auto& c : alive_cells){
        grid[c.row][c.col].flip(); // flip to dead
    }
    alive_cells = temp_grid;
    return is_changed;
}
/**
 * @brief update_grid
 * loops the grid and updates
 * every columns state to next state
 * @param grid
 */
void update_grid(Grid &grid, CoordVect& alive_cells) {

  for (Coord c : alive_cells) {
    grid[c.row][c.col].flip(); // flip to alive

  }
}

