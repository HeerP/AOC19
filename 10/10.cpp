#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>

class Coordinate
{
    int x, y;
    std::vector<Coordinate> not_reachable;
    std::vector<Coordinate> reachable;
    public:
        Coordinate() {}
        Coordinate(int a, int b) {x = a; y = b;}
        inline int get_x() {return x;}
        inline int get_y() {return y;}
        inline void add_not_reachable(Coordinate a) {not_reachable.push_back(a);}
        bool is_not_reachable(Coordinate dst) {return std::find(not_reachable.begin(), not_reachable.end(), dst) != not_reachable.end();}
        inline void add_is_reachable(Coordinate a) {reachable.push_back(a);}
        bool is_reachable(Coordinate dst) {return std::find(reachable.begin(), reachable.end(), dst) != reachable.end();}
        inline friend bool operator== (const Coordinate &c1, const Coordinate &c2) {return (c1.x == c2.x && c1.y == c2.y);}
        inline friend bool operator!= (const Coordinate &c1, const Coordinate &c2) {return !(c1 == c2);}
};

void parse(std::ifstream &inpfile, std::vector<Coordinate> &astr)
{
    std::string cur;
    for(int y = 0; std::getline(inpfile, cur); y++)
    {
        for (int i = 0; i < cur.size(); i++)
        {
            if (cur[i] == '#') astr.push_back(Coordinate(i, y));
        }
    }
}


// return 1 if in the way
bool is_in_the_way(Coordinate src, Coordinate dst, std::vector<Coordinate> &astr)
{
    for (Coordinate i: astr)
    {
        if (i == src || i == dst)
        {
            continue;
        }
        double val = ((i.get_x() - src.get_x()) * (dst.get_y() - src.get_y()))  / ((dst.get_x() - src.get_x()) * (i.get_y() - src.get_y()));
        if (val >= 0 && val <= 1)
        {
            return 1;
        }
    }
    return 0;
}

void solve(std::vector<Coordinate> &astr)
{
    int max_count = 0;
    for (Coordinate i: astr)
    {
        int count = 0;
        for (Coordinate j: astr)
        {
            if (j == i){continue;}
            /*else if (i.is_reachable(j)) {count++; continue;}*/
            bool in_the_way = is_in_the_way(i, j, astr);
            if (!in_the_way) 
            {
                count++;
            }
        }
        if (count > max_count) max_count = count;
    }
    std::cout << "[P1] " << max_count << " other asteroids can be detected from the best location for a new monitoring station.\n";
}


int main()
{
    //auto st = std::chrono::steady_clock::now();
    std::vector<Coordinate> astr;
    std::ifstream inpfile("10.txt");
    parse(inpfile, astr);
    solve(astr);
    inpfile.close();
    /*auto end = std::chrono::steady_clock::now();
    std::cout << "Time: " << std::fixed << std::setprecision(6) << std::chrono::duration<double>{end - st}.count() << " seconds.\n";*/
    return 0;
}