#ifndef GRID_H
#define GRID_H

constexpr static int ALIVE = 1;
constexpr static int DEAD = 0;

struct Cell {
  int current_state{DEAD};
  int next_state{DEAD};
};

#endif // !GRID_H