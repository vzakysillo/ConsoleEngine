#pragma once
#include "Sprite.h"


class Bullet : public Sprite {
private:
    int damage;
    friend class Weapon;
    friend struct level;
protected:
    int DAMAGE() const;
    void DAMAGE(int damage);
public:

    Bullet(int hp, int dx, int dy, int x, int y, const Animation& sequence, int speed, int damage);

    Bullet(int hp, const Animation& sequence, int speed, int damage);

    void movement() override;

};

class Weapon {
    string name;
    Bullet bullet;
    Stopwatch shoot_time;
    int shoot_speed; //shots / 1000ms
    Stopwatch reload_time;
    int reload_speed; // ms / shot
    int ammo;
    int magazine_size;
    int magazine;
//protected:

public:
    const string& NAME() const;
    void NAME(const string& name);

    int MAGAZINE() const;
    void MAGAZINE(int magazine);

    int AMMO() const;
    void AMMO(int ammo);

    const Stopwatch& RELOAD_TIME() const;
    Stopwatch& RELOAD_TIME();

    int RELOAD_SPEED() const;
    void RELOAD_SPEED(int reload_speed);

    Weapon(const string& name, int shoot_speed, int reload_speed, int magazine_size, int ammo, const Bullet& bullet);

    void reload();

    void shoot(list<Bullet>& bullets, const Sprite& shooter, int dx, int dy);

    Bullet sample(const Sprite& shooter, int dx, int dy);

};

namespace Arsenal {
    const Weapon test_gun
    { 
        "Test-Gun",         //name
        5,                  //shoot_speed
        0,               //reload_speed
        50,                  //magazine
        250,                 //ammo
        {
            10,         //bullet hp
            {{{'.'}}},  //bullet "texture"
            25,         //speed
            10          //damage
        }                   //bullet sample
    };

    const Weapon glock17
    {
        "Glock-17",
        8,
        3000,
        17,
        68,
        {10, {{{'.'}}}, 350, 15}
    };

    const Weapon m1911
    {
        "M1911",
        5,
        3000,
        7,
        28,
        {10, {{{'.'}}}, 260, 20}
    };
    
    const Weapon benellim4
    {
        "Beneli-M4",
        1,
        5000,
        5,
        20,
        {20, {{{'"'}}}, 450, 70, }
    };

    const Weapon m4a1
    {
        "M4A1",
        15,
        3000,
        30,
        120,
        {10, {{{','}}}, 850, 25}
    };
}

