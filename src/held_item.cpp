#include <iostream>
#include <vector>
#include <string>
#include "held_item.hpp"

#include <iomanip>
using namespace std;

HeldItem::HeldItem() {
    
    isConsumed = false;
}

void HeldItem::displayInfo(int width) const {
    cout  <<std::setw(width) <<""<<  "== Held Item Info ==\n";
    cout  <<std::setw(width) <<""<< "Name: " << name << endl;
    cout  <<std::setw(width) <<""<< "Consumable: " << (isConsumable ? "Yes" : "No") << endl;
    cout  <<std::setw(width) <<""<< "Consumed: " << (isConsumed ? "Yes" : "No") << endl;
    cout  <<std::setw(width) <<""<< "Effect Type: " << effectType << endl;
    cout  <<std::setw(width) <<""<< "Effect: " << effect << endl;
    cout  <<std::setw(width) <<""<< "Condition Type: " << conditionType << endl;
    cout  <<std::setw(width) <<""<< "Condition: " << condition << endl;
    cout  <<std::setw(width) <<""<< "====================\n";
    
}

void HeldItem::setName(const string& itemName) {
    
    name = itemName;
}

string HeldItem::getName() const {
    
    return name;
}

void HeldItem::setConsumable(bool itemConsumable) {
    
    isConsumable = itemConsumable; //CP
}

bool HeldItem::getConsumable() const {
    
    return isConsumable;
}

void HeldItem::consumeItem() {
    
    if(isConsumable){
        isConsumed = true;
    }
}

bool HeldItem::getConsumed() const {
    
    return isConsumed;
}

void HeldItem::setEffectType(const string& itemType) {
    
    effectType = itemType;
}

string HeldItem::getEffectType() const {
    
    return effectType;
}

void HeldItem::setEffect(double itemEffect) {
    
    effect = itemEffect;
}

double HeldItem::getEffect() const {
    
    return effect;
}

void HeldItem::setConditionType(const string& itemConditionType) {
    
    conditionType = itemConditionType;
}

string HeldItem::getConditionType() const {
    
    return conditionType;
}

void HeldItem::setCondition(const string& itemCondition) {
    
    condition = itemCondition;
}

string HeldItem::getCondition() const {
    
    return condition;
}