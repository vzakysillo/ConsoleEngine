#pragma once
#include "Combat.h"



class Player : public Sprite {
    vector<Weapon> weapon;
    size_t selected_weapon;

    int energy;
    int max_energy;
    bool is_running;

    int energy_speed;
    Stopwatch energy_time;

    friend class Hud;
    friend struct level;
    friend class World;
protected:
    size_t SELECTED_WEAPON() const;
    void SELECTED_WEAPON(size_t selected_weapon);

    int ENERGY() const;
    void ENERGY(int energy);
public:
    Player() = delete;
    Player(int hp, int x, int y, const Animation& sequence, int speed, int max_energy, const vector<Weapon>& weapon);

    void movement() override;

    void change_weapon();

    void combat(list<Bullet>& bullets);

    void reload();

    void stamina();

    void show_info() const {
        char title[128];
        sprintf_s(title, sizeof(title), "(x - %d ; y - %d) (hp - %d)", X(), Y(), HP());
        SetConsoleTitleA(title);
    }


};