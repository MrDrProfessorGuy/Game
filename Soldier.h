#ifndef GAME_SOLDIER_H
#define GAME_SOLDIER_H


#include "Character.h"



class Soldier : public Character{

public:
    Soldier();
    ~Soldier();
    Soldier& clone() const override;
    

};


#endif //GAME_SOLDIER_H
