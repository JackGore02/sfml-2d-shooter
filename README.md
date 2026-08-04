# SFML 2D Shooter

A top-down 2D shooter prototype developed collaboratively in C++ with SFML 2.5.1 and TinyXML2. It was built using a custom game framework supplied with the university assignment.

The player can move and sprint through the game world, aim with the mouse, switch between two weapons, fire and reload, perform a melee attack, collect player upgrades, and fight enemies. Directly connected HUD elements display the player's health, score, equipped weapon, and ammunition.

## Project context and my contribution

This was created as a university group-work project by Ash Henry, Brad Beattie, Daniel Devaney, and Jack Gore. The underlying game framework was provided with the assignment and was not created by any member of the group.

My specific role was **Player and Weapons Developer**. My work focused on the player character and weapon systems, together with any implementation that directly overlapped with those areas. This includes player movement and animation states, mouse-facing behaviour, sprinting and melee, weapon aiming and switching, ammunition and reloading, projectile creation and movement, combat collisions, scoring interactions, and integration with related input, HUD, collectible, camera, and game-state systems.

The repository is preserved as a record of the collaborative coursework in its submitted state. Because responsibility for the complete project was shared across the group, unfinished, incomplete, or inconsistent parts outside my area of ownership should not be interpreted as representative of my individual ability or the quality of my independently developed work.

## Features

- Animated player idle, walking, sprinting, and melee states
- Keyboard movement with mouse-controlled aiming
- Blitz and pistol weapon implementations
- Weapon switching, clip ammunition, reserve ammunition, and reloading
- Animated muzzle flashes and direction-aware projectile spawning
- Bullet movement, lifetime management, collision handling, and scoring
- Player health, movement-speed, and score management
- Enemy contact damage and player melee combat interactions
- Integration with health, ammunition, and speed collectibles
- Integration with the player-following camera
- HUD integration for health, score, equipped weapon, and ammunition

## Controls

| Context | Key or input | Action |
| --- | --- | --- |
| Game | <kbd>W</kbd> / <kbd>A</kbd> / <kbd>S</kbd> / <kbd>D</kbd> or arrow keys | Move |
| Game | Mouse movement | Aim |
| Game | Left click | Fire the equipped weapon |
| Game | <kbd>R</kbd> | Reload |
| Game | <kbd>1</kbd> | Switch weapon |
| Game | Hold <kbd>Left Shift</kbd> | Sprint |
| Game | <kbd>V</kbd> | Melee attack |

The <kbd>F2</kbd>–<kbd>F7</kbd> keys are retained debug controls for modifying player health, score, and maximum health.

## Requirements

- Windows 10 or Windows 11
- Visual Studio 2022 with the **Desktop development with C++** workload
- MSVC v143 platform toolset
- Windows 10 SDK

The repository includes the required SFML 2.5.1 headers, libraries, runtime DLLs, and TinyXML2 source under `ThirdParty`, so separate dependency installation is not required for the supplied Visual Studio solution.

## Building and running

1. Open `SFML 2D Shooter.sln` in Visual Studio 2022.
2. Select either **Debug** or **Release** and the **x86** platform.
3. Choose **Build > Build Solution** or press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>.
4. Run without the debugger using <kbd>Ctrl</kbd>+<kbd>F5</kbd>.

You can also build from a Visual Studio Developer Command Prompt:

```powershell
msbuild "SFML 2D Shooter.sln" /p:Configuration=Release /p:Platform=x86
```

Build output is written beneath `build/Win32/<configuration>`. The game loads its media through paths relative to the `SFML 2D Shooter/Assets` directory. The Visual Studio project supplies this working directory, where the bundled x86 SFML runtime DLLs are located; use the same working directory if launching the executable manually.

## Gameplay

- The player starts with five health, a score of 100, and both available weapons.
- Enemy contact removes health after an attack cooldown.
- Shooting or meleeing a destructible target awards 100 points.
- Ammunition pickups add reserve ammunition to the currently equipped weapon.
- Health pickups restore one health up to the player's current maximum.
- Speed pickups permanently increase the player's movement speed for the current run.
- Player health, maximum health, score, and movement speed can be carried between gameplay states.

## Relevant project structure

```text
SFML 2D Shooter/
|-- Source/
|   |-- Engine/
|   |   |-- Input/                            # Shared input abstractions
|   |   |-- Physics/                          # Colliders used by combat objects
|   |   `-- Renderer/
|   |       |-- AnimatedSprite.*              # Player, weapon, and bullet animation
|   |       `-- FrameTimer.*                  # Cooldowns and projectile movement timing
|   `-- Game/
|       |-- GameObjects/
|       |   |-- Player.*                      # Movement, stats, animations, and combat control
|       |   |-- HUD.*                         # Player and weapon information display
|       |   `-- Collectibles/                 # Health, ammunition, and speed integration
|       |-- Input/
|       |   `-- KeyboardAndMouseInputDevice.* # Player and weapon input mappings
|       `-- Weapons/
|           |-- WeaponBase.*                  # Shared ammunition and firing behaviour
|           |-- BlitzWeapon.*                 # Blitz implementation
|           |-- PistolWeapon.*                # Pistol implementation
|           `-- Bullet.*                      # Projectile movement and collision behaviour
`-- Assets/sprites/
    |-- characters/                           # Player animation sprites
    |-- weapons/                              # Weapon sprites and definitions
    |-- bullets/                              # Projectile sprites and definitions
    `-- HUD/                                  # Health and weapon display assets
```

## How it works

`Player` owns the character's health, maximum health, score, movement speed, animation state, and available weapons. Keyboard input controls movement and sprinting, while the mouse position is converted from screen space into the camera-relative world so the player sprite and equipped weapon face the pointer. The player selects between idle, walking, sprinting, and melee animations according to the current input and combat state.

The player's weapons derive from `WeaponBase`, which stores clip ammunition, reserve ammunition, clip size, and firing timing. `BlitzWeapon` and `PistolWeapon` supply their own starting ammunition and sprite animation. Switching weapons hides the previous weapon and makes the selected weapon follow the player's position, facing direction, and aim angle. Reloading transfers as much reserve ammunition as possible into the current clip.

Firing creates a `Bullet` using the weapon's position, rotation, and horizontal orientation. After its initial muzzle-flash frame, the projectile moves forward using frame delta time. It is removed when its lifetime expires or after hitting a destructible target; a successful combat hit also updates the player's score.

The directly connected systems read or update this player-and-weapon state. Enemy contact reduces player health, collectibles restore health or add ammunition or movement speed, the camera follows the player's position, and the HUD displays the current health, score, weapon, and ammunition values.

## Contributors

- Ash Henry
- Brad Beattie
- Daniel Devaney
- Jack Gore — Player and Weapons Developer

## Disclaimer

This project was developed collaboratively as commissioned coursework for university assessment. The source code presented here is published solely for educational and portfolio purposes only. No permission is granted to reproduce, distribute, submit, or adapt it without prior written permission.
