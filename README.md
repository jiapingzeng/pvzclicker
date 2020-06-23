# pvzclicker
An autoclicker for Plants vs. Zombies survival endless.

WIP! Does not work yet as I still need to tune some constants.

What is this?
Cob cannon automation. Here is what it looks like:
![](demo.gif)

Note:
This script is written and tested on Ubuntu 20.04 LTS with X11 windowing system. Relies on libxdo so probably will not work on other windowing systems. In addition, it only works with a very specific 8-cannon setup at the moment (read below), though I may expand it in the future.

Setup:
1. Install Origin and Plants vs. Zombies using Wine. You can install it any way you want as long as it works. I used [Lutris](https://lutris.net/) which has scripts that set up Wine environment automatically.
2. Try launching the game, then in settings uncheck "Full screen".
3. Set up the 8-cannon formation by following [this](https://www.youtube.com/playlist?list=PLKW1764DaXcoU66mAx3gZ7A3WMcOMGkq1). Ladders are required to avoid damage from Imp zombies as cannons cannot kill those mid air. Alternatively, I have uploaded my survival endless savefile so feel free to use that too.
4. Install libxdo by running `sudo apt install libxdo-dev`.
5. Build the clicker script and run it: `make && ./pvzclicker`, then select your game window when prompted.
6. Voila!