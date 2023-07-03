#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../includes/grid.h"
#include "../includes/patterns.h"

Grid grid_block{};

TEST_CASE("Function init_grid") {
  grid_block = init_grid(3, 3, block);

  SUBCASE("Size of grid") {
    CHECK(grid_block.size() == 3);
    CHECK(grid_block[0].size() == 3);
  }
}

TEST_CASE("Function next_generation") {
  SUBCASE("Test block") {
    grid_block = init_grid(4, 4, block);
    next_generation(grid_block);
    CHECK(grid_block[1][1].next_state == 1);
    CHECK(grid_block[1][2].next_state == 1);
    CHECK(grid_block[2][1].next_state == 1);
    CHECK(grid_block[2][2].next_state == 1);
    CHECK(grid_block[0][0].next_state == 0);
    CHECK(grid_block[3][3].next_state == 0);
  }
  SUBCASE("Test blinker") {
    Grid grid_blinker = init_grid(3, 3, blinker);
    next_generation(grid_blinker);
    CHECK(grid_blinker[1][1].next_state == 1);
  }
}

TEST_CASE("Function get_alive_neighbors") {

  SUBCASE("Test block") {
    grid_block = init_grid(4, 4, block);
    CHECK(get_alive_neighbour(grid_block, 0, 0) == 1);
    CHECK(get_alive_neighbour(grid_block, 0, 1) == 2);
    CHECK(get_alive_neighbour(grid_block, 1, 1) == 3);
    CHECK(get_alive_neighbour(grid_block, 3, 3) == 1);
    grid_block = init_grid(3, 3, blinker);
    CHECK(get_alive_neighbour(grid_block, 1, 1) == 2);
    CHECK(get_alive_neighbour(grid_block, 0, 1) == 3);
    CHECK(get_alive_neighbour(grid_block, 1, 1) == 2);
  }
}