#include <stdint.h>

#include "lab6.h"


// file-scope variables to hold the player's data

static int32_t px = 0;    // player's X position (from 0 to WORLD_WIDTH - 1)
static int32_t py = 0;    // player's Y position (from 0 to WORLD_HEIGHT - 1)
static int32_t pgold = 0; // player's gold       (collect 5 to win the game)


// simple access functions written for you; these functions allow 
// code in main.c to obtain the values of the file-scope variables

int32_t get_player_x (void) { return px; }
int32_t get_player_y (void) { return py; }
int32_t player_has_gold (void) { return pgold; }


//
// YOU MUST WRITE THE FIVE FUNCTIONS BELOW
//
// The specification explains what each should do.
//
// Return values have the following meanings for all five functions...
//    0 -- move failed (move outside world, move into wall)
//    1 -- move successful
//    2 -- player won the game by collecting 5 gold
//    3 -- player died by moving next to a snake
//
int32_t player_move_right(void)
{
    if(px + 1 > WORLD_WIDTH - 1)
    {
        return 0;
    }
    int32_t a;
    a = world_has ( px+1, py);
    if(a==WORLD_WALL)
    {
        return 0;
    }
    px = px + 1;
    int32_t b = check_new_move ();
    return b;


}

int32_t
player_move_left (void)
{
    if(px - 1 < 0)
    {
        return 0;
    }
    int32_t a;
    a = world_has ( px-1, py);
    if(a==WORLD_WALL)
    {
        return 0;
    }
    px = px - 1;
    int32_t b=check_new_move ();
    return b;
}



int32_t
player_move_up (void)
{
    if(py - 1 < 0 )
    {
        return 0;
    }
    int32_t a;
    a = world_has ( px, py-1);
    if(a==WORLD_WALL)
    {
        return 0;
    }
    py = py - 1;
    int32_t b=check_new_move ();
    return b;
}

int32_t
player_move_down (void)
{
    if(py + 1 > WORLD_HEIGHT - 1)
    {
        return 0;
    }
    int32_t a;
    a = world_has ( px, py+1);
    if(a==WORLD_WALL)
    {
        return 0;
    }
    py= py + 1;
    int32_t b=check_new_move ();
    return b;
}

int32_t 
check_new_move ()
{
    int32_t a;
    a = world_has ( px, py);
    if(a==WORLD_GOLD)
    {
        world_set (px, py, WORLD_EMPTY);
        pgold = pgold + 1;
        if(pgold==5)
        {
            return 2;
        }
        return 1;
    }
    if(a==WORLD_SNAKE)
    {
        return 3;
    }
    return 1;
}

