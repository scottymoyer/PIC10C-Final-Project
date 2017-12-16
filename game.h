//
//  game.h
//  BattleshipFinalProject
//
//  Created by Scott Moyer on 12/02/17.
//  Copyright © 2017 Scott Moyer. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>


class Board{
public:
    
    //Constructor and Destructor
    Board(int r, int c, int s);
    virtual ~Board();
    
    //Pure virtual functions to be defined by each subclass
    virtual void setships(){};
    virtual void printboard(){};
    
    //Accessors
    int getvalue(int x, int y) const;
    std::string getshipname(int x, int y) const;
    int getnumrows() const;
    int getnumcols() const;
    int getnumships() const;
    int gethealth() const;
    
    //Checks for valid coordinate
    bool notvalidcoordinate(int x, int y);
    
    //Fires at a coordinate
    void fire(int x, int y);
    
    //Subtracts health if hit
    void minushealth();

    //These variables are common to both subclasses and need to be accessed, therefore they are protected
protected:
    std::vector<std::vector<int>> matrix;
    std::vector<std::string> shipnames = {"Submarine", "Fishing Boat", "Yacht", "Cruiseliner", "Pirate Ship", "Motorboat", "Jetski", "Houseboat", "Kayak", "Rowboat"};
    int numrows;
    int numcols;
    int numships;
    int health;
};




#endif /* game_hpp */
