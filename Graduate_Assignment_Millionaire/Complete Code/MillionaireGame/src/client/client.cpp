/**
 * Client program to access the multithreaded millionaire game using socket programming
 *
 * @author: Maha Krishnan Krishnan
 * @author: Abdul Hakim Shanavas
 *
 */


#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;

/**
 * This is the main method
 * @param argc None
 * @param argv None
 * @return None
 */
int main(int argc, char *argv[]) {

    if (argc > 1) {
        std::cerr << "Client Usage: None" << endl;
        return 0;
    }

    /* Will store the value that is returned by the socket and accept system call*/
    int client;

    /* Storing the port number on which the system accepts*/
    int portNum = 1500;

    /* Client reads the values from the socket connection to the dynamic variable*/
    int bufsize = 1024;
    char buffer[bufsize];

    /* IP address to connect to the server */
    char *ip = "127.0.0.1";

    /* Server address wiil contain the address of the server*/
    struct sockaddr_in server_addr;

    /* Establishing the client socket connection using socket function*/
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        cout << "\nError establishing socket..." << endl;
        return 1;
    }
    cout << "\n=> Socket client has been created..." << endl;

    /* server address sin family contains the code for the address family. It should always be set to AF_INET */
    server_addr.sin_family = AF_INET;

    /* htons converts the port number from host byte order to a port number in network byte order*/
    server_addr.sin_port = htons(portNum);

    /* Connecting the server socket using server connect function*/
    if (connect(client, (struct sockaddr *) &server_addr, sizeof(server_addr)) == 0)
        cout << "=> Connection to the server port number: " << portNum << endl;

    /* If the client has been sucessfully connected with the server. Then the server will sendd the connection confirmation
     * message to the client*/
    cout << "=> Awaiting confirmation from the server..." << endl;
    recv(client, buffer, bufsize, 0);
    cout << "=> Connection confirmed, you are good to go...";

    int count = 0;

    /*Inorder to start the game the user should type their user name and that will send it to the game server*/
    cout << "\n\nPlease Enter your username: ";
    cin >> buffer;
    send(client, buffer, bufsize, 0);

    /*Once the unique game object has been sucessfully created the server will return the username detail back to the client*/
    recv(client, buffer, bufsize, 0);
    cout << buffer << endl;

    /* Below while block will run till the game gets done*/
    while (true) {

        /* Below recv function will show the questions with four options for the user to answer*/
        recv(client, buffer, bufsize, 0);
        cout << buffer << endl;

        /*THen the user has to enter the necessary option (1 or 2 or 3 or 4) and then will send it to the game server*/
        cout << "Enter the correct option #";
        cin >> buffer;
        send(client, buffer, bufsize, 0);

        /* Below code will notify the user from the game server whether the answer to the questions is correct or wrong*/
        recv(client, buffer, bufsize, 0);
        cout << buffer << endl;

        /* Then the user will see the overall statistics after each questions*/
        recv(client, buffer, bufsize, 0);
        cout << buffer << endl;

        /* If the user game is over then the loop terminates*/
        char *go = "Game Over!";
        if (strstr(buffer, go)) {
            break;
        }

        /*If the user won the game then this loop terminates*/
        char *won = "Congratulations!";
        if (strstr(buffer, won)) {
            break;
        }
    }

    /* Print the connection termination message and close the client*/
    cout << "\n=> Connection terminated.\nGoodbye...\n";
    close(client);
    return 0;
}
