#include"Soldier.h"
#include<cmath>
#include "Exceptions.h"


using namespace mtm;

Soldier::Soldier(Team team, units_t health, units_t ammo, units_t attack_range,
                 units_t power, int row, int col) :
                 Character(team, health, ammo, attack_range, power, row, col) {
    move_range = 3;
}

Character* Soldier::clone() const {
    return new Soldier(*this);
    
}

bool Soldier::attackIsValid(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const {
    if ((src_coordinates.row != dst_coordinates.row) && (src_coordinates.col != dst_coordinates.col)) {
        return false;
    }
    if (GridPoint::distance(src_coordinates, dst_coordinates) > attack_range) {
        return false;
    }
    
    return true;
}

void Soldier::attack(std::shared_ptr<Character> ptr_character_attacked, const GridPoint& src_coordinates,
                     const GridPoint& dst_coordinates, bool check_range, bool* health_zero) {
    
    //if it's the first check then it checks if dest out of Soldier attack range
    if (check_range) {
        
        if (!attackIsValid(src_coordinates, dst_coordinates)) {
            throw OutOfRange();
        }
    
        if (ammo < 1) {
            throw OutOfAmmo();
        }
        ammo--;//ammo is decreased only once per attack
        if (ptr_character_attacked == nullptr) {
            return;//does nothing if none is on the cell
        }
        
        if (compareTeam(ptr_character_attacked)) {
            return;
        }

        decreaseHealth(power, ptr_character_attacked, health_zero);//update the power value of the rival in the intial attacked cell
        return;
    }
    
    else if (GridPoint::distance(src_coordinates, dst_coordinates) <= ceil(double(attack_range) / 3)) {
        if (compareTeam(ptr_character_attacked)) {
            return;
        }
        
        decreaseHealth(ceil(double(power) / 2), ptr_character_attacked, health_zero);//update the power value of the rest of the rivals in range
    }
    
}

void Soldier::reload(const GridPoint& coordinates) {
    ammo += 3;
}

void Soldier::print(std::ostream& os) const {
    if (team == CROSSFITTERS) {
        os << "s";//no new line because it should be continuos
    }
    if (team == POWERLIFTERS) {
        os << "S";
    }
}

std::ostream& operator<<(std::ostream& os, const Soldier& soldier) {
    soldier.print(os);
    return os;
}



