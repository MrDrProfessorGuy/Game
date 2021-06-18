#include"Character.h"
#include "Exceptions.h"

using namespace mtm;

bool Character::moveIsValid(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const {
    if (GridPoint::distance(src_coordinates, dst_coordinates) <= range) {
        return true;
    }
    return false;
}

Character::Character(Team team, units_t health, units_t ammo, units_t range, units_t power,
                     int row, int col) : team(team), health(health), ammo(ammo),
                                         range(range), power(power), location(GridPoint(row, col)) {}


void Character::move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) {
    bool valid_move = moveIsValid(src_coordinates, dst_coordinates);
    if (!valid_move) {
        throw MoveTooFar();
    }
    if (this != nullptr) {
        throw CellOccupied();
    }
    location = GridPoint(dst_coordinates);//needs the copy? or just location=dst_coordinates
}

bool Character::compareTeam(std::shared_ptr<Character> ptr_character) {
    return team == ptr_character->team;
}

void Character::decreaseHealth(units_t power, std::shared_ptr<Character> ptr_character_attacked, bool* health_zero) {
    ptr_character_attacked->health -= power;
    if (ptr_character_attacked->health <= 0) {
        *health_zero = true;
        
    }
    
}

bool Character::increaseHealth(units_t power, std::shared_ptr<Character> ptr_character_attacked) {
    ptr_character_attacked->health += power;
}

void Character::addCrossOrPowerCount(int* count_cross_fitters, int* count_power_lifters) {
    if (team == CROSSFITTERS) {
        *(count_cross_fitters) += 1;
    }
    
    if (team == POWERLIFTERS) {
        *(count_power_lifters) += 1;
    }
}
