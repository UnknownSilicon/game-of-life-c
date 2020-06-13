//
// Created by Jake on 5/14/2020.
//
#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define INPLACE true
#define PRINTEACH true

void initialize() {
    FILE* f = fopen("C:/Users/Jake/Documents/Programming/gameOfLifeFAST/input.txt", "r");

    fscanf(f, "%d", &size);
    size = (size+1)/2; // Divide by 2 and round up

    board = malloc(size * sizeof(char*));

    for(int i=0; i<size; i++) {
        board[i] = malloc(size * sizeof(char));

        // This can actually be made even faster since the only possible values are 1 or 0
        unsigned int temp = 0;
        unsigned int val;
        unsigned int combine_mask = 0;
        int j=0;
        while(j<size) {
            fscanf(f, "%d", &val);
            temp = ((temp & combine_mask) | val) | (val & ~combine_mask); // Store either temp, or val in temp based on the mask

            temp = temp << (4u & ~combine_mask);

            board[i][j] = (char)temp;

            j += combine_mask != 0;
            combine_mask = ~combine_mask;
        }
    }

    fclose(f);
}


void start(int iterations) {
    initialize();
    printResults();
    run(iterations);
    printResults();
    cleanup();
}

void run(int iterations) {
        #ifdef INPLACE
        for (int i=0; i< iterations; i++) {
            // Set all values
            for (unsigned int y = 0; y < size; y++) {
                for (unsigned int x = 0; x < size; x++) {
                    // TODO: Rewrite this bit to take into account the shifted values
                    if (board[y][x] % 2) { // Is cell alive?
                        // Increment all adjacent cells by 2. Also check to make sure they exist
                        unsigned int dy = y - 1;
                        unsigned int dx = x - 1;
                        if (dx < size && dy < size && board[dy][dx] < 8) board[dy][dx] += 2;
                        if (++dx < size && dy < size && board[dy][dx] < 8) board[dy][dx] += 2;
                        if (++dx < size && dy < size && board[dy][dx] < 8) board[dy][dx] += 2;
                        dx = x - 1;
                        dy++;
                        if (dx < size && dy < size && board[dy][dx] < 8) board[dy][dx] += 2;
                        dx++; // Skip the middle
                        if (++dx < size && dy < size && board[dy][dx] < 8) board[dy][dx] += 2;
                        dx = x - 1;
                        dy++;
                        if (dx < size && dy < size && board[dy][dx] < 8) board[dy][dx] += 2;
                        if (++dx < size && dy < size && board[dy][dx] < 8) board[dy][dx] += 2;
                        if (++dx < size && dy < size && board[dy][dx] < 8) board[dy][dx] += 2;
                    }
                }
            }

            // Update alive status
            for (unsigned int y = 0; y < size; y++) {
                for (unsigned int x = 0; x < size; x++) {
                    char value = board[y][x];
                    value -= 5;
                    unsigned char uc = value;
                    board[y][x] = (char)(uc <= 2);
                }
            }
            #ifdef PRINTEACH
            printResults();
            #endif
        #endif
    }
}

void printResults() {
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void cleanup() {
    for (int i=0; i<size; i++) {
        free(board[i]);
    }
    free(board);
}