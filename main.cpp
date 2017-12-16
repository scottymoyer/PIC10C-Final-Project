//
//  main.cpp
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

int main() {
    //Prompts user to choose game settings at beginning of game
    srand(int(time(0)));
    std::cout<<"Welcome to Battleship!\n\n";
    std::cout<<"In this version of Battleship, you can choose the number of rows, columns, and ships.\n";
    std::cout<<"The default game settings are a 5x5 board and 5 battleships.\n";
    std::cout<<"Would you like to choose your own game settings?\nEnter 'y' or 'n': ";
    char ans;
    int r,c,s;
    std::cin>>ans;
    std::cin.ignore();
    if(ans=='y'){
        std::cout<<"Okay. How many rows would you like? (Up to 10) ";
        std::cin>>r;
        std::cin.ignore();
        std::cout<<"How many columns? (Up to 10) ";
        std::cin>>c;
        std::cin.ignore();
        std::cout<<"How many battleships? (Up to 10) ";
        std::cin>>s;
        std::cin.ignore();
        while(s > r*c || s > 10){
            std::cout<<"That's too many battleships. How many battleships would you like? (Up to 10) ";
            std::cin>>s;
            std::cin.ignore();
        }
        std::cout<<std::endl;
    }
    else {
        r=5;
        c=5;
        s=5;
    }
    
    //Creates attack and defense boards
    AttackBoard::AttackBoard attackb(r,c,s);
    DefenseBoard::DefenseBoard defenseb(r,c,s);
    
    //Creates base class pointers to use throughout program
    Board::Board *ab = &attackb;
    Board::Board *db = &defenseb;
    
    //Set ships
    ab->setships();
    db->setships();
    
    ab->printboard();
    db->printboard();
    
    //Continue game until one player runs out of health
    while(ab->gethealth()>0 && db->gethealth()>0){
        //Prompts user to enter attack coordinates
        int xattackcoord, yattackcoord;
        std::cout<<std::endl<<"Enter attack X-coordinate: ";
        std::cin>>xattackcoord;
        std::cin.ignore();
        std::cout<<"Enter attack Y-coordinate: ";
        std::cin>>yattackcoord;
        std::cin.ignore();
        std::cout<<std::endl;
        if(ab->notvalidcoordinate(xattackcoord, yattackcoord)){
            std::cout<<"Please enter valid attack coordinates.\n";
            continue;
        }
        else if(ab->getvalue(xattackcoord, yattackcoord)%4>1){
            std::cout<<"You have already fired at these coordinates. Please choose again.\n";
            continue;
        }
        
        //Fires and displays result
        ab->fire(xattackcoord, yattackcoord);
        
        if(ab->getvalue(xattackcoord, yattackcoord)==2){
            std::cout<<"You missed!\n\n";
        }
        else if(ab->getvalue(xattackcoord, yattackcoord)%4==3){
            std::cout<<"Hit! Target acquired.\nYou sunk the enemy's " << ab->getshipname(xattackcoord, yattackcoord)<< ".\n";
            ab->minushealth();
            std::cout<<"Enemy has "<<ab->gethealth()<<" ships remaining.\n\n";
        }
        ab->printboard();
        
        //Enemy generates random coordinates and fires
        int xdefensecoord, ydefensecoord;
        xdefensecoord = 1 + rand() % db->getnumcols();
        ydefensecoord = 1 + rand() % db->getnumrows();
        while(db->getvalue(xdefensecoord, ydefensecoord)%4>1){
            xdefensecoord = 1 + rand() % db->getnumcols();
            ydefensecoord = 1 + rand() % db->getnumrows();
        }
        db->fire(xdefensecoord,ydefensecoord);
        
        //Displays result of fire
        std::cout<<"Enemy fired at ("<<xdefensecoord<<", "<<ydefensecoord<<").\n";
        if(db->getvalue(xdefensecoord, ydefensecoord)==2){
            std::cout<<"They missed!\n\n";
        }
        else if(db->getvalue(xdefensecoord, ydefensecoord)%4==3){
            std::cout<<"You've been hit!\nThe enemy sunk your " << db->getshipname(xdefensecoord, ydefensecoord)<<".\n";
            db->minushealth();
            std::cout<<"You have "<<db->gethealth()<<" ships remaining.\n\n";
        }
        db->printboard();
        
    }
    
    //Different possible outcomes
    if(ab->gethealth()==0 && ab->gethealth()==0){
        std::cout<<"Tie! You both sunk all of each other's ships!\n";
    }
    else if(db->gethealth()==0){
        std::cout<<"You lose! The enemy sunk all of your ships!\n";
    }
    else if(ab->gethealth()==0){
        std::cout<<"You win! You sunk all of your enemy's ships!\n";
    }
    
    

    return 0;
}
