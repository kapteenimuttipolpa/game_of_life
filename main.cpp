#include "./includes/grid.h"
#include "./includes/patterns.h"
#include <iostream>

int main() {
  std::vector<std::vector<Cell>> grid = init_grid(3, 3, blinker);
  print_grid(grid);
  next_generation(grid);
  update_grid(grid);
  print_grid(grid);

  return 0;
}