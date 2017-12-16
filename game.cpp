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
#include <algorithm>

//Constructs an empty matrix of specified row x columns and sets numships and health
Board::Board(int r, int c, int s){
    numrows = r;
    numcols = c;
    numships = s;
    health = 0;
    
    shipnames.erase(shipnames.begin()+numships, shipnames.end());
    shipsizes.erase(shipsizes.begin()+numships, shipsizes.end());
    
    for(auto it : shipsizes){
        health += it;
    }
    
    
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

void Board::minusshiphealth(int k){
    shipsizes[k]-=1;
}

bool Board::sunk(int k){
    if(shipsizes[k]==0){
        return true;
    }
    else
        return false;
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
//Checks to see if coordinates are occupied before placing ship
void AttackBoard::setships(){
    for(int k=0; k<numships; k++){
        int rx = rand() % numcols;
        int ry = rand() % numrows;
        if(matrix[rx][ry]!=0){
            k-=1;
            continue;
        }
        int dir = rand() % 4;
        bool open = true;

        if(dir%4==0){
            for(int i=1; i<shipsizes[k]; i++){
                if(!((rx+i)>=0 && (rx+i)<numcols && matrix[rx+i][ry]==0))
                    open = false;
            }
        }
        if(dir%4==1){
            for(int i=1; i<shipsizes[k]; i++){
                if(!((rx-i)>=0 && (rx-i)<numcols && matrix[rx-i][ry]==0))
                    open = false;
            }
        }
        if(dir%4==2){
            for(int i=1; i<shipsizes[k]; i++){
                if(!((ry+i)>=0 && (ry+i)<numrows && matrix[rx][ry+i]==0))
                    open = false;
            }
        }
        if(dir%4==3){
            for(int i=1; i<shipsizes[k]; i++){
                if(!((ry-i)>=0 && (ry-i)<numrows && matrix[rx][ry-i]==0))
                    open = false;
            }
        }
        if(open==false){
            k-=1;
            continue;
        }
        else{
            if(dir%4==0){
                for(int i=0; i<shipsizes[k]; i++){
                    matrix[rx+i][ry] = (4*k)+1;
                }
            }
            if(dir%4==1){
                for(int i=0; i<shipsizes[k]; i++){
                    matrix[rx-i][ry] = (4*k)+1;
                }
            }
            if(dir%4==2){
                for(int i=0; i<shipsizes[k]; i++){
                    matrix[rx][ry+i] = (4*k)+1;
                }
            }
            if(dir%4==3){
                for(int i=0; i<shipsizes[k]; i++){
                    matrix[rx][ry-i] = (4*k)+1;
                }
            }
        }
    }
}

//Takes in user input to set ships on defense board
//User inputs the (x,y) coordinate for one end of the ship and then the other
//Prompts user to re-input coordinates if the coordinates are not valid for the corresponding ship or if the coordinates are already occupied
void DefenseBoard::setships(){
    for(int k=0; k<numships; k++){
        int xcoord, ycoord, xcoord2, ycoord2;
        std::cout<<"The length of this ship is " << shipsizes[k] << ".\n";
        std::cout<<"Enter the X-coordinate for one end of your "<< shipnames[k] << ": ";
        std::cin>>xcoord;
        std::cin.ignore();
        std::cout<<"Enter the Y-coordinate for one end of your "<< shipnames[k] << ": ";
        std::cin>>ycoord;
        std::cin.ignore();
        std::cout<<std::endl;
        std::cout<<"Enter the X-coordinate for the other end of your "<< shipnames[k] << ": ";
        std::cin>>xcoord2;
        std::cin.ignore();
        std::cout<<"Enter the Y-coordinate for the other end of your "<< shipnames[k] << ": ";
        std::cin>>ycoord2;
        std::cin.ignore();
        std::cout<<std::endl;
        
        
        if(ycoord>numrows || ycoord<1 || xcoord>numcols || xcoord<1){
            std::cout<<"Please enter valid coordinates for this ship.\n";
            k-=1;
            continue;
        }
        else if(ycoord2>numrows || ycoord2<1 || xcoord2>numcols || xcoord2<1){
            std::cout<<"Please enter valid coordinates for this ship.\n";
            k-=1;
            continue;
        }
        else if(!(abs(xcoord-xcoord2)==shipsizes[k]-1 && ycoord==ycoord2) && !(abs(ycoord-ycoord2)==shipsizes[k]-1 && xcoord==xcoord2)){
            std::cout<<"Please enter valid coordinates for this ship.\n";
            k-=1;
            continue;
        }
        
        bool open = true;
        if(xcoord2-xcoord>0){
            for(int i=1; i<shipsizes[k]; i++){
                if(matrix[xcoord+i-1][ycoord-1]!=0)
                    open = false;
            }
        }
        if(xcoord2-xcoord<0){
            for(int i=1; i<shipsizes[k]; i++){
                if(matrix[xcoord-i-1][ycoord-1]!=0)
                    open = false;
            }
        }
        if(ycoord2-ycoord>0){
            for(int i=1; i<shipsizes[k]; i++){
                if(matrix[xcoord-1][ycoord+i-1]!=0)
                    open = false;
            }
        }
        if(ycoord2-ycoord<0){
            for(int i=1; i<shipsizes[k]; i++){
                if(matrix[xcoord-1][ycoord-i-1]!=0)
                    open = false;
            }
        }
        if(open==false){
            k-=1;
            continue;
        }
        else{
            if(xcoord2-xcoord>0){
                for(int i=0; i<shipsizes[k]; i++){
                    matrix[xcoord+i-1][ycoord-1]=(4*k)+1;
                }
            }
            if(xcoord2-xcoord<0){
                for(int i=0; i<shipsizes[k]; i++){
                    matrix[xcoord-i-1][ycoord-1]=(4*k)+1;
                }
            }
            if(ycoord2-ycoord>0){
                for(int i=0; i<shipsizes[k]; i++){
                    matrix[xcoord-1][ycoord+i-1]=(4*k)+1;
                }
            }
            if(ycoord2-ycoord<0){
                for(int i=0; i<shipsizes[k]; i++){
                    matrix[xcoord-1][ycoord-i-1]=(4*k)+1;
                }
            }
        }
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

