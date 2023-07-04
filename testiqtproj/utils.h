#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <thread>

inline constexpr static int SLOW = 1000;
inline constexpr static int MEDIUM = 350;
inline constexpr static int FAST = 100;

inline void sleep(int ms) {

  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#endif // !UTILS_H
