#include "Hud.h"

void Hud::setup(const Player& player)
{
	//UPPER BORDER
	print('+', FG_BLUE, { 0, mHeight });
	for (short i = 1; i < mWidth - 1; i++)
		print('-', FG_BLUE, { i, mHeight });
	print('+', FG_BLUE, { mWidth - 1, mHeight });

	//BOTTOM BORDER
	print('+', FG_BLUE, { 0, mHeight + hHeight - 1 });
	for (short i = 1; i < mWidth - 1; i++)
		print('-', FG_BLUE, { i, mHeight + hHeight - 1 });
	print('+', FG_BLUE, { mWidth - 1, mHeight + hHeight - 1 });

	//LEFT BORDER
	for (short i = mHeight + 1; i < mHeight + hHeight - 1; i++)
		print('|', FG_BLUE, { 0, i });

	//RIGHT BORDER
	for (short i = mHeight + 1; i < mHeight + hHeight - 1; i++)
		print('|', FG_BLUE, { mWidth - 1, i });


	set_colour(BG_MAGENTA);
	set_cursor({ 97, 31 });
	printf("%-8s%-14s", "", "WEAPON");

	set_colour(BG_bRED);
	set_cursor({ 1, 31 });
	printf("%-10s", " HEALTH");
	printf("[%s]", string(150 / 5, ' ').c_str());

	set_colour(BG_bBLUE);
	set_cursor({ 1, 32 });
	printf("%-10s", " SPEED");
	printf("[%30s]", "");

	set_colour(BG_BLUE);
	set_cursor({ 1, 33 });
	printf("%-10s", " ENERGY");
	printf("[%-30s]", string(player.max_energy / 5, ' ').c_str());
}

void Hud::display(const Player& player)
{
	//HEALTH INDICATOR
	set_cursor({ 12, 31 });
	set_colour(BG_bRED);
	printf("%-30s", string(player.HP() / 5, '#').c_str());

	//SPEED INDICATOR
	set_cursor({ 12, 32 });
	set_colour(BG_bBLUE);
	printf("%-30s", string(player.SPEED() / 5, '#').c_str());

	//ENERGY
	set_cursor({ 12, 33 });
	set_colour(BG_BLUE);
	printf("%-30s", string(player.energy / 5, '#').c_str());

	//WEAPON 1
	set_cursor({ 97, 32});
	set_colour(player.selected_weapon ? BG_MAGENTA : BG_bMAGENTA);
	printf(" %-15s", player.weapon[0].NAME().c_str());
	printf("%-2d/%-3d", player.weapon[0].MAGAZINE(), player.weapon[0].AMMO());

	//WEAPON 2
	set_cursor({ 97, 33 });
	set_colour(player.selected_weapon ? BG_bMAGENTA : BG_MAGENTA);
	printf(" %-15s", player.weapon[1].NAME().c_str());
	printf("%-2d/%-3d", player.weapon[1].MAGAZINE(), player.weapon[1].AMMO());
}
