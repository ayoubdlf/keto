# Keto

Keto is a 2d platformer made with [Raylib](https://github.com/raysan5/raylib).


### Prerequisites

Raylib needs these tools and libraries to work

```bash
sudo apt install build-essential git libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev
```

## 👷🏼 Building Keto

Clone the project

```bash
git clone https://gitlab.univ-lorraine.fr/delloufi2u/keto
```

Go to the project directory

```bash
cd keto
```

Use cmake to build files into the `build` folder

```bash
cmake -B build
```

Build the game

```bash
cmake --build build
```

Run it and have fun! 👾

```bash
./build/keto.out
```


## How to play

The goal of this game is to complete all levels.
To complete a level you have to remain and to find the flag,
once you ge to the flag, you will be teleported to the next level.

- Clicking on the screen you will start shooting
- Using the arrow keys, you can go left, right or jump
- Clicking "CTRL+S", your data will be saved to an external file. (or clicking on "save" inside the pause menu)

In the main menu you can:
   - (Play)  Start the game
   - (Load)  Load saved data
   - (Skins) Change the player's skin
   - (Exit)  Exit the game

NOTE: If you load and there is no saved data, you will automatically play a new game



## Authors

- DELLOUFI Ayoub
- KABIDI Safir
