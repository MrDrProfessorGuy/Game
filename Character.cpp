#include"Character.h"
#include "Exceptions.h"

using namespace mtm;

bool Character::moveIsValid(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const {
    if (GridPoint::distance(src_coordinates, dst_coordinates) <= move_range) {
        return true;
    }
    return false;
}

Character::Character(Team team, units_t health, units_t ammo, units_t attack_range, units_t power,
                     int row, int col) : team(team), health(health), ammo(ammo), move_range(),
                     attack_range(attack_range), power(power), location(GridPoint(row, col)) {}

void Character::move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) {
    bool valid_move = moveIsValid(src_coordinates, dst_coordinates);
    if (!valid_move) {
        throw MoveTooFar();
    }
    set_location(dst_coordinates);//needs the copy? or just location=dst_coordinates
}

void Character::set_location(const GridPoint& coordinates){
    location = GridPoint(coordinates);
}


bool Character::isTeamMate(const std::shared_ptr<Character>& character) const{
    if (character == nullptr){
        return false;
    }
    return team == character->team;
}

void Character::decreaseHealth(units_t amount, bool* is_dead) {
    *is_dead = false;
    health -= amount;
    if (health <= 0) {
        *is_dead = true;
    }
}

void Character::increaseHealth(units_t amount) {
    bool tmp_bool = false;
    decreaseHealth(-amount, &tmp_bool);
}

Team Character::getTeam(){
    return team;
}






