#include"Character.h"

namespace mtm {
    class Medic : public Character {
    private:
        bool attackInRange(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const override;
        bool validTarget(const GridPoint& src_coordinates, const GridPoint& dst_coordinates
                ,const std::shared_ptr<Character>& opponent) const override;
                
    public:
        Medic(Team team, units_t health, units_t ammo, units_t attack_range
                ,units_t power, int row, int col);
        
        Medic(const Medic& other) = default;
        
        Medic& operator=(const Medic& other) = default;
        
        ~Medic() = default;
        
        Character* clone() const override;
        
        void reload(const GridPoint& coordinates) override;
        
        void attack(std::shared_ptr<Character> opponent, const GridPoint& src_coordinates, const GridPoint& dst_coordinates, bool check_range, bool* killed_opponent) override;
        
        void print(std::ostream& stream) const override;
        
        //friend std::ostream& operator<<(std::ostream& stream, const Medic& medic);
        
    };
    
    
    std::ostream& operator<<(std::ostream& stream, const Medic& medic);
    
}