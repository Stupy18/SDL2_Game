#include "Inventory.hpp"
#include <algorithm>

Inventory::Inventory(const std::vector<Spell>& initialSpells) : spells(initialSpells) {}

void Inventory::addItem(const Spell& spell) {
    spells.push_back(spell);
}

void Inventory::removeItem(const std::string& itemName) {
    spells.erase(
        std::remove_if(spells.begin(), spells.end(),
            [&itemName](const Spell& spell) { return spell.get_name() == itemName; }),
        spells.end()
    );
}

Spell& Inventory::getItem_with_position(const int& itemPosition) {
    for (auto& spell : spells) {
        if (spell.get_position() == itemPosition) {
            return spell;
        }
    }
    throw std::runtime_error("Spell not found at position: " + std::to_string(itemPosition));
}

// You can add other methods here, like checking inventory size, listing all items, etc.
