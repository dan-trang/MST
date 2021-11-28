#include <iostream>
#include "Edge.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <assert.h>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::ifstream;

bool buildCityList(vector<string> & cityList, const string fileName);
bool readFromFile(vector<Destination> & destinationArray, const string fileName);

int main(){
    const string fileName = "city-pairs.txt";
    vector<Destination> destinationArray;
    vector<string> cityList;
    buildCityList(cityList, fileName);
    //assert (!readFromFile(edgeArray, fileName));
    for (string i: cityList)
        cout << i << '\n';
    return 0;
}

/*This function builds a list of unique cities based on the first
* entry in each line of the input file.  It returns false if the
* file name is unable to be opened.
*/
bool buildCityList(vector<string> & cityList, const string fileName){
    ifstream infile (fileName);
    if (!infile.is_open())
        return false;
    
    string cityName;
    string tmp;

    /*The following code block reads in city names and stores them in a vector.
    * Each string read in is checked for uniqueness with the std::find()
    * function before being added.
    */
    do{
        infile >> cityName;
        infile.ignore(1000, '\n');
        /*
        if (std::find(cityList.begin(), cityList.end(), cityName) != cityList.end()){
            cityList.push_back(cityName);
        }
        */
        bool flag = false;
        for (auto i: cityList){
            if (i == cityName){
                flag = true;
                break;
            }
        }
        if (flag == false){
            cityList.push_back(cityName);
        }
    }while (!infile.eof());
    return true;
}

/*This function reads data from a plain text file and stores the data
* as Edge objects into an array.  The entries are delimited with new
* lines, while an entry's individual attributes are delimited with
* spaces.  If a vertex name is more than one word, the words are
* delimited with a period.  The function returns false if the file
* can not be opened.
*/

bool readFromFile(vector<Destination> & destinationArray, const string fileName){
    ifstream infile;
    infile.open(fileName);
    if (!infile.is_open()){
        return false;
    }
    string cityName;
    string destinationName;
    int distance;
    infile >> cityName;

    while (!infile.eof()){
        infile >> cityName >> destinationName >> distance;
        infile.ignore(1000, '\n');

    }
    return true;
}