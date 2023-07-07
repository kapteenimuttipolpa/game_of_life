#ifndef GRID_H
#define GRID_H
#include "patterns.h"
#include <vector>
#include <QColor>
#include <QGraphicsView>
#include <QGraphicsScene>

constexpr static int ALIVE = 1;
constexpr static int DEAD = 0;
constexpr int cell_size = 4;
constexpr int spacing = 1;
struct Cell {
  int current_state = DEAD;
};

using Grid = std::vector<std::vector<Cell>>;
using CoordVect = std::vector<Coord>;

Grid init_grid(CoordVect& alive_cells, int height, int width, Pattern& start_pattern);
void print_grid(const CoordVect& alive_cells, QGraphicsView* grid_view, QGraphicsScene* scene);
int get_alive_neighbour(const Grid &grid, CoordVect& alive_cells, const int row, const int column);
bool next_generation(Grid &grid, CoordVect& alive_cells);
void update_grid(Grid &grid, CoordVect& alive_cells);
bool coord_found(const std::vector<Coord>& coords, const Coord& targetCoord);
void display_counters();
#endif // !GRID_H
