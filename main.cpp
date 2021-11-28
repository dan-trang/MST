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

bool buildCityList(vector<City> & cityList, const string fileName);
bool readFromFile(vector<Destination> & destinationArray, const string fileName);

int main(){
    const string fileName = "city-pairs.txt";
    vector<Destination> destinationArray;
    vector<City> cityList;
    buildCityList(cityList, fileName);
    //assert (!readFromFile(edgeArray, fileName));
    for (City i: cityList){
        cout << i.name << '\n';
        for (Destination j: i.destination){
            cout << '\t' << j.destinationName << ", " << j.distance << '\n';
        }
    }
    return 0;
}

/*This function builds a list of unique cities based on the first
* entry in each line of the input file.  It returns false if the
* file name is unable to be opened.
*/
bool buildCityList(vector<City> & cityList, const string fileName){
    ifstream infile (fileName);
    if (!infile.is_open())
        return false;
    
    string cityName;
    string destinationName;
    int distance;

    /*The following code block reads in city names and stores them in a vector.
    * Each string read in is checked for uniqueness with the std::find()
    * function before being added.
    */
    do{
        infile >> cityName;
        /*
        if (std::find(cityList.begin(), cityList.end(), cityName) != cityList.end()){
            cityList.push_back(cityName);
        }
        */
        bool flag = false;
        for (auto i: cityList){
            if (i.name == cityName){
                flag = true;
                infile >> destinationName >> distance;
                Destination *newDestination = new Destination(destinationName, distance);
                i.destination.push_back(*newDestination);
            }
        }
        if (flag == false){
            City *newCity = new City(cityName);
            cityList.push_back(*newCity);
            infile >> destinationName >> distance;
            Destination *newDestination = new Destination(destinationName, distance);
            cityList.back().destination.push_back(*newDestination);
        }
        infile.ignore(1000, '\n');
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
