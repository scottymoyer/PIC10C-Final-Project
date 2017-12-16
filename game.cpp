//
//  game.cpp
//  BattleshipFinalProject
//
//  Created by Scott Moyer on 12/02/17.
//  Copyright © 2017 Scott Moyer. All rights reserved.
//

#include "game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

//Constructs an empty matrix of specified row x columns and sets numships and health
Board::Board(int r, int c, int s){
    numrows = r;
    numcols = c;
    numships = s;
    health = s;
    
    shipnames.erase(shipnames.begin()+numships, shipnames.end());
    
    
    matrix.resize(numcols);
    for(auto& it : matrix){
        it.resize(numrows);
    }
    
}

//Accessors
int Board::getvalue(int x, int y) const{
    return matrix[x-1][y-1];
}

std::string Board::getshipname(int x, int y) const{
    int s = matrix[x-1][y-1]/4;
    return shipnames[s];
}

int Board::getnumrows() const{
    return numrows;
}

int Board::getnumcols()const{
    return numcols;
}

int Board::getnumships()const{
    return numships;
}

int Board::gethealth()const{
    return health;
}

//Fires at a coordinate by adding 2 to the value of that square
void Board::fire(int x, int y){
    matrix[x-1][y-1]+=2;
}

//Subtracts 1 from health if hit
void Board::minushealth(){
    health-=1;
}

//Checks for valid coordinate
bool Board::notvalidcoordinate(int x, int y){
    if(y>numrows || y<1 || x>numcols || x<1){
        return true;
    }
    else{
        return false;
    }
}

Board::~Board(){

}

