#pragma once

int ySize;
int xSize;

unsigned char** board;

void initialize();

void start(int iterations);

void run(int iterations);

void printResults();

void cleanup();