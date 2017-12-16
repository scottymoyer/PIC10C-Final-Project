//
//  game.hpp
//  Battleship
//
//  Created by Scott Moyer on 11/7/17.
//  Copyright © 2017 Scott Moyer. All rights reserved.
//

#ifndef game_h
#define game_h

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;


/*const int numrows = 6;
const int numcols = 4;
const int numships = 3;
*/

class Board {
public:
    
    Board();
    Board(int r, int c, int s);
    
    void printdefense();
    void printattack();
    
    void setships(int x, int y, int k);
    int getattackvalue(int x, int y);
    int getdefensevalue(int x, int y);
    
    string getattackship(int x, int y);
    string getdefenseship(int x, int y);
    
    
    bool notvalidcoordinate(int x, int y);
    
    int getnumrows();
    int getnumcols();
    int getnumships();
    
    void attack(int x, int y);
    void defend(int x, int y);
    
    int getmyhealth();
    int getenemyhealth();
    void minusmyhealth();
    void minusenemyhealth();
    
private:
    int** defensearray = NULL;
    int** attackarray = NULL;
    int* shiplist = NULL;
    string shipnames[5] = {"Jetski", "Submarine", "Pirate Ship", "Yacht", "Cruiseliner"};
    int numrows;
    int numcols;
    //int defensearray [numrows][numcols];
    //int attackarray [numrows][numcols];
    //int myhealth = numships;
    //int enemyhealth = numships;
    int numships;
    int myhealth;
    int enemyhealth;
    
};




#endif /* game_h */
