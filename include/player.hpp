#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <vector>
#include "pokemon.hpp"
using namespace std;

// Enum for player actions
enum class Action {
    attack,
    switchPokemon,
    stopGame
};


class Player {

public:
    Player();
    Player(int id);
    const vector<Pokemon>& getPokemons();
    void setPokemons(vector<Pokemon>& pokemons);
    int switchSelect();
    void switchExecute(int choice);
    void switchPokemon();
    Action actionSelect();
    Pokemon& getCurrentPokemon();
    int getNumPokemon() const;
    void reducePokemon();
    void addPokemon(Pokemon& pokemon);
    void setHeldItem(int pokemonIdx, HeldItem item);
    int getId() const;

    int getcIdx(){return currentPokemonIndex;}
    
private:
    vector<Pokemon> pokemons;
    int currentPokemonIndex;
    int numPokemon;
    int id;
};

#endif