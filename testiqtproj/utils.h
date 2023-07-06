#ifndef UTILS_H
#define UTILS_H
#include "patterns.h"
#include "mainwindow.h"
#include <chrono>
#include <thread>
namespace Utils {
    int random_num(int a, int b);
    Pattern random_pattern(int height, int width);

}


#endif // !UTILS_H
