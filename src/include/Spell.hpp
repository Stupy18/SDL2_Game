#pragma once

#include <string>

class Spell {
private:
    std::string name;
    int cost;
    float cooldown;
    float lastUsedTime=0.0f;
    bool used=false;
    int position;

public:
    Spell(std::string name, int cost, float cooldown, int position,float lastUsedTime);

    int get_cost() const;
    float get_lastUsedTime()
    {
        return lastUsedTime;
    }
    float get_cooldown() const;
    std::string get_name() const;
    bool was_used() const;
    int get_position() const;
    void set_used();
    void useSpell(float currentTime);
    void updateCooldown(float currentTime);
    bool canUseSpell() const;
};

