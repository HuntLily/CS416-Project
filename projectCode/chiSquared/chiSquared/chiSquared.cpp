// chiSquared.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 

#include <iostream>
#include <tgmath.h>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <typeinfo>
#include <chrono>


using namespace std;
using namespace std::chrono;

	struct Dataset
	{
		int nrow = 0; //number of rows
		int ncol = 0; //number of columns
		unordered_map<string, vector<string>> catCol; // categorical columns
	};

	struct Correlation
	{
		string col_1_name;
		string col_2_name;
		float coeff;
	};
	
	
	

/*
Steps still necessary for the program
1. Convert the CSV file data to a dataSet w/ Unmapped things [done]
2. loop through all combinations of columns [done]
	1. find the Degrees of Freedom [done]
	2. Call getPValues() [done]
	3. Call the library function for chi val [done]
3. store the p-values [done]
4. display/return the p-values above the threshold. [done]
5. parallelize, -O3 gcc, maybe SIMD instructions
6. find and display our run time [done]
*/

	// the chi-square library because it wouldn't work and there was nothing else in the readme indicating what to do and I am tired
	static double igf(double S, double Z)
	{
		if (Z < 0.0)
		{
			return 0.0;
		}
		double Sc = (1.0 / S);
		Sc *= pow(Z, S);
		Sc *= exp(-Z);

		double Sum = 1.0;
		double Nom = 1.0;
		double Denom = 1.0;

		for (int r = 0; r < 200; r++)
		{
			Nom *= Z;
			S++;
			Denom *= S;
			Sum += (Nom / Denom);
		}

		return Sum * Sc;
	}

	///finding p value functions
	double chisqr(int Dof, float Cv)
	{
		if (Cv < 0 || Dof < 1)
		{
			return 0.0;
		}
		double K = ((double)Dof) * 0.5;
		double X = ((double)Cv) * 0.5;
		if (Dof == 2)
		{
			return exp(-1.0 * X);
		}

		double PValue = igf(K, X);
		if (isnan(PValue) || isinf(PValue) || PValue <= 1e-8)
		{
			return 1e-14;
		}

		PValue /= tgamma(K);

		return (1.0 - PValue);
	}

	// Sean's slightly better second attempt at the PValue bogus
	std:: vector<Correlation> getPValues(Dataset data, float pval)
	{
		/* 
		Things this method should do
		1. Go through each pair of tupples in the unordered_map
		2. find their P-value w/ the math below
		3. create the Correlation struct w/ results
		4. return Correlation
		*/
		
		// create the variables needed for the function
		vector<Correlation> results;
		string c1Name;
		string c2Name;
		float pValue = pval;
		float critVal;

		// first things first, loop through every combination of two columns
		unordered_map<string, vector<string>>::iterator p;
		unordered_map<string, vector<string>>::iterator l;
		for (p = data.catCol.begin(); p != data.catCol.end(); p++)
		{
			l = p;
			l++;
			for (l; l != data.catCol.end(); l++)
			{
				vector<string> &column1 = p->second;
				string cName1 = p->first;
				vector<string> &column2 = l -> second;
				string cName2 = l -> first;

				// inside the for loop, do the fun times chi-square stuff
				// first, get the number of variables in col1 and col2
				vector<string> chiCols;
				vector<int> chiColTot;

				// Get the number of unique variables in column 1, and how often they occur
				for (int i = 0; i < p->second.size(); i++)
				{
					for (int j = 0; j < chiCols.size()+1; j++)
					{
						if (column1[i] != chiCols[j] && j == chiCols.size())
						{
							chiCols.push_back(column1[i]);
							chiColTot.push_back(1);
						}
						else if (column1[i] == chiCols[j])
							chiColTot[j]++;
					}
				}

				// same thing for the rows
				vector<string> chiRows;
				vector<int> chiRowTot;
				for (int i = 0; i < column2.size(); i++)
				{
					for (int j = 0; j < chiRows.size() + 1; j++)
					{
						if (column2[i] != chiRows[j] && j == chiRows.size())
						{
							chiRows.push_back(column2[i]);
							chiRowTot.push_back(1);
						}
						else if (column2[i] == chiRows[j])
							chiRowTot[j]++;
					}
				}

				// create a 2D array to hold all of the observed values for each pair in the 2 columns
				//int* chiSquare = new int[chiRows.size()][chiCols.size()];

				int** chiSquare;
				chiSquare = new int* [chiRows.size()];
				chiSquare[chiRows.size()] = new int[chiCols.size()];

				// go through and fill in the observed values. 
				for (int i = 0; i < column2.size(); i++)
				{
					// this loop goes through each element in column 2 and compares it to each variable in chiRows until it finds a match
					for (int j = 0; j < chiRows.size(); j++)
					{
						if (column2[i] == chiRows[j])
						{
							// once you've found a match, find column1[i]'s match in chiCols
							for (int k = 0; k < chiCols.size(); k++)
							{
								if (column1[i] == chiCols[k])
								{
									// when you find a match for column1, increment the 2d array according to which variables it matches
									chiSquare[j][k]++;
								}
							}
						}
					}
				}

				// find the expected value and chi value for each cell; add them to get the chi Crit value
				float chiCrit = 0;

				for (int i = 0; i < chiRows.size(); i++)
				{
					for (int j = 0; j < chiCols.size(); j++)
					{
						// expected value = (row total * col total) / overall total
						float expected = (chiRowTot[i] * chiColTot[j]) / data.nrow;

						//chi value = (observed - expected)^2 / expected value. chiChrit = sum of all chi values
						chiCrit = pow((chiSquare[i][j] - expected),2) / expected;
					}
				}

				// get the Degrees of Freedom = (# of rows - 1) * (# of columns -1)
				int dof = (chiRows.size() - 1) * (chiCols.size() - 1);

				// find the p-value given chiCrit and dof
				pValue = chisqr(dof, chiCrit);


				// check if pval is above the required amount
				if (pValue >= pval)
				{
					// create a Correlations struct based on the results of this test and add it to the vector of Correlations 'results'
					Correlation result;
					result.coeff = pValue;
					result.col_1_name = cName1;
					result.col_2_name = cName2;
					results.push_back(result);
				}
			}
		}

		return results;
	}


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
	int ncol = 0;
	int nrow = 0;
	struct Dataset data;
	vector<Correlation> results;
	std::ifstream myFile("example.csv");
	std::string line, dataEntry;
	string val;
	
	if (myFile.good())
	{
		std::getline(myFile, line);

		std::stringstream ss(line);
		while (std::getline(ss, dataEntry, ','))
		{
			ncol += 1;
		}

		// clear the cursor
		ss.clear();
		ss.seekg(0, std::ios::beg);
		myFile.clear();
		myFile.seekg(0, std::ios::beg);

		// make the array of unordered maps = the number of columns
		unordered_map<string, vector<string>> dataSet;
		vector<string> colName;

		// go through and set the key string for each map in the array
		while (std::getline(ss, dataEntry, ','))
		{
			dataSet[dataEntry];
			colName.push_back(dataEntry);
		}

		int counter = 0;
		while (std::getline(myFile, line))
		{
			ss.clear();
			ss << line;
			while (std::getline(ss, dataEntry, ','))
			{
				dataSet.at(colName[counter]).push_back(dataEntry);
				counter++;
			}
			// finished a line, reset counter
			counter = 0;
			nrow += 1;
		}

		// checking for good input by listing it in console.
		/*unordered_map<string, vector<string>>::iterator p;
		for (p = dataSet.begin(); p != dataSet.end(); p ++)
		{
			cout << p->first << ": ";
			for (int i = 0; i < dataSet.at(p->first).size(); i++)
			{
				
				 cout << p->second[i] << " ";
			}
			cout << endl;
		}*/

		// fill in the Datasctructure with the values we've found so far
		data.ncol = ncol;
		data.nrow = nrow;
		data.catCol = dataSet;

		// get the results of the chi-square test by calling the getPValues method and storing the results in results
		results = getPValues(data, pval);

		// display all results in console (for now)
		for (int i = 0; i < results.size(); i++)
			cout << "Column 1: " << results[i].col_1_name << "\nColumn 2: " << results[i].col_2_name << "\nCoefficient: " << results[i].coeff << endl;
	}
	
	//time our method 
	//auto start = high_resolution_clock::now();
	//auto stop = high_resolution_clock::now();
	//auto duration = duration_cast<microseconds>(stop - start);
	//cout << "Time taken by the function: " << duration.count() << " microseconds" << endl;
	

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