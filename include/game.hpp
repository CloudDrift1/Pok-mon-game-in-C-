#pragma once
#include <iostream>
#include <vector>
#include "pokemon.hpp"
#include "player.hpp"
#include "held_item.hpp"

using namespace std;

class Game {
    
public:
    Game();
    void run();
    vector<Player> players;
    vector<Pokemon> pokemonPool;
    vector<Move> movePool;
    vector<HeldItem> heldItemPool;
    Move struggle;
    int turn;

    void pokemonSelect();
    void showAvailablePokemons(vector<bool>&, int);
    void heldItemSelect();
    void showAvailableHeldItems(vector<bool>&, int);
    void assignHeldItems(Player&, vector<HeldItem>&);
    void parsePokemonPool();
    void parseMovePool();
    void parseHeldItemPool();
    void matchMove2Pokemon();
    void battle();
    Move& attackSelect(Pokemon&, int);
    void attackExecute(Pokemon&, Pokemon&, Move&);
};