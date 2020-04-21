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


class ChiSquared
{
public:
	double pval = .05;
	struct Dataset
	{
		int nrow; //number of rows
		int ncol; //number of columns
		unordered_map<string, vector<string>> cat_cols; //categorical cols
		unordered_map<string, vector<float>> num_cols; //numerical cols
	};
	struct Correlation
	{
		string col_1_name;
		string col_2_name;
		float coeff;
	};
	
	
	
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



int main()
{
	std::vector<std::pair<std::string, std::vector<int>>> ex = readCSV("example.csv");
	
	std::vector<int>::size_type sz = ex.size();
	for (int i = 0; i < ex.size(); i++)
	{
		cout << ex[i].first << ", " << ex.at(i).second[i] << endl;
		
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
