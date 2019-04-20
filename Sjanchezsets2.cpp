#include <iostream>
#include <sstream>

using namespace std;

void parse(string qs, int & choice) {
  char temp;
  istringstream ss(qs);
  for(int i = 0; i < qs.size(); i++) {
	  ss >> temp;
	  if(temp == '=') {
		  ss >> choice;
		  break;
	  }
  }
}

int main() {
	cout << "Content-type: text/html\n\n" << std::endl;
	string qs(getenv("QUERY_STRING"));
	int choice; //holds the user choice button press
	parse(qs, choice); 
	if(choice == 5) { //if choice is repeat
	  //this whole statement basically prints out the first html page; I couldn't get it to work when in seperate lines
      cout<<"<head>	<title> CS113 Lab 4 Sets CGI </title></head><body style=\"background-color:#E6E6FA\">	<H1>Lab 4 Sets CGI </H1>	<H2>From CS113 - Joshua Sjah and Justin Sanchez</H2>	<H3>April 16, 2019</H3>	<H4>Enter whole numbers only for the relations</H4><form action=\"dame.cgi\">	<label> Enter values for set A: {		<input name=\"a\" value=\"0\" size=\"30\">	}</label>	<label> Enter values for set B:{		<input name=\"b\" value=\"0\" size=\"30\">	}</label>	<p>Please select your binary relation: (Can choose more than one)	<br />	<input type=\"checkbox\" name=\"power\" value=\"1\"/> Power Sets	<br />	<input type=\"checkbox\" name=\"cartesian\" value=\"2\"/> Cartesian Product	<br />	<input type=\"checkbox\" name=\"cardinal\" value=\"3\"/> All possible relations of cardinality	<br />	<input type=\"checkbox\" name=\"transitive\" value=\"4\"/> Transitive Property	<br />	</p><input type=\"submit\" name=\"submit\" value=\"Submit\" /></form>"<<std::endl;
    }
    else if(choice == 6){ //if choice is quit
	  cout << "<body style=\"background-color:#E6E6FA\"><H1>Thank You!</H1></body>";	
	}
}
