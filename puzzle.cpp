#include <iostream>

#define SLICES 16
#define LAYERS 9

using namespace std;

// [PROBLEM] How to know to rotate both connected layers at once?

int layers[LAYERS][SLICES] = {
	{ 0, 16,  8,  4, 15,  7, 10,  1, 10,  4,  5,  3, 15, 16,  4,  7},
	{13, 11, 13, 10, 18, 10, 10, 10, 10, 15,  7, 19, 18,  2,  9, 27},
	{ 9, -1,  8, -1,  8, -1,  9, -1,  6, -1, 10, -1,  8, -1, 10, -1},
	{12,  1, 10, 12, 22,  0,  5,  8,  5,  1, 24,  8, 10, 20,  7, 20},
	{ 0, -1, 11, -1,  8, -1,  8, -1,  8, -1, 10, -1, 11, -1, 10, -1},
	{20,  8, 19, 10, 15, 20, 12, 20, 13, 13,  0, 22, 19, 10,  0,  5},
	{ 3, -1,  8, -1, 10, -1, 14, -1, 11, -1,  8, -1, 12, -1, 11, -1},
	{10, 17, 10,  5,  6, 18,  8, 17,  4, 20,  4, 14,  4,  5,  1, 14},
	{16, -1, 19, -1,  8, -1, 17, -1,  6, -1,  6, -1,  8, -1,  8, -1},
};

int main() {
	cout << "hi" << endl;
}