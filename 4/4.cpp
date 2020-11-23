#include <iostream>
#include <climits>

#define LOWER 265275
#define UPPER 781584

int count_pws()
{
    int count = 0;
    // Looping through given range
    for(int i = LOWER; i <= UPPER; i++)
    {
        // Using temp variable so I don't end up changing the iteration variable
        int temp = i;

        // lastval will contain the last digit that was fetched
        int lastval = INT_MAX;

        // bool for criteria
        bool is_sorted = 1;
        bool has_adjacent = 0;

        // loop for iterating over/fetching digits
        while (temp > 0)
        {
            // if not first iteration, and the next digit is greater than the last fetched digit, then number not sorted
            // this is because we are fetching values in reverse order. so the next fetched value should be smaller than the one fetched prior to it.

            /* TL;DR -> if the number is in increasing order from the left, it should be in a decreasing order from the right!

               i.e. Number = 321 
               this is obviously not in increasing order as the succeeding values are smaller than the preceeding ones (2 < 3 and 1 < 2)
               here, 1 is fetched first. so, if the digit fetched after, suppose 1, is 2 (2 > 1), then the number is not in increasing order.
            */

            // idk how to continue w next iteration from a nested loop so i just break.
            if (lastval != INT_MAX && temp % 10 > lastval)
            {
                is_sorted = 0;
                break;
            }

            // if the next digit is equal to the one fetched prior to it, then we have an adjacent pair.
            // this is because, an adjacent pair will only ever be next to the element itself. if it is anywhere else in the number, it does not count.
            else if (lastval != INT_MAX && temp % 10 == lastval)
            {
                has_adjacent = 1;
            }

            // assign new lastval as the current digit, and divide temp by 10 for fetching next digit
            lastval = temp % 10;
            temp /= 10;
        }

        // if it is sorted, and has adjacent pair, increment count
        if (is_sorted && has_adjacent)
        {
            count++;
        }
    }
    return count;
}

int main()
{
    int total_pw = count_pws();
    std::cout << "[P1] Total passwords that fulfill the criteria are " << total_pw << ".\n";
    return 0;
}