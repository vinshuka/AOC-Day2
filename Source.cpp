#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>


//Day 2 Part 1
//Given a list of passwords, in the format of min-max character: password, where valid passwords contain have the number of occurances of the character
//between the min and max inclusive, count the number of valid passwords.

//Current plan is to create a struct that contains all the variables contained in each password, then we can split each string of the puzzle input and
//make an object for each on, we'll store these objects in a vector or map. Then we will set a count and iterate through the each object, we will count
//the number of the given character in the password, then compare it to the max and min, if it is within the range we increase the count, else we 
//continue to the next object.

//Day 2 Part 2
//The min and max values are actually positions, the character must appear at either position but not both, count the number of passwords that meet this condition

struct password
{
	int min;
	int max;
	char c;
	std::string pass;
};

std::vector<std::string> getPuzzleInput()
{
	std::vector<std::string> input;

	std::ifstream file;
	std::string line;
	file.open("puzzle-input.txt");
	int count = 0;
	while (std::getline(file, line))
	{
		input.push_back(line);
	}

	return input;
}

std::vector<std::string> split(const std::string s, char delim)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> tokens;
	while (getline(ss, item, delim))
	{
		tokens.push_back(item);
	}
	
	return tokens;
}

std::vector<password> splitItems(std::vector<std::string> input)
{
	std::vector<password> result;
	int count = 0;
	std::string pass;
	for (int i = 0; i < input.size(); i++)
	{
		std::vector<std::string> parts = split(input[i], ' ');

		int index = parts[0].find("-");
		int min = std::stoi(parts[0].substr(0, index));
		int max = std::stoi(parts[0].substr(index + 1));
		char c = parts[1][0];
		std::string pass = parts[2];

		result.push_back({ min, max, c, pass });
	}
	return result;
}


//correct solution for part 1, man I had to go through so much nonsense to get here
int findAnswerPart1(std::vector<password> input)
{
	int count = 0;

	for (auto x : input)
	{
		std::string s = x.pass;
		int occurrance = std::count(s.begin(), s.end(), x.c);
		if (occurrance >= x.min && occurrance <= x.max)
			count++;
	}
	return count;
}

//Here we simply check the char at the position to see if it matches while making sure the char at the other position does not match, we subtract 1 to make the positions zero based instead of 1 based.
//If one but not the other of our checks is true we increase our count.
int findAnswerPart2(std::vector<password> input)
{
	int count = 0;

	for (auto x : input)
	{
		if (x.pass.at(x.min - 1) == x.c && x.pass.at(x.max - 1) != x.c || x.pass.at(x.min - 1) != x.c && x.pass.at(x.max - 1) == x.c)
			count++;
	}
	return count;
}

int main()
{
	std::vector<std::string> input = getPuzzleInput();
	/*for (int i = 0; i < input.size(); i++)
	{
		std::cout << input[i] << '\n';
	}*/

	std::vector<password> splitInput = splitItems(input);

	/*for (int i = 0; i < splitInput.size(); i++)
	{
		std::cout << "min:" << splitInput[i].min << " max:" << splitInput[i].max << " char:" << splitInput[i].c << " pass:" << splitInput[i].pass << '\n';
	}*/

	std::cout << findAnswerPart1(splitInput) << '\n';
	std::cout << findAnswerPart2(splitInput) << '\n';

	return 0;
}