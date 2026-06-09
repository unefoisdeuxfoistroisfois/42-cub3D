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

La variable `double` est un nombre decimal en C comme un `float` mais plus precis. 
Il faut utiliser `double` comme variable car la position, direction, champ de vision ne sont pas des entier et si on utilisait des `int` on perdrait toute la precision et on casserait tout le raycasting. 

Init du player / direction / fov :

Le FOV (Champ de vision) :

Il sera toujours perpendiculaire on aura la direction puis de chaque cote on tend nos bras pour qu'il soit perpendiculaire et que la direction sois bien la separation entre nos deux bras tendus et que l'angle de chaque coter entre dir et plane soit la meme. 

Init couleurs : 

un int couleur MLX est encodé sur 32 bits divisés en 4 octets de 8 bits chacun :
bits :  31-24    23-16    15-8     7-0
        alpha    rouge    vert     bleu
        0x00     0xRR     0xGG     0xBB

Chaque composante occupe exactement 8 bits. Donc :

B est aux bits 0-7 → pas de décalage
G est aux bits 8-15 → décalage de 8
R est aux bits 16-23 → décalage de 16
Alpha bits 24-31 → on ne l'utilise pas, reste à 0

Un pixel sur un ecran c'est 3 composants : Rouge, Vert, Bleu.
La MLX represente une couleur comme un seul entier de 32 bits comme ceci : 
[ 00000000 | RRRRRRRR | GGGGGGGG | BBBBBBBB ]
  8 bits     8 bits     8 bits     8 bits

Le probleme que nous on a c'est qu'on a 3 valeurs separees et il faut qu'on les empiles dans un seul entier. Donc on va decaler :

	- R << 16	pousse R dans les bits 16 à 23 — sa position dans l'entier. 
	- G << 8	pousse G dans les bits 8 à 15. 
	- B			reste en position 0 à 7.

puis on va utiliser le `|` qui est un `OU` en binaire qui permet de combiner les trois sans qu'ils se chevauchent puisqu'ils occupent chacun une zone differente. 

Exemple avec notre maps.cub :
F 220,100,0 :
220 << 16 → 0x00DC0000
100 << 8  → 0x00006400
0         → 0x00000000
résultat  → 0x00DC6400
donc game->floor_color = 0x00DC6400

C 225,30,0 :
225 << 16 → 0x00E10000
30  << 8  → 0x00001E00
0         → 0x00000000
résultat  → 0x00E11E00
donc game->ceiling_color = 0x00E11E00

RENDER : 

dans la fonction ft put pixels, on fait un calcule : game->data.addr + (y * game->data.line_length + x * (game->data.bits_per_pixel / 8)) car addr est un char* est composer de ex : `[(0,0)][(1,0)][(2,0)][(3,0)][(0,1)][(1,1)][(2,1)][(3,1)][(0,2)]` donc cette formule nous permet de pouvoir acceder au pixel que l'on veut pour pouvoir y ajouter ce que l'on veut exactement nous

RAYCASTING : 

Le principe général
Le raycaster simule une vue 3D en travaillant colonne par colonne. L'écran fait WIDTH pixels de large, donc on lance WIDTH rayons — un par colonne verticale.
Pour chaque colonne, on calcule où le rayon touche un mur, on mesure la distance, et on dessine la colonne entière d'un coup : plafond en haut, mur au milieu, sol en bas. Plus le mur est proche, plus la colonne du mur est haute à l'écran. Plus il est loin, plus elle est petite.

La direction du rayon
Le joueur a une direction (dir_x, dir_y) — le vecteur qui pointe droit devant lui. Il a aussi un plan caméra (plane_x, plane_y) — une ligne horizontale imaginaire devant lui qui représente la largeur de son champ de vision.
Pour chaque colonne x, on calcule d'abord sa position normalisée dans l'écran :
camera_x = 2 * x / WIDTH - 1
Ça donne une valeur entre -1 (extrême gauche) et 1 (extrême droite), 0 étant le centre. C'est une convention pour ne pas travailler en pixels bruts.
Ensuite la direction du rayon pour cette colonne :
ray_dir_x = dir_x + plane_x * camera_x
ray_dir_y = dir_y + plane_y * camera_x

Colonne du centre (camera_x = 0) → rayon va exactement droit devant
Colonne à droite (camera_x = 1) → rayon dévie vers la droite
Colonne à gauche (camera_x = -1) → rayon dévie vers la gauche

C'est une interpolation entre les bords du plan caméra selon la position dans l'écran.

## Resources

### References
- [Medium by Elmehdielgarouaz](https://medium.com/@elmehdielgarouaz/from-flat-to-fantastic-how-cub3ds-ray-casting-engine-transforms-2d-into-3d-647ff2f7fd4f)
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [miniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)

### AI usage
Claude was used to help debug parsing issues, understand code structure and 
organization, and review logic errors. All code was written and understood by 
the authors.