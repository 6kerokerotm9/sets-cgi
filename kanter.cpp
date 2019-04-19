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

void parse(string qs)
{

}

int main() {
  cout << "Content-type: text/html\n\n" << endl;
  string qs(getenv("QUERY_STRING"));
  //parse(qs);
  cout << qs << endl;
}


