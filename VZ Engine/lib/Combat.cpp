#include "Combat.h"



//BULLET REALIZATION
Bullet::Bullet(int hp, int dx, int dy, int x, int y, const Animation& sequence, int speed, int damage)
    : Sprite(hp, dx, dy, x, y, sequence, true, speed), damage(damage) {}

Bullet::Bullet(int hp, const Animation& sequence, int speed, int damage)
    : Sprite(hp, -1, -1, sequence, true, speed), damage(damage) {}

int Bullet::DAMAGE() const
{
    return damage;
}

void Bullet::DAMAGE(int damage)
{
    this->damage = damage;
}

void Bullet::movement()
{
    move();
}



//WEAPON REALIZATION
Weapon::Weapon(const string& name, int shoot_speed, int reload_speed, int magazine_size, int ammo, const Bullet& bullet)
    : name(name), shoot_speed(shoot_speed), reload_speed(reload_speed), magazine_size(magazine_size), magazine(magazine_size), ammo(ammo), bullet(bullet), shoot_time(), reload_time() {}

const string& Weapon::NAME() const
{
    return name;
}

void Weapon::NAME(const string& name)
{
    this->name = name;
}

int Weapon::MAGAZINE() const
{
    return magazine;
}

void Weapon::MAGAZINE(int magazine)
{
    this->magazine = magazine;
}

int Weapon::AMMO() const
{
    return ammo;
}

void Weapon::AMMO(int ammo)
{
    this->ammo = ammo;
}

const Stopwatch& Weapon::RELOAD_TIME() const
{
    return reload_time;
}

Stopwatch& Weapon::RELOAD_TIME()
{
    return reload_time;
}

int Weapon::RELOAD_SPEED() const
{
    return reload_speed;
}

void Weapon::RELOAD_SPEED(int reload_speed)
{
    this->reload_speed = reload_speed;
}

void Weapon::reload()
{
    if (!magazine and ammo) {
        magazine = magazine_size;
        ammo -= magazine_size;
    }
}

void Weapon::shoot(list<Bullet>& bullets, const Sprite& shooter, int dx, int dy)
{
    if (magazine <= 0) return;
    shoot_time.update();
    if (shoot_time >= 1000 / shoot_speed) {
        shoot_time.reset();
        bullets.emplace_back(sample(shooter, dx, dy));
        magazine--;
    }
}

Bullet Weapon::sample(const Sprite& shooter, int dx, int dy)
{
    return Bullet{ bullet.HP(), dx, dy, shooter.X(), shooter.Y(), bullet.sequence, bullet.SPEED(), bullet.damage};;
}