#include "Enemy.h"

//ENEMY REALIZATION
Enemy::Enemy(int hp, int x, int y, const Animation& sequence, bool collision, int speed, const vector<COORD>& trajectory) :
    Sprite(hp, x, y, sequence, collision, speed), trajectory(trajectory) {}

void Enemy::movement()
{
    DX(0);
    DY(0);

    if (trajectory[trajectoryIndex].X > X())
        DX(1);
    else if (trajectory[trajectoryIndex].X < X())
        DX(-1);
    else if (trajectory[trajectoryIndex].Y > Y())
        DY(1);
    else if (trajectory[trajectoryIndex].Y < Y())
        DY(-1);
    else {
        trajectoryIndex = (trajectoryIndex >= trajectory.size() - 1 ? 0 : trajectoryIndex + 1);
    }

    move();

}

void Enemy::update(const Map& map) const
{
    Sprite::update(map);

    if (DY() == 1)
        update_horizontal(-halfX(), -halfY() - 2, map, sizeX());
    else if (DX() == 1)
        update_horizontal(-2, -halfY() - 1, map, 1);
    else if (DX() == -1)
        update_horizontal(2, -halfY() - 1, map, 1);
    //else if (DX() == 1)
    //    update_vertical(-halfX() - 1, -halfY() - 1, map, 1);
    //else if (DX() == -1)
    //    update_vertical(halfX() + 1, -halfY() - 1, map, 1);

}

void Enemy::clear(const Map& map) const
{
    update_horizontal(-halfX(), -halfY() - 1, map, sizeX());
    Sprite::clear(map);
}

void Enemy::display(const Map& map) const
{
    COORD c = { short(X() - 1), short(Y() - halfY() - 1)};
    if (map.valid_position(c)) {
        //cprint(to_string(HP()).c_str(), BG_bRED, c);
        print(HP() / 100 + 48, BG_bRED | FG_WHITE, c);
        print(HP() / 10 % 10 + 48, BG_bRED | FG_WHITE, { short(c.X + 1), c.Y });
        print(HP() % 10 + 48, BG_bRED | FG_WHITE, { short(c.X + 2), c.Y });
    }

    Object::display(map);
}