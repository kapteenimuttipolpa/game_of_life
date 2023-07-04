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
  int next_state = DEAD;
  QColor color = Qt::white;
  QGraphicsRectItem* rectItem = nullptr;
};

using Grid = std::vector<std::vector<Cell>>;

Grid init_grid(int height, int width, Pattern start_pattern);
void print_grid(const Grid &grid, QGraphicsView* grid_view, QGraphicsScene* scene);
int get_alive_neighbour(const Grid &grid, const int row, const int column);
void next_generation(Grid &grid);
bool update_grid(Grid &grid);

#endif // !GRID_H
