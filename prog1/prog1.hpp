#include <string>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include "stringModifier.hpp"

#define INPUT_MAX_LEN 64

using namespace std;

class Prog1 {
  private:
    string buffer;
    condition_variable cond_var;
    mutex m;

    void task1() {
        while (true) {
            cout << "Enter string of digits (-1 to exit):\n";
            string str;
            getline(cin, str);
            if (str == "-1") {
                {
                    lock_guard<mutex> l{m};
                    buffer = "-1";
                }
                cond_var.notify_one();
                break;
            }
            if (str.length() > INPUT_MAX_LEN) {
                cout << "Input Error: Input must be less than " 
                    << INPUT_MAX_LEN + 1 << " characters long!\n";
                continue;
            }
            if (StringModifier::sort_and_replace_even(str) != 0) continue;
            {
                lock_guard<mutex> l{m};
                buffer = str;
            }
            cond_var.notify_one();
        }
    }

    void task2() {
        while (true) {
            unique_lock<mutex> lock{m};
            cond_var.wait(lock, [this]() { return buffer != ""; });
            if (buffer == "-1") break;
            cout << buffer << "\n";
            string res = StringModifier::sum_of_nums_in_string(buffer);
            buffer = "";
            lock.unlock();
            cout << res << "\n";
        }
    }

  public:

    Prog1() {
        buffer = "";
    }

    void run() {
        thread t1(&Prog1::task1, this);
        thread t2(&Prog1::task2, this);
        t1.join();
        t2.join();
    }
};