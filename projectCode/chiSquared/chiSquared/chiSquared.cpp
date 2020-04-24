// chiSquared.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 

#include <iostream>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <stdexcept>

using namespace std;

	struct Dataset
	{
		int nrow = 0; //number of rows
		int ncol = 0; //number of columns
		unordered_map<string, vector<string>> cat_cols; //categorical cols
		
	};

	struct Correlation
	{
		string col_1_name;
		string col_2_name;
		float coeff;
	};
	
	
	

/*
How to do a Chi-Square Test
Step -1: put the CSV file in a format we can use easily
Step 0: Take two columns and construct the chi square w/ observed values [done]
Step 1: Find the Expected Values
	- Get the total for each column and row being tested
	- Find (Row total * Column total)/total of all rows and columns combined
Step 2: Use formula to get Chi Square values
	- (Observed - Expected)^2 / Expected
Step 3: add all Chi Square values together.
Step 4: find Degrees of Freedom = (# of rows - 1) * (# of columns -1)
Step 5: use library given these 2 values to find p value
*/

	// Sean's dumbass method of building the ChiSquare
	double getChiVal(string c1[], string c2[], int c1Number, int c2Number, string **csv)
	{
		// variables
		string a1[50];
		int count1 = 0;
		int a1Tot[50];
		string a2[50];
		int count2 = 0;
		int a2Tot[50];

		//go through each row in column 1 to populate the a1 variables
		for (int i = 0; i < sizeof(c1); i++)
		{
			for (int j = 0; j <= count1; j++)
			{
				// if the object in c1, row i == the variable in spot j of a1, increment the total for a1Tot[j]
				if (c1[i].compare(a1[j]) == 0)
					a1Tot[j]++;

				// if the object in c1, row i != any of the variables in a1, add it to the list and update
				else if (c1[i].compare(a1[j]) != 0 && j == count1)
				{
					a1[count1] = c1[i];
					a1Tot[count1] = 1;
					count1++;
				}
			}
		}

		// go through each row in column 2 to populate the a2 variables
		for (int i = 0; i < sizeof(c2); i++)
		{
			for (int j = 0; j <= count2; j++)
			{
				// if the object in c1, row i == the variable in spot j of a1, increment the total for a1Tot[j]
				if (c2[i].compare(a2[j]) == 0)
					a2Tot[j] ++;

				// if the object in c1, row i != any of the variables in a1, add it to the list and update
				else if (c2[i].compare(a2[j]) != 0 && j == count2)
				{
					a2[count2] = c1[i];
					a2Tot[count2] = 1;
					count2++;
				}
			}
		}

		// initialize the 2d array for the chi square. a1 are the columns, a2 are the rows
		double chiA[sizeof(a2)][sizeof(a1)];

		// fill in chiA with the observed pairs
		for (int i = 0; i < sizeof(c1); i++)
		{
			for (int j = 0; j < count1; j++)
			{
				// check a1 to see if any entries match csv[i][column #1]
				if (csv[i][c1Number].compare(a1[j]) == 0)
				{
					// once you find a match, search through a2 for a match to csv[i][column #2]
					for (int k = 0; k < count2; k++)
					{
						// once a match is found, increment row k, column j of chiA by 1
						if (csv[i][c2Number].compare(a2[k]) == 0)
							chiA[k][j] += 1;
					}
				}
			}
		}

		// Go through each cell. Find it's expected value, and then use that to set the cell = its chi value
		double total = 0; 
		for (int i = 0; i < sizeof(a1Tot); i++)
		{
			// in case this method of sizeof gives an error: https://www.geeksforgeeks.org/how-to-find-size-of-array-in-cc-without-using-sizeof-operator/
			total += a1Tot[i];
		}

		// variable to return the chi value
		double chiVal = 0;
		for (int i = 0; i < count2; i++)
		{
			for (int j = 0; j < count1; j++)
			{
				// find the expected value
				int expected = expected = (a1Tot[j] * a2Tot[i]) / total;

				// set the chi square table to the chi value using observed and expected
				chiA[i][j] = ((chiA[i][j] - expected) * (chiA[i][j] - expected)) / expected;

				chiVal += chiA[i][j];
			}
		}

		// return the total chiVal
		return chiVal;
	}


int main()
{
	double pval = .05;
	struct Dataset input;
	std::ifstream myFile("example.csv");
	std::string line, colName;
	float val;
	
	if (myFile.good())
	{
		std::getline(myFile, line);

		std::stringstream ss(line);
		
		while (std::getline(myFile, line))
		{
			while (std::getline(ss, colName, ','))
			{
				input.cat_cols[colName];
				input.ncol += 1;
			}
			input.nrow += 1;
		}
	}
	
	while (std::getline(myFile, line))
	{
		std::stringstream ss(line);
		int colIndx = 0;


		while (ss >> val)
		{
			input.cat_cols[colName].at(colIndx).push_back(val);
			
		}

		if (ss.peek() == ',') ss.ignore();

		colIndx++;
	}
	
	
	unordered_map<string, vector<string>>::iterator p;
	for (p = input.cat_cols.begin(); p != input.cat_cols.end(); p++)
	{
		cout << p->first << endl;
	}
	
	
	
	myFile.close();

	return 0;
}
	


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

/*
references used for data input
https://www.geeksforgeeks.org/unordered_map-in-cpp-stl/
http://www.cplusplus.com/reference/vector/vector/at/
https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/

*/