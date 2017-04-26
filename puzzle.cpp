#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

/*	Whilst abstracting the physical board into a digital representation we run into the
	issue where we must rotate connected layers. This is easily achieved by rotating
	the proper numbered layers with the layer below it.	*/
// [OPTIMIZATION] I don't think we ever have to rotate the base two layers

class Puzzle {
public:
	Puzzle(int _layerCount = 5, int _sliceCount = 16) {
		layerCount = _layerCount;
		sliceCount = _sliceCount;
		layerIndexes = vector<int>(layerCount);

		// [TODO] Add initialization support for situations other than the puzzle Philip has
		assert(layerCount == 5);
		assert(sliceCount == 16);

		layers = {
			{{-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
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
	}

	void rotateLayer(int layerIndex) {
		for(int layerIndex = 0;layerIndex < layers.size();layerIndex++) {
			if(layerIndex % 2 == 0) {
				layerIndexes[layerIndex + 0]++;
				layerIndexes[layerIndex + 1]++;
				if(layerIndexes[layerIndex] > sliceCount - 1) {
					// [TODO] Run this the exact number of connected layers. It might NOT be 2 in the future
					layerIndexes[layerIndex + 0] = 0;
					layerIndexes[layerIndex + 1] = 0;

					layerIndexes[layerIndex + 2]++;
					layerIndexes[layerIndex + 3]++;
				}
			}
		}
	}

	// [TODO] Actually show math
	int calculateSlice(int sliceIndex, bool showMath = false) {
		int sum = 0;

		for(int layerIndex = 0;layerIndex < layers.size();layerIndex++) {
			// [TODO] Do asserts here
			int value = 666;
			vector<vector<int>> layer = layers[layerIndex];

			if(false) {}
			// If the layer[0][sliceIndex] is >= 0 then we assume it's value
			else if(layer[0][sliceIndex] >= 0) {
				value = layer[0][sliceIndex];
			}
			// If the layer[0][sliceIndex] is -2 then we assume it's [1] value
			// Exception, if layer[n - 1][sliceIndex] was not -1 then we assume n[1]'s value
			else if(layer[0][sliceIndex] == -2) {
				value = layer[1][sliceIndex];
				// Stopped here, no effing sure what the heck I am doing...
			}
			// If the layer[1][sliceIndex] is -1 then we fall through
			else if(layer[1][sliceIndex] == -1) {
				vector<vector<int>> nextLayer = layers[layerIndex + 1];
				value = nextLayer[1][sliceIndex];
			}

			cout << value << endl;
			sum += value;
		}

		return sum;
	}

	// [TODO] Clean up how this renders sometime
	void renderLayerIndexes() {
		cout << "{";
		for(int layerIndex : layerIndexes)
			cout << layerIndex << ", ";
		cout << "}" << endl;
	}

	int layerCount, sliceCount;
	vector<vector<vector<int>>> layers;
	vector<int> layerIndexes;
};

int main() {
	Puzzle *puzzle = new Puzzle();

	/*int largestConcurrent = 0;
	for(int d = 0;d < 16 * 16 * 16 * 16 * 16 - 1;d++) {
		bool solution = true;
		int concurrent = 0;
		for(int slice = 0;slice < 16;slice++) {
			int currentSlice = puzzle->calculateSlice(slice);
			if(currentSlice == 50) {
				concurrent++;
				if(concurrent > largestConcurrent)
					largestConcurrent = concurrent;
			}
			if(currentSlice != 50) {
				solution = false;
				break;
			}
		}
		if(solution)
			puzzle->renderLayerIndexes();
		puzzle->rotatePhysicalLayer(0);
	}
	cout << "Largest concurrent was " << largestConcurrent << endl;*/

	/*for(int d = 0;d < 16;d++) {
		puzzle->rotatePhysicalLayer(0);
	}
	cout << puzzle->calculateSlice(0, true) << endl;*/

	puzzle->renderLayerIndexes();
	cout << puzzle->calculateSlice(0) << endl;
}