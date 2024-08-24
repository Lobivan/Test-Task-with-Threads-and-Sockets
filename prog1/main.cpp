#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>
#include <math.h>
#include "prog1.hpp"

#define INPUT_MAX_LEN 64
using namespace std;


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
    Prog1 p1;
    p1.run();

    return 0;
}