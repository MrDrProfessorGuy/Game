#include <iostream>

#include <cassert>

#include "Exceptions.h"
#include "Game.h"

using namespace mtm;
using namespace std;

void Test1();

int main() {
    Test1();
}

void Test1(){
    cout << "-----ErrorChecks-----" << endl;
    Game g1(5,10);
    try{
        g1.addCharacter(GridPoint(1,8), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 0, 2, 5, 5));
    } catch (IllegalArgument& e) {
        cout << e.what() << endl;
    }
    try{
        g1.addCharacter(GridPoint(1,8), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 2, 2, -5, 5));
    } catch (IllegalArgument& e) {
        cout << e.what() << endl;
    }
    g1.addCharacter(GridPoint(1,0), Game::makeCharacter(CharacterType::SNIPER, Team::POWERLIFTERS, 5, 2, 8, 15));
    g1.addCharacter(GridPoint(3,0), Game::makeCharacter(CharacterType::SNIPER, Team::POWERLIFTERS, 5, 2, 8, 15));
    g1.addCharacter(GridPoint(2,0), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 20, 2, 5, 5));
    g1.addCharacter(GridPoint(1,1), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 20, 2, 5, 5));
    g1.addCharacter(GridPoint(2,1), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 20, 2, 5, 5));
    g1.addCharacter(GridPoint(3,1), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 20, 2, 5, 5));
    g1.addCharacter(GridPoint(1,9), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 5, 2, 8, 15));
    g1.addCharacter(GridPoint(3,9), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 5, 2, 8, 15));
    g1.addCharacter(GridPoint(2,9), Game::makeCharacter(CharacterType::MEDIC, Team::CROSSFITTERS, 20, 2, 5, 5));
    g1.addCharacter(GridPoint(1,8), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 20, 2, 5, 5));
    g1.addCharacter(GridPoint(2,8), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 20, 2, 5, 5));
    g1.addCharacter(GridPoint(3,8), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 20, 2, 5, 5));
    cout << g1 << endl;
    cout << "-----CellOccupied-----" << endl;
    try{
        g1.addCharacter(GridPoint(1,8), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 20, 2, 5, 5));
    } catch (CellOccupied& e) {
        cout << e.what() << endl;
    }
    try{
        g1.move(GridPoint(3,9), GridPoint(3,9));
    } catch (CellOccupied& e) {
        cout << e.what() << endl;
    }
    try{
        g1.move(GridPoint(3,9), GridPoint(2,9));
    } catch (CellOccupied& e) {
        cout << e.what() << endl;
    }
    try{
        g1.move(GridPoint(1,1), GridPoint(2,1));
    } catch (CellOccupied& e) {
        cout << e.what() << endl;
    }
    try{
        g1.move(GridPoint(3,9), GridPoint(3,9));
    } catch (CellOccupied& e){
        cout << e.what() << endl;
    }
    cout << "-----IllegalCell-----" << endl;
    try{
        g1.move(GridPoint(1,1), GridPoint(-2,1));
    } catch (IllegalCell& e) {
        cout << e.what() << endl;
    }
    cout << "-----CellEmpty-----" << endl;
    try{
        g1.move(GridPoint(4,1), GridPoint(3,1));
    } catch (CellEmpty& e) {
        cout << e.what() << endl;
    }
    cout << "-----MoveTooFar-----" << endl;
    try{
        g1.move(GridPoint(1,0), GridPoint(0,4));
    } catch (MoveTooFar& e) {
        cout << e.what() << endl;
    }
    try{
        g1.move(GridPoint(2,0), GridPoint(0,4));
    } catch (MoveTooFar& e) {
        cout << e.what() << endl;
    }
    try{
        g1.move(GridPoint(1,8), GridPoint(0,5));
    } catch (MoveTooFar& e) {
        cout << e.what() << endl;
    }
    cout << "-----OutOfRange-----" << endl;
    try{
        g1.attack(GridPoint(1,0), GridPoint(1,9));
    } catch (OutOfRange& e){
        cout << e.what() << endl;
    }
    try{
        g1.attack(GridPoint(1,1), GridPoint(1,7));
    } catch (OutOfRange& e){
        cout << e.what() << endl;
    }
    try{
        g1.attack(GridPoint(2,9), GridPoint(4,5));
    } catch (OutOfRange& e){
        cout << e.what() << endl;
    }
    try{
        g1.attack(GridPoint(1,0), GridPoint(0,0));
    } catch (OutOfRange& e){
        cout << e.what() << endl;
    }
    try{
        g1.attack(GridPoint(1,0), GridPoint(1,3));
    } catch (OutOfRange& e){
        cout << e.what() << endl;
    }
    cout << "-----IllegalTarget-----" << endl;
    try{
    g1.attack(GridPoint(1,0), GridPoint(1,7));
    } catch (IllegalTarget& e){
        cout << e.what() << endl;
    }
    try{
    g1.attack(GridPoint(1,0), GridPoint(1,5));
    } catch (IllegalTarget& e){
        cout << e.what() << endl;
    }
    g1.move(GridPoint(1,0), GridPoint(0,0));
    try{
    g1.attack(GridPoint(0,0), GridPoint(1,3));
    } catch (IllegalTarget& e){
        cout << e.what() << endl;
    }
    g1.move(GridPoint(0,0), GridPoint(1,0));
    try{
    g1.attack(GridPoint(2,0), GridPoint(2,0));
    } catch (IllegalTarget& e){
        cout << e.what() << endl;
    }
    try{
    g1.attack(GridPoint(2,8), GridPoint(3,7));
    } catch (IllegalTarget& e){
        cout << e.what() << endl;
    }
    cout << "-----SniperMaxShot-----" << endl;
    g1.attack(GridPoint(1,0), GridPoint(1,8));
    cout << "-----SoldierMovement-----" << endl;
    g1.move(GridPoint(2,8), GridPoint(2,5));
    cout << "-----SniperShot-----" << endl;
    g1.attack(GridPoint(1,0), GridPoint(2,5));
    cout << "-----SoldierShot-----" << endl;
    g1.attack(GridPoint(2,5), GridPoint(2,1));
    cout << "-----MedicHeal-----" << endl;
    g1.attack(GridPoint(2,0), GridPoint(1,0));
    cout << "-----SoldierShot-----" << endl;
    g1.attack(GridPoint(2,5), GridPoint(2,1));
    try{
        g1.attack(GridPoint(1,0), GridPoint(2,5));
    } catch (OutOfAmmo& e){
        cout << e.what() << endl;
    }
        try{
        g1.attack(GridPoint(2,5), GridPoint(2,1));
    } catch (OutOfAmmo& e){
        cout << e.what() << endl;
    }
    cout << "-----SniperReload-----" << endl;
    g1.reload(GridPoint(1,0));
    
    cout << g1 << endl;
    cout << "-----MedicMove-----" << endl;
    g1.move(GridPoint(2,9), GridPoint(2,7));
    cout << "-----SniperHeadShot-----" << endl;
    g1.attack(GridPoint(1,0), GridPoint(2,7));
    cout << "-----CreatingCopyGame-----" << endl;
    Game g2 = g1;
    cout << "-----FirstGame-----" << endl;
    cout << "-----SoldierMove-----" << endl;
    g1.move(GridPoint(3,8), GridPoint(3,6));
    cout << "-----SoldierShot-----" << endl;
    g1.attack(GridPoint(1,1), GridPoint(1,6));
    cout << "-----SoldierShot-----" << endl;
    g1.attack(GridPoint(1,1), GridPoint(1,6));
    cout << "-----SniperShot-----" << endl;
    g1.attack(GridPoint(1,0), GridPoint(3,6));
    cout << g1 << endl;
    try{
        g1.attack(GridPoint(1,1), GridPoint(1,6));
    } catch (OutOfAmmo& e){
        cout << e.what() << endl;
    }
    try{
        g1.attack(GridPoint(1,0), GridPoint(3,6));
    } catch (OutOfAmmo& e){
        cout << e.what() << endl;
    }
    Team *team = new Team;
    assert(g1.isOver(team) == false);
    cout << "-----MedicMove-----" << endl;
    g1.move(GridPoint(2,0), GridPoint(2,5));
    cout << "-----MedicShot-----" << endl;
    g1.attack(GridPoint(2,5),GridPoint(1,9));
    try{
        g1.attack(GridPoint(2,5), GridPoint(3,9));
    } catch (OutOfAmmo& e){
        cout << e.what() << endl;
    }
    cout << "-----MedicReload-----" << endl;
    g1.reload(GridPoint(2,5));
    cout << "-----MedicShot-----" << endl;
    g1.attack(GridPoint(2,5),GridPoint(3,9));
    cout << g1 << endl;
    assert(g1.isOver(team) == true);
    assert(*team == POWERLIFTERS);
    cout << "Winner team is: POWERLIFTERS" << endl;
    cout << "-----SecondGame-----" << endl;
    cout<< g2 << endl;
    cout << "-----SoldierMove-----" << endl;
    g2.move(GridPoint(3,8), GridPoint(3,6));
    cout << "-----SniperShot-----" << endl;
    g2.attack(GridPoint(1,0), GridPoint(1,8));
    cout << g2 << endl;
    cout << "-----SoldierReload-----" << endl;
    g2.reload(GridPoint(2,5));
    cout << "-----SoldierShot-----" << endl;
    g2.attack(GridPoint(2,5), GridPoint(2,0));
    cout << "-----SoldierShot-----" << endl;
    g2.attack(GridPoint(2,5), GridPoint(2,0));
    cout << "-----SoldierShot-----" << endl;
    g2.attack(GridPoint(2,5), GridPoint(2,0));
    cout << g2 << endl;
    assert(g2.isOver(team) == false);
    cout << "-----SniperShot-----" << endl;
    g2.attack(GridPoint(1,9), GridPoint(1,1));
    cout << "-----SniperShot-----" << endl;
    g2.attack(GridPoint(3,9), GridPoint(3,1));
    cout << g2 << endl;
    cout << "-----SniperMove-----" << endl;
    g2.move(GridPoint(1,9), GridPoint(1,8));
    cout << "-----SniperShot-----" << endl;
    g2.attack(GridPoint(1,8), GridPoint(2,1));
    assert(g2.isOver(team) == true);
    cout << g2 << endl;
    assert(*team == CROSSFITTERS);
    cout << "Winner team is: CROSSFITTERS" << endl;
    g1.addCharacter(GridPoint(3,0), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 5, 2, 8, 15));
    assert(g1.isOver(team) == false);
    delete team;
}