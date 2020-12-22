#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>

// Part 1
int compute_p1(std::ifstream &inpfile, int wide, int tall)
{
    char *cur = new char[wide * tall + 1];
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
    delete[] cur;
    return ones * twos;
}

// Part 2
void compute_p2(std::ifstream &inpfile, int wide, int tall)
{
    inpfile.clear();
    inpfile.seekg(0);
    char *img = new char[wide * tall + 1];
    std::fill(img, img + (wide * tall + 1), '2');
    char *cur = new char[wide * tall + 1];
    while (inpfile.read(cur, wide * tall))
    {
        for (int i = 0; i < wide * tall + 1; i++)
        {
            if (cur[i] != '2' && img[i] == '2')
            {
                img[i] = cur[i] == '0' ? ' ' : '#';
            }
        }
    }
    std::cout << "[P2]";
    for (int i = 0; i < tall * wide; i++)
    {
        if (!(i % 25)) std::cout << std::endl;
        std::cout << img[i];
    }
    delete[] img;
    delete[] cur;
}


int main()
{
    std::ifstream inp_file("8.txt");
    int wide, tall;
    std::cout << "How many pixels wide is the image?\n";
    std::cin >> wide;
    std::cout << "How many pixels tall is the image?\n";
    std::cin >> tall;
    int ans_p1 = compute_p1(inp_file, wide, tall);
    std::cout << "[P1] The number of 1 digits multiplied by the number of 2 digits on the layer that contains the fewest 0 digits is " << ans_p1 << std::endl;
    compute_p2(inp_file, wide, tall);
    inp_file.close();
    return 0;
}