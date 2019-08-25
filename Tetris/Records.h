#pragma once
#ifndef RECORDS_H
#define RECORDS_H

#include <iostream>
#include <fstream>
#include <conio.h>
#include "Keyboard.h"

struct Record
{
	char name[6];
	int score;
};

short recordsTable();
void fillList();
void createNewList();
short addNewRecord(int score);
bool isNewRecord(int score);
Record createNewRecord(char name[6], int score);
void printRecordWindow(char name[6], int score);

#endif