#pragma once
#include "string"
#include <vector>
#include "Spell.hpp"
#include <algorithm>

class Inventory {
private:
    std::vector<Spell> spells;
public:
    void addItem(const Spell& spell);

    void removeItem(const std::string& itemName);

    Spell getItem_with_name(const std::string& itemName) {
        for ( auto& spell : spells) {
            if (spell.get_name() == itemName) {
                return spell;
            }
        }

        // Return a default Item or throw an exception if the item is not found
        return Spell("",0,0,0); // Return an empty item or handle it appropriately
    }

    Spell getItem_with_position(const int& itemPosition) {
        for ( auto& spell : spells) {
            if (spell.get_position() == itemPosition) {
                return spell;
            }
        }

        // Return a default Item or throw an exception if the item is not found
        return Spell("",0,0,0); // Return an empty item or handle it appropriately
    }

    // Additional functions like getItem, hasItem, etc.
};
