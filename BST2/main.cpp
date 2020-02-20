//
// Julian Gonzales
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #02: inputs movies and reviews, allowing the user to search
// by movie ID, movie Name, or review ID.  Uses binary search trees for 
// fast search; no other data structures are allowed.
//

#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"


using namespace std;

//
// trim
//
// trims whitespace from beginning and end of string.
//
// Ref: https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
// Modified: to handle empty strings, and strings of all blanks.
//
string trim(const string& str)
{
  size_t first = str.find_first_not_of(" \t\n\r");
  size_t last = str.find_last_not_of(" \t\n\r");

  if (first == string::npos && last == string::npos)  // empty, or all blanks:
    return "";
  else if (first == string::npos)  // no blanks at the start:
    first = 0;                     // 0-based
  else if (last == string::npos)   // no blanks trailing at end:
    last = str.length() - 1;       // 0-based

  return str.substr(first, (last - first + 1));
}


//
// InputMovies
//
// Inputs the data from the "movies" file, which contains N>0 lines, where
// each line contains:
//     id pubYear name
//
template<typename Data> 
void InputMovies(string moviesFilename, binarysearchtree<int, Data> &tree, binarysearchtree<string,Data> &tree2)
{
  ifstream moviesFile(moviesFilename);
  int      id, pubYear;
  string   name;

  if (!moviesFile.good())
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
    return;
  }

 
//if next id exists keep looping
  while (moviesFile>>id)
  {
    // we have more data, so input publication year and movie name:
    moviesFile >> pubYear;
    getline(moviesFile, name);  // movie name fills rest of input line:
    // trim potential whitespace from both ends of movie name:
    name = trim(name);
    MovieData* data = new MovieData;
    data->PubYear = pubYear;
    data->name = name;
    data->id = id;
    data->Num1Star = 0;
    data->Num2Stars = 0;
    data->Num3Stars = 0;
    data->Num4Stars = 0;
    data -> Num5Stars = 0;
    //inserts same data from both trees
    //makes adding values to movie data much easier instead of going through it twice
    tree.insert(id, *data);
    tree2.insert(name, *data);
  }
}
//adds ratings to movie data
template<typename Data> 
void InputRatings(string ratingsFilename, binarysearchtree<int, Data> &tree, binarysearchtree<string, Data> &tree2){
  ifstream ratingsFile(ratingsFilename);
  int id;
  int rating;
  int movieId;
  int review;
  string rest;
  if(!ratingsFile.good()){
    cout << "**Error: unable to open movies file '" << ratingsFilename << "', exiting" << endl;
    return;
  }
  while (ratingsFile >> id)
  {
    ratingsFile >> movieId;
    ratingsFile >> review;
    getline(ratingsFile, rest);
    MovieData* data = tree.searchData(movieId);
    //Goes through all reviews and adds one based on review rating
    tree.numReviewsPlusOne();
    if(review == 5){
      data->Num5Stars++;
    }else if(review == 4){
      data->Num4Stars++;
    }else if(review == 3){
      data->Num3Stars++;
    }else if(review == 2){
      data->Num2Stars++;
    }else{
      data->Num1Star++;
    }

  }
}
//side project idea create a program with ece skills to read in bluetooth or various other frequencies by choice
template<typename Data>
void userInput(binarysearchtree<int, Data> tree, binarysearchtree<string, Data> tree2){
  cout << "Num movies: " << tree.size() << endl;
  cout << "Num reviews: " << tree.numReviews() << endl;
  cout << endl;
  cout << "Tree by movie id: size=" << tree.size() << ", height=" << tree.height() << endl;
  cout << "Tree by movie name: size=" << tree2.size() << ", height=" << tree2.height() <<endl;
  cout << endl;
  string input = "";
  string append;
  while(input != "#"){
  cout << "Enter a movie id or name (or # to quit)> ";
  getline(cin, input);

    if(input[0] == '#'){
      break;
    }
    bool check = false;
    //checks if any of the characters contain a letter through ascii
    //assuming id's are only numbers from data
    for(int i = 0; i < input.size(); i++){
      if((int)input[i] - '0' > 9){
        displayData(input, tree2);
        check = true;
        break; 
      }
    }
    //if does not contain letters then do id tree
    if(!check){
        displayData(stoi(input), tree);

    }
  }

}
//calculates average
double getAvarage(MovieData data){
  double totalReviews = data.Num5Stars + data.Num4Stars + data.Num3Stars + data.Num2Stars + data.Num1Star;
  if(totalReviews == 0){
    return 0.0;
  }
  double star5 = data.Num5Stars*5.0;
  double star4 = data.Num4Stars*4.0;
  double star3 = data.Num3Stars*3.0;
  double star2 = data.Num2Stars*2.0;
  double star1 = data.Num1Star*1.0;
  double totalPoints = star5 + star4 + star3 + star2 + star1;
  totalPoints = totalPoints/totalReviews;
  return totalPoints;
}
//displays data in movieData
template<typename key,typename Data>
void displayData(key id, binarysearchtree<key, Data> tree){
  MovieData* data = tree.searchData(id);
  if(data == nullptr){
    cout << "not found..." << endl;
    cout << endl;
  }else{
    double average = getAvarage(*data);
    cout << "Movie ID: " << data->id <<endl;
    cout << "Movie Name: " << data->name << endl;
    cout << "Avg rating: " << average << endl;
    cout << "5 stars: " << data->Num5Stars<< endl;
    cout << "4 stars: " << data->Num4Stars<< endl;
    cout << "3 stars: " << data->Num3Stars<< endl;
    cout << "2 stars: " << data->Num2Stars<< endl;
    cout << "1 star: " << data->Num1Star<< endl;
    cout << endl;
  }
}


//
// main
//
int main()
{
  string moviesFilename; // = "movies1.txt";
  string reviewsFilename; // = "reviews1.txt";
  binarysearchtree<int, MovieData> IdTree;
  binarysearchtree<string, MovieData> nameTree;
  cout << "movies file?> ";
  cin >> moviesFilename;
  cout << "reviews file?> ";
  cin >> reviewsFilename;
  string junk;
  getline(cin, junk);  // discard EOL following last input:
  InputMovies(moviesFilename, IdTree, nameTree);
  InputRatings(reviewsFilename, IdTree, nameTree);
  userInput(IdTree, nameTree);
  // done:
  return 0;
}
