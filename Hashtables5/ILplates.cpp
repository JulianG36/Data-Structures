/*ILplates.cpp*/

//
// Hashing functions to store (license plate, amount) pairs
// using linear probing.
//
// Julian Gonzales
// NETID: Jgonz96
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <string>
#include "ILplates.h"

using namespace std;


//
// Hash:
//
// Given a specialized Illinois license plate, returns an index into
// the underyling hash table.  If the given plate does not follow the
// formatting rules given below, -1 is returned.
//
// Personalized:
//   letters and numbers, with a space between the letters 
//   and numbers.  Format: 1-5 letters plus 1..99 *OR* 
//   6 letters plus 1..9
//
//   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
//
// Vanity:
//   Format: 1-3 numbers *OR* 1-7 letters
// 
//   Examples: 007, 1, 42, X, AAA, ZZZEFGH
//
bool checkPlate(int countNumbers, int countLetters, int size, int counted){
	if(counted != size){
		return false;
	}else if((countNumbers + countLetters) < 1){
		return false;
	}else if(countLetters >= 1 && countLetters <= 5 && countNumbers >= 1 && countNumbers <= 2){
		return true;
	}else if(countNumbers <= 3 && countLetters == 0){//1 to 3 numbers
		return true;
	}else if(countLetters == 6 && countNumbers == 1){//6 letters and one number
		return true;	
	}else if(countNumbers == 0 && countLetters <=7 && countLetters >= 1){
		return true;
	}else{
		return false;
	}
}
int ILplates::Hash(string plate)
{
	//O(N) for the size of the plate so very small
  	int index = 0;
	int power = 1;
	int size = plate.size();
	int countLetters = 0;
	int countNumbers = 0;
	int i;
	//based on where the letter is positioned it will multiply it by its power
	//gives distinct values for every plate
	//will not execute if no letters
	for(i = 0; i < size; i++){
		if(plate[i] >= 65 && plate[i] <= 90){
			index = index + (plate[i]-65)*power;
			power = power*10;
			countLetters++;
		}else{
			break;
		}
	}
	//checks if theres a space
	if(plate[i] == ' '){
		i++;
	}
	int j;
	//continues from where i left off
	//will not execute if no numbers
	for(j = i; j < size; j++){
		if(plate[j] >= 48 && plate[j] <= 57){
			index = index + (plate[i]-48)*power;
			power = power*10;
			countNumbers++;
		}else{
			break;
		}
	}
	
	//check plate if valid then return the index;
	if(checkPlate(countNumbers, countLetters, size, j)){
		return index % HT.Size();
	}else{
		return -1;
	}
}


//
// Search
// 
// Hashes and searches for the given license plate; returns the 
// associated value for this plate if found, or -1 if not found.
//
int ILplates::Search(string plate)
{
	int index = Hash(plate);
	int size = HT.Size();
	bool emptyCheck;
	int valCheck;
	string keyCheck;
	HT.Get(index, emptyCheck, keyCheck, valCheck);     
	int bucketsProbed = 0;
   	while (bucketsProbed < size) {
		if(keyCheck == plate){
            return valCheck;
		}else if (emptyCheck) {
			return -1;  
		}
		index = (index + 1) % size;
		HT.Get(index, emptyCheck, keyCheck, valCheck);
		++bucketsProbed; 
  	}
	return -1;
}


//
// Insert
//
// Inserts the given (plate, newValue) into the hash table,
// overwriting an existing value if there.
//
void ILplates::Insert(string plate, int newValue)
{
	int index = Hash(plate);
	int size = HT.Size();
	bool emptyCheck;
	int valCheck;
	string keyCheck;
	HT.Get(index, emptyCheck, keyCheck, valCheck);     
	int bucketsProbed = 0;
   	while (bucketsProbed < size) {
     // Insert item in next empty bucket 
        if(keyCheck == plate){
			HT.Set(index, plate, newValue);
			return;
		}else if(emptyCheck) {
        	HT.Set(index, plate, newValue);
        	return;  
     }
      // Increment bucket index
     index = (index + 1) % size;
	 HT.Get(index, emptyCheck, keyCheck, valCheck);
      // Increment number of buckets probed
     ++bucketsProbed; 
  	}
}
