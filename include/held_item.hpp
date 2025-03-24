#pragma once
#ifndef HELD_ITEM_HPP
#define HELD_ITEM_HPP
#include <string>
using namespace std;

class HeldItem {
    
public:
    HeldItem();
    void setConsumable(bool itemConsumable);
    bool getConsumable() const;
    void consumeItem();
    bool getConsumed() const;
    void setName(const string& itemName);
    string getName() const;
    void setEffectType(const string& itemType);
    string getEffectType() const;
    void setEffect(double itemEffect);
    double getEffect() const;
    void setConditionType(const string& itemConditionType);
    string getConditionType() const;
    void setCondition(const string& itemCondition);
    string getCondition() const;
    void displayInfo(int) const;

private:
    bool isConsumable;
    bool isConsumed;
    string name;
    string effectType;
    double effect;
    string conditionType;
    string condition;
};
#endif