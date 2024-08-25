#include <string>
#include <cstring>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "stringModifier.hpp"

#define INPUT_MAX_LEN 64

using namespace std;

class Prog1 {
  private:
    string buffer;

    condition_variable cond_var;
    mutex m;

    int clientSocket;
    sockaddr_in serverAddress;

    int socket_setup() {
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(8080);
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        return 0;
    }

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
            if (buffer == "-1") {
                close(clientSocket);
                break;
            }
            cout << buffer << "\n";
            string res = StringModifier::sum_of_nums_in_string(buffer);
            buffer = "";
            lock.unlock();
            char arr[64];
            strcpy(arr, res.c_str());
            cout << res << "\n";
            if (send(clientSocket, arr, strlen(arr), MSG_NOSIGNAL) == -1) {
                clientSocket = socket(AF_INET, SOCK_STREAM, 0);
                if (connect(clientSocket, (struct sockaddr*)&serverAddress, 
                    sizeof(serverAddress)) < 0) {
                        cout << "Cannot connect to program2\n";
                } else {
                    send(clientSocket, res.c_str(), res.length(), 0);
                }
            }
        }
    }

  public:

    Prog1() {
        buffer = "";
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(8080);
        serverAddress.sin_addr.s_addr = INADDR_ANY;
    }

    void run() {
        thread t1(&Prog1::task1, this);
        thread t2(&Prog1::task2, this);
        t1.join();
        t2.join();
    }
};