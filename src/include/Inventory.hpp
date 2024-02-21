#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include "Spell.hpp"

class Inventory {
private:
    std::vector<Spell> spells;

public:
    Inventory() = default;
    Inventory(const std::vector<Spell>& initialSpells);

    void addItem(const Spell& spell);
    void removeItem(const std::string& itemName);

    Spell& getItem_with_name(const std::string& itemName);
    Spell& getItem_with_position(const int& itemPosition);

    // Additional functions can be added here
};
