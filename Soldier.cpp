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

bool Soldier::attackInRange(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const {
    if (GridPoint::distance(src_coordinates, dst_coordinates) > attack_range) {
        return false;
    }
    return true;
}

bool Soldier::validTarget(const GridPoint& src_coordinates, const GridPoint& dst_coordinates
        ,const std::shared_ptr<Character>& opponent) const{
    
    if ((src_coordinates.row != dst_coordinates.row) && (src_coordinates.col != dst_coordinates.col)) {
        return false;
    }
    return true;
}

void Soldier::attack(std::shared_ptr<Character> opponent, const GridPoint& src_coordinates,
                     const GridPoint& dst_coordinates, bool check_range, bool* killed_opponent) {
    
    //if it's the first check then it checks if dest out of Soldier attack range
    if (check_range) {
        if (!attackInRange(src_coordinates, dst_coordinates)) {
            throw OutOfRange();
        }
        if (ammo < 1) {
            throw OutOfAmmo();
        }
        if (!validTarget(src_coordinates, dst_coordinates, opponent)){
            throw IllegalTarget();
        }
        ammo--;//ammo is decreased only once per attack
        if (opponent == nullptr || isTeamMate(opponent)) {
            return;
        }

        opponent->decreaseHealth(power, killed_opponent);//update the power value of the rival in the intial attacked cell
        return;
    }
    
    else if (GridPoint::distance(src_coordinates, dst_coordinates) <= ceil(double(attack_range) / 3)) {
        if (isTeamMate(opponent)) {
            return;
        }
    
        opponent->decreaseHealth(ceil(double(power) / 2), killed_opponent);//update the power value of the rest of the rivals in range
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



