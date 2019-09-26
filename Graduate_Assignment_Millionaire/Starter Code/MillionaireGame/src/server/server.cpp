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

    return 0;
}