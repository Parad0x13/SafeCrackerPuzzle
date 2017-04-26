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
		layerIndexes = vector<int>(layerCount);		// [TODO] Rename this to rotations or something

		// [TODO] Add initialization support for situations other than the puzzle Philip has
		assert(layerCount == 5);
		assert(sliceCount == 16);

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
	}

	void rotateLayer(int layerIndex) {
		layerIndexes[layerIndex]++;
		for(int layerIndex = 0;layerIndex < layers.size();layerIndex++) {
			if(layerIndexes[layerIndex] > sliceCount - 1) {
				layerIndexes[layerIndex + 0]  = 0;
				layerIndexes[layerIndex + 1] += 1;
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

			int activeLayerRotation = layerIndexes[layerIndex];
			int properLayerSliceIndex = sliceIndex + activeLayerRotation;

			int inner = max(0, layer[0][properLayerSliceIndex]);
			int outer = max(0, layer[1][properLayerSliceIndex]);
			value = inner + outer;

			if(layerIndex > 0) {
				vector<vector<int>> previousLayer = layers[layerIndex - 1];
				int activePreviousLayerRotation = layerIndexes[layerIndex - 1];
				int properPreviousLayerSliceIndex = sliceIndex + activePreviousLayerRotation;
				if(previousLayer[1][properPreviousLayerSliceIndex] != -1) {
					value = outer;
				}
			}

			//cout << value << endl;
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

	int largestConcurrent = 0;
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
		puzzle->rotateLayer(0);
	}
	cout << "Largest concurrent was " << largestConcurrent << endl;
}