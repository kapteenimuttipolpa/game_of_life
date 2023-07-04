#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../includes/grid.h"
#include "../includes/patterns.h"

TEST_CASE("Function init_grid") {
  SUBCASE("Size of grid") {
    Grid grid_block = init_grid(3, 3, block);
    CHECK(grid_block.size() == 3);
    CHECK(grid_block[0].size() == 3);
  }

  SUBCASE("Initialization of glider.") {
    Grid grid_glider = init_grid(5, 5, glider);
    CHECK(grid_glider.size() == 5);
    CHECK(grid_glider[0].size() == 5); // wuz poppin not much just wazzin

    CHECK(grid_glider[0][0].next_state == 0);
    CHECK(grid_glider[0][1].next_state == 0);
    CHECK(grid_glider[0][2].next_state == 0);
    CHECK(grid_glider[0][3].next_state == 0);
    CHECK(grid_glider[0][4].next_state == 0);

    CHECK(grid_glider[1][0].next_state == 0);
    CHECK(grid_glider[1][1].next_state == 0);
    CHECK(grid_glider[1][2].next_state == 1);
    CHECK(grid_glider[1][3].next_state == 0);
    CHECK(grid_glider[1][4].next_state == 0);

    CHECK(grid_glider[2][0].next_state == 0);
    CHECK(grid_glider[2][1].next_state == 0);
    CHECK(grid_glider[2][2].next_state == 0);
    CHECK(grid_glider[2][3].next_state == 1);
    CHECK(grid_glider[2][4].next_state == 0);

    CHECK(grid_glider[3][0].next_state == 0);
    CHECK(grid_glider[3][1].next_state == 1);
    CHECK(grid_glider[3][2].next_state == 1);
    CHECK(grid_glider[3][3].next_state == 1);
    CHECK(grid_glider[3][4].next_state == 0);

    CHECK(grid_glider[4][0].next_state == 0);
    CHECK(grid_glider[4][1].next_state == 0);
    CHECK(grid_glider[4][2].next_state == 0);
    CHECK(grid_glider[4][3].next_state == 0);
    CHECK(grid_glider[4][4].next_state == 0);
  }
}

TEST_CASE("Function next_generation") {

  SUBCASE("Test blocks next gen") {
    Grid grid_block = init_grid(4, 4, block);
    next_generation(grid_block);
    CHECK(grid_block[1][1].next_state == 1);
    CHECK(grid_block[1][2].next_state == 1);
    CHECK(grid_block[2][1].next_state == 1);
    CHECK(grid_block[2][2].next_state == 1);
    CHECK(grid_block[0][0].next_state == 0);
    CHECK(grid_block[3][3].next_state == 0);
  }

  SUBCASE("Test blinkers next gen") {
    Grid grid_blinker = init_grid(3, 3, blinker);
    next_generation(grid_blinker);
    next_generation(grid_blinker);
    CHECK(grid_blinker[0][1].next_state == 1);
    CHECK(grid_blinker[1][1].next_state == 1);
    CHECK(grid_blinker[2][1].next_state == 1);
  }
}

TEST_CASE("Test glider next gen") {
  Grid grid_glider = init_grid(5, 5, glider);
  next_generation(grid_glider);
  update_grid(grid_glider);
  SUBCASE("Test glider next gen 2") {
    CHECK(grid_glider[0][0].next_state == 0);
    CHECK(grid_glider[0][1].next_state == 0);
    CHECK(grid_glider[0][2].next_state == 0);
    CHECK(grid_glider[0][3].next_state == 0);
    CHECK(grid_glider[0][4].next_state == 0);

    CHECK(grid_glider[1][0].next_state == 0);
    CHECK(grid_glider[1][1].next_state == 0);
    CHECK(grid_glider[1][2].next_state == 0);
    CHECK(grid_glider[1][3].next_state == 0);
    CHECK(grid_glider[1][4].next_state == 0);

    CHECK(grid_glider[2][0].next_state == 0);
    CHECK(grid_glider[2][1].next_state == 1);
    CHECK(grid_glider[2][2].next_state == 0);
    CHECK(grid_glider[2][3].next_state == 1);
    CHECK(grid_glider[2][4].next_state == 0);

    CHECK(grid_glider[3][0].next_state == 0);
    CHECK(grid_glider[3][1].next_state == 0);
    CHECK(grid_glider[3][2].next_state == 1);
    CHECK(grid_glider[3][3].next_state == 1);
    CHECK(grid_glider[3][4].next_state == 0);

    CHECK(grid_glider[4][0].next_state == 0);
    CHECK(grid_glider[4][1].next_state == 0);
    CHECK(grid_glider[4][2].next_state == 1);
    CHECK(grid_glider[4][3].next_state == 0);
    CHECK(grid_glider[4][4].next_state == 0);
  }
  next_generation(grid_glider);
  update_grid(grid_glider);
  SUBCASE("Test glider next gen 3") {
    CHECK(grid_glider[0][0].next_state == 0);
    CHECK(grid_glider[0][1].next_state == 0);
    CHECK(grid_glider[0][2].next_state == 0);
    CHECK(grid_glider[0][3].next_state == 0);
    CHECK(grid_glider[0][4].next_state == 0);

    CHECK(grid_glider[1][0].next_state == 0);
    CHECK(grid_glider[1][1].next_state == 0);
    CHECK(grid_glider[1][2].next_state == 0);
    CHECK(grid_glider[1][3].next_state == 0);
    CHECK(grid_glider[1][4].next_state == 0);

    CHECK(grid_glider[2][0].next_state == 0);
    CHECK(grid_glider[2][1].next_state == 0);
    CHECK(grid_glider[2][2].next_state == 0);
    CHECK(grid_glider[2][3].next_state == 1);
    CHECK(grid_glider[2][4].next_state == 0);

    CHECK(grid_glider[3][0].next_state == 0);
    CHECK(grid_glider[3][1].next_state == 1);
    CHECK(grid_glider[3][2].next_state == 0);
    CHECK(grid_glider[3][3].next_state == 1);
    CHECK(grid_glider[3][4].next_state == 0);

    CHECK(grid_glider[4][0].next_state == 0);
    CHECK(grid_glider[4][1].next_state == 0);
    CHECK(grid_glider[4][2].next_state == 1);
    CHECK(grid_glider[4][3].next_state == 1);
    CHECK(grid_glider[4][4].next_state == 0);
  }
  next_generation(grid_glider);
  update_grid(grid_glider);
  SUBCASE("Test glider next gen 4") {
    CHECK(grid_glider[0][0].next_state == 0);
    CHECK(grid_glider[0][1].next_state == 0);
    CHECK(grid_glider[0][2].next_state == 0);
    CHECK(grid_glider[0][3].next_state == 0);
    CHECK(grid_glider[0][4].next_state == 0);

    CHECK(grid_glider[1][0].next_state == 0);
    CHECK(grid_glider[1][1].next_state == 0);
    CHECK(grid_glider[1][2].next_state == 0);
    CHECK(grid_glider[1][3].next_state == 0);
    CHECK(grid_glider[1][4].next_state == 0);

    CHECK(grid_glider[2][0].next_state == 0);
    CHECK(grid_glider[2][1].next_state == 0);
    CHECK(grid_glider[2][2].next_state == 1);
    CHECK(grid_glider[2][3].next_state == 0);
    CHECK(grid_glider[2][4].next_state == 0);

    CHECK(grid_glider[3][0].next_state == 0);
    CHECK(grid_glider[3][1].next_state == 0);
    CHECK(grid_glider[3][2].next_state == 0);
    CHECK(grid_glider[3][3].next_state == 1);
    CHECK(grid_glider[3][4].next_state == 1);

    CHECK(grid_glider[4][0].next_state == 0);
    CHECK(grid_glider[4][1].next_state == 0);
    CHECK(grid_glider[4][2].next_state == 1);
    CHECK(grid_glider[4][3].next_state == 1);
    CHECK(grid_glider[4][4].next_state == 0);
  }
  next_generation(grid_glider);
  update_grid(grid_glider);
  SUBCASE("Test glider next gen 5") {
    CHECK(grid_glider[0][0].next_state == 0);
    CHECK(grid_glider[0][1].next_state == 0);
    CHECK(grid_glider[0][2].next_state == 0);
    CHECK(grid_glider[0][3].next_state == 0);
    CHECK(grid_glider[0][4].next_state == 0);

    CHECK(grid_glider[1][0].next_state == 0);
    CHECK(grid_glider[1][1].next_state == 0);
    CHECK(grid_glider[1][2].next_state == 0);
    CHECK(grid_glider[1][3].next_state == 0);
    CHECK(grid_glider[1][4].next_state == 0);

    CHECK(grid_glider[2][0].next_state == 0);
    CHECK(grid_glider[2][1].next_state == 0);
    CHECK(grid_glider[2][2].next_state == 0);
    CHECK(grid_glider[2][3].next_state == 1);
    CHECK(grid_glider[2][4].next_state == 0);

    CHECK(grid_glider[3][0].next_state == 0);
    CHECK(grid_glider[3][1].next_state == 0);
    CHECK(grid_glider[3][2].next_state == 0);
    CHECK(grid_glider[3][3].next_state == 0);
    CHECK(grid_glider[3][4].next_state == 1);

    CHECK(grid_glider[4][0].next_state == 0);
    CHECK(grid_glider[4][1].next_state == 0);
    CHECK(grid_glider[4][2].next_state == 1);
    CHECK(grid_glider[4][3].next_state == 1);
    CHECK(grid_glider[4][4].next_state == 1);
  }
}

TEST_CASE("Function get_alive_neighbors") {

  Grid grid_block = init_grid(4, 4, block);
  SUBCASE("Test blocks neighbors") {
    CHECK(get_alive_neighbour(grid_block, 0, 0) == 1);
    CHECK(get_alive_neighbour(grid_block, 0, 1) == 2);
    CHECK(get_alive_neighbour(grid_block, 1, 1) == 3);
    CHECK(get_alive_neighbour(grid_block, 3, 3) == 1);
  }
  SUBCASE("Test blinker neighbors") {
    Grid grid_blinker = init_grid(3, 3, blinker);
    CHECK(get_alive_neighbour(grid_blinker, 1, 1) == 2);
    CHECK(get_alive_neighbour(grid_blinker, 0, 1) == 3);
    CHECK(get_alive_neighbour(grid_blinker, 1, 1) == 2);
  }
}
