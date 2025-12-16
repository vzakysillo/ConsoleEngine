#include "PLayer.h"


//PLAYER REALIZATION
Player::Player(int hp, int x, int y, const Animation& sequence, int speed, int max_energy, const vector<Weapon>& weapon) :
    Sprite(hp, x, y, sequence, true, speed), max_energy(max_energy), energy(max_energy), energy_speed(25), energy_time(), weapon(weapon), selected_weapon(0), is_running(false) {}

size_t Player::SELECTED_WEAPON() const
{
    return selected_weapon;
}

void Player::SELECTED_WEAPON(size_t selected_weapon)
{
    this->selected_weapon = selected_weapon;
}

int Player::ENERGY() const
{
    return energy;
}

void Player::ENERGY(int energy)
{
    this->energy = (energy >= max_energy ? max_energy : energy);
}

void Player::movement()
{
    DX(0);
    DY(0);

    if (GetAsyncKeyState((WORD)VK_SHIFT) & 0x8000) {
        if (!is_running and energy > 0)
        {
            is_running = true;
            SPEED(SPEED() * 2);
        }
    }
    else if (is_running)
    {
        is_running = false;
        SPEED(SPEED() / 2);
    }

    if (GetAsyncKeyState((WORD)'W') & 0x8000)
        DY(-1);
    else if (GetAsyncKeyState((WORD)'S') & 0x8000)
        DY(1);
    else if (GetAsyncKeyState((WORD)'A') & 0x8000)
        DX(-1);
    else if (GetAsyncKeyState((WORD)'D') & 0x8000)
        DX(1);

    move();
}

void Player::change_weapon()
{
    if (GetAsyncKeyState((WORD)'1') & 0x8000)
        selected_weapon = 0;
    else if (GetAsyncKeyState((WORD)'2') & 0x8000)
        selected_weapon = 1;
}

void Player::combat(list<Bullet>& bullets)
{
    if (GetAsyncKeyState((WORD)VK_RIGHT) & 0x8000)
        weapon[selected_weapon].shoot(bullets, *this, 1, 0);
    else if (GetAsyncKeyState((WORD)VK_LEFT) & 0x8000)
        weapon[selected_weapon].shoot(bullets, *this, -1, 0);
    else if (GetAsyncKeyState((WORD)VK_DOWN) & 0x8000)
        weapon[selected_weapon].shoot(bullets, *this, 0, 1);
    else if (GetAsyncKeyState((WORD)VK_UP) & 0x8000)
        weapon[selected_weapon].shoot(bullets, *this, 0, -1);

}

void Player::reload()
{
    if (GetAsyncKeyState((WORD)'R') & 0x8000) {
        weapon[selected_weapon].RELOAD_TIME().update();
        if (weapon[selected_weapon].RELOAD_TIME() >= weapon[selected_weapon].RELOAD_SPEED()) {
            weapon[selected_weapon].RELOAD_TIME().reset();
            weapon[selected_weapon].reload();
        }
    }
    else {
        weapon[selected_weapon].RELOAD_TIME().reset();
    }
}

void Player::stamina()
{
    energy_time.update();
    if (energy_time >= energy_speed) {
        energy_time.reset();
        if (is_running and energy > 0) {
            energy -= 1;
        }
        else if (energy < max_energy) {
            energy += 1;
        }
    }
}

