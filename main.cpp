/***** Bryan A. Tremblay, Parad0x13
	[INFO]
	So Philip showed me a puzzle someone got him on 23 April 2017 and wanted to try
	and write a solver for it. The puzzle really interested me so I began writing a
	solver of my own a short while after studying it a bit. It seems to solve it now
	however I'm sure there some optimizations and things I can do to improve it and make
	it work for more difficult versions of the puzzle. There's a sort of symmetry in the solutions
	for the original 5 layer, 16 slice puzzle Philip showed me. I'm sure it's obvious to
	someone who's studied math more than I have but at least to me the pattern is kinda cool.

	[STRUCTURE]
	The physical puzzle can be seen here: http://i.imgur.com/cXxvNXn.jpg
	Or in the folder with this sourcecode

	I decided to group each layer in a nested vector consisting of another vector with their values.
	This presented a problem for the top layer which has no inner ring. To keep some semblance
	of structure I created a virtual inner ring for the top layer so that the algorithm was cleaner.
	I used the value -1 to indicate that there was a gap in the puzzle and the value underneath
	should be read instead and that worked pretty well.

	[OPTIMIZATION]
	As far as optimization goes I'm pretty sure it's very very slow and can be highly optimized.
	For example I spent a majority of time developing the calculateSlice(int) function because
	I had trouble properly managing the rotation of each layer. I eventually opted out of manually
	calculating vector offsets and instead used std::rotate to accomplish the same thing. This means
	I add the time std::rotate takes to execute onto the computation time. I could I suppose hash
	every array rotation but at least for the 5x16 puzzle it calculates fast enough for me not to care.

	Another optimization is not rotating the bottom layer at all. Since every other layer rotates in
	every configuration any distinct solution should be found before the need to rotate the bottom layer.
*****/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Puzzle {
public:
	Puzzle(int _layerCount = 5, int _sliceCount = 16, int _goal = 50) {
		// [TODO] Add initialization support for situations other than the puzzle Philip has
		assert(_layerCount == 5);
		assert(_sliceCount == 16);
		assert(_goal == 50);

		goal = _goal;
		layers = {
			{{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
			{ 16, -1, 19, -1,  8, -1, 17, -1,  6, -1,  6, -1,  8, -1,  8, -1},},

			{{10, 17, 10,  5,  6, 18,  8, 17,  4, 20,  4, 14,  4,  5,  1, 14},
			{  3, -1,  8, -1, 10, -1, 14, -1, 11, -1,  8, -1, 12, -1, 11, -1},},

			{{20,  8, 19, 10, 15, 20, 12, 20, 13, 13,  0, 22, 19, 10,  0,  5},
			{  0, -1, 11, -1,  8, -1,  8, -1,  8, -1, 10, -1, 11, -1, 10, -1},},

			{{12,  1, 10, 12, 22,  0,  5,  8,  5,  1, 24,  8, 10, 20,  7, 20},
			{  9, -1,  8, -1,  8, -1,  9, -1,  6, -1, 10, -1,  8, -1, 10, -1},},

			{{13, 11, 13, 10, 18, 10, 10, 10, 10, 15,  7, 19, 18,  2,  9, 27},
			{  0, 16,  8,  4, 15,  7, 10,  1, 10,  4,  5,  3, 15, 16,  4,  7},},
		};

		layerRotations = vector<int>(layerCount());
	}

	// [TODO] Add bounds checking here
	void rotateLayer(int layerIndex) {
		rotate(layers[layerIndex][0].begin(), layers[layerIndex][0].begin() + 1, layers[layerIndex][0].end());
		rotate(layers[layerIndex][1].begin(), layers[layerIndex][1].begin() + 1, layers[layerIndex][1].end());
		layerRotations[layerIndex]++;

		for(unsigned layerIndex = 0;layerIndex < layers.size();layerIndex++) {
			if(layerRotations[layerIndex] > sliceCount() - 1) {
				layerRotations[layerIndex] = 0;

				rotate(layers[layerIndex + 1][0].begin(), layers[layerIndex + 1][0].begin() + 1, layers[layerIndex + 1][0].end());
				rotate(layers[layerIndex + 1][1].begin(), layers[layerIndex + 1][1].begin() + 1, layers[layerIndex + 1][1].end());
				layerRotations[layerIndex + 1]++;
			}
		}
	}

	int calculateSlice(int sliceIndex) {
		int sum = 0;

		for(unsigned layerIndex = 0;layerIndex < layers.size();layerIndex++) {
			vector<vector<int>>& layer = layers[layerIndex];

			int inner = max(0, layer[0][sliceIndex]);
			int outer = max(0, layer[1][sliceIndex]);
			int value = inner + outer;

			if(layerIndex > 0) {
				vector<vector<int>>& previousLayer = layers[layerIndex - 1];

				if(previousLayer[1][sliceIndex] != -1)
					value = outer;
			}

			sum += value;
		}

		return sum;
	}

	int layerCount() {
		return layers.size();
	}

	int sliceCount() {
		return layers[0][0].size();
	}

	void findSolutions() {
		int largestConcurrent = 0;
		int solutionCount = 0;

		// [OPTIMIZATION] No need to rotate the bottom layer at all
		int requiredIterations = pow(sliceCount(), layerCount() - 1) - 1;
		for(int d = 0;d < requiredIterations;d++) {
			bool solution = true;
			int concurrent = 0;
			for(int slice = 0;slice < sliceCount();slice++) {
				if(calculateSlice(slice) == goal) {
					concurrent++;
					if(concurrent > largestConcurrent)
						largestConcurrent = concurrent;
				}
				else {
					solution = false;
					break;
				}
			}

			if(solution) {
				solutionCount++;
				cout << "Solution found:" << endl;
				for(vector<vector<int>> layer : layers)
					cout << layer[0][0] << ", " << layer[1][0] << endl;
			}

			rotateLayer(0);
		}

		if(solutionCount == 0) {
			cout << "Unable to find a solution..." << endl;
			cout << "Largest concurrent was " << largestConcurrent << endl;
		}
	}

	vector<vector<vector<int>>> layers;
	vector<int> layerRotations;
	int goal;
};

int main() {
	Puzzle *puzzle = new Puzzle();
	puzzle->findSolutions();
}