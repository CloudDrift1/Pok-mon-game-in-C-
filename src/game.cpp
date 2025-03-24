#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <functional>
#include "game.hpp"
#include "solve.hpp"

#include <string>
#include <iomanip>
#include <cmath>

const int L = 0, M = 70, R = 120;  //variables for console output text position 

using namespace std;

Game::Game() {

    turn = 0;
    Pokemon charizard, blastoise, venusaur, rattata, pidgeot, mewtwo, tsm_pokemon;
    pokemonPool = {charizard, blastoise, venusaur, rattata, pidgeot, mewtwo, tsm_pokemon};

    Player player1(1), player2(2);
    players = {player1, player2};

    Move tackle, water_sprout, scratch, ember, fire_blast, flamethrower;
    Move hydropump, scald, vinewhip, fly, grit, mindcontrol, spreadcs, struggle1, struggle2;


    movePool = {tackle, water_sprout, scratch, ember, fire_blast, flamethrower, 
    hydropump, scald, vinewhip, fly, grit, mindcontrol, spreadcs};

    HeldItem oranberry, leftovers, charcoal, blackbelt, shellbell, firegem;
    HeldItem watergem, grassgem;

    heldItemPool = {oranberry, leftovers, charcoal, blackbelt, shellbell, firegem,
    watergem, grassgem};
}

void Game::run() {
    system("clear");

    // Parse the input files
    parsePokemonPool();
    parseMovePool();
    parseHeldItemPool();
    matchMove2Pokemon();

    // Select Pokemons and held items (Draft Phase)
    pokemonSelect();
    heldItemSelect();

    // Start the battle
    battle();
}

void Game::pokemonSelect() {

    /* Each player selects 3 pokemons from the pool with following rules:
    1. Player 1 selects one pokemon
    2. Player 2 selects two pokemons
    3. Player 1 selects two pokemons
    4. Player 2 selects one pokemon
    End of selection

    If invalid choice, ask the player to choose again */
  
    vector<bool> status(pokemonPool.size(), false);
    vector<int> pm1(3, -1), pm2(3, -1);
   
    int i=0, j=0;
    cout<<"Player 1, Select one Pokemon"<<endl;
    showAvailablePokemons(status, L);
    while(true){
        cout<< "Enter the number of the Pokemon: ";
        string ds_;
        getline(cin, ds_);
        std::istringstream inss(ds_);
        if((inss >> pm1[i]) && (!status[pm1[i]]) && (pm1[i]>=0 && pm1[i] < pokemonPool.size())){
        status[pm1[i]] = true;
        players.at(0).addPokemon(pokemonPool.at(pm1[i]));
        i++;
        break;
    }
    cout<<"Invalid choice, please try again."<<endl;
    }

    cout<<std::setw(R)<<""<<"Player 2, Select two Pokemons"<<endl;
    showAvailablePokemons(status, R);
    for(int k = 1; k<= 2; k++){
    while(true){
        cout <<std::setw(R)<<""<< "Enter the number of the Pokemon: ";
        string ds_;
        getline(cin, ds_);
        std::istringstream inss(ds_);
        if((inss >> pm2[j]) && !status[pm2[j]] && (pm2[j]>=0 && pm2[j] < pokemonPool.size())){
        status[pm2[j]] = true;
        players.at(1).addPokemon(pokemonPool.at(pm2[j]));
        j++;
        break;
    }
    cout <<std::setw(R)<<""<<"Invalid choice, please try again."<<endl;
    }}

    cout<<"Player 1, Select two Pokemons"<<endl;
    showAvailablePokemons(status, L);
    for(int l = 1; l<=2 ; l++){
    while(true){
        cout<< "Enter the number of the Pokemon: ";
        string ds_;
        getline(cin, ds_);
        std::istringstream inss(ds_);
        if((inss>>pm1[i]) && !status[pm1[i]] && (pm1[i]>=0 && pm1[i] < pokemonPool.size())){
        status[pm1[i]] = true;
        players.at(0).addPokemon(pokemonPool.at(pm1[i]));
        i++;
        break;
    }
    cout<<"Invalid choice, please try again."<<endl;
    }
    }
   
    cout<<std::setw(R)<<""<<"Player 2, Select one Pokemon"<<endl;
    showAvailablePokemons(status, R);
    while(true){
        cout<<std::setw(R)<<""<< "Enter the number of the Pokemon: ";
        string ds_;
        getline(cin, ds_);
        std::istringstream inss(ds_);
        if((inss>>pm2[j]) && !status[pm2[j]] && (pm2[j]>=0 && pm2[j] < pokemonPool.size())){
        status[pm2[j]] = true;
        players.at(1).addPokemon(pokemonPool.at(pm2[j]));
        j++;
        break;
    }
    cout<<std::setw(R)<<""<<"Invalid choice, please try again."<<endl;
    }
}

void Game::showAvailablePokemons(vector<bool>& selected, int width) {
    // Show available Pokemons
    cout <<std::setw(width) <<"" << "Available Pokemons" << endl;
    cout <<std::setw(width) <<""<< "==================" << endl;
    for (int i = 0; i < pokemonPool.size(); i++) {
        if (!selected[i]) {
            cout <<std::setw(width) <<""<< i << ". " << pokemonPool[i].getName() << endl;
        }
        else {
            cout <<std::setw(width) <<""<< i << ". " << pokemonPool[i].getName() << " (Selected)" << endl;
        }
    }
    cout << endl;
}

bool all_assigned(vector<bool>& vec){
    for(auto elem:vec){
        if(!elem){
            return false;
        }
    }
    return true;
}

void Game::assignHeldItems(Player& player, vector<HeldItem>& heldItems) {


    /* This function assigns held items to the player's pokemons
    It displays the player's pokemons and held items
    It asks the player to choose a pokemon to assign a held item
    If the player chooses an invalid pokemon, it will ask the player to choose again
    If the player chooses a valid pokemon, it will assign the held item to the chosen pokemon
    If the player chooses a pokemon that already has a held item, it will ask the player to choose again
    If the player assigns all held items, it will clear the screen */
    
    int p = 0;
    cout <<std::setw((player.getId()-1)*R)<<""<< "Player " <<player.getId() <<", You have selected the following pokemons:"<<endl;
    for(auto& pokemon:player.getPokemons()){
        cout<<std::setw((player.getId()-1)*R)<<""<< "Pokemon " <<p<<":"<<endl;
        pokemon.displayInfo((player.getId()-1)*R);
        p++;
        cout<<endl;
    }

    int i = 0;
    cout <<std::setw((player.getId()-1)*R)<<""<< "Player " <<player.getId() <<", You have selected the following helditems:"<<endl;
    for(auto& item:heldItems){
        cout <<std::setw((player.getId()-1)*R)<<""<< "Held Item " <<i<<":"<<endl;
        item.displayInfo((player.getId()-1)*R);
        i++;
        cout<<endl;
    }

    vector<int> temp_(player.getPokemons().size(), -1);
    vector<bool> assigned_stat(player.getPokemons().size(), false);

    for(int i=0; i<player.getPokemons().size(); i++){
        cout <<std::setw((player.getId()-1)*R)<<""<< "Assigning the following held item..."<<endl;
        heldItems.at(i).displayInfo((player.getId()-1)*R);

    while(true){
        cout <<std::setw((player.getId()-1)*R)<<""<< "Enter the number of the Pokemon: (0, 1, or 2)";
        int a_;
        string ds_;
        getline(cin, ds_);
        std::istringstream inss(ds_);
            if((inss>>a_) && (a_ < player.getPokemons().size()) && (a_ >=0) && (!assigned_stat[a_])){
                assigned_stat[a_] = true;
                temp_[i] = a_;
                player.setHeldItem(i, heldItems.at(i));
                cout <<std::setw((player.getId()-1)*R)<<""<<"Assigned "<<heldItems.at(i).getName()<<" to "<<player.getPokemons().at(i).getName()<<endl;
                cout<<endl;
                break;
        }
        cout <<std::setw((player.getId()-1)*R)<<""<<"Invalid choice, please try again."<<endl;
    }
    }
if(all_assigned(assigned_stat)){
    system("clear"); //CHKP
}
}


void Game::heldItemSelect() {


    /* Each player selects 3 held-items from the pool with following rules:
    1. Player 1 selects one held-item
    2. Player 2 selects two held-items
    3. Player 1 selects two held-items
    4. Player 2 selects one held-item
    End of selection

    If invalid choice, ask the player to choose again

    Then call assignHeldItems for each player */

    vector<bool> hstatus(heldItemPool.size(), false);
    vector<int> ph1(3, -1), ph2(3, -1);
    vector<HeldItem> p1_hi, p2_hi;
    int i=0, j=0;

    cout<<"Player 1, Select one helditem"<<endl;
    showAvailableHeldItems(hstatus, L);
    while(true){
        cout<< "Enter the number of the Helditem: ";
        string ds_;
        getline(cin, ds_);
        std::istringstream inss(ds_);
        if((inss>>ph1[i]) &&!hstatus[ph1[i]] && (ph1[i] >= 0 && ph1[i] < heldItemPool.size())){
        hstatus[ph1[i]] = true;
        p1_hi.push_back(heldItemPool.at(ph1[i]));
        i++;
        break;
    }
    cout<<"Invalid choice, please try again."<<endl;
    }

    cout <<std::setw(R)<<""<<"Player 2, Select two helditems"<<endl;
    showAvailableHeldItems(hstatus, R);

    for(int k=1; k<=2; k++){
    while(true){
        cout <<std::setw(R)<<""<< "Enter the number of the Helditem: ";
        string ds_;
        getline(cin, ds_);
        std::istringstream inss(ds_);
        if((inss>>ph2[j]) && !hstatus[ph2[j]] && (ph2[j] >= 0 && ph2[j] < heldItemPool.size())){
        hstatus[ph2[j]] = true;
        p2_hi.push_back(heldItemPool.at(ph2[j]));
        j++;
        break;
    }
    cout <<std::setw(R)<<""<<"Invalid choice, please try again."<<endl;
    }}

    cout<<"Player 1, Select two helditems"<<endl;
    showAvailableHeldItems(hstatus, L);

    for(int k=1; k<=2; k++){
    while(true){
        cout<< "Enter the number of the Helditem: ";
        string ds_;
        getline(cin, ds_);
        std::istringstream inss(ds_);
        if((inss>>ph1[i]) && !hstatus[ph1[i]] && (ph1[i] >= 0 && ph1[i] < heldItemPool.size())){
        hstatus[ph1[i]] = true;
        p1_hi.push_back(heldItemPool.at(ph1[i]));
        i++;
        break;
    }
    cout<<"Invalid choice, please try again."<<endl;
    }}

    cout<<std::setw(R)<<""<<"Player 2, Select one helditem"<<endl;
    showAvailableHeldItems(hstatus, R);
    while(true){
        cout <<std::setw(R)<<""<< "Enter the number of the Helditem: ";
        string ds_;
        getline(cin, ds_);
        std::istringstream inss(ds_);
        if((inss>>ph2[j]) && !hstatus[ph2[j]] && (ph2[j] >= 0 && ph2[j] < heldItemPool.size())){
        hstatus[ph2[j]] = true;
        p2_hi.push_back(heldItemPool.at(ph2[j]));
        j++;
        break;
    }
    cout <<std::setw(R)<<""<<"Invalid choice, please try again."<<endl;
    }
    
    assignHeldItems(players.at(0), p1_hi);
    assignHeldItems(players.at(1), p2_hi);
}

void Game::showAvailableHeldItems(vector<bool>& selected, int width) {
    // Show available helditems
    cout <<std::setw(width)<<""<< "Available helditems" << endl;
    cout <<std::setw(width)<<""<< "==================" << endl;
    for (int i = 0; i < heldItemPool.size(); i++) {
        if (!selected[i]) {
            cout <<std::setw(width)<<""<< i << ". " << heldItemPool[i].getName() << endl;
        }
        else {
            cout <<std::setw(width)<<""<< i << ". " << heldItemPool[i].getName() << " (Selected)" << endl;
        }
    }
    cout << endl;
}

void Game::parsePokemonPool() {
    // Read pokemon.txt and parse the information

    ifstream pokemon_file;
    stringstream pss;
    string file_name = "../data/pokemon.txt";
    pokemon_file.open(file_name);

    if(pokemon_file.fail()){
        std::cout<<"Failed to parse "<< file_name <<" file."<<std::endl;
        exit(1);
    }

    int tot_line = 0;
    if(pokemon_file.is_open()){

        pss<<pokemon_file.rdbuf();

        for(int i=0; i<pokemonPool.size(); i++){
        std::string line;
        int lineNum = 0;

        while (std::getline(pss, line)) { 
            if(line == ""){break;}
            tot_line++;
            lineNum++;

            string sub1 = line.substr(0, line.find(":"));
            string sub2 = line.substr(line.find(":") + 2, line.length());

            if(sub1 == "name"){
                pokemonPool.at(i).setName(sub2);
            }
            else if(sub1 == "type"){
                pokemonPool.at(i).setType(sub2);
            }
            else if(sub1 == "hp"){
                int temp_hp = std::stoi(sub2);
                pokemonPool.at(i).setHp(temp_hp);
                pokemonPool.at(i).setMaxHp(temp_hp); //CP MaxHP??
            }
            else if(sub1 == "attack"){
                int temp_attack = std::stoi(sub2);
                pokemonPool.at(i).setAttack(temp_attack);
            }
            else if(sub1 == "defense"){
                int temp_defense = std::stoi(sub2);
                pokemonPool.at(i).setDefense(temp_defense);
            }
            else if(sub1 == "special attack"){
                int spa = std::stoi(sub2);
                pokemonPool.at(i).setSpecialAttack(spa);
            }
            else if(sub1 == "special defense"){
                int spd = std::stoi(sub2);
                pokemonPool.at(i).setSpecialDefense(spd);
            }
            else if(sub1 == "speed"){
                int speed = std::stoi(sub2);
                pokemonPool.at(i).setSpeed(speed);
            }
            else if(sub1 == "moves"){
                stringstream mss(sub2);
                string move;
                vector<string> moves;
                while(std::getline(mss, move, ',')){
                    move.erase(0, move.find_first_not_of(" "));
                    move.erase(move.find_last_not_of(" ") + 1);
                    moves.push_back(move);
                }
                pokemonPool.at(i).setMoves(moves);
            }
            else{
                cout<<"Unknown field in "<< file_name <<" ."<<endl;
            }
        }
        }
        pokemon_file.close();
    }
}

void Game::parseMovePool() {

    // Read moves.txt and parse the information

    ifstream move_file;
    stringstream moss;
    string file_name = "../data/moves.txt";
    move_file.open(file_name);

    if(move_file.fail()){
        std::cout<<"Failed to parse "<< file_name <<" file."<<std::endl;
        exit(1);
    }
    int tot_line = 0;
    if(move_file.is_open()){

        moss<<move_file.rdbuf();

        for(int i=0; i<movePool.size(); i++){
        std::string line;
        int lineNum = 0;

        while (std::getline(moss, line)) { 
            // std::cout << line << std::endl;
            if(line == ""){break;}
            tot_line++;
            lineNum++;

            string sub1 = line.substr(0, line.find(":"));
            string sub2 = line.substr(line.find(":") + 2, line.length());

            if(sub1 == "name"){
                movePool.at(i).setName(sub2);
            }
            else if(sub1 == "type"){
                movePool.at(i).setType(sub2);
            }
            else if(sub1 == "category"){
                movePool.at(i).setCategory(sub2);
            }
            else if(sub1 == "power"){
                int temp_power = std::stoi(sub2);
                movePool.at(i).setPower(temp_power);
            }
            else if(sub1 == "pp"){
                int temp_pp = std::stoi(sub2);
                movePool.at(i).setPP(temp_pp);
            }
            else{
                cout<<"Unknown field in "<< file_name <<" ."<<endl;
            }
        }
        }
        move_file.close();
    }
}

void Game::matchMove2Pokemon() {
    // Assign moves to each pokemon

    for(Pokemon& pokemon: pokemonPool){
        vector<string> pm_names = pokemon.getMoveNames();
        vector<Move> moves;
        for(string& poke_move: pm_names){
        for(Move& move: movePool){
            if(poke_move == move.getName()){
                moves.push_back(move);
            }
        }}
        pokemon.setMoves(moves);
        }
}

bool stringToBool(string strbool){
    if(strbool == "True"){
        return true;
    }
    else if(strbool == "False"){
        return false;
    }
    return false; //CHKP
}

void Game::parseHeldItemPool() {
    // Read held_item.txt and parse the information
    
    ifstream held_item_file;
    stringstream hiss;
    string file_name = "../data/held_items.txt";
    held_item_file.open(file_name);

    if(held_item_file.fail()){
        std::cout<<"Failed to parse "<< file_name <<" file."<<std::endl;
        exit(1);
    }
    int tot_line = 0;
    if(held_item_file.is_open()){

        hiss<<held_item_file.rdbuf();

        for(int i=0; i<heldItemPool.size(); i++){
        std::string line;
        int lineNum = 0;

        while (std::getline(hiss, line)) { 
            if(line == ""){break;}
            tot_line++;
            lineNum++;

            string sub1 = line.substr(0, line.find(":"));
            string sub2 = line.substr(line.find(":") + 2, line.length());

            if(sub1 == "name"){
                heldItemPool.at(i).setName(sub2);
            }
            else if(sub1 == "is consumable"){
                heldItemPool.at(i).setConsumable(stringToBool(sub2));
            }
            else if(sub1 == "effect type"){
                heldItemPool.at(i).setEffectType(sub2);
            }
            else if(sub1 == "effect"){
                double temp_effect = std::stod(sub2);
                heldItemPool.at(i).setEffect(temp_effect);
            }
            else if(sub1 == "condition type"){
                heldItemPool.at(i).setConditionType(sub2);
            }
            else if(sub1 == "condition"){
                heldItemPool.at(i).setCondition(sub2); 
            }
            else{
                cout<<"Unknown field in "<< file_name <<" ."<<endl;
            }
        }
        }
        held_item_file.close();
    }
}

void damaged_info(Pokemon& attacker, Pokemon& defender, Move move, int damage, int width = M){
    cout<< std::setw(width) <<""<< attacker.getName()<<" used "<<move.getName()<<"!"<<"\n";
    cout<< std::setw(width) <<""<< defender.getName()<<" received "<<damage<<" damage!"<<"\n";
}

void useItemHeal(Pokemon& attacker, int width = M){

    if(!attacker.getHeldItem().getConsumed()){  //IF THERES HELDITEM LEFT
    cout<< std::setw(width) <<""<<"Using "<< attacker.getHeldItem().getName()<<"..."<<endl;
    if(attacker.getHeldItem().getConsumable()){
        attacker.getHeldItem().consumeItem();
        attacker.getHeldItem().setName("");  //CP for changing to NONE
        cout<< std::setw(width) <<attacker.getHeldItem().getName()<<" used!"<<endl;}
    if((attacker.getHeldItem().getConditionType() == "hp_below_threshold")){
        double hp_threshold = std::stod(attacker.getHeldItem().getCondition());
        if(attacker.getHp()<(hp_threshold*attacker.getMaxHp())){
        int heal = attacker.getHeldItem().getEffect();
        attacker.reduceHp(-1*heal);
        cout<< std::setw(width) <<""<<attacker.getName()<<" healed "<<heal<<" HP!"<<endl;}}
}}

void EOTHeal(Pokemon& defender, int width = M){
    if(defender.getHeldItem().getConditionType() == "end_of_turn"){
        if(defender.getHeldItem().getEffectType() == "heal_relative"){
            int heal = defender.getHeldItem().getEffect()*defender.getMaxHp();
            defender.reduceHp(-1*heal);
            int print_heal = heal;
            if(defender.getHp()>=defender.getMaxHp()){print_heal = 0;}
            cout<< std::setw(width) <<""<<defender.getName()<<" healed "<<print_heal<<" HP!"<<endl;
            if(defender.getHp()>defender.getMaxHp()){
                defender.setHp(defender.getMaxHp());
            }
        }
    }
}

void checkSpecialFaint(Player& victim, Move move, int width=M){
    bool flag = false;
    if((victim.getCurrentPokemon().getName() == "T.S.M.")&&(move.getName() == "GRIT")){
        //
        if((victim.getCurrentPokemon().getHp()<=0)){
            victim.getCurrentPokemon().setHp(1);
            cout<<std::setw(width)<<""<<"T.S.M. has GRIT!"<<endl;
            flag = true;
        }
    }
}

bool checkFaint(Player& victim, int width=M){

    bool faint = false;
    if((victim.getCurrentPokemon().getHp()<=0)){
        faint = true;
        victim.getCurrentPokemon().setHp(0); //WHY
        cout<<std::setw(width)<<""<<victim.getCurrentPokemon().getName()<<" fainted!"<<endl;
        victim.reducePokemon();
        if(victim.getNumPokemon() == 0){
            cout<<std::setw(M)<<""<<"Player "<<((victim.getId()-1)?1:2)<<" wins!"<<endl;
            exit(1);
        }
        victim.switchPokemon();
    }
    return faint;
}

void mindControlAttack(Pokemon& attacker, Pokemon& defender, Move& att_move, Move& def_move, int damage, int width=M){

        cout<<std::setw(width)<<""<<"T.S.M. used M.IN.D Control!"<<endl;
        cout<<std::setw(width)<<""<<attacker.getName()<<" is controlled and attacked itself!"<<endl;
        cout<<std::setw(width)<<""<<attacker.getName()<<" used "<<att_move.getName()<<"!"<<endl;
        cout<<std::setw(width)<<""<<attacker.getName()<<" received "<<damage<<" damage!"<<endl;
    
}
void Game::battle() {
    // Select first Pokémon for each player

    players[0].switchPokemon();
    players[1].switchPokemon();

    system("clear");

    while (true) {
        cout <<std::setw(M)<<""<< "----------" << endl;
        cout <<std::setw(M)<<""<< "| Turn " << turn + 1 << " |"<< endl;
        cout <<std::setw(M)<<""<< "----------" << endl;

        int disp_w = M-8;
        cout <<std::setw(disp_w)<<""<<"=========================="<<endl;
        cout <<std::setw(disp_w)<<""<<"Player 1 Pokémon index: "<<players.at(0).getcIdx()<<endl;
        cout <<std::setw(disp_w)<<""<<"Player 2 Pokémon index: "<<players.at(1).getcIdx()<<endl;
        cout <<std::setw(disp_w)<<""<<"=========================="<<endl;
        cout <<std::setw(disp_w)<<""<<"Player 1 total Pokémons: "<<players.at(0).getNumPokemon()<<endl;
        cout <<std::setw(disp_w)<<""<<"Player 2 total Pokémons: "<<players.at(1).getNumPokemon()<<endl;
        cout <<std::setw(disp_w)<<""<<"=========================="<<endl;
        cout<<endl;

        int speed1 = players.at(0).getCurrentPokemon().getSpeed();
        int speed2 = players.at(1).getCurrentPokemon().getSpeed();

        if(speed1 == speed2){
            exit(1);  //speed tie -> exit
        }

        if(speed1>speed2){

            cout<<"Player 1, Choose an action:"<<endl;
            Action p1_action, p2_action;
            Move p1_move, p2_move;

            p1_action = players.at(0).actionSelect();

            if(p1_action == Action::stopGame){exit(1);}

            else if(p1_action == Action::switchPokemon){

                    players.at(0).switchPokemon(); //switches pokemon -> cannot attack

                    cout<<std::setw(R)<<""<<"Player 2, Choose an action:"<<endl;
                    Action p2_action = players.at(1).actionSelect();

                    if(p2_action == Action::stopGame){exit(1);}

                    else if(p2_action == Action::switchPokemon){ //proceed to next turn
                            players.at(1).switchPokemon();

                            EOTHeal(players.at(0).getCurrentPokemon());
                            EOTHeal(players.at(1).getCurrentPokemon());

                            cout << "Player 1 Pokémon" << endl;
                            players[0].getCurrentPokemon().displayInfo((players[0].getId()-1)*R);
                            cout <<std::setw(R)<<""<< "Player 2 Pokémon" << endl;
                            players[1].getCurrentPokemon().displayInfo((players[1].getId()-1)*R);

                            turn++;
                            continue; //no attacks this turn --> EOTHeal
                    }

                    else if(p2_action == Action::attack){
                            

                        Move p2_move = attackSelect(players.at(1).getCurrentPokemon(), R);  

                        attackExecute(players.at(1).getCurrentPokemon(), players.at(0).getCurrentPokemon(), p2_move);
                        bool f0 = checkFaint(players.at(0)); 
                        if(f0) {if(players.at(0).getNumPokemon()== 0){
                            break; //player 2 wins
                            }  }

                        if(!f0) useItemHeal(players.at(0).getCurrentPokemon(), M);
                        useItemHeal(players.at(1).getCurrentPokemon(), M);  //can it use item while not attacked??

                        EOTHeal(players.at(0).getCurrentPokemon());
                        EOTHeal(players.at(1).getCurrentPokemon());

                        cout << "Player 1 Pokémon" << endl;
                        players[0].getCurrentPokemon().displayInfo((players[0].getId()-1)*R);
                        cout <<std::setw(R)<<""<< "Player 2 Pokémon" << endl;
                        players[1].getCurrentPokemon().displayInfo((players[1].getId()-1)*R);

                        turn++;
                        continue; //next turn
                        }
            }

            else if(p1_action == Action::attack){

                p1_move = attackSelect(players.at(0).getCurrentPokemon(), L);
            
                cout<<std::setw(R)<<""<<"Player 2, Choose an action:"<<endl;

                p2_action = players.at(1).actionSelect();

                if(p2_action == Action::stopGame){exit(1);}

                else if(p2_action == Action::switchPokemon){
                        players.at(1).switchPokemon(); //switches pokemon -> cannot attack

                        attackExecute(players.at(0).getCurrentPokemon(), players.at(1).getCurrentPokemon(), p1_move);

                        bool f1 = checkFaint(players.at(1)); 
                        if(f1) {if(players.at(1).getNumPokemon()== 0){
                            break; //player 1 wins
                            }  }

                        useItemHeal(players.at(0).getCurrentPokemon(), M);
                        if(!f1) useItemHeal(players.at(1).getCurrentPokemon(), M);

                        EOTHeal(players.at(0).getCurrentPokemon());
                        EOTHeal(players.at(1).getCurrentPokemon());

                        cout << "Player 1 Pokémon" << endl;
                        players[0].getCurrentPokemon().displayInfo((players[0].getId()-1)*R);
                        cout <<std::setw(R)<<""<< "Player 2 Pokémon" << endl;
                        players[1].getCurrentPokemon().displayInfo((players[1].getId()-1)*R);

                        continue; //next turn 
                }

                else if(p2_action == Action::attack){

                    p2_move = attackSelect(players.at(1).getCurrentPokemon(), R);

                    if((players.at(0).getCurrentPokemon().getName() == "T.S.M.")&&(p1_move.getName() == "M.IN.D Control")){
                        attackExecute(players.at(1).getCurrentPokemon(), players.at(1).getCurrentPokemon(), p2_move);
                        bool special_faint = checkFaint(players.at(1)); 
                        if(players.at(1).getNumPokemon()== 0){
                        break; //player 1 wins
                        }

                        EOTHeal(players.at(0).getCurrentPokemon());
                        if(!special_faint) EOTHeal(players.at(1).getCurrentPokemon());

                        cout << "Player 1 Pokémon" << endl;
                        players[0].getCurrentPokemon().displayInfo((players[0].getId()-1)*R);
                        cout <<std::setw(R)<<""<< "Player 2 Pokémon" << endl;
                        players[1].getCurrentPokemon().displayInfo((players[1].getId()-1)*R);

                        turn++;
                        continue; //self attack
                    }

                    attackExecute(players.at(0).getCurrentPokemon(), players.at(1).getCurrentPokemon(), p1_move);
                    checkSpecialFaint(players.at(1), p2_move);

                    bool f1 = checkFaint(players.at(1)); 

                    if(players.at(1).getNumPokemon()== 0){
                        break; //player 1 wins
                        }  
                    
                    if(!f1) attackExecute(players.at(1).getCurrentPokemon(), players.at(0).getCurrentPokemon(), p2_move); //if not all dead, it should attack -> TSM here
                    checkSpecialFaint(players.at(0), p1_move);
                    bool f0 = checkFaint(players.at(0));

                    if(players.at(0).getNumPokemon()== 0){
                        break; //player 2 wins
                        }  

                    if(!f0) useItemHeal(players.at(0).getCurrentPokemon(), M);
                    if(!f1) useItemHeal(players.at(1).getCurrentPokemon(), M);
                    
                    }
            }
        }
        
        if(speed2>speed1){ //second case

            cout<<std::setw(R)<<""<<"Player 2, Choose an action:"<<endl;
            Action p2_action = players.at(1).actionSelect();

            if(p2_action == Action::stopGame){exit(1);}

            else if(p2_action == Action::switchPokemon){
                        players.at(1).switchPokemon();

                        cout<<"Player 1, Choose an action:"<<endl;
                        Action p1_action = players.at(0).actionSelect();

                        if(p1_action == Action::stopGame){exit(1);}

                        else if(p1_action == Action::switchPokemon){ //proceed to next turn
                                players.at(0).switchPokemon();

                                EOTHeal(players.at(0).getCurrentPokemon());
                                EOTHeal(players.at(1).getCurrentPokemon());

                                cout << "Player 1 Pokémon" << endl;
                                players[0].getCurrentPokemon().displayInfo((players[0].getId()-1)*R);
                                cout <<std::setw(R)<<""<< "Player 2 Pokémon" << endl;
                                players[1].getCurrentPokemon().displayInfo((players[1].getId()-1)*R);

                                turn++;
                                continue; //no attacks this turn
                        }

                        else if(p1_action == Action::attack){

                            Move p1_move = attackSelect(players.at(0).getCurrentPokemon(), L);  

                            attackExecute(players.at(0).getCurrentPokemon(), players.at(1).getCurrentPokemon(), p1_move);
                            bool f1 = checkFaint(players.at(1)); 
                            if(f1) {
                                if(players.at(1).getNumPokemon()== 0){
                                break; //player 1 wins
                                }  }

                            if(!f1) useItemHeal(players.at(1).getCurrentPokemon(), M);
                            useItemHeal(players.at(0).getCurrentPokemon(), M);  

                            EOTHeal(players.at(0).getCurrentPokemon());
                            EOTHeal(players.at(1).getCurrentPokemon());

                            cout << "Player 1 Pokémon" << endl;
                            players[0].getCurrentPokemon().displayInfo((players[0].getId()-1)*R);
                            cout <<std::setw(R)<<""<< "Player 2 Pokémon" << endl;
                            players[1].getCurrentPokemon().displayInfo((players[1].getId()-1)*R);

                            turn++;
                            continue; //next turn
                            }
            }

            else if(p2_action == Action::attack){

            Move p2_move = attackSelect(players.at(1).getCurrentPokemon(), R);

            cout<<"Player 1, Choose an action:"<<endl;
            Action p1_action = players.at(0).actionSelect();

            if(p1_action == Action::stopGame){exit(1);}

            else if(p1_action == Action::switchPokemon){
                
                        players.at(0).switchPokemon();
                        attackExecute(players.at(1).getCurrentPokemon(), players.at(0).getCurrentPokemon(), p2_move);
                        bool f0 = checkFaint(players.at(0)); 
                        if(f0) {
                            if(players.at(0).getNumPokemon()== 0){
                            break; //player 2 wins
                            }  }

                        if(!f0) useItemHeal(players.at(0).getCurrentPokemon(), M);
                        useItemHeal(players.at(1).getCurrentPokemon(), M);  

                        EOTHeal(players.at(0).getCurrentPokemon());
                        EOTHeal(players.at(1).getCurrentPokemon());

                        cout << "Player 1 Pokémon" << endl;
                        players[0].getCurrentPokemon().displayInfo((players[0].getId()-1)*R);
                        cout <<std::setw(R)<<""<< "Player 2 Pokémon" << endl;
                        players[1].getCurrentPokemon().displayInfo((players[1].getId()-1)*R);

                        turn++;
                        continue; //next turn
            }

            else if(p1_action == Action::attack){

                Move p1_move = attackSelect(players.at(0).getCurrentPokemon(), L);

                if((players.at(1).getCurrentPokemon().getName() == "T.S.M.")&&(p2_move.getName() == "M.IN.D Control")){
                        attackExecute(players.at(0).getCurrentPokemon(), players.at(0).getCurrentPokemon(), p1_move);
                        bool special_faint = checkFaint(players.at(0)); 
                        if(players.at(0).getNumPokemon()== 0){
                        break; //player 2 wins
                        }

                        cout << "Player 1 Pokémon" << endl;
                        players[0].getCurrentPokemon().displayInfo((players[0].getId()-1)*R);
                        cout <<std::setw(R)<<""<< "Player 2 Pokémon" << endl;
                        players[1].getCurrentPokemon().displayInfo((players[1].getId()-1)*R);

                        if(!special_faint) EOTHeal(players.at(0).getCurrentPokemon());
                        EOTHeal(players.at(1).getCurrentPokemon());

                        turn++;
                        continue; //self attack
                    }


                attackExecute(players.at(1).getCurrentPokemon(), players.at(0).getCurrentPokemon(), p2_move);
                checkSpecialFaint(players.at(0), p1_move);
                bool f0 = checkFaint(players.at(0)); 
                if(f0) {
                    if(players.at(0).getNumPokemon()== 0){
                    break; } }
                if(!f0) attackExecute(players.at(0).getCurrentPokemon(), players.at(1).getCurrentPokemon(), p1_move);
                checkSpecialFaint(players.at(1), p2_move);
                bool f1 = checkFaint(players.at(1));

                 if(f1) {
                    if(players.at(1).getNumPokemon()== 0){
                    break; }  
                    }

                if(!f0) useItemHeal(players.at(0).getCurrentPokemon(), M);
                if(!f1) useItemHeal(players.at(1).getCurrentPokemon(), M);
                }
            }
        }

        EOTHeal(players.at(0).getCurrentPokemon());
        EOTHeal(players.at(1).getCurrentPokemon());
        turn++;

        // Display Pokémon information
        cout << "Player 1 Pokémon" << endl;
        players[0].getCurrentPokemon().displayInfo((players[0].getId()-1)*R);
        cout <<std::setw(R)<<""<< "Player 2 Pokémon" << endl;
        players[1].getCurrentPokemon().displayInfo((players[1].getId()-1)*R);

    }

     if(players.at(0).getNumPokemon()== 0 || players.at(0).getNumPokemon()== 0){
            if(players.at(0).getNumPokemon()== 0){
                    cout<<std::setw(M)<<""<<"Player "<<players.at(1).getId()<<" wins!"<<endl;
                    exit(1);
            }
            else if(players.at(1).getNumPokemon() == 0){
                    cout<<std::setw(M)<<""<<"Player "<<players.at(0).getId()<<" wins!"<<endl;
                    exit(1);
            }
        }
}

void print_pokemon_move(Pokemon& p, int width){

    int i = 0;
    for(auto& move:p.getMoves()){
        cout <<std::setw(width)<<""<<i<<". "<<move.getName()<<" ("<<move.getPP()<<" PP)"<<endl;
        i++;
    }
}

bool allMovesDone(Pokemon& p){
    bool allGone = false;
    for(Move& mov:p.getMoves()){
        if(mov.getPP() > 0){
            allGone = true;
            return false;
        }
    }
    return true;
}

Move& Game::attackSelect(Pokemon& attacker, int width) {

    /* 1. Get the choice from the user
    2. if the choice is invalid, ask the user to choose again
    3. return the selected move */

    if(allMovesDone(attacker)){
        cout<<std::setw(width)<<""<<"You only have Struggle move left."<<endl;
        return struggle;
    }
    
    while(true){
        cout <<std::setw(width)<<""<<"Pokemon: "<<attacker.getName()<<", Choose a move:"<<endl;
        print_pokemon_move(attacker, width);
        cout<<std::setw(width)<<""<<"Enter the number of the move: ";

        int a;
        string ds_;
        getline(std::cin, ds_);
        std::istringstream inss(ds_);
            if((inss>>a) && (a<attacker.getMoves().size()) && (a>=0) && (attacker.getMoves().at(a).getPP()>0)){
                attacker.getMoves().at(a).reducePP(); 
                return attacker.getMoves().at(a);
                break;
            }

            else if(attacker.getMoves().at(a).getPP()<=0){
                cout<<std::setw(width)<<""<<"No PP left for this move, choose another move!"<<endl;;
            }

        else {cout<<std::setw(width)<<""<<"Invalid choice, please try again."<<endl;}
    }
}

string typeCheck(Type type){
    if(type == Type::FIRE){
      return "fire";
    }
    else if(type == Type::GRASS){
        return "grass";
    }
    else if(type == Type::NORMAL){
        return "normal";
    }
    else if(type == Type::WATER){
        return "water";
    }
    else{
        return "UNAVAILABLE"; //PLACE HOLDER
    }
}
string moveCategoryCheck(MoveCategory category){
    if(category == MoveCategory::Physical){
        return "physical";
    }
    else if(category == MoveCategory::Special){
        return "special";
    }
    else{
        return "UNAVAILABLE"; //PLACE HOLDER
    }
}

void Game::attackExecute(Pokemon& attacker, Pokemon& defender, Move& move) {

    /* Calculate the damage
    Check if the attacker/defender's held item is triggered
    Apply the damage to the defender  */

    vector<vector<double>> ad_factor = {{0.5, 0.5, 2},{2, 0.5, 0.5},{0.5,2,0.5}};
    double stab = 1;
    double mul = 1;

    double damage;
    if(move.getCategory() == MoveCategory::Physical){
        double physical_damage;
        physical_damage = (attacker.getAttack()*move.getPower())/defender.getDefense();
        damage = physical_damage;
    }
    else if(move.getCategory() == MoveCategory::Special){
        double special_damage;
        special_damage = (attacker.getSpecialAttack()*move.getPower())/defender.getSpecialDefense();
        damage = special_damage;
    }

    //same type multiplier
    if(attacker.getType() == move.getType()){
        stab *= 1.5;
    }

    //type effectiveness
    if((defender.getType() == Type::NORMAL) || move.getType() == Type::NORMAL){
        mul = 1; //case 1
    }
    else if((move.getType() == defender.getType()) && move.getType() != Type::NORMAL){
        mul = 0.5; //case 2
    }
    else if((move.getType() == Type::FIRE) && (defender.getType() == Type::WATER)){
        mul = 0.5; //case 3
    }
    else if((move.getType() == Type::WATER) && (defender.getType() == Type::FIRE)){
        mul = 2;  //case 4
    }
    else if((move.getType() == Type::GRASS) && (defender.getType() == Type::FIRE)){
        mul = 0.5; //case 5
    }
    else if((move.getType() == Type::GRASS) && (defender.getType() == Type::WATER)){
        mul = 2;  //case 6
    }
    else if((move.getType() == Type::WATER) && (defender.getType() == Type::GRASS)){
        mul = 0.5;  //case 7
    }
    else if((move.getType() == Type::FIRE) && (defender.getType() == Type::GRASS)){
        mul = 2;    //case 8
    }

    double held_item_mul = 1;

    if(attacker.getHeldItem().getConditionType() == "move_type"){  //move_type
        if((attacker.getHeldItem().getCondition() == typeCheck(move.getType())) && (!attacker.getHeldItem().getConsumed())){
            if(attacker.getHeldItem().getConsumable()){
                attacker.getHeldItem().consumeItem();
                attacker.getHeldItem().setName("");
            }
            held_item_mul = attacker.getHeldItem().getEffect();
        }
    }

    if(attacker.getHeldItem().getConditionType() == "move_category"){ //move_category
        if((attacker.getHeldItem().getCondition() == moveCategoryCheck(move.getCategory())) && (!attacker.getHeldItem().getConsumed()))
            if(attacker.getHeldItem().getConsumable()){
                    attacker.getHeldItem().consumeItem();
                    attacker.getHeldItem().setName("");
                }
            held_item_mul = attacker.getHeldItem().getEffect();
    }

    double damage_mul = mul*stab*held_item_mul;
    int tot_damage = std::floor(damage_mul*damage);

    if(attacker.getName() == "T.S.M."){
        if(move.getName() == "SpreadCs"){
            Challenge ask_math = Challenge();
            bool get_ans = ask_math.run();
            if(get_ans){
                tot_damage /= 2;
                cout<<std::setw(M)<<""<<"Damage halved!"<<endl;
            }
        }
    }

    if(tot_damage > defender.getHp()){
        tot_damage = defender.getHp();
    }

    if((attacker.getName() == defender.getName())){
        mindControlAttack(attacker, attacker, move, move, tot_damage);
        attacker.reduceHp(tot_damage);
    }

    else{
        defender.reduceHp(tot_damage);
        damaged_info(attacker, defender, move,tot_damage, M);
        }

    if(attacker.getHeldItem().getConditionType() == "damage_done"){   //damage_done
        if((attacker.getHeldItem().getCondition() == "none") && (!attacker.getHeldItem().getConsumed())){

        if(attacker.getHeldItem().getConsumable()){
                    attacker.getHeldItem().consumeItem();
                    attacker.getHeldItem().setName("");
                }
            if(attacker.getHp() <= attacker.getMaxHp()){
                double steal = attacker.getHeldItem().getEffect()*tot_damage;
                int damage_done_heal = -1*std::floor(steal);  //negative for increasing HP
                attacker.reduceHp(damage_done_heal);
                cout<<std::setw(M)<<""<<"Using "<<attacker.getHeldItem().getName()<<"..."<<endl;
                if(attacker.getHp() >= attacker.getMaxHp()){
                    attacker.setHp(attacker.getMaxHp());
                    cout<<std::setw(M)<<""<<attacker.getName()<<" healed "<<" 0 HP!"<<endl;
                }
                else{
                    cout<<std::setw(M)<<""<<attacker.getName()<<" healed "<<-1*damage_done_heal<<" HP!"<<endl;
                }
            }
        }
    }

}
