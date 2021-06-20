#include"Exceptions.h"
#include"Sniper.h"

using namespace mtm;
#define SNIPER_MOVE_RANGE 4
#define SNIPER_POWER_ATTACK 3

Sniper::Sniper(Team team, units_t health, units_t ammo, units_t attack_range,
               units_t power, int row, int col) :
               Character(team, health, ammo, attack_range, power, row, col), count_attacks(0) {
    move_range = SNIPER_MOVE_RANGE;
}


Character* Sniper::clone() const {
    return new Sniper(*this);
}

bool Sniper::attackInRange(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const {
    double distance = GridPoint::distance(src_coordinates, dst_coordinates);
    if ((distance <= attack_range) && (distance >= ceil(double(attack_range) / 2))) {
        return true;
    }
    return false;
}

bool Sniper::validTarget(const GridPoint& src_coordinates, const GridPoint& dst_coordinates
        ,const std::shared_ptr<Character>& opponent) const {
    
    if (opponent == nullptr || isTeamMate(opponent)){
        return false;
    }
    return true;
}

void Sniper::attack(std::shared_ptr<Character> opponent, const GridPoint& src_coordinates
                    , const GridPoint& dst_coordinates, bool check_range, bool* killed_opponent) {
    if (!attackInRange(src_coordinates, dst_coordinates)) {
        throw OutOfRange();
    }
    if (ammo < 1) {
        throw OutOfAmmo();
    }
    if (!validTarget(src_coordinates, dst_coordinates, opponent)) {
        throw IllegalTarget();
    }
    
    count_attacks++;
    ammo--;
    if (count_attacks == SNIPER_POWER_ATTACK) {
        opponent->decreaseHealth(2 * power, killed_opponent);//update the health value
        count_attacks = 0;
    }
    else{
        opponent->decreaseHealth(power, killed_opponent);//update the health value
    }
    
}

void Sniper::reload(const GridPoint& coordinates) {
    ammo += 2;
}

void Sniper::print(std::ostream& os) const {
    if (team == CROSSFITTERS) {
        os << "n";
    }
    if (team == POWERLIFTERS) {
        os << "N";
    }
}

std::ostream& operator<<(std::ostream& os, const Sniper& sniper) {
    sniper.print(os);
    return os;
}
