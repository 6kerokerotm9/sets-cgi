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

int main() {
  vector<int> working = {1, 2, 3, 4, 5};
  vector<int> binary;
  vector<vector<int>> power;
  int div = (pow(2, working.size())) - 1;
  binaryC(binary, working.size(), 7);
  powerset(working, power);
  vector<int> temp;
 for(int i = 0; i<power.size(); i++) {
    temp = power[i];
    for(int j = 0; j < (power[i]).size(); j++) {
      cout << temp[j] << " ";
    }
    cout << endl;
  }
}

/*for(int i = 0; i < binary.size(); i++) {
   cout << binary[i] << endl;
  }

 vector<int> temp;
 for(int i = 0; i<power.size(); i++) {
    temp = power[i];
    for(int j = 0; j < (power[i]).size(); j++) {
      cout << temp[j] << " ";
    }
    cout << endl;
  }

*/
