#include <iostream>
#include <vector>
#include <string>
#include "pokemon.hpp"

#include <iomanip>
using namespace std;

Pokemon::Pokemon() {
    
}

string Pokemon::getName() const {
    
    return name;
}

Type Pokemon::getType() const {
    
    return type;
}

int Pokemon::getMaxHp() const {
    
    return maxHp;
}

int Pokemon::getHp() const {
    
    return hp;
}

int Pokemon::getAttack() const {
    
    return attack;
}

int Pokemon::getDefense() const {
    
    return defense;
}

int Pokemon::getSpecialAttack() const {
    
    return specialAttack;
}

int Pokemon::getSpecialDefense() const {
    
    return specialDefense;
}

int Pokemon::getSpeed() const {
    
    return speed;
}

vector<string>& Pokemon::getMoveNames() {
    
    return moveNames;
}

vector<Move>& Pokemon::getMoves() {
    
    return moves;
}

HeldItem& Pokemon::getHeldItem() {
    
    return heldItem;
}

void Pokemon::setName(string name_) {
    
    name = name_;
}

void Pokemon::setType(string type_) {
    

     if(type_ == "normal"){
        type = Type::NORMAL;
    }
    else if(type_ == "fire"){
        type = Type::FIRE;
    }
    else if(type_ == "grass"){
        type = Type::GRASS;
    }
    else if(type_ == "water"){
        type = Type::WATER;
    }
    else{
        cout<<"Invalid move type."<<endl;
        exit(1);
    }
}

void Pokemon::setType(Type type_) {
    
    type = type_;  //OVERLOAD
}

void Pokemon::setMaxHp(int maxHp_) {
    
    maxHp = maxHp_;
}

void Pokemon::setHp(int hp_) {
    
    hp = hp_;
}

void Pokemon::setAttack(int attack_) {
    
    attack = attack_;
}

void Pokemon::setDefense(int defense_) {
    
    defense = defense_;
}

void Pokemon::setSpecialAttack(int specialAttack_) {
    
    specialAttack = specialAttack_;
}

void Pokemon::setSpecialDefense(int specialDefense_) {
    
    specialDefense = specialDefense_;
}

void Pokemon::setSpeed(int speed_) {
    
    speed = speed_;
}

void Pokemon::setMoves(vector<string>& moves_) {
    
    moveNames = moves_;
}

void Pokemon::setMoves(vector<Move>& moves_) {
    
    moves = moves_; //OVERLOAD
}

void Pokemon::setHeldItem(HeldItem heldItem_) {
    
    heldItem = heldItem_;
}

void Pokemon::reduceHp(int damage) {
    
    hp -= damage;  //CHANGED FOR HEALING
}

void Pokemon::displayInfo(int width) const {
    cout <<std::setw(width)<<""<< "Name: " << name << endl;
    if (type == Type::NORMAL) {
        cout <<std::setw(width)<<""<< "Type: Normal" << endl;
    }
    else if (type == Type::FIRE) {
        cout <<std::setw(width)<<""<< "Type: Fire" << endl;
    }
    else if (type == Type::WATER) {
        cout <<std::setw(width)<<""<< "Type: Water" << endl;
    }
    else if (type == Type::GRASS) {
        cout <<std::setw(width)<<""<< "Type: Grass" << endl;
    }
    cout  <<std::setw(width)<<"" << "Current HP: " << hp << endl;
    cout  <<std::setw(width)<<"" << "Max HP: " << maxHp<< endl;
    cout  <<std::setw(width)<<"" << "Attack: " << attack << endl;
    cout  <<std::setw(width)<<"" << "Defense: " << defense << endl;
    cout  <<std::setw(width)<<"" << "Special Attack: " << specialAttack << endl;
    cout  <<std::setw(width)<<"" << "Special Defense: " << specialDefense << endl;
    cout  <<std::setw(width)<<"" << "Speed: " << speed << endl;
    cout  <<std::setw(width)<<"" << "Moves: ";
    for (size_t i = 0; i < moveNames.size(); ++i) {
        cout << moveNames[i];
        if (i < moveNames.size() - 1) {
            cout << ", ";
        }
    }
    if (heldItem.getName() != "") {
        cout << endl;
        cout  <<std::setw(width)<<"" << "Held Item: " << heldItem.getName() << endl;
    } else {
        cout << endl;
        cout  <<std::setw(width)<<"" << "Held Item: None" << endl;
    }
    cout  <<std::setw(width)<<"" << "==================" << endl;
}