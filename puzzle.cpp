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
	Puzzle(int _layers = 9, int _slices = 16) {
		layers = _layers;
		slices = _slices;
		layerIndexes = vector<int>(layers);

		// [TODO] Add initialization support for situations other than the puzzle Philip has
		assert(layers == 9);
		assert(slices == 16);
		data = {
			{16, -1, 19, -1,  8, -1, 17, -1,  6, -1,  6, -1,  8, -1,  8, -1},
		{10, 17, 10,  5,  6, 18,  8, 17,  4, 20,  4, 14,  4,  5,  1, 14},
		{ 3, -1,  8, -1, 10, -1, 14, -1, 11, -1,  8, -1, 12, -1, 11, -1},
			{20,  8, 19, 10, 15, 20, 12, 20, 13, 13,  0, 22, 19, 10,  0,  5},
			{ 0, -1, 11, -1,  8, -1,  8, -1,  8, -1, 10, -1, 11, -1, 10, -1},
			{12,  1, 10, 12, 22,  0,  5,  8,  5,  1, 24,  8, 10, 20,  7, 20},
			{ 9, -1,  8, -1,  8, -1,  9, -1,  6, -1, 10, -1,  8, -1, 10, -1},
			{13, 11, 13, 10, 18, 10, 10, 10, 10, 15,  7, 19, 18,  2,  9, 27},
			{ 0, 16,  8,  4, 15,  7, 10,  1, 10,  4,  5,  3, 15, 16,  4,  7},
		};
	}

	/***** [Info]
		For abstraction we will treat each physical layer of the puzzle as connected (Vice the top layer)
	*****/
	int physicalLayerCount() {
		return (layers - 1) / 2 + 1;
	}

	vector<int> associatedLayers(int physicalLayerIndex) {
		vector<int> associatedLayerIndexes;
		if(physicalLayerIndex == 0)
			associatedLayerIndexes.push_back(0);
		else {
			associatedLayerIndexes.push_back((physicalLayerIndex * 2) - 1);
			associatedLayerIndexes.push_back((physicalLayerIndex * 2) - 1 + 1);
		}
		return associatedLayerIndexes;
	}

	void rotatePhysicalLayer(int physicalLayerIndex) {
		vector<int> associatedLayerIndexes = associatedLayers(physicalLayerIndex);

		bool shouldRollOver = false;
		for(int layerIndex : associatedLayerIndexes) {
			layerIndexes[layerIndex]++;
			if(layerIndexes[layerIndex] > slices - 1)
				shouldRollOver = true;
		}

		if(shouldRollOver) {
			for(int layerIndex : associatedLayerIndexes)
				layerIndexes[layerIndex] = 0;
			rotatePhysicalLayer(physicalLayerIndex + 1);
		}
	}

	int calculateSlice(int sliceIndex, bool showMath = false) {
		int sum = 0;

		for(int physicalLayerIndex = 0;physicalLayerIndex <= physicalLayerCount() - 1;physicalLayerIndex++) {
			vector<int> associatedLayerIndexes = associatedLayers(physicalLayerIndex);
			assert(associatedLayerIndexes.size() <= 2);

			int associatedLayerValue = data[associatedLayerIndexes.back()][sliceIndex + layerIndexes[associatedLayerIndexes.back()]];

			if(associatedLayerValue == -1) {
				vector<int> associatedNextLayerIndexes = associatedLayers(physicalLayerIndex + 1);
				associatedLayerValue = data[associatedNextLayerIndexes.front()][sliceIndex + layerIndexes[associatedNextLayerIndexes.front()]];
			}

			if(showMath) {
				static bool introduce = false;
				if(!introduce) {
					cout << "Calculating Slice " << sliceIndex << " of:" << endl;
					renderLayerIndexes();
					introduce = true;
				}

				cout << associatedLayerValue << endl;
			}

			sum += associatedLayerValue;
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

	int layers, slices;
	vector<vector<int>> data;
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

	for(int d = 0;d < 16;d++) {
		puzzle->rotatePhysicalLayer(0);
	}
	cout << puzzle->calculateSlice(0, true) << endl;
}