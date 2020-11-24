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
        int adjnum = INT_MAX; 

        // bool for criteria
        bool is_sorted = 1;
        bool has_adjacent = 0;
        bool c = 0;

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

            // [PART 1] if the next digit is equal to the one fetched prior to it, then we have an adjacent pair.
            // this is because, an adjacent pair will only ever be next to the element itself. if it is anywhere else in the number, it does not count.

            // [PART 2]
            if (!has_adjacent)
            {
                // if adjacent elements are found
                if (lastval != INT_MAX && temp % 10 == lastval)
                {
                    // if it is the same as the last found adjacent pair, then count = 0 (pair does not count)
                    if (adjnum == temp % 10)
                    {
                        c = 0;
                    }
                    else
                    {
                        // if the last pair was of length 2, then adjacent pair found, condition satisfied.
                        // once this is done, it does not need to keep checking for pairs again
                        // so, the parent if condition (!has_adjacent), skips this part as soon as a valid pair is found
                        if (c == 1) has_adjacent = 1;

                        // since this is the start of a new pair, set the adjacent pair variable to the current number
                        adjnum = temp % 10;

                        // set c = 1 as a valid pair of length 2 is found
                        c = 1;
                    }
                }

                // when the valid pair is found at the far right of the number (223456), the loop ends when temp becomes 0,
                // and hence, has_adjacent is not set to 1.
                /* This condition will set has_adjacent to 1 when : c is 1 (a valid pair of two is found) and
                                                                    when two digits are either not equal or when it is the last digit
                */                       
                if (lastval != INT_MAX && (temp % 10 != lastval || temp % 10 == temp) && c)
                {
                    has_adjacent = 1;
                }
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
    std::cout << "[P2] Total passwords that fulfill the criteria are " << total_pw << ".\n";
    return 0;
}