#ifndef GAME_SNIPER_H
#define GAME_SNIPER_H

#include "Character.h"




class Sniper : public Character {
public:
    Sniper(mtm::Team character_team, mtm::units_t health_units) {
        team = character_team;
        health = health_units;
        ammo = 3;
        range = 4;
    
        attack_cost = 1;
        reload_addition = 2;
        if (team == mtm::POWERLIFTERS) {
            identifier = 'N';
        }
        else if (team == mtm::CROSSFITTERS) {
            identifier = 'n';
        
        }
    }
    
    
    Character* clone() const override;
    
    void reload() override;
    void attack(mtm::GridPoint attack_coordinate) const override;
private:
    
    bool validMove(mtm::GridPoint& src_coordinates, mtm::GridPoint& dst_coordinates) const;
    bool validAttack(mtm::GridPoint& src_coordinates, mtm::GridPoint& dst_coordinates) const;




};


#endif //GAME_SNIPER_H
