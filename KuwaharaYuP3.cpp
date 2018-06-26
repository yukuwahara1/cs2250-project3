//============================================================================
// Name        : KuwaharaYuP3.cpp  
// Author      : Yu Kuwahara
//============================================================================

#include "stdafx.h"
#include <iostream>
#include <fstream> // open and read a file
#include <string> 
#include <vector> // need to make a vector inside of a structure
using namespace std;

//=============STRUCTURE======================================================

struct Replacemap
{
	// if there is a pair of words, shown in a line as "cat dog"
	string original; // "cat"
	string replacement; // "cat" will be replaced with "dog"
};

//=============FUNCTION PROTOTYPES============================================

void readFile(string fileOriginal, vector<Replacemap> & replaceMap);

//=======MAIN=================================================================

int main()
{

//=======TASK 1===============================================================

	// declare a variable for a vector of the "Replacemap" object
	vector<Replacemap> replaceMap;

	string fileOriginal; // variable for the file name with pairs of words

	ifstream fin;

	cout << "Welcome to the supersecret company!\n";

	// ask a user for the name of the file with the pairs
	cout << "Please enter a file name: ";
	getline(cin, fileOriginal); // use "getline" command since the file name contains "."
	readFile(fileOriginal, replaceMap); // call the function to perform task 1

//=======TASK 2===============================================================

	cin.clear(); // clear all the error flags

	// variable used when modifying the target file to create the destination file with the vector from task 1
	string inputSpring; 
	string fileTarget; // target file needs to be stored as string
	string fileDestination; // same as above for destination file

	// ask the user for the name of the target file
	cout << "Please enter the name of the target file: ";
	getline(cin, fileTarget);

	fin.open(fileTarget);

	// Error check 1
	// show an error message if the file cannot be located

	if (!fin) 
	{
		cout << "There is an error opening the file.\n";
		cin.get(); // avoid exiting the whole window
		exit(1); // keep the message above shown
	}

	// Error check 2
	// check if the file is empty or not

	// "peek" command returns the next character in the input sequence without extracting it
	int firstCharacter = fin.peek(); 

	if (firstCharacter == EOF) // EOF means end if the file
	{
		cout << "This file is empty.\n";
		cin.get(); // avoid exiting the whole window
		exit(1); // keep the message above shown
	}

	// ask the user for the name of the destination file
	cout << "Please enter the name of the destination file: ";
	getline(cin, fileDestination);

	// create the destination file by modifying the target file
	ofstream fout;
	fout.open(fileDestination);

	// read the target file line by line
	while (getline(fin, inputSpring))
	{
		// search for the words in the vector from task 1
		// need to use "size_t" instead of "int" since it is vector
		for (size_t i = 0; i < replaceMap.size(); ++i)
		{
			// replace words  
			// "find" command to search for the words that need to be replaced
			while (inputSpring.find(replaceMap.at(i).original) != -1)
			{
				inputSpring.replace(inputSpring.find(replaceMap.at(i).original), replaceMap.at(i).original.size(), replaceMap.at(i).replacement);
			}
		}
	
		fout << inputSpring << endl;
	}

	fout.close();
	fin.close();

	// open to read the file and output it line by line
	fin.open(fileDestination);

	// string to store the line read from the destination file
	string outputString;

	// read the file line by line and display it
	while (getline(fin, outputString)) 
	{
		cout << outputString << endl;
	}

	fin.close();

	return 0;

}

//===========FUNCTION DEFINITIONS=============================================

// This function takes in a file name entered by a user
// and put the content of the file into a vector of "ReplaceMap" by reference
// and finally display the entire vector

void readFile(string fileOriginal, vector<Replacemap> & replaceMap)
{

	ifstream fin; 
	string fileName; // variable used to create the vector

	fin.open(fileOriginal);

	// Error check 1
	// show an error message if the file cannot be located

	if (!fin) 
	{
		cout << "There is an error opening the file.\n";
		cin.get(); 
		exit(1); 
	}

	// Error check 2
	// check if the file is empty or not

	int firstCharacter = fin.peek(); 

	if (firstCharacter == EOF) 
	{
		cout << "This file is empty.\n";
		cin.get(); 
		exit(1); 
	}

	// Error check 3
	// each of the lines can only have one white space

	string currentLine;

	while (getline(fin, currentLine))
	{
		int count = 0;

		// use auto since the data type is not clear
		// "begin" command returns an iterator pointing to the first element in the sequence
		// "end" command returns an iterator pointing to the past-the-end element in the sequence

		// exit once the program detects a line that has more or less than once white space
		for (auto i = currentLine.begin(); i != currentLine.end(); ++i)
		{
			if (*i == ' ')
			{
				count++;
			}
		}

		if (count != 1)
		{
			cout << "At least one of the lines does not have a pair of words." << endl;
			exit(1);
		}

		count = 0;

		while (fin >> fileName)
		{
			Replacemap temp; // declare a temporary variable for the structure
			temp.original = fileName;
			fin >> temp.replacement;
			replaceMap.push_back(temp); 
		}

		// display the entire vector 
		// convert the size into bytes since it needs to display a vector not an integer
		for (size_t i = 0; i < replaceMap.size(); i++)
		{
			cout << replaceMap[i].original << " -> " << replaceMap[i].replacement << endl;
		}

	}

	fin.close();

}
