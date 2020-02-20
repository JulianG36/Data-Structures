/*main.cpp*/

//
// myDB project using AVL trees
//
// Julian Gonzales
// NetID: Jgonz96
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project #04
// Description: Creates a database like scenerio using trees to search quickly could implement more queries like insert
// Improvements: Graballdata and grabPartialData could be combined, more passing by address with vectors to avoid copy constructor

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>

#include "avl.h"
#include "util.h"

using namespace std;


//
// tokenize
//
// Given a string, breaks the string into individual tokens (words) based
// on spaces between the tokens.  Returns the tokens back in a vector.
//
// Example: "select * from students" would be tokenized into a vector
// containing 4 strings:  "select", "*", "from", "students".
//
vector<string> tokenize(string line)
{
  vector<string> tokens;
  stringstream  stream(line);
  string token;

  while (getline(stream, token, ' '))
  {
    tokens.push_back(token);
  }

  return tokens;
}

vector<avltree<string, int>*> createTrees(string tablename, vector<string>* allColumns, vector<int>* indexPositions, ifstream *data){
	cout << "Reading meta-data..." << endl;
	ifstream file(tablename + ".meta");
	if(!file.good()){
		cout << "Could not find metaData" << endl;
		exit(0);
	}
	string dataSize = "";
	string columns = "";
	file >> dataSize;
	file >> columns;
	string columnFromfile = "";
	char indexed;
	file >> columnFromfile;
	file >> indexed;
	int index = 0;
	while(file.good()){
		if(indexed == '1'){
			indexPositions->push_back(index);
		}
		allColumns->push_back(columnFromfile);
		index++;
		file >> columnFromfile;
		file >> indexed;
    }
	//
	// TODO:
	//
	cout << "Building index tree(s)..." << endl;
	vector<avltree<string, int>*> trees(indexPositions->size());
	int positon = 0;
	string currValue;
	*data >> currValue;
	while(!data->eof()){
		
		vector<string> lineValues;
		// grabs from file for the amount of columns
		
		for(string names : *allColumns){
			lineValues.push_back(currValue);
			*data >> currValue;
		}
		//values for indexPositions
		vector<string> treeKeys;
		for(int i : *indexPositions){
			treeKeys.push_back(lineValues.at(i));
		}
		//from the amount of indexed positions create that amount of trees
		//places the data value into specified tree
		for(unsigned int keyPosition = 0; keyPosition < treeKeys.size(); keyPosition++){
			avltree<string, int> *currTree = trees.at(keyPosition);
			if(currTree == nullptr){
				currTree = new avltree<string, int>;
			}
			currTree->insert(treeKeys.at(keyPosition), positon);
			trees.at(keyPosition) = currTree;
		}
		positon = positon + stoi(dataSize);
		string padding = "";
		getline(*data, padding);
		*data >> currValue;
	}
	int i = 0;
	for(avltree<string, int>* tree : trees){
		cout << "Index column: " << allColumns->at(indexPositions->at(i)) << endl;
      	cout << "  Tree size: " << tree->size() << endl;
		cout << "  Tree height: "<< tree->height() << endl;
		i++;
	}
	return trees;
}
//erases first token in a vector 
vector<string> eraseFirstToken(vector<string> tokens){
	vector<string> tokensResize(tokens.size()-1);
	for(unsigned int i = 1; i < tokens.size(); i++){
			tokensResize.at(i-1) = tokens.at(i); 
	}
	return tokensResize;
}
//searches columns that are indexed 
int indexedSearch(string target, vector<vector<string>> *matches, vector<avltree<string, int>*> *trees, int positon){
	avltree<string,int>* tree = trees->at(positon);
	int* offset = tree->search(target);
	if(offset == nullptr){
		return -1;
	}else{
		return *offset;
	}	
}
//searches sequentialy the specified table
void seqSearch(string target, vector<vector<string>> *matches, int positon, vector<string> *allColumns, ifstream *data){
	data->clear();
	data->seekg(0, ios::beg);
	string val = "";
	*data >> val;
	while(data->good()){
		vector<string> lineValues;
		for(unsigned int i = 0; i < allColumns->size(); i++){
			lineValues.push_back(val);
			*data >> val;
		}
		if(lineValues.at(positon) == target){
			matches->push_back(lineValues);
		}
		string garbage = "";
		getline(*data, garbage);
		*data >> val;		
	}
	return;
}
//checks if the target is in the vector and if it is indexed
bool checkIfInVector(vector<string> *targetValues, string target, int* positon){
	bool indexed = false;	
	for(unsigned int i = 0; i < targetValues->size(); i++){
		if(targetValues->at(i) == target){
			indexed = true;
			*positon = i;
			break;
		}
	}
	return indexed;
}
//gets the record from the offset
vector<string> GetRecord(ifstream* data, int pos, int numColumns)
{
	vector<string> values;
	data->clear();
	data->seekg(0, ios::beg);
	if (!data->good())
	{
		cout << "**Error: couldn't open data file '" << endl;
		return values;
	}
	string    value;
	data->seekg(pos, data->beg);
	for(int i = 0; i < numColumns; i++){
		string lineValue = "";
		*data >> lineValue;
		values.push_back(lineValue);
	}


  return values;
}
//handles printing the entire row of data
void printAll(vector<vector<string>> *results, vector<string> *allColumns){
	for(vector<string> item: *results){
		for(unsigned int i = 0; i < item.size(); i++){
			cout<<allColumns->at(i)<<": "<< item.at(i) << endl;
		}
	}
}
//handles printing some of the data 
void printSome(int columnToPrint ,vector<vector<string>> *results, vector<string> *allColumns){
	for(vector<string> item: *results){
		cout << allColumns->at(columnToPrint) << ": " << item.at(columnToPrint)<<endl;
	}
}
//grabs data like grabpartial data but displays everything
void grabAllData(vector<string> tokens, vector<string> indexedColumns, vector<string> allColumns, vector<avltree<string, int>*> *trees, ifstream *data){
	string column2 = tokens[4];
	string target = tokens[6];
	vector<vector<string>> results;
	int offset;
	int positon = 0;
	int positon2 = 0;
	if(checkIfInVector(&indexedColumns, column2, &positon)){
		offset = indexedSearch(target, &results, trees, positon);
		if(offset == -1){
			cout<<"Not found..."<<endl;
			return;
		}
		results.push_back(GetRecord(data, offset, allColumns.size()));
	}else if(checkIfInVector(&allColumns, column2, &positon2)){
		seqSearch(target, &results, positon2, &allColumns, data);
	}else{
		cout << "Invalid where column, ignored..." << endl;
		return;
	}
	if(results.size() == 0){
		cout <<"Not found..." << endl;
		return;
	}
	printAll(&results, &allColumns);
}
//grabs the data with the specified offset or sequential search
void grabPartialData(vector<string> tokens, int columnToPrint ,vector<string> indexedColumns, vector<string> allColumns, vector<avltree<string, int>*> *trees, ifstream* data){
	string column1 = tokens[0];
	string column2 = tokens[4];
	string target = tokens[6];
	vector<vector<string>> results;
	int offset;
	int positon = 0;
	int positon2 = 0;
	//checks if its indexed if not then go to a sequential search. checks if its a valid second column
	if(checkIfInVector(&indexedColumns, column2, &positon)){
		offset = indexedSearch(target, &results, trees, positon);
		if(offset == -1){
			cout<<"Not found..."<<endl;
			return;
		}
		results.push_back(GetRecord(data ,offset,allColumns.size()));
	}else if(checkIfInVector(&allColumns, column2, &positon2)){
		seqSearch(target, &results, positon2, &allColumns, data);
	}else{
		cout << "Invalid where column, ignored..." << endl;
		return;
	}
	if(results.size() == 0){
		cout <<"Not found..." << endl;
	}
	
	printSome(columnToPrint, &results, &allColumns);
}
//checks if the structure of select is correct
bool checkSelectStructure(vector<string>* tokens, string tablename){
	if(tokens->size() != 7){
		cout << "Invalid select query, ignored..." << endl;
		return false;
	}
	if(tokens->at(1) != "from"){
		cout << "Invalid select query, ignored..." << endl;
		return false;
	}if(tokens->at(2) != tablename){
		cout << "Invalid table name, ignored..." << endl;
		return false;
	}if(tokens->at(3) != "where"){
		cout << "Invalid select query, ignored..." << endl;
		return false;
	}if(tokens->at(5) != "="){
		cout << "Invalid select query, ignored..." << endl;
		return false;
	}
	return true;
}

//determines what type of select it is wether its select everything or partial data
void handleSelect(vector<string> tokens, vector<string> indexedColumns, vector<string> allColumns, string tablename, vector<avltree<string, int>*> *trees, ifstream* data){
	if(!checkSelectStructure(&tokens, tablename)){
		return;
	}
	if(tokens[0] == "*"){
		grabAllData(tokens, indexedColumns, allColumns, trees, data);
	}else{
		//checks if the specified column is part of the valid columns 
		for(unsigned int i = 0 ; i < allColumns.size(); i++){
			if(allColumns.at(i) == tokens[0]){
				grabPartialData(tokens, i,indexedColumns, allColumns, trees, data);
				return;
			}
		}
		cout << "Invalid select column, ignored..." << endl;
	}
}
//creates a vector with all the valid indexed columns
vector<string> getIndexedColumns(vector<int> indexPositions, vector<string> allColumns){
	vector<string> newVector;
	for(unsigned int i = 0; i < allColumns.size(); i++){
		for(unsigned int j = 0; j < indexPositions.size(); j++){
			if(i == (unsigned int)indexPositions[j]){
				newVector.push_back(allColumns.at(i));
			}
		}
	}
	return newVector;	
}


int main()
{
	string tablename;
	cout << "Welcome to myDB, please enter tablename> ";
	getline(cin, tablename);
	vector<int> indexPositions;
	vector<string> allColumns;
	ifstream data(tablename + ".data");
	vector<avltree<string, int>*> trees = createTrees(tablename, &allColumns, &indexPositions, &data);
	vector<string> indexedColumns = getIndexedColumns(indexPositions, allColumns);
	//
	// TODO:
	//

	//
	// Main loop to input and execute queries from the user:
	//
	string query;
	cout << endl;
	cout << "Enter query> ";
	getline(cin, query);

	while (query != "exit")
	{
	vector<string> tokens = tokenize(query);
	if(tokens[0] == "select"){
		handleSelect(eraseFirstToken(tokens), indexedColumns, allColumns, tablename, &trees, &data);
		//could do any other query
	}else{
		cout << "Unknown query, ignored..." << endl;
	}


	//
	// TODO:
	//


	cout << endl;
	cout << "Enter query> ";
	getline(cin, query);
	}

	//
	// done:
	//
	return 0;
}
