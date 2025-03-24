#include <iostream>
#include "player.hpp"

#include <sstream>
#include <string>
#include <iomanip>
#include <limits> 

int L = 0, M = 70, R = 150;

using namespace std;


const vector<Pokemon>& Player::getPokemons() {
    
    return pokemons;
}

void Player::setPokemons(vector<Pokemon>& pokemons) {
    
    pokemons = pokemons; //CHKP
}

int Player::switchSelect() {
    

   /*  This function is used to switch the current pokemon in battle
    It displays the player's pokemon and asks the player to choose a pokemon
    If the player chooses an invalid pokemon, it will ask the player to choose again
    If the player chooses a fainted pokemon, it will ask the player to choose again

    If the player chooses the current pokemon, it will ask the player to choose again  

    If the player chooses a valid pokemon, it will return the index of the chosen pokemon */

        int w = (getId()-1)*R;

        while(true){
        cout <<std::setw(w)<<""<<"Player "<<id<<" Choose a Pokémon : "<<endl;
        int i = 0;
        for(auto& elem:pokemons){
        cout <<std::setw(w)<<""<< i << ". "<< elem.getName() <<" (" << elem.getHp() << " HP)"<<endl; //HP or MaxHP ??
        i++;
        }

        int poke_num = -1;
        string ds_;
        cout <<std::setw(w)<<"";
        cout << "Enter a number: ";
        getline(std::cin, ds_);
        std::istringstream inss(ds_);
            
            if((inss >>poke_num) && ((poke_num >= pokemons.size()) || (poke_num < 0))){
                cout <<std::setw(w)<<""<<"Invalid choice, please try again."<<endl;
            }

            else if((poke_num<pokemons.size()) && (poke_num>=0) && (pokemons.at(poke_num).getHp()>0) && (poke_num != currentPokemonIndex)){  //LAST COND CP

                return poke_num;
                break;
            }
            else if(pokemons.at(poke_num).getHp()<=0){
                cout <<std::setw(w)<<""<<"This Pokémon has fainted. Choose another."<<endl;
            }
            else if(poke_num == currentPokemonIndex){
                cout <<std::setw(w)<<""<<"This Pokémon is already in battle. Choose another."<<endl; 
            }
            else{
            cout <<std::setw(w)<<""<<"Invalid choice, please try again."<<endl;}
    }
}

void Player::switchExecute(int choice) {
    
    // Update the `currentPokemonIndex` to the chosen pokemon index

    if((choice>=0) && (choice < pokemons.size())){
        currentPokemonIndex = choice;
    }
}

void Player::switchPokemon() {
    int choice = switchSelect();
    switchExecute(choice);
}

void print_action(int width){

    cout<<std::setw(width)<<""<<"0. Attack"<<endl;
    cout<<std::setw(width)<<""<<"1. Switch Pokémon"<<endl;
    cout<<std::setw(width)<<""<<"2. Stop Game"<<endl;
}

Action Player::actionSelect() {
    
    
    /* This function is used to ask the player to choose an action
    If the player has only one pokemon, the player must attack
    If the player chooses to attack, return Action::attack
    If the player chooses to switch pokemon, return Action::switchPokemon
    If the player chooses to stop game, return Action::stopGame */
    
    print_action((getId()-1)*R);

    if(getNumPokemon() == 1){

        while(true){
        cout <<std::setw((getId()-1)*R)<<""<<"Enter your choice: ";
        int a;
        string ds_;
        getline(std::cin, ds_);
        std::istringstream inss(ds_);
            if(inss>>a && a<3 && a>=0){

                if(a == 0){return Action::attack;}
                else if(a == 1){
                    cout<<"You only have one Pokémon. You must attack."<<endl;
                    return Action::attack;
                    }
                else if(a == 2){return Action::stopGame;}
            }
        
        cout <<std::setw((getId()-1)*R)<<""<<"Invalid choice, please try again."<<endl;
    }

        // return Action::attack;
    }

    while(true){
        cout <<std::setw((getId()-1)*R)<<""<<"Enter your choice: ";
        int a;
        string ds_;
        getline(std::cin, ds_);
        std::istringstream inss(ds_);
            if(inss>>a && a<3 && a>=0){

                if(a == 0){return Action::attack;}
                else if(a == 1){return Action::switchPokemon;}
                else if(a == 2){return Action::stopGame;}
            }
        
        cout <<std::setw((getId()-1)*R)<<""<<"Invalid choice, please try again."<<endl;
    }
}

Pokemon& Player::getCurrentPokemon() {
    
    return pokemons.at(currentPokemonIndex);
}

int Player::getNumPokemon() const {
    
    return numPokemon;
}

void Player::reducePokemon() {
    
    numPokemon -= 1;
}

void Player::addPokemon(Pokemon& pokemon) {
    
    pokemons.push_back(pokemon);
    numPokemon++;
}

void Player::setHeldItem(int pokemonIdx, HeldItem item) {
    
    pokemons.at(pokemonIdx).setHeldItem(item);
}

Player::Player(int id_) {
    
    id = id_;
    currentPokemonIndex = -10; 
    numPokemon = pokemons.size();
}

Player::Player() {
    
    currentPokemonIndex = -100; 
    numPokemon = pokemons.size();
}

int Player::getId() const {
    
    return id;
}