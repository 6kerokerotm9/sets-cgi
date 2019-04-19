#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cmath>

//template <class T>

using namespace std;
/**
void binaryC(vector<int>, int , int );
void powerset(vector<int>, vector<vector<int>>&);
void cartesian(vector<int>, vector<int>, vector<vector<int>>&);
void evenroll(vector<vector<int>>&, vector<vector<vector<int>>>&);
void evenroll(vector<vector<int>>&, vector<vector<vector<int>>>&);
void printpower(vector<vector<int>>&);
void printproduct(vector<vector<int>>&)
void printeven(vector<vector<vector<int>>>&)
*/
//void powerset(vector<int>);
//void cartesian(vector<int>, vector<int>, vector<vector<int>>&);
//void binaryRelations(vector<int>, vector<int>);
//void display (T);



struct FIELDS //This will help parse strings to the HTML (helped by Prof.  Degallier)
{
	string name; 
	string value;
	string comma;
};

const int cnt = 6; // This will count both sets ex set A and set B
					//Then it will also count for cartesian, power, etc.

void parse(string);

void binaryC(vector<int>& binary, int workingsize, int div) {
  int rem = 1; 
  //variable to hold the remainder during the division processes
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
  int tempsize = product.size();
  binaryC(binary, tempsize, tempsize);
  for(int i = 0; i < tempsize; i++) { 
    temp = {};
    for(int j = 0; j < binary.size(); j++) {
      if(binary[j] == 1) {
        temp.push_back(product[j]);
      }
    }
    binary[i] = 0;
    relations.push_back(temp); 
    tempsize--; 
  }
}

void transitive(vector<int>& working) {
  for(int i = 0; i < working.size()-1; i++) {
    for(int j = i+1; j < working.size(); j++) {
	  cout << "Content-type: text/html\n\n" << endl;
      cout << working[i] << ", " << working[j] << endl;
    }
  }
}

void printpower(vector<vector<int>>& power) {
  vector<int> temp;
  for(int i = 0; i<power.size(); i++) {
    temp = power[i];
    for(int j = 0; j < (power[i]).size(); j++) {
	  cout << "Content-type: text/html\n\n" << endl;
      cout << temp[j] << " ";
    }
    cout << endl;
  }
}

void printproduct(vector<vector<int>>& product) {
  vector<int> temp;
  for(int i = 0; i<product.size(); i++) {
      temp = product[i];
      //cout << "Content-type: text/html\n\n" << endl;
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

void parse(string qs)
{
	string name, value, comma;
	int start_pos = 0;
	int pos;
	for(int counter = 0; counter<=cnt; counter++) {
		pos = qs.find("=", start_pos); //This first find the separator and also where to start
		name = qs.substr(start_pos, pos- start_pos);
		//cout << "Content-type: text/html\n\n" << endl;
		cout << "\nname: " << name << "<br>" << endl; //debug statement
		start_pos = pos + 1; //Finding the second start position (where the positioned stopped + 1)
								// This will help find the value
		pos = qs.find("%", start_pos);
		comma = qs.substr(start_pos, pos-start_pos);
		//cout << "comma: " << comma << "<br>" << endl;
		pos = qs.find("&", start_pos); //Finding the '&' separates fields
		if(pos == string::npos) { //this will check if the function goes out of bounds
			pos = qs.length();
		}
		value = qs.substr(start_pos, pos - start_pos);
		
		cout << "Content-type: text/html\n\n" << endl;
		cout << "\nvalue: " << value << "<br>" << endl;
		start_pos = pos + 1;
		cout << name << " = " << value << endl;
	}
}
/*
	The parse function essentially will take the names and values from the HTML url after '?'. IN
	our case it will read the value for set A and set B along with if we chose any of the other check box inputs. 
	It will first find the names of the url. The names and values are separated by "=" so the parse function will find
	the "=" and then print out the name. We have a debugger that will post the names of it. Then it will find the values,
	to separate between values and the next name with "&" so the next it will find "&" and then print out the values.   
*/

int main() {
  cout << "Content-type: text/html\n\n" << endl;
  //string qs(getenv("QUERY_STRING"));
  //parse(qs);
  //cout << qs << endl;
  vector<int> working = {1, 2, 3, 4};
  vector<int> setB = {3, 4};
  vector<vector<int>> power;
  vector<vector<int>> product;
  vector<vector<vector<int>>> relations;
  vector<int> temp;
  int div = (pow(2, working.size())) - 1;
  powerset(working, power);
  cartesian(working, setB, product);
  evenroll(product, relations);
  
  //transitive(working);
  //printpower(power);
  //printproduct(product);
  printeven(relations);
 //cout << "Content-type: text/html\n\n" << endl;
}







