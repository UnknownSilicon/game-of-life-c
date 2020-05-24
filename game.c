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

    board = malloc(size * sizeof(char*));

    for(int i=0; i<size; i++) {
        board[i] = malloc(size * sizeof(char));

        int val;
        for (int j=0; j<size; j++) {
            fscanf(f, "%d", &val);
            board[i][j] = (char)val;
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
    if (INPLACE) {
        for (int i=0; i< iterations; i++) {
            // Set all values
            for (unsigned int y = 0; y < size; y++) {
                for (unsigned int x = 0; x < size; x++) {
                    if (board[y][x] % 2) { // Is cell alive?
                        // Increment all adjacent cells by 2. Also check to make sure they exist
                        unsigned int dy = y - 1;
                        unsigned int dx = x - 1;
                        if (dx < size && dy < size) board[dy][dx] += 2;
                        if (++dx < size && dy < size) board[dy][dx] += 2;
                        if (++dx < size && dy < size) board[dy][dx] += 2;
                        dx = x - 1;
                        dy++;
                        if (dx < size && dy < size) board[dy][dx] += 2;
                        dx++; // Skip the middle
                        if (++dx < size && dy < size) board[dy][dx] += 2;
                        dx = x - 1;
                        dy++;
                        if (dx < size && dy < size) board[dy][dx] += 2;
                        if (++dx < size && dy < size) board[dy][dx] += 2;
                        if (++dx < size && dy < size) board[dy][dx] += 2;
                    }
                }
            }

            // Update alive status
            for (unsigned int y = 0; y < size; y++) {
                for (unsigned int x = 0; x < size; x++) {
                    char value = board[y][x];
                    value -= 5;
                    unsigned char uc = value;
                    if (uc <= 2) {
                        board[y][x] = 1;
                    } else {
                        board[y][x] = 0;
                    }
                }
            }
            #ifdef PRINTEACH
            printResults();
            #endif
        }
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