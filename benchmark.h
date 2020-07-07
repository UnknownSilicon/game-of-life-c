//
// Created by Jake on 7/6/2020.
//

#ifndef GAMEOFLIFEFAST_BENCHMARK_H
#define GAMEOFLIFEFAST_BENCHMARK_H

#include <sys/time.h>

struct timespec start_time, end_time;

void startClock();

void endClock();

uint64_t getDelta();

#endif //GAMEOFLIFEFAST_BENCHMARK_H
