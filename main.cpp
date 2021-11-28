#include <iostream>
#include "Edge.h"
#include <vector>
#include <fstream>
#include <algorithm>

using std::cin
using std::cout
using std::string
using std::vector
using std::map


int main(){
    const string fileName = "city-pairs.txt"
    vector<Edge> edgeArray;
    map<string, int> cityList;
    assert (!buildCityList(cityList, fileName));
    assert (!readFromFile(edgeArray, fileName));

}

bool buildCityList(vector<string> cityList, const string fileName){
    ifstream infile (fileName);
    if (!infile.isopen())
        return false;
    
    string cityName;
    string tmp;

    /*The following code block reads in city names and maps them to integers (i).
    * Each string read in is checked for uniqueness with the cityList.find()
    * function before being added.  The iterator i is incremented whenever a
    * unique city name is added to the map.
    */
    int i = 1;
    do{
        infile >> cityName;
        infile.ignore(1000, '\n');
        if (std::find(cityList.begin(), cityList.end(), cityName != cityList.end())){
            cityList.pushback(cityName);
            ++i;
        }
    }while (!infile.eof());
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
    infile.open(fileName);
    if (!infile.isopen()){
        return false;
    }
    string cityName;
    string destinationName;
    int distance;
    infile << cityName;

    while (!infile.eof()){
        infile >> cityName >> destinationName >> distance;
        infile.ignore(1000, '\n');

    }
}