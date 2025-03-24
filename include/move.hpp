#pragma once
#ifndef MOVE_HPP
#define MOVE_HPP
#include <string>
using namespace std;

// Enum for move category
enum class MoveCategory {
    Physical,
    Special
};

// Enum for Pokémon types
enum class Type {
    NORMAL,
    FIRE,
    WATER,
    GRASS
};

class Move {
    
public:
    Move();
    void displayInfo(int);

    string getName() const; 
    Type getType() const;
    MoveCategory getCategory() const;
    int getPower() const;
    int getPP() const;
    
    void setCategory(const string& moveCategory);
    void setName(string name);
    void setType(string type);
    void setType(Type type);
    void setPower(int power);
    void setPP(int pp);
    void reducePP();

private:
    string name;
    Type type;
    MoveCategory category;
    int power;
    int pp;
};
#endif