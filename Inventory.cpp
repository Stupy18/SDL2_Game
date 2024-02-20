#include "Inventory.hpp"

  void Inventory::addItem(const Spell& spell) {
        spells.push_back(spell);
    }

    void Inventory::removeItem(const std::string& spellName) {
        spells.erase(std::remove_if(spells.begin(), spells.end(), 
            [&spellName](Spell& spell) { return spell.get_name() == spellName; }), spells.end());
    }