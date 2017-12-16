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

//Subclass constructors that that pass an initializer list to the base class constructor
AttackBoard::AttackBoard(int r, int c, int s) : Board(r,c,s){};

DefenseBoard::DefenseBoard(int r, int c, int s) : Board(r,c,s){};

//Randomly sets ships for the enemy
void AttackBoard::setships(){
    for(int k=0; k<numships; k++){
        int rx = rand() % numcols;
        int ry = rand() % numrows;
        if(matrix[rx][ry]!=0){
            k-=1;
            continue;
        }
        matrix[rx][ry] = (4*k)+1;
    }
}

//Takes in user input to set ships on defense board
void DefenseBoard::setships(){
    for(int k=0; k<numships; k++){
        int xcoord, ycoord;
        std::cout<<"Enter the X-coordinate for your "<< shipnames[k] << ": ";
        std::cin>>xcoord;
        std::cin.ignore();
        std::cout<<"Enter the Y-coordinate for your "<< shipnames[k] << ": ";
        std::cin>>ycoord;
        std::cin.ignore();
        std::cout<<std::endl;
        
        
        if(ycoord>numrows || ycoord<1 || xcoord>numcols || xcoord<1){
            std::cout<<"Please enter valid coordinates for this ship.\n";
            k-=1;
            continue;
        }
        if(matrix[xcoord-1][ycoord-1]>0){
            std::cout<<"Please enter different coordinates for this ship.\n";
            k-=1;
            continue;
        }
        matrix[xcoord-1][ycoord-1]=(4*k)+1;
    }
}

//Prints the attack board, showing only squares that have been fired at as a hit or miss
void AttackBoard::printboard(){
    std::cout<<"Attack\n | ";
    for(int c=0; c < numcols-1; c++){
        std::cout<<(c+1)<<" | ";
    }
    std::cout<<numcols<<std::endl<<"-|";
    for(int k = 0; k<(numcols-1); k++){
        std::cout<<"----";
    }
    std::cout<<"---"<<std::endl;
    for(int i=0; i < numrows; i++){
        std::cout<<(i+1)<<"| ";
        for(int j=0; j < numcols; j++){
            if(matrix[j][i]%4<2){
                std::cout<<" ";
            }
            else if(matrix[j][i]==2){
                std::cout<<"0";
            }
            else if(matrix[j][i]%4==3){
                std::cout<<"*";
            }
            
            if(j!=(numcols-1)){
                std::cout<<" | ";
            }
        }
        std::cout<<std::endl;
        if(i!=(numrows-1)){
            std::cout<<"-|";
            for(int k = 0; k<(numcols-1); k++){
                std::cout<<"----";
            }
            std::cout<<"---"<<std::endl;
        }
    }
    std::cout<<std::endl;
}

//Prints the defense board which displays the placement of all your ships and your enemy's hits and misses
void DefenseBoard::printboard(){
    std::cout<<"Defense\n | ";
    for(int c=0; c < numcols-1; c++){
        std::cout<<(c+1)<<" | ";
    }
    std::cout<<numcols<<std::endl<<"-|";
    for(int k = 0; k<(numcols-1); k++){
        std::cout<<"----";
    }
    std::cout<<"---"<<std::endl;
    for(int i=0; i < numrows; i++){
        std::cout<<(i+1)<<"| ";
        for(int j=0; j < numcols; j++){
            if(matrix[j][i]==0){
                std::cout<<" ";
            }
            else if(matrix[j][i]%4==1){
                int s = matrix[j][i]/4;
                std::cout<<shipnames[s][0];
            }
            else if(matrix[j][i]==2){
                std::cout<<"0";
            }
            else if(matrix[j][i]%4==3){
                std::cout<<"*";
            }
            if(j!=(numcols-1)){
                std::cout<<" | ";
            }
        }
        std::cout<<std::endl;
        if(i!=(numrows-1)){
            std::cout<<"-|";
            for(int k = 0; k<(numcols-1); k++){
                std::cout<<"----";
            }
            std::cout<<"---"<<std::endl;
        }
    }
    std::cout<<std::endl;
}

//Destructors
AttackBoard::~AttackBoard(){
    
}

DefenseBoard::~DefenseBoard(){
    
}

Board::~Board(){

}

