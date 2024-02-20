#include "Spell.hpp"

Spell::Spell(std::string name, int cost, float cooldown, int position)
    : name(std::move(name)), cost(cost), cooldown(cooldown), lastUsedTime(0.0f), used(false), position(position) {}

int Spell::get_cost() const {
    return cost;
}

float Spell::get_cooldown() const {
    return cooldown;
}

std::string Spell::get_name() const {
    return name;
}

bool Spell::was_used() const {
    return used;
}

int Spell::get_position() const {
    return position;
}

void Spell::set_used() {
    used = true;
}

void Spell::useSpell(float currentTime) {
    if (!used) {
        used = true;
        lastUsedTime = currentTime;
    }
}

void Spell::updateCooldown(float currentTime) {
    if (used && (currentTime - lastUsedTime >= cooldown)) {
        used = false;
    }
}

bool Spell::canUseSpell() const {
    return !used;
}
