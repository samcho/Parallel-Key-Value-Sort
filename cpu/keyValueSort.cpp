#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>

#define MAX_DATA 30

using namespace std;

void printKeyValues(int *keys, int *values, std::string filename){
	ofstream outFile;
  outFile.open (filename);
	for (int i = 0; i < MAX_DATA; i++) {
		outFile << keys[i] << " " << values[i] << "\n";
	}
	outFile.close();
}

void keySort(int *keys, int *values){
	int changes = MAX_DATA / 2;
	int ones[MAX_DATA];
	int onesIndex = 0;
	int zeroes[MAX_DATA];
	int zeroesIndex = 0;
	int value1, value2, key1, key2;

	// bitonic split
	for (int i = 0; i < changes; i++) {
		value1 = values[i];
		value2 = values[changes+i];
		key1 = keys[i];
		key2 = keys[changes+i];

		if (value1 != value2){
			//comparing 1-0
			if (value2 > value1){
				//swap values
				values[i] = value2;
				keys[i] = key2;
				values[changes+i] = value1;
				keys[changes+i] = key1;
			}
		} else if (value1 == 1){
			//both numbers are ones
			ones[onesIndex] = changes+i;
			onesIndex++;
		} else {
			//both numbers are zeroes
			zeroes[zeroesIndex] = i;
			zeroesIndex++;
		}
	}

	printKeyValues(keys, values, "partial.txt");
	int sparse = zeroesIndex > onesIndex ? 1 : 0;

	// rematch round

	int rematched = sparse ? onesIndex : zeroesIndex;
	std::cout << "rematching: " << rematched << '\n';
	int key0;

	for (int i = 0; i < rematched; i++) {
		key1 = keys[ones[i]];
		key0 = keys[zeroes[i]];

		// swap values
		values[zeroes[i]] = 1;
		keys[zeroes[i]] = key1;

		values[ones[i]] = 0;
		keys[ones[i]] = key0;
	}

	printKeyValues(keys, values, "partial2.txt");

	//arrange unmatched values
	if(sparse) {
		int unmatchedCount = zeroesIndex - onesIndex;
		int baseHalf = changes - unmatchedCount;
		int baseLeft = onesIndex;
		int keyH, keyL, valueH, valueL;
		std::cout << "Moving to the border: " << unmatchedCount << '\n';

		for (int i = 0; i < unmatchedCount; i++) {
			std::cout << i << " " << baseHalf + i << " " << baseLeft + i << '\n';
			keyH = keys[baseHalf+i];
			valueH = values[baseHalf+i];
			keyL = keys[zeroes[baseLeft+i]];
			valueL = values[zeroes[baseLeft+i]];

			std::cout << keyH << " " << keyL << '\n';

			if (valueH != valueL){
				//comparing 1-0
				if (valueL > valueH){
					//swap values
					values[baseHalf+i] = valueL;
					keys[baseHalf+i] = keyL;
					values[zeroes[baseLeft+i]] = valueH;
					keys[zeroes[baseLeft+i]] = keyH;
				}
			} else if (value1 == 1){
				//both numbers are ones
				// std::cout << "OOPS 1" << '\n';
			} else {
				//both numbers are zeroes
				// std::cout << "OOPS 0" << '\n';
			}
		}

		printKeyValues(keys, values, "partial3.txt");
	}
}

int main()
{
	srand(time(NULL));

	ifstream inputFile("data.txt");
	int keys[MAX_DATA];
	int values[MAX_DATA];

	int i = 0;
	int a, b;

	while ( i < MAX_DATA ){
		inputFile >> keys[i] >> values[i];
		i++;
	}

	inputFile.close();

	printKeyValues(keys, values, "initial.txt");

	clock_t begin = clock();

	//Decreasing sort
	keySort(keys, values);

	clock_t end = clock();
  double elapsed = double(end - begin) / CLOCKS_PER_SEC;

	std::cout << "Seconds elapsed: " << elapsed << '\n';

	return 0;
}
