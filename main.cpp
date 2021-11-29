#include <iostream>
#include "City.h"
#include "PQ.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <assert.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;

//Function forward declarations
bool buildCityList(vector<City> & cityList, const string fileName);
int prims(vector<City> & cityList, vector<string> & visitedList);
int primsRecursive(vector<City> cityList, vector<string> & visitedList, City *& currentCity, vector<PQ> priorityList);
bool visited(string checkCity, vector<string> visitedList);


//Main 
int main(){
    const string fileName = "city-pairs.txt";
    vector<Destination> destinationArray;
    vector<City> cityList;
    vector<string> visitedList;
    
    if (!buildCityList(cityList, fileName)){
        cout << "Error opening file \"" << fileName << "\"" << '\n';
        return 1;
    }

    /*
    for (City i: cityList){
        cout << i.name << '\n';
        for (Destination j: i.destination){
            cout << '\t' << j.destinationName << ", " << j.distance << '\n';
        }
    }
    */

    int total = prims(cityList, visitedList);
    cout << endl << "Total distance: " << total << endl;
    return 0;
}

/*This function builds a list of unique cities based on the first in each line
 * of the input file.  Each City object's destination list
 * is also populated.  It returns false if the file name is unable to be opened.
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
     * function before being added.  The destination and distance values are
     * also read in and stored in the City object's destination list.
     */
    do{
        infile >> cityName;
        bool flag = false;
        for (auto &i: cityList){
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


/* This function implements Prim's greedy algorithm for finding a minimum 
 * spanning tree (MST).  For simplicity, the resulting tree will be represented
 * as a matrix where each square representing a nonexistent or not-utilized edge
 * contains a 0 and each edge used in the the MST displays the edge's weight.
 * The function keeps a running total of the overall weight as edges are added
 * to the MST.
 */
int prims(vector<City> & cityList, vector<string> & visitedList){ 
    if (cityList.empty())
        return 0;
    else{
        vector<PQ> priorityList; 
        City* currentCity = new City(cityList[0]);
        return primsRecursive(cityList, visitedList, currentCity, priorityList);
    }
}

int primsRecursive(vector<City> cityList, vector<string> & visitedList, City *& currentCity, vector<PQ> priorityList){ 
    if (cityList.empty())
        return 0;
    
    visitedList.push_back(currentCity->name);
    for (long unsigned int i = 0; i < cityList.size(); i++){
        if (currentCity->name == cityList[i].name){
            cityList.erase(cityList.begin() + i);
            break;
        }
    }

    //for loop to add new unvisited cities to priority list
    for (long unsigned int i = 0; i < currentCity->destination.size(); i++){
        if (visited(currentCity->destination[i].destinationName, visitedList) == false){ 
            PQ * newEdge = new PQ(currentCity->name, currentCity->destination[i].destinationName, currentCity->destination[i].distance);
            priorityList.push_back(*newEdge);
        }
    }

    //for loop to find the nearest City and index of that city in the priority list
    int smallestDistance = 0;
    int smallestIndex = 0;
    for (long unsigned int j = 0; j < priorityList.size(); j++){
        if (!visited(priorityList[j].endCity, visitedList)){
            if (smallestDistance == 0 || priorityList[j].distance < smallestDistance){
                smallestIndex = j;
                smallestDistance = priorityList[j].distance;
            }
        }
    }

    cout << priorityList[smallestIndex].startCity << "(" << priorityList[smallestIndex].endCity << "), " << priorityList[smallestIndex].distance << "\n";   //prints out MST edge
    //visitedList.push_back(priorityList[smallestIndex].endCity);     //add destination city to list of visited

    for (long unsigned int i = 0; i < cityList.size(); i++){
        if (priorityList[smallestIndex].endCity == cityList[i].name){
            currentCity = new City(cityList[i]);
            cityList.erase(cityList.begin() + i);
            break;
        }
    }

    priorityList.erase (priorityList.begin() + smallestIndex);      //pops entry from priority list

    return smallestDistance + primsRecursive(cityList, visitedList, currentCity, priorityList);
}

bool visited(string checkCity, vector<string> visitedList){
    for (long unsigned int i = 0; i < visitedList.size(); i++){
        if (checkCity == visitedList[i])
            return true;
    }
    return false;
}
