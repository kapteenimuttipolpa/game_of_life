#ifndef GRID_H
#define GRID_H
#include "patterns.h"
#include <vector>
#include <QColor>
#include <QGraphicsView>
#include <QGraphicsScene>

constexpr static int ALIVE = 1;
constexpr static int DEAD = 0;
struct Cell {
  int current_state = DEAD;
};

using Grid = std::vector<std::vector<Cell>>;
using Subgrid = std::vector<Coord>;

Grid init_grid(Subgrid& active_grid, int height, int width, Pattern& start_pattern);
void print_grid(const Grid &grid, QGraphicsView* grid_view, QGraphicsScene* scene);
int get_alive_neighbour(const Grid &grid, Subgrid& active_grid, const int row, const int column);
bool next_generation(Grid &grid, Subgrid& active_grid);
void update_grid(Grid &grid, Subgrid& active_grid);
bool coord_found(const std::vector<Coord>& coords, const Coord& targetCoord);
void display_counters();
#endif // !GRID_H
