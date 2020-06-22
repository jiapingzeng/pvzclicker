#include <stdio.h>
#include <xdo.h>

int DEBUG = 1;

// game field position relative to window
// TODO: calculate these using window size
const int field_start_x = 35;
const int field_start_y = 40 + 90;
const int block_width = 80;     // width of each block in PvZ
const int block_height = 75;     // height of each block in PvZ
const int cannon_cooldown = 36;  // cob cannon cooldow
const int click_cooldown = 0.3;  // cooldown between each click (in seconds)
const int left_click_button = 1; // button number of left click

Window wid; // window ID
xdo_t *xdo; // xdo context
int sn = 0; // screen number, only supports primary monitor (0) currently
int in_game = 0;

// fire cannon at block position (cbx,cby) to target block position (tbx,tby)
void fire_cannon(int cbx, int cby, int tbx, int tby);
// convert block x position bx to pixel x position
int pixel_pos_x(int bx);
// convert block x position by to pixel y position
int pixel_pos_y(int by);
// start next game
void next_round();

int main()
{

    // window-related variables
    int mx;          // mouse x position
    int my;          // mouse y position
    int wx;          // window x position
    int wy;          // window y position
    unsigned int ww; // window width
    unsigned int wh; // window height

    int i = 0;

    xdo = xdo_new(NULL);

    printf("Please select the window of your game.\n");
    xdo_select_window_with_click(xdo, &wid);
    printf("Selected window ID: %lu\n", wid);

    xdo_get_window_location(xdo, wid, &wx, &wy, NULL);
    printf("Window location: x: %d, y: %d\n", wx, wy);

    if (DEBUG)
    {
        xdo_get_mouse_location(xdo, &mx, &my, NULL);
        printf("Current mouse location: x: %d, y: %d\n", mx, my);

        xdo_get_window_size(xdo, wid, &ww, &wh);
        printf("Window size: width: %d, height: %d\n", ww, wh);

        /*
        while (1)
        {
            xdo_get_mouse_location(xdo, &mx, &my, NULL);
            printf("Current relative location: x: %d, y: %d\n", mx - wx, my - wy);
            sleep(1);
        }
        */
    }

    // game-related variables
    const int target_x[2] = {8, 8};                   // x position of target square
    const int target_y[2] = {2, 5};                   // y position of target square
    const int cannon_x[8] = {2, 2, 4, 4, 6, 6, 6, 6}; // x position of cob cannons
    const int cannon_y[8] = {3, 4, 3, 4, 2, 5, 1, 6}; // y position of cob cannons
    int cannon_wave_sleep = cannon_cooldown / 4;      // sleep time between waves

    next_round();
    sleep(3);

    while (in_game)
    {
        fire_cannon(cannon_x[i], cannon_y[i], target_x[0], target_y[0]);
        fire_cannon(cannon_x[i + 1], cannon_y[i + 1], target_x[1], target_y[1]);
        i = (i + 2) % 8;

        if (DEBUG)
        {
            printf("Firing success, sleeping for %d seconds\n", cannon_wave_sleep);
        }

        // TODO: allow fractions in sleep duration
        sleep(cannon_wave_sleep);
    }

    xdo_free(xdo);
}

// fire cannon at block position (cbx,cby) to target block position (tbx,tby)
void fire_cannon(int cbx, int cby, int tbx, int tby)
{
    int cpx = pixel_pos_x(cbx); // cannon pixel position-x
    int cpy = pixel_pos_y(cby); // cannon pixel position-y
    int tpx = pixel_pos_x(tbx); // target pixel position-x
    int tpy = pixel_pos_y(tby); // target pixel position-y

    // move cursor to cannon and select
    xdo_move_mouse_relative_to_window(xdo, wid, cpx, cpy);
    xdo_click_window(xdo, wid, left_click_button);

    if (DEBUG)
    {
        printf("Selected cannon at (%d,%d)\n", cpx, cpy);
    }

    sleep(click_cooldown);

    // move cursor to target and select
    xdo_move_mouse_relative_to_window(xdo, wid, tpx, tpy);
    xdo_click_window(xdo, wid, left_click_button);

    if (DEBUG)
    {
        printf("Fired at target (%d,%d)\n", tpx, tpy);
    }

    sleep(click_cooldown);
}

// convert block x position bx to pixel x position
int pixel_pos_x(int bx)
{
    return field_start_x + block_width * bx - block_width / 2;
}

// convert block x position by to pixel y position
int pixel_pos_y(int by)
{
    return field_start_y + block_height * by - block_height / 2;
}

void next_round()
{
    // TODO: move mouse to start next round
    in_game = !in_game;
}