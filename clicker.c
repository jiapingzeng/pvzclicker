#include <stdio.h>
#include <xdo.h>

int main() {

    int mx; // mouse x position
    int my; // mouse y position
    int wx; // window x position
    int wy; // window y position
    int sn = 0; // screen number, only supports primary monitor (0) currently
    Window wid; // window ID
    xdo_t *xdo;

    xdo = xdo_new(NULL);

    xdo_get_mouse_location(xdo, &mx, &my, NULL);
    printf("Current mouse location: x: %d, y: %d\n", mx, my);

    printf("Please select the window of your game.\n");
    xdo_select_window_with_click(xdo, &wid);
    printf("Selected window ID: %lu\n", wid);

    xdo_get_window_location(xdo, wid, &wx, &wy, NULL);
    printf("Window location: x: %d, y: %d\n", wx, wy);

    xdo_move_mouse(xdo, wx, wy, sn);
    printf("Moved mouse to window location\n");

    xdo_free(xdo);

}