/**
 * This game logic is based on the popular game show who wants to be a Millionaire
 *
 * we will be implementing a Quiz game where n players can play simultaneously (Each
 * player playing their own game).
 *
 *
 * Each game contains 10 questions with the four options and it is divided into 3 segments.
 *
 * First segment has 4 questions and the next two segments have three questions each.
 *
 *
 * @author: Abdul Hakim Shanavas
 * @author: Maha Krishnan Krishnan
 */

#ifndef MILLIONAIREGAME_GAME_H
#define MILLIONAIREGAME_GAME_H


#include <string>
#include <vector>
#include <map>
#include <sys/socket.h>

class Game {
public:

    /**
     * Game constructor will create the new game for each client
     * @param player
     * @param server
     */
    Game(std::string player, int server);

    /**
     * Static initialize game method will it be called only once by the server as soon the server establishes the connection
     *
     * This method set of default questions and 4 options for each questions and the answer for the questions which all are
     * stored in the vector.
     *
     * This method also contains the prize money for each questions which is also stored in the vector
     */
    void play_game();

    /**
     * This method is to implement the game logic.
     *
     * Once the thread has been succesfully started the play game will implement
     *
     */
    static void initialize_game();

private:

    /*To track the total number of attempts that the user has*/
    int attempts_;

    /*To get the prize money for the particular question*/
    std::string prize_won_;

    /*To get and store the player name when new unique game object has been created*/
    std::string player_;

    /*Unique Server connection number to connect between client and server*/
    int server_;

    /* Server reads the values from the socket connection to the dynamic variable*/
    char buffer_[1024];

    /*Vector Collection to store the questions*/
    static std::vector<std::string> questions_;

    /*Vector Collection to sstore the options to the questions*/
    static std::vector<std::string> options_;

    /*Vector Collection to store the correct answers to the questions*/
    static std::vector<std::string> correct_answers_;

    /*Vector Collection to store the prize money to the questions*/
    static std::vector<std::string> prize_money_;

};


#endif //MILLIONAIREGAME_GAME_H
