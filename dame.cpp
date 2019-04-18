#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

//converts integers into binary similar to the method by hand; accepts a vector to store the binary bit-by-bit, the amount of bits required, and the integer to be converted
void binaryC(vector<int>& binary, int workingsize, int div) {
  int rem = 1; //variable to hold the remainder during the division processes
  for(int i = 0; i < workingsize; i++) { //this whole part is taking the integer and dividing it by 2 each time to find the binary representation of the integer
    rem = div % 2;
    binary.insert(binary.begin(), rem); //puts the result of the modulus in the binary
    div = div / 2; 
  }
}

//function to find the powerset; accepts the set and a vector to hold all the possible subsets
void powerset(vector<int>& working, vector<vector<int>>& power) {
  vector<int> binary; //declares empty binary list to be used in conversion function
  vector<int> temp; //one dimensional that helps create subsets
  int tempsize = (pow(2, working.size())) - 1; //variable which will hold the expected amount subsets: (2^n)-1
  for(int i = 0; i < (pow(2, working.size())) - 1; i++) { //first for loop will be compared to total amount of subsets
    binaryC(binary, working.size(), tempsize); //convert the tempsize int into binary
    temp = {}; //clears out array
    for(int j = 0; j < binary.size(); j++) {//second loop will be compared to the amount of bits in the binary sequence
      if(binary[j] == 1) { //the location of binary corresponds to a place in the working array of values 
        temp.push_back(working[j]);
      }
    }
    power.push_back(temp); //push the subset into the powerset
    tempsize--; //decrements to create a new binary value which in turn creates new subsets
    binary = {}; //clears out binary so binaryC can create new
  }
}

//finds the cartesian product of two sets
void cartesian(vector<int> setA, vector<int> setB, vector<vector<int>>& product) {
  vector<int> temp;
  for(int i = 0; i < setA.size(); i++) { //first loop starts at first set and finds all the coordinates for each index 
    for(int j = 0; j < setB.size(); j++) { //second loop is second set and program finishes all of the index of first set
      temp = {setA[i], setB[j]}; 
      product.push_back(temp); 
    }
  }
}

void evenroll(vector<vector<int>>& product, vector<vector<vector<int>>>& relations) {
  vector<int> binary; 
  vector<vector<int>> temp; 
  int tempsize = (pow(2, product.size())) - 1;
  for(int i = 0; i < (pow(2, product.size())) - 1; i++) { 
    binaryC(binary, product.size(), tempsize); 
    temp = {};
    for(int j = 0; j < binary.size(); j++) {
      if(binary[j] == 1) {
        temp.push_back(product[j]);
      }
    }
    relations.push_back(temp); 
    tempsize--; 
    binary = {}; 
  }
}


void printpower(vector<vector<int>>& power) {
  vector<int> temp;
  for(int i = 0; i<power.size(); i++) {
    temp = power[i];
    for(int j = 0; j < (power[i]).size(); j++) {
      cout << temp[j] << " ";
    }
    cout << endl;
  }
}

void printproduct(vector<vector<int>>& product) {
  vector<int> temp;
  for(int i = 0; i<product.size(); i++) {
      temp = product[i];
      cout << temp[0] << ", " << temp[1] << endl;
  }
}

void printeven(vector<vector<vector<int>>>& relations) {
  vector<int> temp;
  vector<vector<int>> temp2;
  for(int i = 0; i<relations.size(); i++) {
    temp2 = relations[i];
    for(int j = 0; j < (relations[i]).size(); j++) {
      temp = relations[i][j];
      cout << "( ";
      for(int k = 0; k < (relations[i][j]).size(); k++) {
        cout << temp[k] << " ";
      }
      cout << "), ";
    }
    cout << endl;
  }
}

int main() {
  vector<int> working = {1, 2};
  vector<int> setB = {3, 4};
  vector<int> binary;
  vector<vector<int>> power;
  vector<vector<int>> product;
  vector<vector<vector<int>>> relations;
  vector<int> temp;
  int div = (pow(2, working.size())) - 1;
  binaryC(binary, working.size(), 7);
  powerset(working, power);
  cartesian(working, setB, product);
  evenroll(product, relations);
  printpower(power);
  //printproduct(product);
  //printeven(relations);
}

