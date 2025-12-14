# gameTest-Lantern
Branched prototype of a 2D platformer in C++ using SFML 3.
Made to figure out and demonstrate a simple lighting system. 

## About this project
I made this to familarise myself with lighting. It features a multi-layered music track, influenced by the player actions. It also features a player character, based on Toby Fox's Ralsei from Deltarune, that can be controlled by the user via A, D and Space Bar. It explores the concept of radial lighting around a player and an object percieved as important. There are two types of lighting that I have named: Fake Lighting and Real Lighting. Fake Lighting is where an object isn't explicitly glowing to create light as a light source, but rather it makes a circular cut-out in the darkness so that it is still dim but not missable. Real lighting is where an object is explicitly glowing to create light as a light source, where it doesn't cut-out the darkness but rather makes the area from a point brighter. The player, when walking up to the lantern, will ignite it. This will also cause the second layer of the music track to fade in.
Some challenges I faced:
- The Rendering Pipeline. I learnt how a mix of different terminologies can be confusing, so learning what they mean and using a consistent and appropiate term is best. player.render() before is now player.draw(), as render implies it is a rendertarget when it is not.
- Blending Modes. I learnt how different blending mdoes can create different effects with lighting. A "Multiply" Blending Mode is ideal when making cut-outs in the dark, but an "Additive" blending mode is ideal when actually lighting up the dark.
- Music. I learnt how audio buffers work, when to and when to not use them. For music, audio buffers are not needed and music is instead directly streamed from the file. Setting the volume and looping also stepped me back, but I figured the latter and discovered that what I thought was the range -0.f to 1.0f- was actually 0 to 100.

## Features
- A character that has more functionality. It can look up, move around, jump and has health.
- A vertex-array tilemap and basic level system, allowing for environments that are more complex than drawing rectangles.
- A basic gamestate system that loads the Playing State on launch, but can be adapted to load different game states.
- Object-Oriented Programming allowing the use of an "Object" superclass with a "Lantern" and "Entity" subclass, where the latter forms a "Player" subclass.
- A lighting system that can react depending on the environment
- An environment that reacts to player interaction
- Music that plays in the background, that dynamically changes based on what the player has done

## Gallery
https://github.com/user-attachments/assets/7b8db032-19dd-40f1-bece-3631d24ff9ce


## Build & Run
```bash
mkdir build
cd build
cmake ..
cmake --build .
cd bin
./gametest-lantern
```

Requires SFML 3.0.2, C Make and C++17.

## Licence
Copyright © 2025 Jay Rickaby,
Licensed under the MIT License
