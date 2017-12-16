//
//  main.cpp
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



int main(){
    srand(int(time(0)));
    std::cout<<"Welcome to Battleship!\n\n";
    std::cout<<"Would you like to choose your own game settings?\nEnter 'y' or 'n': ";
    char ans;
    int r,c,s;
    std::cin>>ans;
    cin.ignore();
    if(ans=='y'){
        std::cout<<"Okay. How many rows would you like? ";
        std::cin>>r;
        cin.ignore();
        std::cout<<"How many columns? ";
        std::cin>>c;
        cin.ignore();
        std::cout<<"How many battleships? ";
        std::cin>>s;
        cin.ignore();
        std::cout<<std::endl;
    }
    else {
        std::cout<<"The default game settings are a 5x5 board and 5 battleships.\n\n";
        r=5;
        c=5;
        s=5;
    }
    Board::Board b(r,c,s);
    
    //Fix set up
    
    for(int i = 0; i<b.getnumships(); i++){
        int xcoord, ycoord;
        std::cout<<"Enter the X-coordinate for ship #"<< (i+1) << ": ";
        std::cin>>xcoord;
        std::cin.ignore();
        std::cout<<"Enter the Y-coordinate for ship #"<< (i+1) << ": ";
        std::cin>>ycoord;
        std::cin.ignore();
        std::cout<<std::endl;

        
        if(b.notvalidcoordinate(xcoord, ycoord)){
            std::cout<<"Please enter valid coordinates for this ship.\n";
            i-=1;
            continue;
        }
        if(b.getdefensevalue(xcoord,ycoord)>0){
            std::cout<<"Please enter different coordinates for this ship.\n";
            i-=1;
            continue;
        }
           b.setships(xcoord, ycoord, i);
    }
    
    b.printattack();
    b.printdefense();
    
    while(b.getmyhealth()>0 && b.getenemyhealth()>0){
        
        int xattackcoord, yattackcoord;
        std::cout<<std::endl<<"Enter attack X-coordinate: ";
        std::cin>>xattackcoord;
        std::cin.ignore();
        std::cout<<"Enter attack Y-coordinate: ";
        std::cin>>yattackcoord;
        std::cin.ignore();
        std::cout<<std::endl;
        if(b.notvalidcoordinate(xattackcoord, yattackcoord)){
            std::cout<<"Please enter valid attack coordinates.\n";
            continue;
        }
        else if(b.getattackvalue(xattackcoord, yattackcoord)%4>1){
            std::cout<<"You have already fired at these coordinates. Please choose again.\n";
            continue;
        }
        
        b.attack(xattackcoord, yattackcoord);
        if(b.getattackvalue(xattackcoord, yattackcoord)==2){
            std::cout<<"You missed!\n\n";
        }
        else if(b.getattackvalue(xattackcoord, yattackcoord)%4==3){
            std::cout<<"Hit! Target acquired.\nYou sunk the enemy's " << b.getattackship(xattackcoord, yattackcoord)<< ".\n";
            b.minusenemyhealth();
            std::cout<<"Enemy has "<<b.getenemyhealth()<<" ships remaining.\n\n";
        }
        b.printattack();
        
        int xdefensecoord, ydefensecoord;
        xdefensecoord = 1 + rand() % b.getnumcols();
        ydefensecoord = 1 + rand() % b.getnumrows();
        while(b.getdefensevalue(xdefensecoord, ydefensecoord)%4>1){
            xdefensecoord = 1 + rand() % b.getnumcols();
            ydefensecoord = 1 + rand() % b.getnumrows();
        }
        b.defend(xdefensecoord,ydefensecoord);
        
        std::cout<<"Enemy fired at ("<<xdefensecoord<<", "<<ydefensecoord<<").\n";
        if(b.getdefensevalue(xdefensecoord, ydefensecoord)==2){
            std::cout<<"They missed!\n\n";
        }
        else if(b.getdefensevalue(xdefensecoord, ydefensecoord)%4==3){
            std::cout<<"You've been hit!\nThe enemy sunk your " << b.getdefenseship(xdefensecoord, ydefensecoord)<<".\n";
            b.minusmyhealth();
            std::cout<<"You have "<<b.getmyhealth()<<" ships remaining.\n\n";
        }
        b.printdefense();
 
    }
    
    if(b.getmyhealth()==0 && b.getenemyhealth()==0){
        std::cout<<"Tie! You both sunk all of each other's ships!\n";
    }
    else if(b.getmyhealth()==0){
        std::cout<<"You lose! The enemy sunk all of your ships!\n";
    }
    else if(b.getenemyhealth()==0){
        std::cout<<"You win! You sunk all of your enemy's ships!\n";
    }

    return 0;
}
