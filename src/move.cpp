#include <iostream>
#include "move.hpp"

#include <iomanip>
using namespace std;


Move::Move() {
   
    pp = 999;  //DEFAULT FOR STRUGGLE MOVE
    power = 30;
    name = "struggle";
    type = Type::NORMAL;
    category = MoveCategory::Physical;
}

void Move::displayInfo(int width) {
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
    if (category == MoveCategory::Physical) {
        cout <<std::setw(width)<<""<< "Category: Physical" << endl;
    }
    else {
        cout <<std::setw(width)<<""<< "Category: Special" << endl;
    }
    cout <<std::setw(width)<<""<< "Power: " << power << endl;
    cout <<std::setw(width)<<""<< "PP: " << pp << endl;
}

string Move::getName() const {
   
    return name;
}

Type Move::getType() const {
   
    return type;
}

int Move::getPower() const {
   
    return power;
}

int Move::getPP() const {
   
    return pp;
}

void Move::setCategory(const string& moveCategory) {
   
    if(moveCategory == "special"){
        category = MoveCategory::Special;
    }
    else if(moveCategory == "physical"){
        category = MoveCategory::Physical;
    }
    else{
        cout<<"Invalid move category."<<endl;
        exit(1);
    }
}

MoveCategory Move::getCategory() const {
   
    return category;
}

void Move::setName(string name_) {
   
    name = name_;
}

void Move::setType(string type_) {
   
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

void Move::setType(Type type_) {
   
    type = type_;
}

void Move::setPower(int power_) {
   
    power = power_;
}

void Move::setPP(int pp_) {
   
    pp = pp_;
}   

void Move::reducePP() {
   
    pp -= 1;
}