#pragma once
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include "Keyboard.h"
#include "Brick.h"

const short WIDTH = 10;
const short HEIGHT = 20;

int game();
bool defeat();
void control(char key);
void initField();
void printField(int score, char nextBrick[7]);
bool hasFullLine(short line);
void cleanLine(short line);
void newFigure(char field[7], Type type);
void createFigure(const char figure[8], char field[7]);
short getDelay(int score);
#endif