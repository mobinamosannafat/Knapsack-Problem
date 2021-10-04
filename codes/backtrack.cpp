/*test case:
val:10,20,30,40,60,70
weights=1,2,3,6,7,4
w=7
ans=100*/

#include <iostream>
#include <time.h>
#include <conio.h>
#include <vector>
#include <fstream>

using namespace std;

//function that calculate maximum numbaer between two integer number
int max(int num1, int num2);   

//main function to do backtracking opration for solving knapsack problem
void knapSack(int kSweight, vector<int> weights, vector<int> values, int number);


int main()
{
	cout << "Enter the number of items in a Knapsack:";
	int number;            //number of items
	int knapsackWeight;    //weight of knapsack
	cin >> number;		   //getting number of items
	cout << endl << endl;

	vector<int> values;   //array of values of items
	vector<int> weights;  //array of weights of items


						 
	ifstream inputFile("output.dat", ios::in);   // define object of read file stream

	//check for file opening
	if (!inputFile)
	{
		cerr << "some thing wrong during opening file!" << endl;
		exit(1);
	}

	//getting value and weight of each item from file
	for (int i = 0; i < number; i++)
	{
		cout << "value and weight item " << i << ":";
		int val1;
		int val2;

		inputFile >> val1;
		values.push_back(val1);

		inputFile >> val2;
		weights.push_back(val2);

		cout << val1 << " " << val2 << " " << endl << endl;

	}

	//getting weight of knapsack from file
	cout << "the capacity of knapsack: ";

	cin >> knapsackWeight;


	//calling Knapsack function with 4 parameters:
	//weight of knapsack , array of weights of items 
	//array of values of items , number of items
	knapSack(knapsackWeight, weights, values, number);
	_getch();
	return 0;
}

int max(int num1, int num2)
{
	return (num1 > num2) ? num1 : num2;
}


void knapSack(int KSweight, vector<int> weights, vector<int> values, int number)
{
	clock_t Start = clock();  //for saving the starting time

	int i, wt;

	//defining a 2D vector for doing backtracking opration
	//it reserve (number*weight) of memory
	vector<vector<int>> KS;  //k
							 //int KS[n + 1][W + 1];
	
	for (i = 0; i <= number; i++)
	{
		KS.push_back(vector<int>());

		for (wt = 0; wt <= KSweight; wt++)
		{
			//if we have item but remaining empty weight is zero 
			//or we have remaining empty weight but no item for choosing
			//we set that element of array 0
			if (i == 0 || wt == 0)
			{
				KS[i].push_back(0);
			}

			//if weight of the item that we want choose is less than of remaining empty weight
			//if choosing this option give us a better profit of not choosing it
			//we choose this item else we ignor it
			else if (weights[i - 1] <= wt)
			{
				int val = max(values[i - 1] + KS[i - 1][wt - weights[i - 1]], KS[i - 1][wt]);
				KS[i].push_back(val);
			}

			else
			{
				int val = KS[i - 1][wt];
				KS[i].push_back(val);
			}
		}
	}
	//claculating time of the this function
	cout << endl << "Time = " << double(clock() - Start) / (double)CLOCKS_PER_SEC << " seconds" << endl << endl;

	//the last element in array(last column and last row) is the answer
	cout << "max profit = " << KS[number][KSweight] << endl << endl;

	cout << "Items we picked up: \n";
	//printing Items we picked up
	int res = KS[number][KSweight];  
	wt = KSweight;

	// either the result comes from the top 
	// (KS[i - 1][wt]) or from (val[i-1] + K[i-1])
	//  wt - weights[i - 1] as in Knapsack table. If it comes from the latter one/ it means the item is included. 

	for (i = number; i > 0 && res > 0; i--)
	{
		if (res == KS[i - 1][wt]) continue;
		else
		{
			cout << values[i - 1] << " " << weights[i - 1] << endl;
			res = res - values[i - 1];
			wt = wt - weights[i - 1];
		}
	}

}
