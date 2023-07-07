#include "utils.h"
#include "mainwindow.h"
#include "grid.h"
#include <random>
#include <chrono>
int Utils::random_num(int a, int b)
{
    std::random_device rd{};
    std::seed_seq ss{
        static_cast<std::seed_seq::result_type>
        (std::chrono::steady_clock::now().time_since_epoch().count()),
        rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    std::mt19937 mt {ss};
    std::uniform_int_distribution distr{a, b};
    return distr(mt);
}
/**
 * @brief Utils::random_pattern
 * creates a randomized pattern
 * @return
 */
Pattern Utils::random_pattern()
{
    int width = 20;
    int height = 20;
    int divider = 5;
    Pattern rand_pattern {width, height, {}};
    for (int i = 0; i < height * width / divider; i++)
    {
      while (true)
      {
        int x = random_num(0, height - 1);
        int y = random_num(0, width - 1);
        if (coord_found(rand_pattern.coords, {x,y}))
          continue;
        rand_pattern.coords.push_back({x,y});
        break;
      }
    }
    return rand_pattern;
}
