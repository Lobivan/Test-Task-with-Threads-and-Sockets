#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

class Prog2 {
  private:
    int serverSocket;
    sockaddr_in serverAddress;

    void analyse(string num) {
        int n = num.length();
        if (n < 3) {
            cout << "Error: Number must be greater than 99. Recieved: " << num << "\n";
            return;
        }
        int last_five_digits = stoi(num.substr(max(0, n - 5)));
        cout << last_five_digits << "\n";
        if (last_five_digits % 32 == 0)
            cout << "Data recieved: \'" << num << "\'\n";
        else
            cout << "Error: Recieved number is not divisible by 32!\n";
    }

  public:
    Prog2() {
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(8080);
        serverAddress.sin_addr.s_addr = INADDR_ANY;
    }
    void run() {
        bind(serverSocket, (struct sockaddr*)&serverAddress,
            sizeof(serverAddress));
        listen(serverSocket, 5);
        cout << "Listening for clients, ctrl+c to exit\n";
        while (true) {
            int clientSocket = accept(serverSocket, nullptr, nullptr);

            char buffer[1024] = { 0 };
            while (recv(clientSocket, buffer, sizeof(buffer), 0) > 0) {
                analyse(string(buffer));
                memset(buffer, '\0', sizeof(buffer));
            }
        }
    }
};