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
	
	
	

std::vector<std::pair<std::string, std::vector<int>>> readCSV(std::string filename)
{
	std::vector<std::pair<std::string, std::vector<int>>> result;
	//create an input filestream
	std::ifstream myFile(filename);

	//make sure the file is open
	if (!myFile.is_open()) throw std::runtime_error("Could not open file");

	//helper values
	std::string line, colname;
	int val;
	//read column names
	if (myFile.good())
	{
		std::getline(myFile, line);

		std::stringstream ss(line);
		//extract each column name
		while (std::getline(ss, colname, ','))
		{
			//add column name and int vector pairs to result
			result.push_back({ colname, std::vector<int>{}});
		}
	}
	//read data line by line
	while (std::getline(myFile, line))
	{
		std::stringstream ss(line);
		//keep track of the column
		int colIndex = 0;
		while (ss >> val)
		{
			result.at(colIndex).second.push_back(val);
			if (ss.peek() == ',') ss.ignore();
			colIndex++;
		}
	}


	myFile.close();
	return result;

}

/*
How to do a Chi-Square Test
Step 1: Find the Expected Values
	- Get the total for each column and row being tested
	- Find (Row total * Column total)/total of all rows and columns combined
Step 2: Use formula to get Chi Square values
	- (Observed - Expected)^2 / Expected
Step 3: add all Chi Square values together.
Step 4: find Degrees of Freedom = (# of rows - 1) * (# of columns -1)
Step 5: use library given these 2 values to find p value
*/



int main()
{
	double pval = .05;
	//std::vector<std::pair<std::string, std::vector<int>>> ex = readCSV("example.csv");
	
	//std::vector<int>::size_type sz = ex.size();
	//for (int i = 0; i < ex.size(); i++)
	//{
	//	cout << ex[i].first << ", " << ex.at(i).second[i] << endl;
	//	
	//}
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