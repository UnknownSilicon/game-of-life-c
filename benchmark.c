//
// Created by Jake on 7/6/2020.
//

#include "benchmark.h"

void startClock() {
    clock_gettime(CLOCK_MONOTONIC, &start_time);
}

void endClock() {
    clock_gettime(CLOCK_MONOTONIC, &end_time);
}

// Yes, this is gross. Stack overflow says it's the best way to get ms time
uint64_t getDelta() {
    return (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_nsec - start_time.tv_nsec) / 1000;
}
