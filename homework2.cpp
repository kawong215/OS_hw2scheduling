#include <iostream>
#include <fstream> // to read files
#include <string>
using namespace std;

const int columns = 3;

void fifo(int job[][columns], int num_rows); // FIFO scheduling
void sjf(int job[][columns], int num_rows); // SJF scheduling
void bjf(int job[][columns], int num_rows); // BJF scheduling
void stcf(int job[][columns], int num_rows); // STCF scheduling
void rr(int job[][columns], int num_rows); // RR scheduling

int main()
{
	int readline1, readline2, readline3;
	int rows = 100;

	int jobs[rows][columns]; // holds jobs.dat data
	
	int row_count = 0;
	int column_count = 0;
	int algorithm;

	ifstream inFile;
	inFile.open("jobs.dat"); // read file

	if (!inFile)
	{
		cout << "Cannot open file" << endl;
	}

	while (inFile >> readline1 >> readline2 >> readline3)
	{
		column_count = 0; // restart column count
		
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
	cout << "Select scheduling algorithm. Please type the number corresponding to the algorithm." << endl;
	cout << "1: FIFO" << endl << "2: SJF" << endl << "3: BJF " << endl << "4: STCF " << endl << "5: RR" << endl;
	cin >> algorithm; 

	// if input is not one of the case statements
	while (algorithm < 1 || algorithm > 5) 
	{
		cout << "Please choose an algorithm: " << endl;
		cin.clear();
		cin >> algorithm; 
	}
	
	switch (algorithm)
	{
		case 1: fifo(jobs, row_count);
		case 2: sjf(jobs, row_count);
		case 3: bjf(jobs, row_count);
		case 4: stcf(jobs, row_count);
		case 5: rr(jobs, row_count);
	}	
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
		response_time = start_time + job[i][2] - job[i][1]; // start_time + duration - arrival_time
		
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


void sjf(int job[][columns], int num_rows)
{

} 

void bjf(int job[][columns], int num_rows)
{

}

void stcf(int job[][columns], int num_rows)
{

}

void rr(int job[][columns], int num_rows)
{

}
