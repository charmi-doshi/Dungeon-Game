## RPG Dungeon game
A RPG dungeon game built in C++20 and SDL3, combining console-style visuals with a custom font renderer and algorithm-driven dungeon systems.

The project focuses on implementing the core gameplay systems from scratch rather than relying on an existing dungeon-generation or pathfinding framework.
## Core System

- Procedural Dungeon Generation : Generates dungeon layouts using **Binary Space Partitioning (BSP)** to recursively divide the map into rooms and corridors.
- Field of View : Implemented a **raycasting-based FOV system** to determine which parts of the dungeon are visible around the player.
- Enemy Pathfinding : Uses A* pathfinding to allow enemies to navigate the dungeon and move toward the player.
- Grid-Based Movement : Built player and enemy movement around a tile-based dungeon map.
- Custom Rendering : Uses keyboard/ASCII-style characters and a custom bitmap font renderer to display the dungeon and game state.
- Procedural Gameplay : Each dungeon floor is generated dynamically, with progression through staircases increasing the difficulty.


## Gameplay

The player explores procedurally generated dungeon floors, collects items, and fights enemies while navigating through the visible portion of the map.

The > staircase takes the player to the next floor. Each new floor increases the challenge by introducing more enemies and a more difficult dungeon layout.

The FOV system limits the player to the area that can currently be seen, while enemy movement uses A* to navigate through the generated dungeon toward the player.

## Game symbols
The game uses simple characters to represent the world:

| Symbol | Meaning |
|--------|---------|
| `@` | Player |
| `g` | Goblin |
| `r` | Rat |
| `s` | Snake |
| `!` | Potion |
| `/` | Sword |
| `>` | Staircase |

## Gameplay Showcase

The following video demonstrates the dungeon generation, player movement, field of view, enemies, items, and floor progression.



https://github.com/user-attachments/assets/b7580924-b36e-4fef-b69a-98627db02394





