#include"Character.h"

namespace mtm {
    class Sniper : public Character {
    private:
        int count_attacks;
        bool attackInRange(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const override;
        bool validTarget(const GridPoint& src_coordinates, const GridPoint& dst_coordinates
                ,const std::shared_ptr<Character>& opponent) const override;
    
    public:
        Sniper(Team team, units_t health, units_t ammo, units_t attack_range
                ,units_t power, int row, int col);
        Sniper(const Sniper& other) = default;
        Sniper& operator=(const Sniper& other) = default;
        ~Sniper() = default;
        Character* clone() const override;
        void reload(const GridPoint& coordinates) override;
        void attack(std::shared_ptr<Character> opponent, const GridPoint& src_coordinates
                    , const GridPoint& dst_coordinates, bool check_range, bool* killed_opponent) override;
        void print(std::ostream& stream) const override;
    };
    
    
    std::ostream& operator<<(std::ostream& stream, const Sniper& sniper);
    
}

