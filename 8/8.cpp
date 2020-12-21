#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>


int compute(std::ifstream &inpfile, int wide, int tall)
{
    char cur[wide * tall + 1];
    std::vector<std::string> seen;
    int min = INT_MAX;
    while(inpfile.read(cur, tall * wide))
    {
        std::string st = cur;
        int zero = std::count(st.begin(), st.end(), '0');
        if (zero < min)
        {
            min = zero;
            seen.push_back(st);
        }
    }
    int ones = std::count(seen[seen.size() - 1].begin(), seen[seen.size() - 1].end(), '1');
    int twos = std::count(seen[seen.size() - 1].begin(), seen[seen.size() - 1].end(), '2');
    return ones * twos;
}

int main()
{
    std::ifstream inp_file("8.txt");
    int wide, tall;
    std::cout << "How many pixels wide is the image?\n";
    std::cin >> wide;
    std::cout << "How many pixels tall is the image?\n";
    std::cin >> tall;
    int ans = compute(inp_file, wide, tall);
    std::cout << "[P1] The number of 1 digits multiplied by the number of 2 digits on the layer that contains the fewest 0 digits is " << ans << std::endl;
    inp_file.close();
    return 0;
}