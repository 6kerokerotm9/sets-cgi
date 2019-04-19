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
  int tempsize = (pow(2, product.size()))-1;
  binaryC(binary, product.size(), tempsize);
  for(int i = 0; i < product.size(); i++) {  
    temp = {};
    binary[i] = 0;
    for(int j = 0; j < binary.size(); j++) {
      if(binary[j] == 1) {
        temp.push_back(product[j]);
      }
    }
    relations.push_back(temp); 
    binary[i] = 1;
  }
}

void transitive(vector<vector<int>>& power) {
  vector<vector<int>> pairs;
  vector<int> temp;
  vector<int> temp2;
  vector<int> temp3;
  for(int i = 0; i < power.size(); i++) {
	temp = power[i];
    if(temp.size() == 2) {
      pairs.push_back(temp);
	}
  }
  for(int i = 0; i < pairs.size()-1; i++) {
    temp = pairs[i];
	for(int j = i+1; j < pairs.size(); j++) {
	  temp2 = pairs[j];
	  if(temp[1] == temp2[0]) {
	    for(int k = 0; k < pairs.size(); k++) {
	      temp3 = pairs[k];
		  if(temp3[0] == temp[0] && temp3[1] == temp2[1]) {
		    cout << "(" << temp[0] << ", " << temp[1] << "), ";
		    cout << "(" << temp2[0] << ", " << temp2[1] << "), ";
		    cout << "(" << temp3[0] << ", " << temp3[1] << "), " << endl;
		    cout << "</br>";
		  }
	    }
	  }
	}
  }
}

void parse(string qs, vector<int>&setA, vector<int>&setB, vector<int>& boxes)
{
  int temp;
  char temp2;
  int index = 0;
  vector<int> set;
  istringstream ss(qs);
  for(int i = 0; i < 2; i++) {
	if(i == 1) {
		setA = set;
		set = {};
	}
    for(int j = index; j < qs.size(); j++) {
		ss >> temp2;
		if(temp2 == '=') {
		  ss >> temp;
		  j++;	
		  set.push_back(temp);
		}
		else if(temp2 == 'C') {
		  ss >> temp;
		  j++;
		  set.push_back(temp);
		}
		else if(temp2 == '&') {
		  index = j+1;
		  break;
		}  
	}
  }
  setB = set;
  for(int i = index; i < qs.size(); i++) {
	  ss >> temp2;
	  if(temp2 == '=') {
		  ss >> temp;
		  i++;	
		  if(temp == 0) {
			  break;
		  }
		  boxes.push_back(temp);
	  }
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
    cout << "</br>";
  }
}

void printproduct(vector<vector<int>>& product) {
  vector<int> temp;
  for(int i = 0; i<product.size(); i++) {
      temp = product[i];
      cout << temp[0] << ", " << temp[1] << endl;
  }
  cout << "</br>";
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
    cout << "</br>";
  }
}

int main() {
  cout << "Content-type: text/html\n\n" << endl;
  string qs(getenv("QUERY_STRING"));
  //string qs = "a=1%2C2%2C3&b=1%2C2&power=1&transitive=4&submit=Submit";
  vector<int> working;
  vector<int> setB;
  vector<int> boxes;
  parse(qs, working, setB, boxes);
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
  transitive(power);
  printpower(power);
  printproduct(product);
  printeven(relations);
}
