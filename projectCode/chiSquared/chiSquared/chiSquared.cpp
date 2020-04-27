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
#include "ChisquarePValueFinder.h"


using namespace std;

	struct Dataset
	{
		int nrow = 0; //number of rows
		int ncol = 0; //number of columns
		unordered_map<string, vector<string>> col1; // column 1
		unordered_map<string, vector<string>> col2; // column 2
	};

	struct Correlation
	{
		string col_1_name;
		string col_2_name;
		float coeff;
	};
	
	
	

/*
Steps still necessary for the program
1. Convert the CSV file data to a dataSet w/ Unmapped things
2. loop through all combinations of columns
	1. find the Degrees of Freedom [done]
	2. Call getChiVal [done]
	3. Call the library function for chi val [done]
3. store the p-values
4. display/return the p-values above the threshold. 
5. parallelize, -O3 gcc, maybe SIMD instructions
6. find and display our run time
*/

	// Sean's dumbass method of building the ChiSquare, and getting the chi value for the 2 columns, getting their dof, and returning the p-value
	/*double getPVal(string c1[], string c2[], int c1Number, int c2Number, string **csv)
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
		double chiCrit = 0;
		for (int i = 0; i < count2; i++)
		{
			for (int j = 0; j < count1; j++)
			{
				// find the expected value
				int expected = expected = (a1Tot[j] * a2Tot[i]) / total;

				// set the chi square table to the chi value using observed and expected
				chiA[i][j] = ((chiA[i][j] - expected) * (chiA[i][j] - expected)) / expected;

				chiCrit += chiA[i][j];
			}
		}

		// get Degrees of Freedom
		int dof = (count1 - 1) * (count2 - 1);
		
		// find the p-value given chiCrit and DoF
		double pVal = chisqr(dof, chiCrit);

		return pVal;
	}*/


int main()
{
	/*
	the main() function should:
	1. find the number of columns and rows
	2. make every column of data into a unordered_map (either cat or num)
		2.1 the keys for the columns are strings, name of column, must be unique
		2.2 the values are either a string or floating point vector (column data)
	3. call another function that finds the p-value when passed the dataset & threshold
	4. main then displays/whatever the p-values as output
	*/

	double pval = .05;
	//struct Dataset input;
	int ncol = 0;
	int nrow = 0;
	std::ifstream myFile("example.csv");
	std::string line, colName;
	string val;
	
	if (myFile.good())
	{
		std::getline(myFile, line);

		std::stringstream ss(line);
		while (std::getline(ss, colName, ','))
		{
			ncol += 1;
		}

		// clear the cursor
		ss.clear();
		ss.seekg(0, std::ios::beg);

		// make the array of unordered maps = the number of columns
		//std::unordered_map<string, vector<string>> dataSet(ncol);
		unordered_map<string, vector<string>>* dataSet = new unordered_map<string, vector<string>>[ncol];

		// go through and set the key string for each map in the array
		int counter = 0;
		while (std::getline(ss, colName, ','))
		{
			dataSet[counter][colName];
		}
		while (std::getline(myFile, line))
		{
			nrow += 1;
		}
		


		// checking for good input by listing it in console.
		unordered_map<string, vector<string>>::iterator p;
		for (int i = 0; i < ncol; i++)
		{
			for (p = dataSet[i].begin(); p != dataSet[i].end(); p++)
			{
				cout << p->first << endl;
				
			}
		}

		counter = 0;
		while (std::getline(myFile, line))
		{
			while (std::getline(ss, colName, ','))
			{
				dataSet[counter].emplace(colName, std::vector<string>{(unsigned int)nrow});
			}
		}

		// checking for good input by listing it in console.
		for (int i = 0; i < ncol; i++)
		{
			for (p = dataSet[i].begin(); p != dataSet[i].end(); p++)
			{
				for (int j = 0; j < 1; j++)
				{
					cout << p->second.at(j) << endl;
				}
			}
		}
	}



		/*
		while (std::getline(myFile, line))
		{
			while (std::getline(ss, colName, ','))
			{
				input.cat_cols.insert({ colName, std::vector<string>{(unsigned int) input.nrow} });

				input.ncol += 1;
			}
			
			
		}
	}
	

	
	while (std::getline(myFile, line))
	{
		std::stringstream ss(line);
		int colIndx = 0;


		while (ss >> val)
		{
			input.cat_cols[colName];
		}

		if (ss.peek() == ',') ss.ignore();

		colIndx++;
	}
	
	
	unordered_map<string, vector<string>>::iterator p;

	for (p = input.cat_cols.begin(); p != input.cat_cols.end(); p++)
	{
		cout << p->first << endl;
		for (string s : p->second)
		{
			cout << s << endl;
		}*/
	
	
	
	
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
http://www.cplusplus.com/reference/random/chi_squared_distribution/
*/