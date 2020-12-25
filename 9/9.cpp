#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

void parse(std::string s, std::vector<long long> &arr)
{
    std::istringstream ss(s);
    std::string thing;
    while (std::getline(ss, thing, ','))
    {
        arr.push_back(stoll(thing));
    }
}

/*  A valuable piece of information is that the opcode only goes upto the last "1"
    So, if opcode is 02, then the only way it is specified as 02, would be if there was an immediate parameter later
    so if opcode is 02, then it has to have other parameters like 11102, or 1002. If all parameters are in position mode (0)
    then the opcode will always be specified as 1 digit.
*/
int part = 1;

void compute(std::vector<long long> arr)
{
    int i = 0;
    long long relative_base = 0;
    while (true)
    {
        // because if extra memory is accessed, it starts from 0 again
        long long parameters[3] = {0, 0, 0}; // 1st val stored at 0 2nd at 1 3rd at 2

        /*  i.e 1002 -> opcode
            1002 / 100 = 10 (remove opcode for calculating reference values) */

        int dupl = arr[i] / 100; // so i dont edit opcode values in original instruction

        /* This will instantiate the parameters array with the actual array references
         * Assigns parameter 1 value at position 0, and so forth
         * in this loop, we wont have to worry about dupl variable becoming 0, because it means that from that point on, the modes will be 0 only.
         * and as 0 % 10 = 0, it works! */
        for (int j = 0; j < 3; j++) 
        {
            // if mode is 0 (position), assign it to the value of the parameter
            // this extracts the last digit from the 3 digit parameter code
            if (i + j + 1 >= arr.size())
            {
                arr.resize(arr.size() + (i + j + 1));
            }
            if (arr[i + j + 1] >= arr.size() && dupl % 10 != 1)
            {
                arr.resize(arr.size() + (arr[i + j + 1] - arr.size()));
            }
            if (dupl % 10 == 0)
            {
                parameters[j] = arr[i + j + 1];
            }
            // if mode is 1 (immediate), assign it to the address of the parameter
            else if (dupl % 10 == 1)
            {
                parameters[j] = i + j + 1;
            }
            // if mode is 2 (relative), assign it to the relative base + address
            else
            {
                if (relative_base + arr[i + j + 1] >= arr.size())
                {
                    arr.resize(arr.size() + relative_base);
                }
                parameters[j] = (relative_base + arr[i + j + 1]);
            }
            // remove a digit from the opcode (here too, we dont have to worry about dupl being zero because 
            // anything divided by zero = zero)
            dupl /= 10;
        }

        // This again, won't mess with the operation modes, because if the opcode is 1 digit, it means that all modes are 0
        // so 102 % 100 == 2 (opcode) and 2 % 100 == 2 (opcode), we're safe!
        switch(arr[i] % 100)
        {
            // Addition
            case 1:
                // here references are made according to the parameters array.
                // so, if suppose the value is the address of parameter, then it will refer to the immediate value of the parameter
                // otherwise, it will refer to the value stored at the address in the parameter

                arr[parameters[2]] = arr[parameters[0]] + arr[parameters[1]]; 
                i += 4;
                break;

            // Multiplication
            case 2:
                arr[parameters[2]] = arr[parameters[0]] * arr[parameters[1]];
                i += 4;
                break;

            // Store input value at given location
            case 3:
                arr[parameters[0]] = part;
                i += 2;
                break;
            
            // Output value stored at given location
            case 4:
                std::cout << "output value: " << arr[parameters[0]] << std::endl;
                i += 2;
                break;

            // jump-if-true
            case 5:
                i = arr[parameters[0]] ? arr[parameters[1]] : i + 3;
                break;

            // jump-if-false
            case 6:
                i = !arr[parameters[0]] ? arr[parameters[1]] : i + 3;
                break;

            // less than
            case 7:
                arr[parameters[2]] = arr[parameters[0]] < arr[parameters[1]];
                i += 4;
                break;
                
            // equals
            case 8:
                arr[parameters[2]] = arr[parameters[0]] == arr[parameters[1]];
                i += 4;
                break;

            // modifies relative base
            case 9:
                relative_base += arr[parameters[0]];
                i += 2;
                break;

            // Halt program
            case 99:
                return;

            // should not happen xd
            default:
                std::cout << "SOME ERROR OCCURED!" << std::endl;
                std::cout << arr[i] << std::endl;
                return;
        };
    }
}


int main()
{
    auto st = std::chrono::steady_clock::now();
    std::string opcode;
    std::vector<long long> arr;
    std::ifstream file("9.txt");
    std::getline(file, opcode);
    parse(opcode, arr);
    file.close();
    std::cout << "[P1]\n";
    compute(arr);
    part = 2;
    std::cout << "[P2]\n";
    compute(arr);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Time: " << std::fixed << std::setprecision(6) << std::chrono::duration<double>{end - st}.count() << " seconds.\n";
    return 0;
}


// Another way i could do this is just manipulate things in the string itself, because i only need to consider the final ouput here and not the edited values