// chiSquared.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>


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



int main()
{
	
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
