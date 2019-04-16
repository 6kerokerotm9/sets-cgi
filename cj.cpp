#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

void pascal(int, vector<int>&);
void powerset(vector<int>);
void cartesian(vector<int>, vector<int>, vector<vector<int>>&);
void binaryRelations(vector<int>, vector<int>);

int main()
{
  vector<int> set = {1, 2, 3, 4};
  vector<int> set2 = {1, 2 ,3};
  vector<vector<int>> product;
  cartesian(set, set2, product);
  cout << "asdf" << endl;
  //for(int i = 0; i<product.size(); i++) {
  //}
}

//pascal's triangle function which takes an int for the line number and vector to store the values of the line
void pascal(int line, vector<int> &working){
    vector <int> prev = {1, 1}; //the line before the current working one; also starts at line 2 of pascal's triangle
    vector <int> kerr; //current working line of pascal's triangle
    int temp = 0; //temporary variable as a index of the previous line
    if(line == 1) { //if the program just needs the first line
        working = {1};
        return;
    }
    else if(line == 2) { //if the program just needs the second line
        working = prev;
        return;
    }
    for(int i = 2; i < line; i++) //fills each line of pascal's triangle by first identifying how many lines are needed 
    {
        temp = 0; //reinitializes the temp everytime so the index will start at the beginning everytime
        for(int j = 0; j < i+1; j++) //fills out the next line with one added element 
        {
            if(j == 0) { //starts the new line with a 1 
                kerr.push_back(1);
            } 
            else if(j+1 == i+1) { //ends the line with a 1
                kerr.push_back(1);
                break;
            }
            else { //fills out the in between
                kerr.push_back(prev[temp] + prev[temp+1]); //adds together the index and the next index of the previous line
                temp++; //moves the index 
            }
        }
        prev = kerr; //sets the new line to the previous 
        kerr = {}; //creates a new line to repeat the processes to fill out the lines of pascal's triangle
    }
    working = prev;
}

//finds the powerset by accepting a set of ints 
void powerset(vector<int> set) {
    //vector<string> power = {"0"}; //this is a string as the different subsets will be stored into strings, starts with null already in it
    vector<int> working; //stores the line from pascal's triangle; to be used with the function pascal
    pascal(set.size()+1, working); 
    for(int i=0; i<set.size(); i++) {
        cout << set[i] << endl;
    }
    for(int i = 0; i < set.size()-1; i++) {
        for(int j = i+1; j < set.size(); j++) {
            cout << set[i] << ", " << set[j] << endl;
        }
    }
}

//finds the cartesian product of two sets
void cartesian(vector<int> setA, vector<int> setB, vector<vector<int>>& product) {
	//vector<vector<int>> product;
    for(int i = 0; i < setA.size(); i++) { //first loop starts at first set and finds all the coordinates for each index 
        for(int j = 0; j < setB.size(); j++) { //second loop is second set and program finishes all of the index of first set
            vector<int> temp = {setA[i], setB[j]}; 
            product.push_back(temp); 
        }
    }
}

void binaryRelations(vector<int> p1, vector<int> p2) {
	int p3 = p1.size() * p2.size();
}
