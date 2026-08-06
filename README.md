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

Once the parsing is done, I start rendering the game. The first thing I do is initialize the player, load the textures and prepare everything needed to draw the scene.

To render the 3D world, I use the **raycasting** technique. Instead of drawing the whole scene at once, I compute one vertical screen column at a time.

---

## Player Initialization

The first thing I do is scan the map until I find the only player spawn (`N`, `S`, `E` or `W`).

I place the player at the center of the tile by adding `0.5` to both coordinates. Without this offset, the player could start too close to a wall.

Two vectors define the player's view:

```text
                    Camera Plane
        <------------------------------>

                    ^
                    |
                    |
                    P ---------> Direction
                 Player
```

- **Direction vector (`dir_x`, `dir_y`)**  
  This vector shows where the player is looking.

- **Camera plane (`plane_x`, `plane_y`)**  
  This vector is always perpendicular to the direction vector. Together, they define the player's field of view.

I use `double` values for the player's position and vectors because they keep movement, rotations and raycasting calculations precise.

---

## Texture Initialization

Before rendering anything, I load the four wall textures (`NO`, `SO`, `WE`, `EA`) from their `.xpm` files using MiniLibX.

For each texture, I store:

- image pointer;
- width and height;
- pixel buffer address;
- bits per pixel;
- line length;
- endian information.

I keep this information because I need it to read every pixel from the texture while rendering a wall.

---

## Color Initialization

The floor and ceiling colors are stored as three RGB values.

Before using them, I pack them into a single 32-bit integer.

```text
0x00RRGGBB
```

```text
Red   -> bits 16-23
Green -> bits  8-15
Blue  -> bits  0-7
```

This format is the one MiniLibX expects when writing pixels into the image buffer.

---

## Rendering Pipeline

Once everything is initialized, the rendering loop runs continuously through `mlx_loop_hook`.

Each frame always follows the same steps:

```text
Keyboard / Mouse
        │
        ▼
 Update Player
        │
        ▼
 Raycasting
        │
        ▼
 Texture Mapping
        │
        ▼
 Draw Minimap
        │
        ▼
 Display Frame
```

1. Read the current keyboard state.
2. Update the player's movement.
3. Update the player's rotation.
4. Run the raycasting algorithm.
5. Draw the minimap.
6. Display the final frame.

I first draw everything into an off-screen image. Once the frame is finished, I display it with a single `mlx_put_image_to_window()` call. This avoids visible flickering.

---

## Writing Pixels

Instead of using drawing functions, I write every pixel directly into the MLX image buffer.

Its address depends on:

- the pixel coordinates `(x, y)`;
- the image line length;
- the number of bytes per pixel.

This lets me access every pixel directly without relying on higher-level drawing functions.

---

## Player Movement

Movement is entirely vector-based.

```text
             Forward
                ▲
                │
Left ◄──── P ───► Right
                │
                ▼
            Backward
```

To move forward or backward, I use the direction vector.

To strafe left or right, I use its perpendicular vector.

Before applying the new position, I check the surrounding cells with a safety margin. This prevents the player from entering walls or clipping through corners.

---

## Player Rotation

To rotate the camera, I apply a 2D rotation matrix to both the direction vector and the camera plane.

```text
Before                 After

   ↑                     ↗
   │                    /
   P                   P
```

```text
x' = x cos(θ) - y sin(θ)
y' = x sin(θ) + y cos(θ)
```

Rotating both vectors together keeps the camera plane perpendicular to the direction vector and preserves the correct field of view.

Rotation can come from the keyboard or from horizontal mouse movement.

---

## Raycasting

The raycasting algorithm renders one screen column at a time.

For every column, it:

1. computes the ray direction;
2. initializes the DDA variables;
3. traverses the map;
4. finds the first wall;
5. computes the perpendicular distance;
6. calculates the projected wall height;
7. selects the correct texture;
8. draws the final column.

```text
               Camera Plane

 | | | | | | | | | | | | | |

  \  \  \  |  /  /  /  /  /
   \  \  \ | /  /  /  /  /
    \  \  \|/  /  /  /  /
          Player
```

I repeat this process for every screen column, so each ray produces one vertical slice of the final image.

---

## DDA Algorithm

To detect walls, I use the **Digital Differential Analyzer (DDA)** algorithm.

The ray does not move pixel by pixel. Instead, it jumps from one map cell to the next until it reaches a wall.

```text
+---+---+---+---+---+
|   |   |   |   |   |
+---+---+---+---+---+
| P | → | → | X |   |
+---+---+---+---+---+
|   |   |   |   |   |
+---+---+---+---+---+

P = Player
X = First wall hit
```

At each step, the algorithm compares the next vertical and horizontal intersection and keeps the closest one.

---

## Texture Mapping

Once a wall has been hit, the renderer knows which face has been intersected (North, South, East or West) and selects the corresponding texture.

```text
 Wall

+------------------+
|        ●         |
|                  |
+------------------+
         │
         ▼
      tex_x
```

The impact position gives the horizontal coordinate `tex_x`.

Then I compute `tex_y` for every pixel of the wall before drawing it. Doing this prevents the texture from sliding when the player gets close to a wall.

---

## Floor, Ceiling and Walls

Each rendered column is split into three parts.

```text
┌───────────────┐
│    Ceiling    │
├───────────────┤
│ Textured Wall │
├───────────────┤
│     Floor     │
└───────────────┘
```

Pixels above the wall use the ceiling color.

Pixels below use the floor color.

Pixels inside the wall are read directly from the selected texture.

---

## Minimap

After rendering the 3D scene, I draw the minimap.

```text
■■■■■■■■■
■□□□□□□□■
■□□□P□□□■
■□□□□□□□■
■■■■■■■■■

■ Wall
□ Empty space
P Player
```

I only display a small area around the player. Before drawing each cell, I also check that I'm still inside the map.

---

## Event Handling

Keyboard events are handled through MiniLibX hooks.

Instead of moving the player immediately, I simply update an internal key state array.

The rendering loop reads this array every frame, making movement smooth while allowing multiple keys to be pressed at the same time.

Horizontal mouse movement is converted into a rotation angle and applied to the camera.

## Resources

### References

- [Medium by Elmehdielgarouaz](https://medium.com/@elmehdielgarouaz/from-flat-to-fantastic-how-cub3ds-ray-casting-engine-transforms-2d-into-3d-647ff2f7fd4f)
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [miniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)

### AI usage

Claude was used to help debug parsing issues, understand code structure and organization, and review logic errors. All code was written and understood by the authors.