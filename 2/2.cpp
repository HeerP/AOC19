#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<int> parse(std::string &s)
{
    std::vector<int> arr;
    size_t i = 0;
    int j = 0;
    while (i < s.size())
    {
        if (s[i] != ',')
        {
            j = j * 10 + (s[i] - '0');
        }
        else
        {
            arr.push_back(j);
            j = 0;   
        }
        i++;
    }
    arr.push_back(j);
    return arr;
}

std::vector<int> compute(std::vector<int> arr)
{
    int i = 0;
    while (i < arr.size())
    {
        switch(arr[i])
        {
            case 1:
                arr[arr[i + 3]] = arr[arr[i + 1]] + arr[arr[i + 2]];
                i += 4;
                break;
            case 2:
                arr[arr[i + 3]] = arr[arr[i + 1]] * arr[arr[i + 2]];
                i += 4;
                break;
            case 99:
                return arr;
            default:
                std::cout << "SOME ERROR OCCURED!" << std::endl;
                return {};
        }
    }
    return {};
}


int main()
{
    std::string opcode;
    std::vector<int> arr;
    std::ifstream file("2.txt");
    std::getline(file, opcode);
    arr = parse(opcode);


    // Part one
    arr[1] = 12;
    arr[2] = 2;
    arr = compute(arr);
    std::cout << "[P1] The value at position 0 is " << arr[0] << std::endl;

    // Reset vector for part two
    arr = parse(opcode);

    // Part two
    for (int noun = 1; noun <= 99; noun++)
    {
        for (int verb = 1; verb <= 99; verb++)
        {
            std::vector<int> temp;
            arr[1] = noun;
            arr[2] = verb;
            temp = compute(arr);
            if (temp[0] == 19690720)
            {
                std::cout << "[P2] The required noun and verb is " << noun << " and " << verb << std::endl;
                return 0;
            }
        }
    }
    std::cout << "COULDNT FIND SHIT!" << std::endl;
    return -1;
}
