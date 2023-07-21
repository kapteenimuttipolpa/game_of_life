/***
 * pattern.h defines patterns that
 * user can choose
 * **/
#ifndef PATTERNS_H
#define PATTERNS_H

#include <vector>
#include <unordered_set>

struct Coord {
  int row{};
  int col{};
};
struct Pattern {
  int height{};
  int width{};
  std::vector<Coord> coords{};
};

inline bool operator==(Coord c1, Coord c2) { return c1.row == c2.col && c1.row == c2.col; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
  std::size_t operator()(Coord xy) const
  {
      auto hasher = std::hash<int>();
      auto xhash = hasher(xy.row);
      auto yhash = hasher(xy.col);
      // Combine hash values (magic!)
      return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
  }
};

inline static Pattern blinker{1, 3, {{0, 0}, {0, 1}, {0, 2}}};

inline static Pattern block{2, 2, {{0, 0}, {0, 1}, {1, 0}, {1, 1}}};

inline static Pattern glider{3, 3, {{0, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}}};

inline static Pattern gosper_glider_gun{
    11, 38, {{1, 25}, {2, 23}, {2, 25}, {3, 13}, {3, 14}, {3, 21},
             {3, 22}, {3, 35}, {3, 36}, {4, 12}, {4, 16}, {4, 21},
             {4, 22}, {4, 35}, {4, 36}, {5, 1},  {5, 2},  {5, 11},
             {5, 17}, {5, 21}, {5, 22}, {6, 1},  {6, 2},  {6, 11},
             {6, 15}, {6, 17}, {6, 18}, {6, 23}, {6, 25}, {7, 11},
             {7, 17}, {7, 25}, {8, 12}, {8, 16}, {9, 13}, {9, 14}}};

inline static Pattern c_heptomino{3, 4, {{0, 1}, {0, 2}, {0, 3}, {1, 0},
          {1, 1}, {1, 2}, {2, 1}}};

inline static Pattern biloaf{
  7, 4, {{0, 2}, {1, 1}, {1, 3}, {2, 0}, {2, 3}, {3, 1}, {3, 2},
          {4, 0}, {4, 3}, {5, 0}, {5, 2}, {6, 1}}};

inline static Pattern octagon_II{
  8, 8, {{0, 3}, {0, 4}, {1, 2}, {1, 2}, {1, 5},
        {2, 1}, {2, 6}, {3, 0}, {3, 7}, {4, 0}, {4, 7},
        {5, 1}, {5, 6}, {6, 2}, {6, 5}, {7, 3}, {7, 4}}};

inline static Pattern copperhead{
  8, 12, {{0,5}, {0, 7}, {0, 8}, {1, 4}, {1, 11},
          {2, 3}, {2, 4}, {2, 8}, {2, 11},
          {3, 0}, {3, 1}, {3, 3}, {3, 9}, {3, 10},
          {4, 0}, {4, 1}, {4, 3}, {4, 9}, {4, 10},
          {5, 3}, {5, 4}, {5, 8}, {5, 11},
          {6, 4}, {6, 11}, {7, 5}, {7, 7}, {7, 8}}};

inline static Pattern diamond_4_8_12{
  9, 12, {{0, 4}, {0, 5}, {0, 6}, {0, 7},
          {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 8}, {2, 9},
          {4, 0}, {4,1}, {4,2}, {4,3}, {4,4}, {4,5}, {4,6}, {4,7}, {4,8}, {4,9},
          {4,10}, {4,11}, {6,2}, {6,3}, {6,4}, {6,5}, {6,6},{6,7}, {6,8}, {6,9},
          {8, 4}, {8, 5}, {8, 6}, {8, 7}}};
inline static Pattern full {3, 3, {{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2}}};

inline static std::vector<Pattern> custom_patterns;
inline static std::vector<Pattern> all_patterns  {blinker, block, glider, gosper_glider_gun, c_heptomino, biloaf, octagon_II, copperhead, diamond_4_8_12, full};
#endif // !UTILS_H
