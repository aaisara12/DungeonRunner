# Dungeon Runner

![The Dungeon Runner home screen](/images/dungeon_runner_title.png)

## About

Build a party of heroes to fight through dungeons of enemies in Pokemon-esque turn-based combat! Heroes permanently gain experience and power the more battles they win and persist across play sessions.

This is a personal project I've been working on for the past month as an excuse to learn tools development. While the base game has lots of interesting technical challenges, my main focus is on building a companion desktop app that can be used to design the heroes, enemies, and levels in the game. This app will let designers create custom moves and effects, set character stats, draw ASCII art for the game, and more!

For details on high-level design decisions I've made while making this project, see the [Progression Log](/Progression%20Log.txt).

## How to Play the Game

You can either clone the repo and compile then execute, or you can just download the executable I've provided under Releases.

## Current Progress

![Gul'dan's move selection](/images/dungeon_runner_guldan_move.png)

The actual game looks barely complete, but I promise the core systems are almost finished and will bear fruit soon! The core battle system is pretty much finished, the UI framework is in a decent state, and the game state machine is looking good. One of the last big remaining pieces is a system for injecting game data into the executable to simplify the process of adding content to the game. Also there are still quite a few bugs and unhandled errors mainly due to a lack of input validation. Stay tuned!

Broadly, here are the main items I'd like to address:

1. **Configurable characters and UI through plain text or special script files read by the executable at runtime.** This would make it 100 times faster to tweak the game since I wouldn't need to recompile anything. It would probably also make it a lot easier for the game to communicate with any external game design tools.
2. **More visuals.** In its current state, I have bare-bones UI that can display text. It would be cool to add in some graphics like health bars or rough enemy ASCII art.
3. **Actual levels.** Right now, the game sends you into a single battle. There should probably be more, right?
