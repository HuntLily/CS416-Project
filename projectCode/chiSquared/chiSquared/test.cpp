#define CONFIG_CATCH_MAIN
#include "catch.hpp"
#include <unordered_map>
#include <vector>

struct Dataset
{
	int nrow = 0; //number of rows
	int ncol = 0; //number of columns	
	std::unordered_map<std::string, std::vector<std::string>> catCol; // categorical columns
};

TEST_CASE("", "[classic]")
{
}