#ifndef GAME_MEDIC_H
#define GAME_MEDIC_H

#include "Auxiliaries.h"
#include "Character.h"

class Medic : public Character {
public:
    Medic(mtm::Team character_team, mtm::units_t health_units);
    
    
    Character* clone() const;
    
    void reload();
    void attack(mtm::GridPoint attack_coordinate) const;
private:
    
    bool validMove(mtm::GridPoint& src_coordinates, mtm::GridPoint& dst_coordinates) const;
    bool validAttack(mtm::GridPoint& src_coordinates, mtm::GridPoint& dst_coordinates) const;
    
    
    
    
};


#endif //GAME_MEDIC_H
