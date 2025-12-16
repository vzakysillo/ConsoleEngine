//#include "lib/PLayer.h"
//#include "lib/Combat.h"
#include "lib/Enemy.h"
#include "lib/Hud.h"
#include "lib/Bonus.h"

namespace img {
    Texture house0
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', '_', '_', '_', '_', '_', '_', '_', '_', '|', '+', '|', '_', '_', ' ', ' '},
        {' ', '/', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\\', ' '},
        {'/', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\\'},
        {'|', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '|'},
        {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
        {'|', ' ', ' ', ' ', '+', '+', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
        {'|', ' ', ' ', ' ', '+', '+', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '|'},
        {'|', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '#', '#', '_', '_', '_', '|'},
    };

    Texture house1
    {
        {' ', ' ', '_', '_', '_', '_', '_', '|', '+', '|', '_', ' ', ' '},
        {' ', '/', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\\', ' '},
        {'/', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\\'},
        {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
        {'|', ' ', ' ', '+', '+', ' ', ' ', ' ', ' ', '#', '#', ' ', '|'},
        {'|', '_', '_', '_', '_', '_', '_', '_', '_', '#', '#', '_', '|'},
    };


    Animation enemy_animation0
    {
        {
        {'@', '-', '@'},
        {'/', '|', '\\'},
        {'/', '\0', '\\'},
        },

        {
        {'@', '-', '@'},
        {'/', '|', '\\'},
        {'\0', '|', '\0'},
        }
    };

    Animation enemy_animation1
    {
        {
        {'\0', '(', '@', ')', '\0'},
        {'\0', '/', '|', '\\', '\0'},
        {'/', '\0', '|', '\0', '\\'},
        {'\0', '/', '\0', '\\', '\0'},
        {'/', '\0', '\0', '\0', '\\'},
        },

        {
        {'\0', '(', '@', ')', '\0'},
        {'\0', '/', '|', '\\', '\0'},
        {'/', '\0', '|', '\0', '\\'},
        {'\0', '\0', '|', '\0', '\0'},
        {'\0', '\0', '|', '\0', '\0'},
        }
    };

    Animation enemy_animation2
    {
        {
        {'<', '^', '>'},
        {'/', '+', '\\'},
        {'/', '\0', '\\'},
        },

        {
        {'<', '^', '>'},
        {'/', '+', '\\'},
        {'\0', '|', '\0'},
        }
    };


    Animation player_animation
    {
        {
        {'\0', 'O', '\0'},
        {'/', '|', '\\'},
        {'/', '\0', '\\'},
        },

        {
        {'\0', 'O', '\0'},
        {'/', '|', '\\'},
        {'\0', '|', '\0'},
        }
    };



    Texture hp_bonus
    ({
        {'*', '-', '*'},
        {'|', '+', '|'},
        {'*', '-', '*'}
    });

    Texture speed_bonus
    ({
        {'*', '-', '*'},
        {'|', '>', '|'},
        {'*', '-', '*'}
    });

    Texture energy_bonus
    ({
        {'*', '-', '*'},
        {'|', '/', '|'},
        {'*', '-', '*'}
    });
}

struct level {
    Map map;
    vector<Object> objs;
    list<Enemy> enms;
    list<Bonus> bnss;
    list<Bullet> blts;
    level(const Map& map, const vector<Object>& objs, const list<Enemy>& enms, const list<Bonus>& bnss) :
        map(map), objs(objs), enms(enms), bnss(bnss), blts() {}
    void bullet_destruction() {
        for (auto b = blts.begin(); b != blts.end(); ) {
            if (b->dead()) {
                b->clear(map);
                b = blts.erase(b);
            }
            else {
                b++;
            }
        }
    }
    void enemy_destruction() {
        for (auto e = enms.begin(); e != enms.end(); ) {
            if (e->dead()) {
                e->clear(map);
                e = enms.erase(e);
            }
            else {
                e++;
            }
        }
    }
    void bonus_destruction() {
        for (auto bn = bnss.begin(); bn != bnss.end(); ) {
            if (bn->dead()) {
                bn->clear(map);
                bn = bnss.erase(bn);
            }
            else {
                bn++;
            }
        }
    }

    void player_n_enemy(Player& player) {
        bool flag = true;
        for (const auto& e : enms) {
            if (player.collide(e))
                flag = false;
        }
        if (flag) player.DAMAGEABLE(true);

        for (auto& e : enms)
        {
            if (player.collide(e) and player.DAMAGEABLE()) {
                player.HP(player.HP() - 10);
                player.DAMAGEABLE(false);
                break;
            }
        }
    }
    void player_n_object(Player& player) {
        for (const auto& o : objs) {
            if (player.collide(o)) {
                player.X(player.X() - player.DX());
                player.DX(0);
                player.Y(player.Y() - player.DY());
                player.DY(0);
            }
        }
    }
    void player_n_bonus(Player& player) {
        for (auto& bn : bnss) {
            if (player.collide(bn)) {
                if (bn.TYPE() == 1) {
                    player.HP(player.HP() + bn.VALUE());
                }
                else if (bn.TYPE() == 2) {
                    player.SPEED(player.SPEED() + bn.VALUE());
                }
                else if (bn.TYPE() == 3) {
                    player.ENERGY(player.ENERGY() + bn.VALUE());
                }
                bn.HP(0);
            }
        }
    }
    void bullet_n_enemy() {
        for (auto& b : blts) {
            for (auto& e : enms) {
                if (b.collide(e) and e.DAMAGEABLE()) {
                    e.HP(e.HP() - b.DAMAGE());
                    e.DAMAGEABLE(false);
                    b.HP(0);
                }
            }
        }


        for (auto& e : enms) {
            bool flag = false;
            for (auto& b : blts) {
                flag = b.collide(e);
            }
            if (!flag) e.DAMAGEABLE(true);
        }
    }
    void bullet_n_object() {
        for (Bullet& b : blts) {
            for (const Object& o : objs) {
                if (b.collide(o) or b.border_collision()) {
                    b.HP(0);
                }
            }
        }

    };
};



class World {
private:
    vector<level> world;

public:
    size_t lvl;
    World() = delete;
    World(const initializer_list<level>& world, size_t lvl = 0)
        : world(world), lvl(lvl) {}

    size_t size() const {
        return world.size();
    }

    const level& operator[](size_t index) const {
        return world[index];
    }
    level& operator[](size_t index) {
        return world[index];
    }


    void transportation(Player& player) {
        int ofm = player.border_collision();
        if (!ofm) return;
        switch (ofm)
        {
        case 1:
            if (lvl > 0) {
                lvl--;
                player.X(mWidth - player.halfX());
                world[lvl].map.display();
            }
            break;
        case 3:
            if (lvl < size() - 1) {
                lvl++;
                player.X(player.halfX());
                world[lvl].map.display();
            }
        }

    }

    void show_info() {
        char title[64];
        sprintf_s(title, sizeof(title), "(ememy - %zd) (bullets - %zd) (lvl - %zd)", world[lvl].enms.size(), world[lvl].blts.size(), lvl);
        SetConsoleTitleA(title);
    }
};





int main()
{
    cursor_visible(false);

    level level_0
    {
        Map("map/grass0.bin"),
        {
            {100, 10, 5, img::house0, true, true},
            {100, 50, 15, img::house1, true, true},
        },
        {
            {100, 30, 5, img::enemy_animation0, true, 8, { {30, 5}, {70, 5 }}},
            {300, 10, 15, img::enemy_animation1, true, 8, { {10, 15}, {30, 15 }}}
        },
        {
            {5, 25, img::hp_bonus, 1, 10, BG_bRED},
            {65, 15, img::speed_bonus, 2, 10, BG_bBLUE},
        }
    };

    level level_1
    {
        Map("map/grass1.bin"),
        {
            {100, 80, 20, img::house0, true, true}
        },
        {
            {60, 30, 8, img::enemy_animation2, true, 20, { {30, 8}, {70, 8 }}},
            {120, 50, 13, img::enemy_animation0, true, 8, { {50, 13}, {110, 13 }}},
            {80, 10, 20, img::enemy_animation2, true, 15, { {10, 20}, {40, 20 }}},
        },
        {
            {10, 5, img::hp_bonus, 1, 10, BG_bRED},
            {115, 25, img::speed_bonus, 2, 10, BG_bBLUE},
            {90, 8, img::energy_bonus, 3, 100, BG_BLUE},
        }
    };


    level level_2
    {
        Map("map/grass2.bin"),
        {
            {100, 10, 15, img::house0, true, true}
        },
        { 
        },
        {
        }
    };


    World world{ {level_0, level_1, level_2}, 0 };

    Player player = { 100, 80, 28, img::player_animation, 15, 100, {Arsenal::glock17, Arsenal::m4a1} };

    
    world[world.lvl].map.display();
    Hud hud;

    hud.setup(player);
    
    FPS_counter fpsc;

    while (!player.dead())
    {
        //MAP UPDATE
        player.update(world[world.lvl].map);
        for (const auto& e : world[world.lvl].enms)
            e.update(world[world.lvl].map);
        for (const auto& b : world[world.lvl].blts)
            b.update(world[world.lvl].map);



        //SPRITE TRANSPORTATION
        world.transportation(player);
        world[world.lvl].enemy_destruction();
        world[world.lvl].bullet_destruction();
        world[world.lvl].bonus_destruction();



        //OBJECT
        for (const auto& o : world[world.lvl].objs)
            o.display(world[world.lvl].map);



        //BONUS
        for (const auto& bn : world[world.lvl].bnss)
            bn.display(world[world.lvl].map);



        //COMABT
        world[world.lvl].bullet_n_object();
        for (const auto& b : world[world.lvl].blts)
            b.display(world[world.lvl].map);
        for (auto& b : world[world.lvl].blts)
            b.movement();



        //PLAYER
        player.display(world[world.lvl].map);
        player.movement();
        player.stamina();
        player.change_weapon();
        player.combat(world[world.lvl].blts);
        player.reload();
        world[world.lvl].player_n_object(player);
        world[world.lvl].player_n_enemy(player);
        world[world.lvl].player_n_bonus(player);
        player.animation();
        


        //ENEMY
        world[world.lvl].bullet_n_enemy();
        for (const auto& e : world[world.lvl].enms)
            e.display(world[world.lvl].map);
        for (auto& e : world[world.lvl].enms)
            e.movement();
        for (auto& e : world[world.lvl].enms)
            e.animation();
        


        //HUD
        hud.display(player);



        //DEBUG
        fpsc.show_info();
        fpsc.update();
        //player.show_info();
        //world.show_info();
    }

}