#include <iostream>
#include "Edge.h"
#include <vector>
#include <fstream>

using std::cin
using std::cout
using std::string
using std::vector


int main(){
    vector<Edge> edgeArray;
    readFromFile(edgeArray, "city-pairs.txt")

}

/*This function reads data from a plain text file and stores the data
* as Edge objects into an array.  The entries are delimited with new
* lines, while an entry's individual attributes are delimited with
* spaces.  If a vertex name is more than one word, the words are
* delimited with a period.
*/
bool readFromFile(vector<Edge> edgeArray, const string fileName){
    //<vector>.pushback() adds an element to the end of a vector
    ifstream infile;
    infile.open("fileName");
    if (!infile.isopen()){
        return false;
    }
    string cityName;
    string destinationName;
    int distance;

    while (!infile.eof()){
        infile
    }
}