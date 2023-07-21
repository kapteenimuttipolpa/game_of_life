#include "./includes/grid.h"
#include "./includes/patterns.h"
#include "./includes/utils.h"
#include <chrono>
#include <iostream>
#include <thread>

int simulate(Grid grid) {
  int generations = 0;
  bool changed = false;
  int speed = SLOW;
  while (true) {
    print_grid(grid);
    next_generation(grid);
    changed = update_grid(grid);
    if (!changed) {
      std::cout << "Game over!\n";
      return generations;
    }
    generations++;
    sleep(speed);
  }
}

int main() {
  std::vector<std::vector<Cell>> grid = init_grid(3, 3, block);

  while (true) {
    int result = simulate(grid);

    if (result == 0)
      break;
    else {
      std::cout << "\nTotal generations: " << result << '\n';
      break;
    }
  }

  return 0;
}