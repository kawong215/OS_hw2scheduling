#include <iostream>
#include <fstream> // to read files
#include <string>
using namespace std;

const int columns = 3;

void fifo(int job[][columns], int num_rows); // fifo scheduling

int main()
{
	int readline1, readline2, readline3;
	int rows = 100;

	int jobs[rows][columns]; 
	
	int row_count = 0;
	int column_count = 0;
	string algorithm;

	ifstream inFile;
	inFile.open("jobs.dat"); // read file

	if (!inFile)
	{
		cout << "Cannot open file" << endl;
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

	cout << "Contents of file: " << endl; 
	
	// print contents of jobs.dat
	for (int i = 0; i < row_count; i++)
    {
    	for (int j = 0; j < columns; j++)
    	{
    		cout << jobs[i][j] << " ";
    	}
    	cout << endl;
    }

	// row count display for checking purposes
	cout << endl << "Number of jobs = " << row_count << endl << endl; 
	
	// select scheduling algorithm to perform
	cout << "Select scheduling algorithm (FIFO, SJF, BJF, STCF, RR): " << endl << "(in all CAPs or all lowercase)" << endl;
	getline(cin, algorithm); 

	if (algorithm == "FIFO" || algorithm == "fifo")
	{
		fifo(jobs, row_count);
	}

	cout << endl;
}

void fifo(int job[][columns], int num_rows)
{	
	int start_time; 
	int finish_time; 
	int completion_time; 
	int response_time; 
	float avg = 0;

	completion_time = job[0][2];
	start_time = job[0][1];

	for (int i = 0; i < num_rows; i++)
	{
		finish_time = start_time + job[i][2];
		response_time = start_time + job[i][2] - job[i][1];
		
		cout << "Start time of job ID " << job[i][0] << ": " << start_time << " sec" << endl;
		cout << "Finish time of job ID " << job[i][0] << ": " << finish_time << " sec" << endl;
		cout << "Total time elapse of job ID " << job[i][0] << ": " << finish_time - job[i][1] << " sec" << endl; // finish time - time arrived

		cout << "Response time of job ID " << job[i][0] << ": " << response_time << " sec" << endl << endl; // turnaround time
		
		start_time += job[i][2];
		avg += response_time; 
	}

	// for checking purposes
	cout << "Avg turnaround: " << avg / num_rows << endl; 
}
