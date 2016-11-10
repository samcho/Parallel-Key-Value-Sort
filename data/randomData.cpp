#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
	srand(time(NULL));

	ofstream outputFile;

	outputFile.open("data.txt");

	int i = 0;

	while ( i < 100000 )
	{
		bool value;
		value = ( rand() / (double) RAND_MAX < .2 );
		outputFile << rand() + 1 << "\t" << value << "\n";
		i++;
		cout << "here" << endl;
	}

	outputFile.close();

	return 0;
}
