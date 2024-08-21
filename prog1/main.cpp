#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>
#include <math.h>

#define INPUT_MAX_LEN 64
using namespace std;

int task1(string & res) {
    string str;
    getline(cin, str);
    if (str.length() > INPUT_MAX_LEN) {
        cout << "Input Error: Input must be less than " << INPUT_MAX_LEN + 1 << " characters long!\n";
        return -1;
    }
    vector<int> numCnt(10, 0);
    int num;
    for (char c: str) {
        if (isdigit(c))
            numCnt[c - '0']++;
        else {
            cout << "Input Error: Input must only contain digits!\n";
            return -1;
        }
    }
    for (int i = 9; i >= 0; i--) {
        if (i % 2 == 0)
            while (numCnt[i]-- > 0)
                res += "KB";
        else 
            res += string(numCnt[i], '0' + i);
    }
    return 0;
}

int task2(string buff) {
    cout << buff << "\n";
    int res = 0;
    int n = buff.length();
    for (int i = 0; i < n;) {
        char c = buff[i];
        if (isdigit(c)) {
            int num = c - '0';
            while (i < n && buff[i] == c) {
                res += num;
                i++;
            }
        } else {
             while (i < n && isdigit(buff[i]) == false)
                i += 2;
        }
    }
    return res;
}

void task3(string num) {
    int n = num.length();
    if (n < 3) {
        cout << "Error: sum must be bigger than 99. Recieved: " << num << "\n";
        return;
    }
    int last_five_digits = stoi(num.substr(max(0, n - 5)));

    if (last_five_digits % 32 == 0)
        cout << "Data recieved!\n";
    else
        cout << "Error: Recieved number is not divisible by 32!\n";
}

int main() {
    string buff;
    if (task1(buff) != 0) return -1;

    int sum = task2(buff);
    string num = to_string(sum);
    cout << num << "!!!\n";
    task3(num);

    return 0;
}