#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#define P1 "YOU"
#define P2 "SAN"

// Be careful, ugly code ahead

// contains orbits : orbiting pair thingy
std::unordered_map<std::string, std::vector<std::string>> orbits;
// vector for the path of YOU and SAN (for this problem)
std::vector<std::string> path1 = {P1}, path2 = {P2};
int total = 0;
std::string p2;

void parse(std::ifstream &file)
{
    std::string code;
    while (std::getline(file, code))
    {
        std::string being_orbited = code.substr(0, code.find(')'));
        std::string orbiting = code.substr(code.find(')') + 1);
        orbits[orbiting].push_back(being_orbited);
    }
}

void recur_compute(std::string obj)
{
    // if object does not orbit anything (end of path)
    if (orbits.find(obj) == orbits.end())
    {
        return;
    }
    else
    {
        // for all the objects that are BEING orbited by obj
        for (auto i = orbits[obj].begin(); i != orbits[obj].end(); i++)
        {
            // increment total
            total += 1;
            // if the path is of YOU or SAN, then push the object names to vectors


            /* P2 path implementation */
            if (p2 == P1) path1.push_back(*i);
            else if (p2 == P2) path2.push_back(*i);
            /* P2 implementation end */


            // recursively call function for all objects
            recur_compute(*i);
        }
    }
}

int compute()
{
    // if both of them are literally next to each other?
    if (path1.size() == 1 && path2.size() == 1)
    {
        return 0;
    }
    for (auto i = path1.begin(); i != path1.end(); i++)
    {
        // trying to find same element in path2
        std::vector<std::string>::iterator a = std::find(path2.begin(), path2.end(), *i);
        // if it exists
        if (a != path2.end())
        {
            // iterator to element - iterator to beginning element = index of given element
            // return the sum of distance of element from both path1 and path2
            return (i - path1.begin()) + (a - path2.begin());
        }
    }
    // lets hope this doesn't happen
    std::cout << "NOT FOUNd HaHAH\n";
    return 1;
}

int main()
{
    std::ifstream file("6.txt");
    int dist;
    parse(file);
    // for all keys in the orbits map
    for (auto i = orbits.begin(); i != orbits.end(); i++)
    {
        // p2 is to keep track of base object, as this function is called recursively, it cannot be kept track of
        p2 = i -> first;
        // Compute the orbit for given key
        recur_compute(i -> first);
        
        // We dont need to worry about objects that don't orbit anything (key doesn't exist) because essentially, they don't amount to the number of total orbits
    }
    dist = compute();
    std::cout << "[P1] Total orbits are " << total << std::endl;
    std::cout << "[P2] The minimum number of orbital transfers required to move from the object " << P1 << " are orbiting to the object " << P2 << " is orbiting is " << dist << std::endl;
    file.close();
}