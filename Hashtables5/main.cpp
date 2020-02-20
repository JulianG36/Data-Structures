/*main.cpp*/

//
// Hashing program for specialized Illinois license plates,
// which processes an input file of license plates and fines.
// The output is the total fines per license plate, in 
// sorted order.
//
// Original author: Prof. Joe Hummel
// Modified by:     Julian Gonzales
// NetID: Jgonz96
//
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>


#include "ILplates.h"

using namespace std;


//
// hashInput:
//
void hashInput(string basename, ILplates& hashplates)
{
  string infilename = basename + ".txt";
  ifstream infile(infilename);

  if (!infile.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << infilename << "', exiting." << endl;
    cout << endl;
    exit(-1);
  }

  //
  // input the plates and fines:
  //
  cout << "Reading '" << infilename << "'..." << endl;

  string fine;
  string plate;

  getline(infile, fine);

  //
  // for each pair (fine, license plate), hash and store/update fine:
  //
  while (!infile.eof())
  {
    getline(infile, plate);

    //cout << fine << endl;
    //cout << plate << endl;

    // 
    // is plate valid?  Only process valid plates:
    //
    if (hashplates.Hash(plate) >= 0)  // yes:
    {
      int amount = hashplates.Search(plate);

      if (amount < 0)  // not found:
      {
        hashplates.Insert(plate, stoi(fine));
      }
      else  // we found it, so update total in hash table:
      {
        amount += stoi(fine);
        hashplates.Insert(plate, amount);
      }

    }//valid

    getline(infile, fine);
  }
}
void _merge(vector<string> &plates, vector<int> &tickets, int left, int middle, int right){
	//size of the left and right subArray
	int start1 = 1 + (middle-left);
	int start2 = right - middle;
	//Temporary vectors to store left and right subArrays
	//sorts the tickets vector the same way the plates vector get sorted
	//to keep equal positions
	vector<string> plateLeft(start1);
	vector<int> valLeft(start1);
	vector<string> plateRight(start2);
	vector<int> valRight(start2);
	//storing first and second half
	for (int i = 0; i < start1; i++){
		plateLeft.at(i) = plates.at(left+i);
		valLeft.at(i) = tickets.at(left+i);
	}
    for (int j = 0; j < start2; j++){
		plateRight.at(j) = plates.at(middle+j+1);
		valRight.at(j) = tickets.at(middle+j+1);
	}
	int i = 0;
	int j = 0;
	int k = left;
	//storing values from start to end based on wether the left or right is greater
	while (i < start1 && j < start2) 
    { 
        if (plateLeft.at(i)<= plateRight.at(j)){ 
			plates.at(k) = plateLeft.at(i);
            tickets.at(k) = valLeft.at(i);
			i++; 
        }else{ 
            plates.at(k) = plateRight.at(j);
			tickets.at(k) = valRight.at(j);
            j++; 
        } 
        k++; 
    } 
	//stores the remaining values will only do one of the loops
	while(i < start1){
		plates.at(k) = plateLeft.at(i);
        tickets.at(k) = valLeft.at(i);
		i++; 
		k++;
	}
	while(j < start2){
		plates.at(k) = plateRight.at(j);
		tickets.at(k) = valRight.at(j);
        j++;
		k++;
	}
}
//starts the merge sort and splits array into sub arrays
void mergeSort(vector<string> &plates, vector<int> &tickets, int left, int right){
	if(left < right){
		int middle = (right + left) /2;
		
		mergeSort(plates, tickets, left, middle);
		mergeSort(plates, tickets, middle+1, right);
		_merge(plates, tickets, left, middle, right);
	}
}

int main()
{
  int    N;        // = 10000;
  string basename; // = "tickets1";

  cout << "Enter hashtable size> ";
  cin >> N;

  hashtable<string, int>  ht(N);
  ILplates                hashplates(ht);

  cout << "Enter base filename> ";
  cin >> basename;
  cout << endl;

  //
  // process input file of fines and license plates:
  //
  hashInput(basename, hashplates);

  //
  // debugging:
  //
  vector<string> plates = ht.Keys();
  vector<int> amounts = ht.Values();
  mergeSort(plates, amounts, 0, plates.size()-1);
  for (size_t i = 0; i < plates.size(); ++i)
  {
    cout << plates[i] << ", " << amounts[i] << endl;
  }
  ofstream file;
  file.open(basename+"-output.txt", ofstream::out | ofstream::trunc);
  file.close();
  file.open(basename+"-output.txt");
  
	
  for(unsigned int j = 0; j < plates.size(); j++){
  	file << "\"" << plates.at(j) << "\"" << " $" << amounts.at(j) << endl;
  }
  return 0;
}