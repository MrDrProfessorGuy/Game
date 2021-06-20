#include "Medic.h"
#include"Exceptions.h"

using namespace mtm;

Medic::Medic(Team team, units_t health, units_t ammo, units_t attack_range,
             units_t power, int row, int col) : Character(team, health, ammo, attack_range
                                                          , power, row, col) {
    move_range = 5;
}


Character* Medic::clone() const {
    return new Medic(*this);
    
}

bool Medic::attackInRange(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const {
    if (GridPoint::distance(src_coordinates, dst_coordinates) <= attack_range) {
        return true;
    }
    return false;
}

bool Medic::validTarget(const GridPoint& src_coordinates, const GridPoint& dst_coordinates
                ,const std::shared_ptr<Character>& opponent) const{
    if (opponent == nullptr || GridPoint::distance(src_coordinates,dst_coordinates) == 0) {
        return false;
    }
    return true;
}

void Medic::attack(std::shared_ptr<Character> opponent, const GridPoint& src_coordinates,
                   const GridPoint& dst_coordinates, bool check_range, bool* killed_opponent) {
    
    if (!attackInRange(src_coordinates, dst_coordinates)) {
        throw OutOfRange();
    }
    if (ammo < 1) {
        throw OutOfAmmo();
    }
    if (!validTarget(src_coordinates, dst_coordinates, opponent)) {
        throw IllegalTarget();
    }
    else {
        if (isTeamMate(opponent)) {
            opponent->increaseHealth(power);//increase health for who's in the targeted cell
            return;
        }
        else {
            ammo--;
            opponent->decreaseHealth(power, killed_opponent);
            return;
        }
    }
    
}

void Medic::reload(const GridPoint& coordinates) {
    ammo += 5;
}


void Medic::print(std::ostream& os) const {
    if (team == CROSSFITTERS) {
        os << "m";//no new line because it should be continuos
    }
    if (team == POWERLIFTERS) {
        os << "M";
    }
}

std::ostream& operator<<(std::ostream& os, const Medic& medic) {
    medic.print(os);
    return os;
    
}

