#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include <iostream>
#include "Auxiliaries.h"




class Character {
public:
    
    virtual ~Character() = 0;
    virtual Character* clone() const = 0;
    
    virtual void reload() = 0;
    virtual void attack(Character& opponent) const = 0;
    
    std::ostream& operator<<(std::ostream& stream, const Character character);

protected:
    mtm::Team team;
    int health;
    int ammo;
    int range;
    int power;
    
    int attack_cost;
    int reload_addition;
    bool in_game;
    char identifier;
    
    virtual bool validMove(mtm::GridPoint& src_coordinates, mtm::GridPoint& dst_coordinates) const = 0;
    virtual bool validAttack(mtm::GridPoint& src_coordinates, mtm::GridPoint& dst_coordinates) const = 0;
    
};


#endif //GAME_CHARACTER_H
