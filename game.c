//
// Created by Jake on 5/14/2020.
//
#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define INPLACE true
#define PRINTEACH true
#define PRINTABSOLUTE false
#define BENCHMARK true
#if BENCHMARK
#include "benchmark.h"
#endif

void initialize() {
    FILE* f = fopen("C:/Users/Jake/Documents/Programming/gameOfLifeFAST/input.txt", "r");

    fscanf(f, "%d", &ySize);
    xSize = (ySize+1)/2; // Divide by 2 and round up
    bool isEven = ySize/2 == ySize;

    board = malloc(ySize * sizeof(char*));

    for(int i=0; i<ySize; i++) {
        board[i] = malloc(xSize * sizeof(char));

        // This can actually be made even faster since the only possible values are 1 or 0
        unsigned int temp = 0;
        unsigned int val;
        unsigned int combine_mask = 0;
        int j=0;

        int xLimit = xSize;
        bool oneLess = xSize != ySize/2;
        while(j<xSize) {
            fscanf(f, "%d", &val);
            temp = ((temp & combine_mask) | val) | (val & ~combine_mask); // Store either temp, or val in temp based on the mask

            temp = temp << (4u & ~combine_mask);

            board[i][j] = (char)temp;

            j += combine_mask != 0;

            combine_mask = ~combine_mask;
            if ( (!isEven && j+1 == xSize && combine_mask == ~0u)
            || isEven && j == xSize && combine_mask == 0u) {
                break;
            }
        }
    }

    fclose(f);
}


void start(int iterations) {
    initialize();
    printResults();
#if BENCHMARK
    startClock();
#endif
    run(iterations);
#if BENCHMARK
    endClock();
#endif
    printResults();
#if BENCHMARK
    uint64_t final_time = getDelta();
    printf("Took %lu us, %lf s\n", final_time, final_time/1000000.0);
#endif
    cleanup();
}

void run(int iterations) {
        #if INPLACE
        for (int i=0; i< iterations; i++) {
            // Set all values
            for (unsigned int y = 0; y < ySize; y++) {

                unsigned int combine_mask = 0;
                unsigned int x = 0;
                while (x < xSize) {
                    unsigned char value = board[y][x];
                    if (combine_mask == 0) {
                        value = value >> 4u;
                    } else {
                        value = value & 15u;
                    }

                    if (value % 2) { // Is cell alive?
                        // Increment all adjacent cells by 2. Also check to make sure they exist
                        unsigned dy = y - 1;

                        // Note: This could probably be optimized a bit more, but it would be very, very gross
                        // This conditional could be killed in favor of a bitwise method, although this is probably faster
                        if (combine_mask == 0) {
                            unsigned dx = x - 1;

                            if (dx < xSize && dy < ySize && ((board[dy][dx] & 15u) < 8)) board[dy][dx] += 2;
                            dx++;
                            if(dx < xSize && dy < ySize && (board[dy][dx]>>4u) < 8) board[dy][dx] += 32; // Account for the shift
                            if (dx < xSize && dy < ySize && ((board[dy][dx] & 15u) < 8)) board[dy][dx] += 2;

                            dy++;
                            dx = x-1;
                            if (dx < xSize && dy < ySize && ((board[dy][dx] & 15u) < 8)) board[dy][dx] += 2;
                            dx++;
                            // Ignore center
                            if (dx < xSize && dy < ySize && ((board[dy][dx] & 15u) < 8)) board[dy][dx] += 2;

                            dy++;
                            dx = x-1;
                            if (dx < xSize && dy < ySize && ((board[dy][dx] & 15u) < 8)) board[dy][dx] += 2;
                            dx++;
                            if(dx < xSize && dy < ySize && (board[dy][dx]>>4u) < 8) board[dy][dx] += 32;
                            if (dx < xSize && dy < ySize && ((board[dy][dx] & 15u) < 8)) board[dy][dx] += 2;
                        } else {
                            unsigned dx = x;
                            if (dx <xSize && dy< ySize && (board[dy][dx]>>4u) < 8) board[dy][dx] += 32;
                            if (dx < xSize && dy < ySize && ((board[dy][dx] & 15u) < 8)) board[dy][dx] += 2;
                            dx++;
                            if (dx <xSize && dy< ySize && (board[dy][dx]>>4u) < 8) board[dy][dx] += 32;

                            dy++;
                            dx = x;
                            if (dx <xSize && dy< ySize && (board[dy][dx]>>4u) < 8) board[dy][dx] += 32;
                            // Ignore center
                            dx++;
                            if (dx <xSize && dy< ySize && (board[dy][dx]>>4u) < 8) board[dy][dx] += 32;

                            dy++;
                            dx = x;
                            if (dx <xSize && dy< ySize && (board[dy][dx]>>4u) < 8) board[dy][dx] += 32;
                            if (dx < xSize && dy < ySize && ((board[dy][dx] & 15u) < 8)) board[dy][dx] += 2;
                            dx++;
                            if (dx <xSize && dy< ySize && (board[dy][dx]>>4u) < 8) board[dy][dx] += 32;
                        }
                    }

                    x += combine_mask != 0;
                    combine_mask = ~combine_mask;
                }
            }

            // Update alive status
            for (unsigned int y = 0; y < ySize; y++) {

                unsigned int x = 0;
                unsigned int combine_mask = 0;
                while (x < xSize) {
                    unsigned char value = board[y][x];
                    unsigned char left = value >> 4u;
                    unsigned char right = value & 15u;
                    left -= 5;
                    right -=5;

                    unsigned char newValue = 0;
                    newValue = left <= 2u;
                    newValue = newValue << 4u;
                    right = right <= 2u;
                    board[y][x] = newValue | right;

                    x++;
                }
            }
            #if PRINTEACH
            printResults();
            #endif
        #endif
    }
}

void printResults() {
#if PRINTABSOLUTE
    for (int i=0; i<ySize; i++) {
        for (int j=0; j<xSize; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
#else
    for (int i=0; i<ySize; i++) {
        for (int j=0; j<xSize; j++) {
            unsigned char val = board[i][j];
            printf("%d ", val >> 4u);
            printf("%d ", val & 15u);
        }
        printf("\n");
    }
    printf("\n");
#endif
}

void cleanup() {
    for (int i=0; i<ySize; i++) {
        free(board[i]);
    }
    free(board);
}