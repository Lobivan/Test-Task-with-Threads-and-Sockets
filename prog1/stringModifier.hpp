#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <algorithm>

using namespace std;

class StringModifier {
  public:
    static string str_sum_num(string num1, string num2) {
        string res;
        int n1 = num1.length();
        int n2 = num2.length();
        int nmin = min(n1, n2);
        int carry = 0;
        for (int i = 0; i < nmin; i++) {
            int d1 = num1[n1 - 1 - i] - '0';
            int d2 = num2[n2 - 1 - i] - '0';
            int d = d1 + d2 + carry;
            carry = d / 10;
            res += '0' + (d % 10);
        }
        if (n2 > n1) {
            for (int i = n2 - n1 - 1; i >= 0; i--) {
                int d = num2[i] - '0' + carry;
                carry = d / 10;
                res += '0' + (d % 10);
            }
        } else {
            for (int i = n1 - n2 - 1; i >= 0; i--) {
                int d = num1[i] - '0' + carry;
                carry = d / 10;
                res += '0' + (d % 10);
            }
        }
        if (carry == 1) res += '1';
        reverse(res.begin(), res. end());
        return res;
    }
    
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

    static string sum_of_nums_in_string(string str) {
        string res = "0";
        int n = str.length();
        for (int i = 0; i < n;) {
            if (isdigit(str[i])) {
                string num;
                while (isdigit(str[i])) {
                    num += str[i++];
                }
                res = str_sum_num(res, num);
                cout << "> " << num << "\n";
            } else {
                 while (i < n && isdigit(str[i]) == false)
                    i += 2;
            }
        }
        return res;
    }
};