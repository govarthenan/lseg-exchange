#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

void read_record()
{
  
    // File pointer
    fstream fin;
    // create vector to store data
    vector<vector<string>>r;
    // string variables
    string line,title,temp,word;
    // Open an existing file
    fin.open("..\\orders.csv", ios::in);
    // extract data from each row
    while(getline(fin,line)){
        stringstream x(line);
        vector<string> m;
	        while(getline(x,word,',')){
    	        m.push_back(word);
	        }
	    r.push_back(m);
    }
}

int main(){
	read_record();
}