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

using namespace std;

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

int main() {
  //cout << "Content-type: text/html\n\n" << endl;
  //string qs(getenv("QUERY_STRING"));
  string qs = "a=1%2C2%2C3&b=1%2C2&power=1&transitive=4&submit=Submit";
  vector<int> setA;
  vector<int> setB;
  vector<int> boxes;
  parse(qs, setA, setB, boxes);
  cout << "as" << endl;
}

/*for(int i = 0; i < setA.size(); i++) {
	  cout << setA[i] << " ";
  }
  cout << endl;
  for(int i = 0; i < setB.size(); i++) {
	  cout << setB[i] << " ";
  }
  */
