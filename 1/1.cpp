#include <iostream>
#include <fstream>
#include <string>

// Part 1 function

int fuel_req(int mass)
{
    return (mass / 3 - 2);
}

// Part 2 function

int total_fuel_req(int mass)
{
    int fuel = mass / 3 - 2;
    if (fuel <= 0)
    {
        return 0;
    }
    return fuel + total_fuel_req(fuel);
}

int main()
{
    int mass, sum = 0;
    std::ifstream file("1.txt");
    while (file >> mass)
    {
        std::cout << mass << std::endl;
        sum += total_fuel_req(mass);
    }
    std::cout << "The total fuel required is " << sum << std::endl;
    file.close();
    return 0;
}