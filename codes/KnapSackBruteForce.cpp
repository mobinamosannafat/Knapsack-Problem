#include <iostream>
#include <time.h>
#include <conio.h>
#include <vector>
#include <fstream>

using namespace std;

//Brute Force implementation of 0-1 Knapsack problem
void bruteforce(); 

//globl values
int *weights, *values, *selected;  //array of weights of items ,array of  values of items
								   //array of items we select to pickup
int number;                        //number of items
int knapsackWeight;                //weight of knapsack



int main()
{
	int k;

	cout << "Enter the number of items in a Knapsack:";
	cin >> number;		  //getting number of items
	cout << endl << endl;


	//Create weight and profit array
	weights = (int*)malloc(sizeof(int)*number);
	values = (int*)malloc(sizeof(int)*number);
	selected = (int*)malloc(sizeof(int)*number);

	// define object of read file stream
	ifstream inputFile("output.dat", ios::in);

	//check for file opening
	if (!inputFile)
	{
		cerr << "some thing wrong during opening file!" << endl;
		exit(1);
	}

	//getting value and weight of each item from user
	for (int i = 0; i < number; i++)
	{
		cout << "value and weight for item " << i + 1 << ": ";


		int val1;
		inputFile >> val1;
		values[i] = val1;

		int val2;
		inputFile >> val2;
		weights[i] = val2;


		//outputFile << val1 << "  " << val2 << "  " << endl;
		cout << val1 << " " << val2 << " " << endl << endl;

	}


	cout << endl << endl;

	//getting weight of knapsack from user
	cout << "Enter the capacity of knapsack: ";

	cin >> knapsackWeight;
	cout << endl << endl;

	bruteforce(); //calling bruteforce function

	//free memories that was reserved
	free(selected);
	free(weights);
	free(values);

	_getch();
	return 0;
}





void bruteforce()
{
	clock_t Start = clock();  //for saving the starting time

	int i, j, isSelected = 1, maxWt, maxProfit = 0;
	int iter = pow(2.0, number);
	int result = 0;


	vector <int> temp;

	for (i = 0; i < number; i++)      //Initialize the temp vector  to 0
	{
		temp.push_back(0);
	}

	for (i = 0; i<iter; i++)
	{
		isSelected = 1;
		maxProfit = 0;
		maxWt = 0;

		for (j = 0; j < number; j++)
		{
			if (temp[j] == 1)
			{
				maxWt += weights[j];
				maxProfit += values[j];
			}
		}

		//Copies the selected item in array
		if (maxWt <= knapsackWeight && maxProfit > result)
		{

			for (j = 0; j < number; j++)
			{
				selected[j] = temp[j];
			}

			result = maxProfit;
		}

		//Calculate the next subset 
		for (j = 0; j<number; j++)
		{
			temp[j] = temp[j] + isSelected;
			isSelected = temp[j] / 2;
			temp[j] = temp[j] % 2;
		}
	}

	//claculating time of the this function
	cout << "Time = " << double(clock() - Start) / (double)CLOCKS_PER_SEC << " seconds" << endl << endl;

	//the last element in array(last column and last row) is the answer
	cout << "max profit = " << result << endl << endl;

	cout << "item in knapsack\n";
	for (int k = 0; k<number; k++)
		if (selected[k] != 0)
		{
			cout << values[k] << " " << weights[k] << endl;
		}
}





