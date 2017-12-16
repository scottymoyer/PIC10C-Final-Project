//
//  game.cpp
//  Battleship
//
//  Created by Scott Moyer on 11/7/17.
//  Copyright © 2017 Scott Moyer. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include "game.h"

Board::Board(){
    numrows = 5;
    numcols = 5;
    numships = 5;
    myhealth = numships;
    enemyhealth = numships;
    
    defensearray = new int*[numcols];
    attackarray= new int*[numcols];
    for (int i = 0; i<numcols; i++){
        defensearray[i] = new int[numrows];
        attackarray[i] = new int[numrows];
    }
    for(int i=0; i<numrows; i++){
        for(int j=0; j<numcols; j++){
            defensearray[j][i] = 0;
            attackarray[j][i] = 0;
        }
    }
    
    for(int k=0; k<numships; k++){
        int rx = rand() % numcols;
        int ry = rand() % numrows;
        if(attackarray[rx][ry]>0){
            k-=1;
            continue;
        }
        attackarray[rx][ry] = (4*k)+1;
    }
}

Board::Board(int r, int c, int s){
    numrows = r;
    numcols = c;
    numships = s;
    myhealth = numships;
    enemyhealth = numships;
    
    defensearray = new int*[numcols];
    attackarray= new int*[numcols];
    for (int i = 0; i<numcols; i++){
        defensearray[i] = new int[numrows];
        attackarray[i] = new int[numrows];
    }
    for(int i=0; i<numrows; i++){
        for(int j=0; j<numcols; j++){
            defensearray[j][i] = 0;
            attackarray[j][i] = 0;
        }
    }
    
    for(int k=0; k<numships; k++){
        int rx = rand() % numcols;
        int ry = rand() % numrows;
        if(attackarray[rx][ry]>0){
            k-=1;
            continue;
        }
        attackarray[rx][ry] = (4*k)+1;
    }
}


void Board::printdefense(){
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
            if(defensearray[j][i]==0){
                std::cout<<" ";
            }
            else if(defensearray[j][i]%4==1){
                int s = defensearray[j][i]/4;
                std::cout<<shipnames[s][0];
            }
            else if(defensearray[j][i]==2){
                std::cout<<"O";
            }
            else if(defensearray[j][i]%4==3){
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

void Board::printattack(){
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
            if(attackarray[j][i]%4<2){
                std::cout<<" ";
            }
            else if(attackarray[j][i]==2){
               std::cout<<"O";
            }
            else if(attackarray[j][i]%4==3){
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

//Fix these functions

void Board::setships(int x, int y, int k){
    defensearray[x-1][y-1]=(4*k)+1;
}

int Board::getattackvalue(int x, int y){
    return attackarray[x-1][y-1];
}

int Board::getdefensevalue(int x, int y){
    return defensearray[x-1][y-1];
}

string Board::getattackship(int x, int y){
    int s = attackarray[x-1][y-1]/4;
    return shipnames[s];
}

string Board::getdefenseship(int x, int y){
    int s = defensearray[x-1][y-1]/4;
    return shipnames[s];
}

bool Board::notvalidcoordinate(int x, int y){
    if(y>numrows || y<1 || x>numcols || x<1){
        return true;
    }
    else{
        return false;
    }
}

int Board::getnumrows(){
    return numrows;
}

int Board::getnumcols(){
    return numcols;
}

int Board::getnumships(){
    return numships;
}

int Board::getmyhealth(){
    return myhealth;
}

int Board::getenemyhealth(){
    return enemyhealth;
}

void Board::attack(int x, int y){
    attackarray[x-1][y-1]+=2;
}

void Board::defend(int x, int y){
    defensearray[x-1][y-1]+=2;
}

void Board::minusmyhealth(){
    myhealth-=1;
}

void Board::minusenemyhealth(){
    enemyhealth-=1;
}

