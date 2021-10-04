#include <iostream>
#include <conio.h>
#include <queue>
#include <fstream>
#include <time.h>

using namespace std;

// Stucture for Item which store weight and corresponding value of Item 
struct Item

{
	int weight;

	int value;
};



// Node structure to store information of decision  tree 
struct Node

{

	// level  --> Level of node in decision tree (or index in arr[] )

	// profit --> Profit of nodes on path from root to this node (including this node) 

	// bound ---> Upper bound of maximum profit in subtree of this node

	int level, profit, bound;

	int weight, parent;

	short int taken;

};


// Comparison function to sort Item according to val/weight ratio 
bool cmp(Item a, Item b);

// Returns bound of profit in subtree rooted with u. 
// This function mainly uses Greedy solution to find an upper bound on maximum profit. 
int bound(Node u, int number, int KSweight, Item arr[]);

// Returns maximum profit we can get with capacity W 
void knapsack(int KSweight, Item arr[], int number);



int main()

{
	cout << "Enter the number of items in a Knapsack:";
	int number;   //number of items
	int knapsackWeight;  //weight of knapsack
	cin >> number;		//getting number of items
	cout << endl << endl;

	Item* arr; //creating array of Item for reciving values and weights from file

	arr = (Item*)malloc(sizeof(Item)*number);
	// define object of read file stream
	ifstream inputFile("output.dat", ios::in);

	//check for file opening
	if (!inputFile)
	{
		cerr << "some thing wrong during opening file!" << endl;
		exit(1);
	}

	int val1;
	int val2;

	//getting value and weight of each item from file
	for (int i = 0; i < number; i++)
	{
		cout << "value and weight item " << i << ":";

		inputFile >> val1;
		cout << val1 << " ";
		arr[i].value = val1;

		inputFile >> val2;
		cout << val2 << " " << endl;
		arr[i].weight = val2;
		cout << endl;

	}

	//getting weight of knapsack from file
	cout << "Enter the capacity of knapsack: ";
	cin >> knapsackWeight;

	//calling Knapsack function with 4 parameters:
	//weight of knapsack , array of weights of items 
	//array of values of items , number of items
	knapsack(knapsackWeight, arr, number);


	free(arr); //free memory that was used for arr

	_getch();
	return 0;

}

//comprision
bool cmp(Item a, Item b)
{

	double r1 = (double)a.value / a.weight;

	double r2 = (double)b.value / b.weight;

	return r1 > r2;

}

int bound(Node u, int number, int KSweight, Item arr[])
{
	// if weight overcomes the knapsack capacity, return 0 as expected bound 
	if (u.weight >= KSweight) return 0;


	// initialize bound on profit by current profit 
	int profit_bound = u.profit;


	// start including items from index 1 more to current item index 
	int j = u.level + 1;
	int totalweight = u.weight;


	// checking index condition and knapsack capacity condition 
	while ((j < number) && (totalweight + arr[j].weight <= KSweight))
	{
		totalweight += arr[j].weight;

		profit_bound += arr[j].value;

		j++;
	}


	// If k is not n, include last item partially for upper bound on profit 
	if (j < number)
	{
		profit_bound += (KSweight - totalweight) * arr[j].value / arr[j].weight;//akhari kasri
	}


	return profit_bound;

}


void knapsack(int KSweight, Item arr[], int number)
{

	clock_t Start = clock();         //for saving the starting time

							  
	sort(arr, arr + number, cmp);   // sorting Item on basis of value per unit weight


	// make a queue for traversing the node 
	queue<Node> Q;
	vector<Node>selected;

	Node u, v;



	// dummy node at starting 
	u.level = -1;
	u.parent = -1;
	u.taken = -1;

	u.profit = u.weight = 0;

	Q.push(u);



	// One by one extract an item from decision tree compute profit of all children of extracted item 
	// and keep saving maxProfit 

	int maxProfit = 0;
	Node last = u;

	while (!Q.empty())
	{
		// Dequeue a node 

		u = Q.front();

		Q.pop();

		// If it is starting node, assign level 0 

		//if (u.level == -1) v.level = 0;

		// If there is nothing on next level 

		if (u.level == number - 1) continue;

		// Else if not last node, then increment level, and compute profit of children nodes. 
		v.level = u.level + 1;

		// Taking current level's item add current level's weight 
		//and value to node u's weight and value 

		v.weight = u.weight + arr[v.level].weight;
		v.profit = u.profit + arr[v.level].value;
		v.parent = u.level;  


		// If cumulated weight is less than W and profit is greater than previous profit, 
		// update maxprofit 
		if (v.weight <= KSweight && v.profit > maxProfit)
		{
			maxProfit = v.profit;
			last = v;
		}


		// Get the upper bound on profit to decide whether to add v to Q or not. 
		v.bound = bound(v, number, KSweight, arr);



		// If bound value is greater than profit, 
		//then only push into queue for further consideration 
		if (v.bound > maxProfit)
		{
			v.taken = 1;
			Q.push(v);
			selected.push_back(v);
		}


		// Do the same thing,  but Without taking the item in knapsack 

		v.weight = u.weight;

		v.profit = u.profit;

		v.bound = bound(v, number, KSweight, arr);

		if (v.bound > maxProfit)
		{
			v.taken = 0;
			Q.push(v);
			selected.push_back(v);
		}
	}

	//claculating time of the this function
	cout << endl << "Time = " << double(clock() - Start) / (double)CLOCKS_PER_SEC << " seconds" << endl << endl;

	//the last element in array(last column and last row) is the answer
	cout << "max profit = " << maxProfit << endl << endl << "selected Items are: " << endl;


	//printing Item we picked up

	//print nodes that was picked up and they are not the kids of dummy node
	while (last.parent != -1)
	{
		if (last.taken = 1)
			cout << arr[last.level].value << "," << arr[last.level].weight << endl;
		last = selected[last.parent];
	}

	//if a node is selected and its the child of dummy node
	if (last.taken = 1 && last.parent == -1)
		cout << arr[last.level].value << "," << arr[last.level].weight << endl;
}



