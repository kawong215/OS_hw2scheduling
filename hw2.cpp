#include <iostream>
#include <fstream> // to read files
#include <string>
#include <climits> //to set max in STCF
using namespace std;

const int columns = 3;

void fifo(int job[][columns], int num_rows); // FIFO scheduling
void sjf(int job[][columns], int num_rows); // SJF scheduling
void bjf(int job[][columns], int num_rows); // BJF scheduling
void stcf(int job[][columns], int num_rows); // STCF scheduling
void rr(int job[][columns], int num_rows); // RR scheduling

void algorithm_check(string choice, int job[][columns], int num_rows); 
void print_array(int arr[][columns], int num_rows); 


int main()
{
	int readline1, readline2, readline3;
	int rows = 100;

	int jobs[rows][columns]; // holds jobs.dat data
	
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
		column_count = 0; // restart column count
		
		jobs[row_count][column_count] = readline1;
		column_count++;
		jobs[row_count][column_count] = readline2;
		column_count++;
		jobs[row_count][column_count] = readline3;
		column_count++;
		
		row_count++;
	}

	cout << "Contents of jobs.dat: " << endl; 
	
	// print contents of jobs.dat
	print_array(jobs, row_count); 

	// row count display total number of jobs
	cout << endl << "Number of jobs = " << row_count << endl << endl; 
	
	// select scheduling algorithm to perform
	cout << "Select scheduling algorithm. Type algorithm in all CAPS or lowercase." << endl;
	cout << "1: FIFO" << endl << "2: SJF" << endl << "3: BJF " << endl << "4: STCF " << endl << "5: RR" << endl;
	getline(cin, algorithm); 

	algorithm_check(algorithm, jobs, row_count);
}


void fifo(int job[][columns], int num_rows)
{	
	int start_time, finish_time, completion_time, total_time; 
	float avg = 0;

	completion_time = job[0][2];
	start_time = job[0][1];

	for (int i = 0; i < num_rows; i++)
	{
		finish_time = start_time + job[i][2];
		total_time = start_time + job[i][2] - job[i][1]; // start_time + duration - arrival_time
		
		cout << "JOB ID: " << job[i][0] << endl; 
		cout << "Start time: " << start_time << " sec" << endl;
		cout << "Finish time: " << finish_time << " sec" << endl;
		cout << "Total time lapsed: " << job[0][2] << " sec" << endl; // turnaround time
		cout << "Response time: " << start_time - job[i][1] << " sec" << endl; // response = start - time arrived
		cout << endl;

		start_time += job[i][2];
		avg += total_time; 
	}
	cout << "Avg turnaround: " << avg / num_rows << " sec" << endl; 
}


void sjf(int job[][columns], int num_rows)
{
	int arrivals[num_rows];
	int next = 0;
	int next_count = 0;
	int match = 1; 
	int location[num_rows];

	int count = 0;
	int index = 0; // finding matches
	int temp, min; // sorting

	// find matching arrivals
	for (int i = 0; i < num_rows; i++)
	{
		arrivals[i] = job[i][1];
		next = i + 1;
		next_count = count + 1; 
		
		if (arrivals[i] == job[next][1])
		{
			match++; 
			location[count] = job[i][0]; 
			location[next_count] = job[next][0]; 
			index = next; 
			count++; 
		}
	}

	int non_dupes = num_rows - match;  // non-duplicated arrival jobs
	int duplicate_start = index - match + 1; // index where duplicated arrivals start
	int dupe_arrivals[match][columns]; // array to hold duplicate jobs at the same arrival

	for (int m = 0; m < match; m++)
	{
		for (int n = 0; n < columns; n++)
		{
			dupe_arrivals[m][n] = job[duplicate_start + m][n]; 
		}
	}

	// sort the jobs with the same arrival time from smallest to largest
	for (int i = 0; i < match; i++)
	{
		min = i;

		for (int j = i + 1; j < match; j++)
		{
			if (dupe_arrivals[j][2] < dupe_arrivals[min][2])
			{
				min = j;
			}
		}
		temp = dupe_arrivals[min][2];
		dupe_arrivals[min][2] = dupe_arrivals[i][2];
		dupe_arrivals[i][2] = temp;

		temp = dupe_arrivals[min][0];
		dupe_arrivals[min][0] = dupe_arrivals[i][0];
		dupe_arrivals[i][0] = temp;

		temp = dupe_arrivals[min][1];
		dupe_arrivals[min][1] = dupe_arrivals[i][1];
		dupe_arrivals[i][1] = temp;
	}

	// copy duplicate array into jobs.dat array
	for (int m = 0; m < match; m++)
	{
		for (int n = 0; n < columns; n++)
		{
    			job[duplicate_start+m][n] = dupe_arrivals[m][n]; 
		}
	}
	cout << endl; 	
	fifo(job, num_rows); 

} 

void bjf(int job[][columns], int num_rows)
{
	int arrivals[num_rows];
	int next = 0;
	int next_count = 0;
	int match = 1; 
	int location[num_rows];

	int count = 0;
	int index = 0; 
	int temp, max; // for sorting

	// find matching arrivals
	for (int i = 0; i < num_rows; i++)
	{
		arrivals[i] = job[i][1];
		next = i + 1;
		next_count = count + 1; 
		
		if (arrivals[i] == job[next][1])
		{
			match++; 
			location[count] = job[i][0]; 
			location[next_count] = job[next][0]; 
			index = next; 
			count++; 
		}
	}
	
	// non-duplicated arrival jobs
	int non_dupes = num_rows - match; 

	// index where duplicated arrivals start
	int duplicate_start = index - match + 1; 

	int dupe_arrivals[match][columns]; // array to hold duplicate jobs at the same arrival

	for (int m = 0; m < match; m++)
	{
		for (int n = 0; n < columns; n++)
		{
			dupe_arrivals[m][n] = job[duplicate_start + m][n]; 
		}
	}

	// sort the jobs with the same arrival time from largest to smallest
	for (int i = 0; i < match; i++)
	{
		max = i;

		for (int j = i + 1; j < match; j++)
		{
			if (dupe_arrivals[j][2] > dupe_arrivals[max][2])
			{
				max = j;
			}
		}
		temp = dupe_arrivals[max][2];
		dupe_arrivals[max][2] = dupe_arrivals[i][2];
		dupe_arrivals[i][2] = temp;

		temp = dupe_arrivals[max][0];
		dupe_arrivals[max][0] = dupe_arrivals[i][0];
		dupe_arrivals[i][0] = temp;

		temp = dupe_arrivals[max][1];
		dupe_arrivals[max][1] = dupe_arrivals[i][1];
		dupe_arrivals[i][1] = temp;
	}

	// merge back with jobs.dat array
	for (int m = 0; m < match; m++)
	{
		for (int n = 0; n < columns; n++)
		{
    			job[duplicate_start+m][n] = dupe_arrivals[m][n]; 
		}
	}
	cout << endl; 	
	fifo(job, num_rows); 
}

void stcf(int job[][columns], int num_rows)
{
	int remaining_time[num_rows];
	int burst_time[num_rows];
	int arrival_time[num_rows];
	int waiting_time[num_rows];
	int completion_time;
	int finish_time[num_rows];
	int smallest;
	int min_time = INT_MAX;
	int time;
	bool check = false;
	int start_time[num_rows];
	int elapse_time[num_rows];	//start to finish
	int rt[num_rows];		//response time = start-finish
	
	for (int i = 0; i < num_rows; i++)
	{
		arrival_time[i] = job[i][1];
		//burst time(duration) = remaining time
		//find total proccess time
		burst_time[i] = job[i][2];
		remaining_time[i] = burst_time[i];
	}

	while (completion_time != num_rows)
	{
		
		for (int j = 0; j < num_rows; j++)
		{
			arrival_time[j] = job[j][1];
			if((arrival_time[j] <= time) && (remaining_time[j] < min_time) && remaining_time[j] > 0)
			{
				min_time = remaining_time[j];
				smallest = j;
				check = true;
			}
		}

		if(check == false)
		{
			time++;
			continue;
		}

		remaining_time[smallest]--;

		min_time = remaining_time[smallest];
		if(min_time == 0)
		{
			min_time = INT_MAX;
		}

		if(remaining_time[smallest] == 0)
		{
			completion_time++;

			finish_time[smallest] = time + 1;

			waiting_time[smallest] = finish_time[smallest] - burst_time[smallest] - arrival_time[smallest];

			if (waiting_time[smallest] < 0)
			{
				waiting_time[smallest] = 0;
			}
		}
		time++;
		
	}
	
	cout << endl;
	
	for(int k = 0; k < num_rows; k++)
	{
		cout << "Process: " << job[k][0] << endl;

		start_time[k] = arrival_time[k];
		cout << "Start Time: " << arrival_time[k] << endl;

		cout << "Finish Time: " << finish_time[k] << endl;

		elapse_time[k] = finish_time[k] + start_time[k];
		cout << "Total Time Elapsed: " << elapse_time[k] << endl;

		rt[k] = start_time[k] - arrival_time[k];
		cout << "Response Time: " << rt[k] << endl;

		cout << endl;
	}
}

void rr(int job[][columns], int num_rows)
{
	int arrival[num_rows];
	int burst[num_rows];
	int remaining[num_rows];		//copies burst and subtracts from this
	int process = 0;
	int quantum_time = 1;
	int time = 0;
	int finish_time[num_rows];
	int max_process = 0;

	for(int i = 0; i < num_rows; i++)
	{
		arrival[i] = job[i][1];
		burst[i] = job[i][2];
		remaining[i] = burst[i];

		max_process = max_process + burst[i];
	}

	while (1)
	{
		bool completion = true;

		for(int j = 0; j < num_rows; j++)
		{	
			if(remaining[j] > 0)
			{
				completion = false;

				if(remaining[j] > quantum_time)
				{
					remaining[j] = remaining[j] - quantum_time;
					time = time + quantum_time;
				}

				else 
				{
					time = time + remaining[j];
					remaining[j] = 0;
				}
				
			}
			if (remaining[j] == 0)
			{
				finish_time[j] = time;
			}
		}
		if(completion == true)
		{
			break;
		}
	}

	for (int k = 0; k < num_rows; k++)
	{
		cout << endl;
		cout << "Jod ID: " << job[k][0] << endl;
		cout << "Start Time: " << arrival[k] << endl;
		cout << "Finish Time: " << finish_time[k] << endl;
		cout << "Total Time Elapsed: " << finish_time[k] - arrival[k] << endl;
		cout << "Reponse Time: " << arrival[k] -  arrival[k] << endl; 
	}
}

void algorithm_check(string choice, int job[][columns], int num_rows)
{
	string algorithm = choice; 

	while (!(algorithm == "FIFO" || algorithm == "fifo" || algorithm == "SJF" || algorithm == "sjf" || algorithm == "BJF" || algorithm == "bjf" || algorithm == "STCF" || algorithm == "stcf" || algorithm == "RR" || algorithm == "rr"))
	{
		cout << "Please enter an algorithm choice" << endl;
		getline(cin, algorithm); 
	}

	if (algorithm == "FIFO" || algorithm == "fifo")
	{
		fifo(job, num_rows);
	}
		
	else if (algorithm == "SJF" || algorithm == "sjf")
	{
		sjf(job, num_rows);
	}

	else if (algorithm == "BJF" || algorithm == "bjf")
	{
		bjf(job, num_rows);
	}
	
	else if (algorithm == "STCF" || algorithm == "stcf")
	{
		stcf(job, num_rows);
	}
	
	else if (algorithm == "RR" || algorithm == "rr")
	{
		rr(job, num_rows);
	}	
}


void print_array(int arr[][columns], int num_rows)
{
	// print contents of jobs.dat
	for (int i = 0; i < num_rows; i++)
    	{
    		for (int j = 0; j < columns; j++)
    		{
    			cout << arr[i][j] << " ";
    		}
    		cout << endl;
    	}
}
