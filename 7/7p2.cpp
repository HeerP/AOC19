#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <climits>

class intcode
{
    int i = 0;
    bool valnum = 0;
    int phase;
    std::vector<long> program;
    public:
        intcode(){};
        intcode (std::string &s, int p)
        {
            phase = p;
            std::istringstream ss(s);
            std::string thing;
            while (std::getline(ss, thing, ','))
            {
                program.push_back(stoi(thing));
            }
        }
        long get_next_output(long inp2)
        {
            while (program[i] != 99)
            {
                int parameters[3] = {0, 0, 0}; // 1st val stored at 0 2nd at 1 3rd at 2


                /*  i.e 1002 -> opcode
                    1002 / 100 = 10 (remove opcode for calculating reference values) */

                int dupl = program[i] / 100; // so i dont edit opcode values in original instruction

                /* This will instantiate the parameters programay with the actual programay references
                * Assigns parameter 1 value at position 0, and so forth
                * in this loop, we wont have to worry about dupl variable becoming 0, because it means that from that point on, the modes will be 0 only.
                * and as 0 % 10 = 0, it works! */
                for (int j = 0; j < 3; j++) 
                {
                    // if mode is 0 (position), assign it to the value of the parameter
                    // this extracts the last digit from the 3 digit parameter code
                    if (!(dupl % 10))
                    {
                        parameters[j] = program[i + j + 1];
                    }
                    // if mode is 1 (immediate), assign it to the address of the parameter
                    else
                    {
                        parameters[j] = i + j + 1;
                    }

                    // remove a digit from the opcode (here too, we dont have to worry about dupl being zero because 
                    // anything divided by zero = zero)
                    dupl /= 10;
                }

                // This again, won't mess with the operation modes, because if the opcode is 1 digit, it means that all modes are 0
                // so 102 % 100 == 2 (opcode) and 2 % 100 == 2 (opcode), we're safe!
                // Addition
                if (program[i] % 100 == 1)
                {
                    // here references are made according to the parameters programay.
                    // so, if suppose the value is the address of parameter, then it will refer to the immediate value of the parameter
                    // otherwise, it will refer to the value stored at the address in the parameter
                    program[parameters[2]] = program[parameters[0]] + program[parameters[1]]; 
                    i += 4;
                }
                // Multiplication
                else if (program[i] % 100 == 2)
                {
                    program[parameters[2]] = program[parameters[0]] * program[parameters[1]];
                    i += 4;
                }
                // Store input value at given location
                else if (program[i] % 100 == 3)
                {
                    if (!valnum)
                    {
                        program[parameters[0]] = phase;
                        valnum = 1;
                    }
                    else
                    {
                        program[parameters[0]] = inp2;
                    }
                    i += 2;
                }
                // Output value stored at given location
                else if (program[i] % 100 == 4)
                {
                    //std::cout << "output value: " << program[parameters[0]] << std::endl;
                    i += 2;
                    return program[parameters[0]];
                }
                // jump-if-true
                else if (program[i] % 100 == 5)
                {
                    i = program[parameters[0]] ? program[parameters[1]] : i + 3;
                }
                // jump-if-false
                else if (program[i] % 100 == 6)
                {
                    i = !program[parameters[0]] ? program[parameters[1]] : i + 3;
                }
                // less than
                else if (program[i] % 100 == 7)
                {
                    program[parameters[2]] = program[parameters[0]] < program[parameters[1]];
                    i += 4;
                }    
                // equals
                else if (program[i] % 100 == 8)
                { 
                    program[parameters[2]] = program[parameters[0]] == program[parameters[1]];
                    i += 4;
                }
                // Halt program
                /*else if (program[i] % 100 == 99)
                {
                    return 99;
                }*/
                // should not happen xd
                else
                {
                    std::cout << "SOME ERROR OCCURED!" << std::endl;
                    return LONG_MAX;
                }
            }
            return LONG_MAX;   
        }
};




/*  A valuable piece of information is that the opcode only goes upto the last "1"
    So, if opcode is 02, then the only way it is specified as 02, would be if there was an immediate parameter later
    so if opcode is 02, then it has to have other parameters like 11102, or 1002. If all parameters are in position mode (0)
    then the opcode will always be specified as 1 digit.
*/

long get_largest_thrust_signal(std::string opcode)
{
    long max = 0;
    std::vector<int> p_settings = {5, 6, 7, 8, 9};
    do
    {
        std::vector<intcode> comps;
        long prev;
        for (int i = 0; i < 5; i++)
        {
            comps.push_back(intcode(opcode, p_settings[i]));
        }
        long opval = 0;
        for (int i = 0; ; i++)
        {
            opval = comps[i % 5].get_next_output(opval);
            if (opval == LONG_MAX)
            {
                break;
            }
            prev = opval;
        }
        max = prev > max ? prev : max;
    } while (std::next_permutation(p_settings.begin(), p_settings.end()));
    return max;
}


int main()
{
    std::string opcode;
    std::ifstream file("7.txt");
    std::getline(file, opcode);
    std::cout << "[P2] The highest signal that can be sent to the thrusters is " << get_largest_thrust_signal(opcode) << std::endl;
    file.close();
    return 0;
}


// Another way i could do this is just manipulate things in the string itself, because i only need to consider the final ouput here and not the edited values