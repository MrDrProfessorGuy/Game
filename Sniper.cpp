#include"Exceptions.h"
#include"Sniper.h"


using namespace mtm;

Sniper::Sniper(Team team, units_t health, units_t ammo, units_t attack_range,
               units_t power, int row, int col, int count_attacks) :
               Character(team, health, ammo, attack_range, power, row, col), count_attacks(0) {
    move_range = 4;
}


Character* Sniper::clone() const {
    return new Sniper(*this);
    
}

bool Sniper::attackIsValid(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const {
    double distance = GridPoint::distance(src_coordinates, dst_coordinates);
    if ((distance <= attack_range) && (distance >= ceil(attack_range / 2))) {
        return true;
    }
    return false;
}

void Sniper::attack(std::shared_ptr<Character> ptr_character_attacked, const GridPoint& src_coordinates, const GridPoint& dst_coordinates, bool check_range, bool* health_zero) {
    if (!attackIsValid(src_coordinates, dst_coordinates)) {
        throw OutOfRange();
    }
    
    if (ptr_character_attacked != nullptr) {
        if (ammo < 1) {
            throw OutOfAmmo();
        }
        if (compareTeam(ptr_character_attacked)) {
            throw IllegalTarget();
        }
        count_attacks++;
        ammo--;
        if (count_attacks == 3) {
            decreaseHealth(2 * power, ptr_character_attacked, health_zero);//update the health value
            count_attacks = 0;
        }
        decreaseHealth(power, ptr_character_attacked, health_zero);//update the health value
        return;
    }
    throw IllegalTarget();
    
}

void Sniper::reload(const GridPoint& coordinates) {
    ammo += 2;
}

void Sniper::print(std::ostream& os) const {
    if (team == CROSSFITTERS) {
        os << "n";//no new line because it should be continuos
    }
    if (team == POWERLIFTERS) {
        os << "N";
    }
}

std::ostream& operator<<(std::ostream& os, const Sniper& sniper) {
    sniper.print(os);
    return os;
    
}
