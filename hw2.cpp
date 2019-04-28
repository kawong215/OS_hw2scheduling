#include <iostream>
#include <fstream> // to read files
#include <string>
using namespace std;

int num_jobs;
const int columns = 3;

void fifo(int job[][columns], int num_rows);

int main()
{
	int readline1, readline2, readline3;
	int rows = 100;

	int jobs[rows][columns]; 
	
	int row_count = 0;
	int column_count = 0;

	ifstream inFile;
	
	inFile.open("jobs.dat"); // read file

	if (!inFile)
	{
		cout << "Cannot open file";
	}

	while (inFile >> readline1 >> readline2 >> readline3)
	{
		column_count = 0;
		
		jobs[row_count][column_count] = readline1;
		column_count++;
		jobs[row_count][column_count] = readline2;
		column_count++;
		jobs[row_count][column_count] = readline3;
		column_count++;
		
		row_count++;
	}

	// print contents
	for (int i = 0; i < row_count; i++)
    	{
    		for (int j = 0; j < columns; j++)
    		{
    			cout << jobs[i][j] << " ";
    		}
    		cout << endl;
    	}

	cout << endl; 
}
