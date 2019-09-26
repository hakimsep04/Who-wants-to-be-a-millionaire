/**
 *
 * This is the multithreaded client-server socket program where the game questions and options have been initialized and unique game object
 * will be creted for each client connected with the single server
 *
 *
 * @author: Maha Krishnan Krishnan
 * @author: Abdul Hakim Shanavas
 *
 */

#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "game.h"
#include <memory>
#include <thread>

using namespace std;

/**
 * To print the error message
 * @param msg: Message from the socket
 */
void error(const char *msg) {
    perror(msg);
    exit(1);
}


/**
 * This is the main method
 * @param argc None
 * @param argv None
 * @return None
 */
int main(int argc, char *argv[]) {


    if (argc > 1) {
        std::cerr << "Server Usage: None" << endl;
        return 0;
    }


    /* Client and server will store the values that will returned by the socket and accept system calls*/
    int client, server;

    /* Storing the port number on which the system accepts*/
    int portNum = 1500;

    /* Server reads the values from the socket connection to the dynamic variable*/
    int bufsize = 1024;
    char buffer[bufsize];

    /* Server address wiil contain the address of the server*/
    struct sockaddr_in server_addr;
    socklen_t size;

    /* Establishing the server socket connection using socket function*/
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }
    int enable = 1;
    if (setsockopt(client, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        error("setsockopt(SO_REUSEADDR) failed");
    cout << "\n=> Socket server has been created..." << endl;

    /* server address sin family contains the code for the address family. It should always be set to AF_INET */
    server_addr.sin_family = AF_INET;

    /*INADDR_ANY contains the IP address of the host on which the server is running*/
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);

    /* htons converts the port number from host byte order to a port number in network byte order*/
    server_addr.sin_port = htons(portNum);


    /* Bind the socket to an host socket address and the port number*/
    if ((bind(client, (struct sockaddr *) &server_addr, sizeof(server_addr))) < 0) {
        cout << "=> Error binding connection, the socket has already been established..." << endl;
        return -1;
    }
    size = sizeof(server_addr);

    /*Listening call. Now the server socket will look for the client to establish the socket connection*/
    cout << "=> Looking for clients..." << endl;
    listen(client, 1);

    /*Counter to know how many total clients are connected to this server */
    int clientCount = 1;

    /* Once the server socket establishs the game will initialized with the set of questions and options*/
    Game::initialize_game();

    /* the server will accepts 'n' number of new clients and for each new unique game object has been created*/
    while ((server = accept(client, (struct sockaddr *) &server_addr, &size))) {

        /* Checking whether the server and client is connected or not*/
        if (server < 0)
            cout << "=> Error on accepting..." << endl;

        /* If connected then the server will send the confirmation message to the client*/
        strcpy(buffer, "=> Server connected...\n");
        send(server, buffer, bufsize, 0);

        cout << "=> Connected with the client #" << clientCount << ", you are good to go..." << endl;

        /*Client sends the username to the game server with new unique game object will created and new thread has been
         * created for the game object and this thread has been detached to run in the background */
        recv(server, buffer, bufsize, 0);
        std::string str = buffer;
        unique_ptr<Game> game(make_unique<Game>(str, server));
        std::thread{&Game::play_game, std::move(game)}.detach();

        clientCount++;
    }

    /*Once the server stops it will terminate the client and server connection*/
    close(client);
    close(server);
    return 0;
}