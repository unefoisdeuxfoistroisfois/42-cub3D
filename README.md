*This project has been created as part of the 42 curriculum by britela-, sariee.*

## Description

cub3D is a raycasting engine inspired by Wolfenstein 3D, the first FPS in video game
history. The goal is to render a dynamic 3D view of a maze from a first-person 
perspective using ray-casting techniques, based on a scene description file (`.cub`).

## Instructions

### Compilation

```bash
make
```

### Execution

```bash
./cub3D maps/your_map.cub
```

### Map format (.cub)

```
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
WE ./path/to/west_texture.xpm
EA ./path/to/east_texture.xpm

F R,G,B
C R,G,B

1111111
1000N01
1111111
```

- `0` -> empty space
- `1` -> wall
- `N/S/E/W` -> player start position and orientation (only one allowed)
- `F` -> floor color (RGB 0-255)
- `C` -> ceiling color (RGB 0-255)

## Parsing

The parsing reads and validates the `.cub` scene file before launching the engine.

### Validation steps

- [x] File extension must be `.cub`
- [x] Textures `NO`, `SO`, `WE`, `EA` must be present and point to valid `.xpm` files
- [x] Colors `F` and `C` must be present with valid RGB values between 0 and 255
- [x] All 6 elements must be present in the file
- [x] Map must contain only valid characters: `0`, `1`, `N`, `S`, `E`, `W` and spaces
- [x] Map must contain exactly one player start position (`N`, `S`, `E` or `W`)
- [x] Map must be closed/surrounded by walls
- [x] Map must be the last element in the file

## Exec
Sam.

## Resources

### References
- [Medium by Elmehdielgarouaz](https://medium.com/@elmehdielgarouaz/from-flat-to-fantastic-how-cub3ds-ray-casting-engine-transforms-2d-into-3d-647ff2f7fd4f)
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [miniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)

### AI usage
Claude was used to help debug parsing issues, understand code structure and 
organization, and review logic errors. All code was written and understood by 
the authors.