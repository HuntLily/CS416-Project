// chiSquared.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 

#include <iostream>
#include <tgmath.h>
#include <math.h>
#include <vector>
#include <omp.h>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <typeinfo>
#include <chrono>
#include <thread>
#include "catch.hpp"
#define CATCH_CONFIG_MAIN


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
		// create the variables needed for the function
		vector<Correlation> results;
		string c1Name;
		string c2Name;
		float pValue = pval;

		// first things first, loop through every combination of two columns
		unordered_map<string, vector<string>>::iterator p;
		unordered_map<string, vector<string>>::iterator l;

		
		

			for (p = data.catCol.begin(); p != data.catCol.end(); p++)
			{
				for ((l = p, l++); l != data.catCol.end(); l++)
				{
					vector<string>& column1 = p->second;
					string cName1 = p->first;
					vector<string>& column2 = l->second;
					string cName2 = l->first;

					// inside the for loop, do the fun times chi-square stuff
					// first, get the number of variables in col1 and col2
					vector<string> chiCols;
					vector<int> chiColTot;


					// Get the number of unique variables in column 1, and how often they occur

					// want to parallelize, maybe can't if 2 threads find the same unique value simultaneously?

//#pragma omp parallel for schedule(dynamic,1000)
					for (int i = 0; i < p->second.size(); i++)
					{
						bool breaker = true;

						for (int j = 0; j <= chiCols.size(); j++)
						{
							//mtx.lock();

							// on the first item, always push onto the vector

							if (breaker && chiCols.size() == 0)
							{
								chiCols.push_back(column1[i]);
								chiColTot.push_back(1);
								breaker = false;

							}

							// if the item is unique and you have finished comparing to all current variables, push onto the vector
							else if (breaker && (column1[i] != chiCols[j] && j == chiCols.size() - 1))
							{
								chiCols.push_back(column1[i]);
								chiColTot.push_back(1);
								breaker = false;
							}

							// if you find a match, increase the count of that match
							else if (breaker && (column1[i] == chiCols[j]))
							{
								chiColTot[j]++;
								breaker = false;
							}
							//mtx.unlock();

						}

					}

					// same thing for the rows
					vector<string> chiRows;
					vector<int> chiRowTot;
					

//#pragma omp parallel for schedule(dynamic,10000000)
					for (int i = 0; i < column2.size(); i++)
					{
						bool breaker = true;

						for (int j = 0; j <= chiRows.size(); j++)
						{
//#pragma omp critical 
							// on the first item, always push onto the vector

							if (breaker && chiRows.size() == 0)
							{
								chiRows.push_back(column2[i]);
								chiRowTot.push_back(1);
								breaker = false;
							}

							// if the item is unique and you have finished comparing to all current variables, push onto the vector
							else if (breaker && column2[i] != chiRows[j] && j == chiRows.size() - 1)
							{
								chiRows.push_back(column2[i]);
								chiRowTot.push_back(1);
								breaker = false;
							}

							else if (breaker && column2[i] == chiRows[j])
							{
								chiRowTot[j]++;
								breaker = false;

							}
							//std::cout << "INNER " << j << " THREAD "<< omp_get_thread_num() <<endl;
						}
						//std::cout << "OUTER " << i << " " << endl;
					}

				
		

					// create a 2D vector to hold all of the observed values for each pair in the 2 columns
					// parallelize?
					vector<vector<int>> chiSquare(chiRows.size());
					for (int i = 0; i < chiRows.size(); i++)
						chiSquare[i] = vector<int>(chiCols.size());

					// go through and fill in the observed values. 
					// parallelize
#pragma omp for collapse(2) schedule(static,10000) //good to go
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
										//chiSquare[j][k]++;
										chiSquare[j][k]++;
									}
								}
							}
						}
					}

					// find the expected value and chi value for each cell; add them to get the chi Crit value
					float chiCrit = 0;
					// parallelize
//#pragma omp for collapse(2) schedule(dynamic) //need test
					for (int i = 0; i < chiRows.size(); i++)
					{
						for (int j = 0; j < chiCols.size(); j++)
						{
							// expected value = (row total * col total) / overall total
							float expected = ((float)chiRowTot[i] * (float)chiColTot[j]) / ((float)data.nrow - 1);

							//chi value = (observed - expected)^2 / expected value. chiChrit = sum of all chi values
							chiCrit += pow(((float)chiSquare[i][j] - expected), 2) / expected;
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

					// clear the 2D vector's memory
					chiSquare.clear();
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

	double pval = 0.5;
	int ncol = 0;
	int nrow = 0;
	struct Dataset data;
	vector<Correlation> results;
	string fileName;
	
	//get the file and pvalue from the user
	std::cout << "Enter a file name: " << endl;
	std::cin >> fileName;
	fileName = fileName + ".csv";
	std::cout << "enter a p-value." << endl;
	std::cin >> pval;
	
	// paralellize???
	std::ifstream myFile(fileName);
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

		// fill in the Datasctructure with the values we've found so far
		data.ncol = ncol;
		data.nrow = nrow;
		data.catCol = dataSet;

		// get the results of the chi-square test by calling the getPValues method and storing the results in results
		auto start = high_resolution_clock::now();
		results = getPValues(data, pval);
		auto stop = high_resolution_clock::now();
		// display all results in console (for now)
		for (int i = 0; i < results.size(); i++)
			std::cout << "Column 1: " << results[i].col_1_name << "\nColumn 2: " << results[i].col_2_name << "\nCoefficient: " << results[i].coeff << endl;



		auto duration = duration_cast<microseconds>(stop - start);
		std::cout << "Time taken by the function: " << duration.count() << " microseconds" << endl;
	}
	
	//time our method 
	//
	//

	

	myFile.close();

	return 0;
}
	
// testing

TEST_CASE("Given standard input", "[classic]")
{
	// create our custom input to test the standard input
	Dataset data;
	vector<string> col1{"cat", "cat", "cat", "cat","cat","cat","cat","cat","cat","cat",
		"dog","dog","dog","dog","dog","dog","dog","dog","dog","dog","dog"};
	vector<string> col2{"bird","bird","bird","bird","bird","fish","fish","fish","fish","fish",
		"bird","bird","bird","bird","bird","bird","fish","fish","fish","fish","fish"};
	unordered_map<string, vector<string>> entries;

	for (int i = 0; i < col1.size(); i++)
	{
		entries["pet1"].push_back(col1[i]);
	}
	for (int i = 0; i < col2.size(); i++)
	{
		entries["pet2"].push_back(col2[i]);
	}

	data.ncol = 2;
	data.nrow = 21;
	data.catCol = entries;

	SECTION("Testing standard input")
	{
		REQUIRE(getPValues(data, .05)[1].col_1_name == "pet1");
		REQUIRE(getPValues(data, .05)[1].col_2_name == "pet2");
		REQUIRE(getPValues(data, .05)[1].coeff == 1);
	}
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