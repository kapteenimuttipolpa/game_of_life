#ifndef PATTERNS_H
#define PATTERNS_H

#include <vector>

struct Coord {
  int row{};
  int col{};
};

struct Pattern {
  int height{};
  int width{};
  std::vector<Coord> coords{};
};

inline static Pattern blinker{1, 3, {{0, 0}, {0, 1}, {0, 2}}};

inline static Pattern block{2, 2, {{0, 0}, {0, 1}, {1, 0}, {1, 1}}};

inline static Pattern glider{3, 3, {{0, 0}, {0, 2}, {1, 1}, {1, 2}, {2, 1}}};

inline static Pattern gosper_glider_gun{
    11, 38, {{1, 25}, {2, 23}, {2, 25}, {3, 13}, {3, 14}, {3, 21},
             {3, 22}, {3, 35}, {3, 36}, {4, 12}, {4, 16}, {4, 21},
             {4, 22}, {4, 35}, {4, 36}, {5, 1},  {5, 2},  {5, 11},
             {5, 17}, {5, 21}, {5, 22}, {6, 1},  {6, 2},  {6, 11},
             {6, 15}, {6, 17}, {6, 18}, {6, 23}, {6, 25}, {7, 11},
             {7, 17}, {7, 25}, {8, 12}, {8, 16}, {9, 13}, {9, 14}}};
#endif // !UTILS_H
