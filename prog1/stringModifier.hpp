#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#define INPUT_MAX_LEN 64
using namespace std;

class StringModifier {
  public:
    static int sort_and_replace_even(string & str) {
        vector<int> numCnt(10, 0);
        for (char c: str) {
            if (isdigit(c))
                numCnt[c - '0']++;
            else {
                cout << "Input Error: Input must only contain digits!\n";
                return -1;
            }
        }
        str = "";
        for (int i = 9; i >= 0; i--) {
            if (i % 2 == 0)
                while (numCnt[i]-- > 0)
                    str += "KB";
            else 
                str += string(numCnt[i], '0' + i);
        }
        return 0;
    }
    static int sum_of_digits(string str) {
        int res = 0;
        int n = str.length();
        for (int i = 0; i < n;) {
            char c = str[i];
            if (isdigit(c)) {
                int num = c - '0';
                while (i < n && str[i] == c) {
                    res += num;
                    i++;
                }
            } else {
                 while (i < n && isdigit(str[i]) == false)
                    i += 2;
            }
        }
        return res;
    }
};