#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <climits>

class Coordinate
{
    int x, y;
    public:
        Coordinate(int xval = 0, int yval = 0)
        {
            x = xval;
            y = yval;
        }
        inline int getx() {return x;}
        inline int gety() {return y;}
        inline void print_coord() {std::cout << "(" << x << ", " << y << ")" << std::endl;}
        void call_func(std::string opcode)
        {
            switch(opcode[0])
            {
                case 'U':
                    opcode.erase(opcode.begin());
                    this->up(std::stoi(opcode));
                    break;
                case 'D':
                    opcode.erase(opcode.begin());
                    this->down(std::stoi(opcode));
                    break;
                case 'L':
                    opcode.erase(opcode.begin());
                    this->left(std::stoi(opcode));
                    break;
                case 'R':
                    opcode.erase(opcode.begin());
                    this->right(std::stoi(opcode));
                    break;
                default:
                    std::cout << "NOT RECOGNIZED" << std::endl;
            }
        }
        inline const void up(int val) {y += val;}
        inline const void down(int val) {y -= val;}
        inline const void right(int val) {x += val;}
        inline const void left(int val) {x -= val;}
        inline friend bool operator== (const Coordinate &c1, const Coordinate &c2) {return (c1.x == c2.x && c1.y == c2.y);}
        inline friend bool operator!= (const Coordinate &c1, const Coordinate &c2) {return !(c1 == c2);}
};

double manhattan_distance(Coordinate c1, Coordinate c2)
{
    return std::abs(c1.getx() - c2.getx()) + std::abs(c1.gety() - c2.gety());
}

std::vector<Coordinate> parse(std::string line)
{
    std::vector<Coordinate> coords = {};
    std::istringstream linestrm(line);
    std::string opcode;
    Coordinate a;
    while (std::getline(linestrm, opcode, ','))
    {
        a.call_func(opcode);
        coords.push_back(a);
    }

    return coords;
}

Coordinate is_intersecting(Coordinate l11, Coordinate l12, Coordinate l21, Coordinate l22)
{
    int a1 = l12.gety() - l11.gety();
    int b1 = l11.getx() - l12.getx();
    int a2 = l22.gety() - l21.gety();
    int b2 = l21.getx() - l22.getx();
    if (a1 * b2 - a2 * b1 == 0)
    {
        //lets hope this doesnt happen lol
        return Coordinate(INT_MAX, INT_MAX);
    }
    else
    {
        // line1
        int c1 = (a1 * l11.getx()) + (b1 * l11.gety()); 
        // line2
        int c2 = (a2 * l21.getx()) + (b2 * l21.gety());

        int x = (b2 * c1 - b1 * c2) / (a1 * b2 - a2 * b1);
        int y = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1); 

        int l1l2 = manhattan_distance(l11, l12);
        int l2l1 = manhattan_distance(l21, l22);
        int l11x = manhattan_distance(l11, Coordinate(x, y));
        int l12x = manhattan_distance(Coordinate(x, y), l12);
        int l21x = manhattan_distance(l21, Coordinate(x, y));
        int l22x = manhattan_distance(Coordinate(x, y), l22);

        if (l1l2 == l11x + l12x && l2l1 == l21x + l22x)
        {
            return Coordinate(x, y);
        }
        return Coordinate(INT_MAX, INT_MAX);
    }
    
}

std::vector<Coordinate> return_intersection(std::vector<Coordinate> l1, std::vector<Coordinate> l2)
{
    std::vector<Coordinate> intrs;
    for (int i = 1; i < l1.size(); i++)
    {
        for (int j = 1; j < l2.size(); j++)
        {
            Coordinate instrction = is_intersecting(l1[i - 1], l1[i], l2[j - 1], l2[j]);
            if (instrction.getx() != INT_MAX && instrction.gety() != INT_MAX)
            {
                intrs.push_back(instrction);
            }
        }
    }
    return intrs;
}


int main()
{
    std::string l1, l2;
    std::vector<Coordinate> line1, line2;
    std::ifstream file("3.txt");
    std::getline(file, l1);
    std::getline(file, l2);
    line1 = parse(l1);
    line2 = parse(l2);
    // You can implement this without these coordinate pairs if u only store the manhattan_distances
    // which is what we need, but im storing coordinates because i didn't think of this till now :/
    std::vector<Coordinate> intrs = return_intersection(line1, line2);
    auto srule = [] (Coordinate const& c1, Coordinate const& c2) -> bool
    {
        return manhattan_distance(Coordinate(), c1) < manhattan_distance(Coordinate(), c2);
    };
    std::sort(intrs.begin(), intrs.end(), srule);
    std::cout << "The Manhattan manhattan_distance from the central port to the closest intersection is " << manhattan_distance(Coordinate(), intrs[0]) << ".\nI FUCKING DID IT BITCHEZ I WANNA DIE\n";
    return 0;
}