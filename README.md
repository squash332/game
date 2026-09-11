# Game

A 2D top-down action RPG built from scratch in C++ with [raylib](https://www.raylib.com/), inspired by the feel of games like *Heroes of Hammerwatch* and WoW-style targeting/UI. Built as a learning project with an emphasis on understanding engine-level systems rather than relying on a full game engine.

## Features

- **Tile-based dungeon rendering** — loads maps authored in [Tiled](https://www.mapeditor.org/), parsed via `cute_tiled`, with multi-tileset GID resolution and infinite-map chunk support.
- **Smooth 2D camera** — player-following camera with framerate-independent lerp and pixel-perfect snapping to avoid shimmer on low-resolution pixel art.
- **Delta-time movement** — 8-directional movement with correct diagonal normalization and axis-separated collision (slide along walls instead of stopping dead).
- **Animation system** — per-state sprite animations (idle / walk, with attack support) driven by an `AnimationState` enum and per-animation frame data.
- **Entity system** — shared `Entity` base class with `Player` and `Enemy` subclasses, holding position, health, allegiance, and hitbox/melee-range data.
- **Targeting** — click-to-target enemies (or self), tab-target-style selection, with target and focus frames.
- **Combat** — melee range checks via circle collision, ability casting with per-ability damage, allegiance/range validation.
- **WoW-style HUD** — draggable, resizable player/target frames, action bar with ability icons, editable via an in-game Edit Mode.
- **Edit Mode** — reposition and resize HUD elements at runtime, with Save/Discard, persisted to `settings.json`.
- **Settings persistence** — HUD layout and (planned) keybinds saved to and loaded from JSON via [nlohmann/json](https://github.com/nlohmann/json).

## Tech Stack

- **Language:** C++17
- **Rendering / windowing / input:** raylib 5.5
- **Map parsing:** cute_tiled (single-header)
- **JSON:** nlohmann/json
- **Build:** CMake + Ninja, dependencies fetched via `FetchContent`

## Project Structure

```
game/
├── source/            # main.cpp, Game.cpp (top-level orchestration)
├── include/           # shared headers (Game, Constants, Entity, etc.)
├── components/        # gameplay systems
│   ├── entity/        # Entity, Player, Enemy
│   ├── input/         # InputManager (keybinding abstraction)
│   ├── map/           # Map loading & tile rendering
│   └── camera/        # Cam2d
├── ui/                # presentation & interaction
│   ├── HUD            # player/target frames, edit mode
│   ├── ActionBar      # ability slots
│   ├── Renderer       # sprite/map/entity drawing
│   └── Window         # window & render-texture management
├── utils/             # standalone, low-dependency utilities
│   ├── Collision      # AABB & circle collision helpers
│   ├── Settings       # JSON save/load
│   ├── Ability        # Ability & Keybind structs
│   └── Mouse          # virtual-resolution mouse position
└── res/               # sprites, tilesets, maps, settings.json
```

The architecture separates concerns into three layers: **components** (gameplay logic), **ui** (presentation and interaction), and **utils** (shared, dependency-light utilities used across systems). `Game` acts as the central orchestrator, owning all top-level systems and coordinating anything that spans multiple of them (targeting, combat resolution, edit mode).

## Building

Requires CMake (≥ 3.14), a C++17 compiler, and Ninja. Dependencies (raylib, nlohmann/json, cute_tiled) are fetched automatically by CMake.

```bash
cmake -S . -B build -G Ninja
cmake --build build
./build/game
```

A `Makefile` is also provided for convenience:

```bash
make build   # configure + build
make run     # build + run
make clean    # remove build directory
```

## Controls

| Input | Action |
|-------|--------|
| `W` `A` `S` `D` | Move |
| Left click | Target enemy / self |
| `1` (and per-ability keybinds) | Cast ability |
| `Escape` | Open settings menu / Edit Mode |
| `T` | Toggle debug overlay |
| `F10` | Toggle fullscreen |
| Mouse wheel | Zoom (integer steps) |

## Roadmap

- [ ] Enemy AI (patrol, aggro, attack)
- [ ] Full ability system (cooldowns, VFX, ranged/projectile abilities)
- [ ] Multiple classes (Warrior, Mage, Paladin) with distinct ability sets
- [ ] Data-driven abilities (JSON) once ability count grows
- [ ] Game states (main menu, town/headquarters, dungeon)
- [ ] Keybind remapping UI
- [ ] Audio & graphics settings
- [ ] Multiplayer (host-authoritative, small-group dungeon instances)

## Notes

This is a learning-focused project — many engine-level systems (tilemap loading, animation state machines, collision, camera, UI) are implemented by hand rather than delegated to an engine, to build a deep understanding of how these systems actually work.
