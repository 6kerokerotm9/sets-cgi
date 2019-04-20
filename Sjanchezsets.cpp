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

//finds all the binary relations of n-1
void evenroll(vector<vector<int>>& product, vector<vector<vector<int>>>& relations) {
  vector<int> binary; 
  vector<vector<int>> temp; 
  int tempsize = (pow(2, product.size()))-1; //finds the n-1 amount of expected results
  binaryC(binary, product.size(), tempsize); //here binary is only converted once 
  for(int i = 0; i < product.size(); i++) {  
    temp = {};
    binary[i] = 0; //changes indexes to 0 as the loop goes on to keep n-1 size subsets
    for(int j = 0; j < binary.size(); j++) {
      if(binary[j] == 1) {
        temp.push_back(product[j]);
      }
    }
    relations.push_back(temp); 
    binary[i] = 1; //changes the current index back to 1 as only one bit at a time can be 0 for this function
  }
}

//transitive subsets
void transitive(vector<vector<int>>& power) {
  vector<vector<int>> pairs; //vector to hold the pairs of 2
  vector<int> temp; 
  vector<int> temp2;
  vector<int> temp3;
  for(int i = 0; i < power.size(); i++) { //first finds all the sets of 2 and puts them in pairs
	temp = power[i]; //sets temp to a set inside the powerset
    if(temp.size() == 2) { //if the set is a pair of 2 elements
      pairs.push_back(temp);
	}
  }
  for(int i = 0; i < pairs.size()-1; i++) { //now finds all the transitive relations
    temp = pairs[i]; //first temp is assigned to a pair
	for(int j = i+1; j < pairs.size(); j++) {
	  temp2 = pairs[j]; //second temp starts on the element right after the first and will be used to compare
	  if(temp[1] == temp2[0]) { //if the second coordinate of the first pair is equal to the first coordinate of the second pair
	    for(int k = 0; k < pairs.size(); k++) { //looks through all other pairs to see if there is a proper transitive pair
	      temp3 = pairs[k]; 
		  if(temp3[0] == temp[0] && temp3[1] == temp2[1]) { //if the pair has the first element of the first pair and the second element of the second pair
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

//function that takes the data from the url for values to be used in the program
//arguments: string qs from the url, the two sets setA (working) and setB, and the vector boxes
void parse(string qs, vector<int>&setA, vector<int>&setB, vector<int>& boxes)
{
  int temp;
  char temp2; //temp char variable to hold all the non int values from the url
  int index = 0; //index will keep track of the location of the string the program is working on
  vector<int> set; //temporary set to hold values
  istringstream ss(qs); //runs string though stream to allow conversions to int and char (later)
  for(int i = 0; i < 2; i++) {
	if(i == 1) { //basically means if all of setA is obtained already and setB needs to be filled
		setA = set; //put the temp set into setA
		set = {}; //empty the temp set for use in setB
	}
    for(int j = index; j < qs.size(); j++) {
		ss >> temp2; //puts the char into the temp
		if(temp2 == '=') { //if the char is '=' then there should be an int value directly to the right
		  ss >> temp; //finds the int value and puts it into the temp int
		  j++; //increment j so the location in the string can be consistent to the stream
		  set.push_back(temp); 
		}
		else if(temp2 == 'C') { //if the char is a captial C then usually there should be a value next to it as well
		  ss >> temp;
		  j++;
		  set.push_back(temp);
		}
		else if(temp2 == '&') { //if the char is '&' the it signals the end of the sets
		  index = j+1; //set index to j so the program can pick up where it left off in the string
		  break;
		}  
	}
  }
  setB = set;
  for(int i = index; i < qs.size(); i++) { //this loop will find the checkboxes selected
	  ss >> temp2;
	  if(temp2 == '=') { //for the checkboxes the value of the box is only directly after the '='
		  ss >> temp;
		  i++;	
		  if(temp == 0) { //breaks if 0 because the box values are 1-4 and so when the string hits submit the loop breaks
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
      cout << "</br>";
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
    cout << "</br>";
  }
}

int main() {
  cout << "Content-type: text/html\n\n" << endl;
  string qs(getenv("QUERY_STRING"));
  vector<int> working;
  vector<int> setB;
  vector<int> boxes;
  parse(qs, working, setB, boxes);
  
  //operations on the first set
  vector<vector<int>> power;
  vector<vector<int>> product;
  vector<vector<vector<int>>> relations;
  vector<int> temp;
  int div = (pow(2, working.size())) - 1;
  powerset(working, power);
  cartesian(working, setB, product);
  evenroll(product, relations);
  
  //operations on the second set
  vector<vector<int>> power2;
  vector<vector<int>> product2;
  powerset(setB, power2);
  cartesian(setB, working, product2);
  
  for(int i = 0; i < boxes.size(); i++) {
	switch(boxes[i]) {
	  case 1: 
	    cout << "Including the null set, here is the powerset for setA: </br>" << endl;
	    printpower(power);
	    cout << "</br>Including the null set, here is the powerset for setB: </br>" << endl;
	    printpower(power2);
	    cout << "</br>" << endl;
	    break;
	  case 2:
	    cout << "Here is the cartesian product of A X B: </br>" << endl;
	    printproduct(product);
	    cout << "</br>Here is the cartesian product of B X A: </br>" << endl;
	    printproduct(product2);
	    cout << "</br>" << endl;
	    break;
	  case 3:
	    cout << "Here are the binary relations of n-1, where n = |A X B|:</br>" << endl;
	    printeven(relations);
	    cout << "</br>" << endl;
	    break;
	  case 4:
	    cout << "Here are the binary relations of A which are transitive:</br>" << endl;
	    transitive(power);
	    cout << "</br>" << endl;
	    break;
	  default:
	    cout << "No operations chosen. </br>" << endl; 	
	    break;
	}  
  }
  cout << "<form action=\"Sjanchezsets2.cgi\"><button type=\"submit\" name=\"repeat\" value=\"5\"/> Repeat</form>";
  cout << "<form action=\"Sjanchezsets2.cgi\"><button type=\"submit\" name=\"quit\" value=\"6\"/> quit </br> </form>";
}
