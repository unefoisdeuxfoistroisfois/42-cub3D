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


README ia : 

La variable `double` est un nombre decimal en C comme un `float` mais plus precis.
Il faut utiliser `double` comme variable car la position, direction, champ de vision ne sont pas des entier et si on utilisait des `int` on perdrait toute la precision et on casserait tout le raycasting.

Init du player / direction / fov (init.c) :

Le FOV (Champ de vision) :

Il sera toujours perpendiculaire on aura la direction puis de chaque cote on tend nos bras pour qu'il soit perpendiculaire et que la direction sois bien la separation entre nos deux bras tendus et que l'angle de chaque coter entre dir et plane soit la meme.

Init couleurs (init_colors.c) :

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

RENDER (render.c) :

dans la fonction ft_put_pixel, on fait un calcule : game->data.addr + (y * game->data.line_length + x * (game->data.bits_per_pixel / 8)) car addr est un char* est composer de ex : `[(0,0)][(1,0)][(2,0)][(3,0)][(0,1)][(1,1)][(2,1)][(3,1)][(0,2)]` donc cette formule nous permet de pouvoir acceder au pixel que l'on veut pour pouvoir y ajouter ce que l'on veut exactement nous.

ft_render tourne a chaque frame (via mlx_loop_hook) : il regarde l'etat des flags de touches (game->keys), applique le mouvement ou la rotation correspondante, relance le raycaster pour redessiner l'image avec la nouvelle position/direction du joueur, dessine la minimap par dessus, puis envoie l'image au buffer vers la fenetre.

RAYCASTING (raycaster.c / raycaster2.c) :

Le principe général :
Le raycaster simule une vue 3D en travaillant colonne par colonne. L'écran fait WIDTH pixels de large, donc on lance WIDTH rayons — un par colonne verticale.
Pour chaque colonne, on calcule où le rayon touche un mur, on mesure la distance, et on dessine la colonne entière d'un coup : plafond en haut, mur au milieu, sol en bas. Plus le mur est proche, plus la colonne du mur est haute à l'écran. Plus il est loin, plus elle est petite.

La direction du rayon :
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

Le DDA (recherche du mur) :

Une fois qu'on a la direction du rayon, il faut savoir où il touche un mur. Le DDA (Digital Differential Analysis) fait avancer le rayon case par case dans la grille de la map jusqu'à tomber sur un `1`, sans jamais tester de position en dehors de la grille.

delta_dist_x et delta_dist_y = la distance que parcourt le rayon pour traverser une case entière en x ou en y. Comme le rayon n'est pas forcément aligné avec les axes, on calcule ça avec `fabs(1 / ray_dir_x)` et `fabs(1 / ray_dir_y)`.

side_dist_x / side_dist_y = la distance jusqu'au premier croisement de grille. Le joueur est au milieu d'une case donc ce n'est pas un delta complet au départ, il faut le calculer a part.

step_x / step_y = la direction dans laquelle le rayon avance sur chaque axe (`1` ou `-1`) selon le signe de ray_dir_x/ray_dir_y.

Ensuite dans ft_run_dda, tant qu'on n'a pas touché de mur, on avance sur l'axe qui a le side_dist le plus petit (donc le prochain croisement de grille le plus proche), et on note `side = 0` si on a touché un mur vertical (face EA/WE) ou `side = 1` si horizontal (face NO/SO). C'est ce qui permet de savoir quelle texture utiliser juste après.

Distance perpendiculaire et effet fish-eye :

Si on utilisait la distance en ligne droite entre le joueur et le mur, l'image serait déformée : les murs sur les bords de l'écran paraîtraient plus proches qu'ils ne le sont vraiment (effet "fish-eye"). Il faut donc utiliser la distance perpendiculaire au plan caméra du joueur, pas la distance euclidienne.

perp_wall_dist = side_dist_x - delta_dist_x (ou l'équivalent en y). On soustrait un delta_dist car dans la boucle du DDA on avance déjà d'un pas de trop avant de détecter le mur.

line_height = HEIGHT / perp_wall_dist : plus le mur est proche (distance petite), plus la colonne dessinée est haute à l'écran, et inversement.

Choix et affichage de la texture :

Une fois qu'on sait quelle face a été touchée (side + step_x/step_y), ft_select_texture choisit la bonne texture parmi NO/SO/WE/EA. On calcule ensuite wall_x, la position exacte où le rayon a touché la face du mur (entre 0 et 1), en propageant la position du joueur avec perp_wall_dist * ray_dir. On garde uniquement la partie décimale pour avoir une position relative sur la face du mur, ce qui donne tex_x, la colonne de la texture à afficher.

Pour dessiner la colonne verticale pixel par pixel (ft_draw_wall_pixel), on avance dans la texture avec tex_pos qui progresse de tex_step à chaque pixel. Le point important : tex_pos est initialisé a partir du vrai centre du mur (HEIGHT/2 - line_height/2), et pas depuis draw_start qui lui peut etre "clampé" à 0 si le mur dépasse de l'écran. Sans cette distinction la texture "glisse" quand on est trop près d'un mur.

MOUVEMENT (move.c) :

Chaque touche de déplacement calcule une nouvelle position (new_pos_x, new_pos_y) à partir de la direction du joueur (dir_x, dir_y) multipliée par SPEED :
- W avance dans le sens de la direction du joueur.
- S recule, on soustrait la direction au lieu de l'additionner.
- A et D se déplacent perpendiculairement à la direction sans tourner la caméra, en utilisant la perpendiculaire du vecteur direction : (-dir_y, dir_x) pour la gauche, (dir_y, -dir_x) pour la droite.

Avant d'appliquer le déplacement, on vérifie que la nouvelle position ne tombe pas dans un mur. Comme le joueur a une taille et pas juste un point, on vérifie 8 points autour de la nouvelle position (new_pos +/- MARGIN en x et en y, plus les 4 diagonales) plutôt qu'un seul point : ça évite que le joueur puisse se coller dans un coin de mur en diagonale et rentrer dedans.

ROTATION (rotate.c) :

Tourner la caméra revient à faire tourner les deux vecteurs qui définissent la vue du joueur : dir (direction du regard) et plane (le plan caméra / FOV), avec la même matrice de rotation 2D d'angle rot :
new_x = x * cos(rot) - y * sin(rot)
new_y = x * sin(rot) + y * cos(rot)

On applique cette matrice à dir_x/dir_y puis à plane_x/plane_y, en sauvegardant les valeurs avant rotation dans old_dir_x / old_plane_x (sinon dir_x serait déjà écrasé avant de pouvoir calculer dir_y avec l'ancienne valeur). ft_rotate_player prend l'angle depuis les touches fléchées (ROT_SPEED fixe), et ft_rotate_angle prend un angle variable en paramètre, utilisée par la souris.

CLAVIER ET SOURIS (events.c) :

ft_key_press et ft_key_release ne font que mettre à jour un tableau de flags (game->keys[0] à [5]) à 1 ou 0 : la touche pressée passe le flag à 1, relâchée on le repasse à 0. Le mouvement réel est ensuite appliqué dans ft_render à chaque frame en fonction de l'état de ces flags, ce qui permet de gérer plusieurs touches enfoncées en même temps (ex : avancer + tourner) sans latence.

ft_mouse calcule delta, la distance en pixels entre la position x de la souris et le centre de l'écran (WIDTH / 2). Ce delta est multiplié par MOUSE_SPEED pour le convertir en un petit angle de rotation, passé à ft_rotate_angle. On recentre ensuite la souris avec mlx_mouse_move pour qu'elle ne sorte jamais de la fenêtre, ce qui permet de tourner à l'infini dans un sens comme dans un vrai FPS.

MINIMAP (minimap.c) :

La minimap affiche une zone de MINI_RANGE cases autour du joueur, centrée sur lui, en haut à droite de l'écran. Pour chaque case visible (une double boucle de -MINI_RANGE à MINI_RANGE autour du joueur), on calcule sa position réelle dans la map (map_x/map_y) puis sa position à l'écran (screen_x/screen_y), avant de dessiner un carré de MINI_SIZE pixels avec ft_draw_mini_square.

La couleur dépend du contenu de la case : mur (`1`) en gris clair, case vide en gris foncé, et le joueur (toujours affiché au centre de la minimap, quand j == 0 et i == 0) en rouge par dessus. ft_check_minimap_segfault vérifie les limites (coordonnées négatives, ligne ou colonne hors de la map) avant d'aller lire game->maps.map : sans cette vérification le joueur pourrait faire crash le programme juste en s'approchant du bord de la map.


# readme finale de l'IA :

## Exec

The execution engine is responsible for transforming the parsed `.cub` scene
into a real-time first-person 3D environment.

Once the parsing phase succeeds, the engine initializes the player, loads the
textures, prepares the rendering data and continuously redraws the scene while
handling user inputs.

The rendering process is entirely based on the **raycasting** technique, where
each vertical column of the screen is computed independently.

---

### Player Initialization

The player is initialized by scanning the map until the unique player spawn
(`N`, `S`, `E` or `W`) is found.

The initial position is centered inside the tile by adding `0.5` to both
coordinates. This prevents the player from spawning directly against a wall and
ensures that movement starts from the center of the cell.

Two vectors define the player's view:

- **Direction vector (`dir_x`, `dir_y`)**

  Indicates the direction the player is facing.

- **Camera plane (`plane_x`, `plane_y`)**

  Always perpendicular to the direction vector and defines the field of view
  used during raycasting.

Floating-point (`double`) values are used for positions and vectors in order to
maintain precision during movement, rotations and distance calculations.

---

### Texture Initialization

During initialization, the four wall textures (`NO`, `SO`, `WE`, `EA`) are
loaded from their corresponding `.xpm` files using MiniLibX.

Each texture stores:

- image pointer;
- width and height;
- pixel buffer address;
- bits per pixel;
- line length;
- endian information.

These values allow the renderer to directly access every pixel of the texture
during the rendering phase.

---

### Color Initialization

The floor and ceiling colors are stored in the map as three separate RGB
components.

To make them compatible with MiniLibX, they are packed into a single
32-bit integer using bit shifting.

```
0x00RRGGBB
```

Each component occupies one byte:

```
Red   -> bits 16-23
Green -> bits 8-15
Blue  -> bits 0-7
```

The resulting integer can then be written directly into the image buffer.

---

### Rendering Pipeline

The rendering loop is executed continuously through `mlx_loop_hook`.

Each frame follows the same pipeline:

1. Read the current keyboard state.
2. Update player movement.
3. Update player rotation.
4. Execute the raycasting algorithm.
5. Draw the minimap.
6. Display the final image inside the window.

Instead of drawing directly into the window, every pixel is first written into
an off-screen image buffer.

Once the frame is complete, the entire image is sent to the window using a
single `mlx_put_image_to_window()` call.

This approach eliminates flickering and produces smooth rendering.

---

### Writing Pixels

Every pixel is written manually inside the MiniLibX image buffer.

Its memory address is computed from:

- the pixel coordinates `(x, y)`;
- the image line length;
- the number of bytes per pixel.

This allows direct access to any pixel without using high-level drawing
functions.

---

### Player Movement

Movement is entirely vector-based.

Forward and backward movement use the player's direction vector, while lateral
movement (strafing) uses its perpendicular vector.

Before updating the player's position, collision detection checks every
surrounding tile using a safety margin.

This prevents the player from:

- entering walls;
- clipping through corners;
- getting visually stuck against obstacles.

Only when every surrounding cell is free is the movement applied.

---

### Player Rotation

Player rotation is performed by applying a 2D rotation matrix to both the
direction vector and the camera plane.

```
x' = x cos(θ) - y sin(θ)
y' = x sin(θ) + y cos(θ)
```

Updating both vectors together guarantees that the camera plane always remains
perpendicular to the viewing direction, preserving a correct field of view.

Rotation is triggered either by the keyboard arrows or by horizontal mouse
movement.

---

### Raycasting

The engine renders the world one vertical screen column at a time.

For every column:

1. Compute the ray direction.
2. Initialize DDA variables.
3. Traverse the map.
4. Detect the first wall.
5. Compute the wall distance.
6. Calculate the projected wall height.
7. Select the correct texture.
8. Draw the final column.

This process is repeated once for every column of the screen.

---

### DDA Algorithm

Wall detection is performed using the **Digital Differential Analyzer (DDA)**
algorithm.

Instead of moving pixel by pixel, the ray advances from one map cell to the next.

At every iteration, the algorithm compares:

- the next vertical intersection;
- the next horizontal intersection.

The closest one is selected, and the ray progresses until a wall (`'1'`) is
reached.

This approach provides an efficient grid traversal while avoiding unnecessary
calculations.

---

### Texture Mapping

Once a wall has been hit, the renderer determines which wall face has been
intersected:

- North
- South
- East
- West

The corresponding texture is then selected.

The exact impact position on the wall is converted into a horizontal texture
coordinate (`tex_x`).

Each screen pixel samples its corresponding vertical texture coordinate
(`tex_y`), producing a correctly mapped textured wall.

The texture coordinates are computed using the true wall height, preventing
visible texture sliding when the player approaches walls.

---

### Floor, Ceiling and Walls

Each rendered column is divided into three distinct regions:

- ceiling;
- textured wall;
- floor.

Pixels above the wall are filled with the ceiling color.

Pixels below the wall are filled with the floor color.

Pixels inside the wall region are sampled directly from the selected texture.

---

### Minimap

A minimap is rendered after the 3D scene.

Only a limited area around the player is displayed.

Each visible map cell is converted into screen coordinates and drawn as a small
colored square.

Additional boundary checks prevent any access outside the map, ensuring safe
rendering even near map borders.

---

### Event Handling

Keyboard events are handled through MiniLibX hooks.

Instead of moving the player immediately, key presses update an internal state
array.

The rendering loop continuously checks this state to provide smooth and
responsive movement while allowing multiple keys to be held simultaneously.

Mouse movement is also supported by converting the horizontal cursor
displacement into a rotation angle applied to the player's camera.


---

1. src/parsing/events.c — Inputs
Ce que ça fait : gère clavier + souris via des hooks MLX branchés dans mlx.c:28-30 :


mlx_hook(win, 2, 1L<<0, ft_key_press, game);   // KeyPress
mlx_hook(win, 3, 1L<<1, ft_key_release, game); // KeyRelease
mlx_hook(win, 6, 1L<<6, ft_mouse, game);       // MotionNotify
mlx_hook(win, 17, 0, ft_clean, game);          // fermeture fenêtre (croix)
Les 2, 3, 6, 17 sont les codes d'événements X11, les 1L<<n sont les masques de sélection d'événements associés (obligatoires sous X11/Linux, ignorés côté Mac mais il faut les mettre quand même).

Point clé à savoir dire : je ne déplace pas le joueur directement dans le hook de touche. ft_key_press ne fait que mettre un flag à 1 dans game->keys[6]. Le déplacement réel se fait dans ft_render (appelé à chaque frame par mlx_loop_hook) qui checke ces flags. Pourquoi : si je bougeais le joueur seulement au moment de l'événement KeyPress, le mouvement serait saccadé (un mouvement par pression, pas de mouvement continu tant qu'on maintient), et impossible de combiner plusieurs touches (diagonale W+D par exemple).

Souris : ft_mouse calcule delta = x - WIDTH/2 puis recentre le curseur au milieu de l'écran à chaque appel. Pourquoi recentrer : ça permet une rotation infinie façon FPS — sans ça, la souris sortirait de l'écran et on ne pourrait plus tourner au-delà d'un certain angle.

Mac vs Linux : keycodes différents entre X11 (Linux) et macOS, d'où les macros W/W_MAC etc. Si on te demande pourquoi : le protocole clavier n'est pas le même sur les deux OS, la mlx Linux transmet un keysym X11, la mlx Mac transmet un keycode matériel Apple.

2. src/init/ — Initialisation
init.c : parcourt la map à la recherche de N/S/E/W, place pos_x/pos_y au centre de la case (j + 0.5, i + 0.5) — sinon le joueur serait collé au coin et pourrait spawn "dans" un mur limite. Initialise dir (vecteur unitaire de direction, ex N = (0,-1)) et plane (perpendiculaire à dir, magnitude 0.66).

Question classique : pourquoi 0.66 ? C'est ce qui donne un FOV (champ de vision) d'environ 66°. La formule : FOV = 2 * atan(longueur_plane / longueur_dir). Comme dir est normalisé (longueur 1), 2*atan(0.66) ≈ 66°. Si on voulait un FOV de 90°, il faudrait plane ≈ 1.0.

init_textures.c : charge les 4 XPM avec mlx_xpm_file_to_image, puis récupère l'adresse mémoire brute des pixels avec mlx_get_data_addr. Pourquoi cette 2e étape : l'img renvoyé par mlx est opaque, on n'a pas accès direct aux pixels sans passer par get_data_addr qui donne le pointeur vers le buffer + les infos (bits_per_pixel, line_length, endian) nécessaires pour lire/écrire un pixel à la main.

init_colors.c : convertit floor[3]/ceil[3] (RGB séparés) en un seul entier 0xRRGGBB par décalage de bits (R<<16 | G<<8 | B). C'est le format attendu par ft_put_pixel.

3. src/render/ — Le raycasting (partie la plus scrutée, à maîtriser à fond)
C'est l'algorithme DDA (Digital Differential Analysis), technique classique (tuto Lodev). Déroule mentalement l'ordre d'appel dans raycaster.c:90-107 pour une colonne x :

ft_calc_ray_dir : camera_x = 2*x/WIDTH - 1 normalise la colonne d'écran entre -1 (bord gauche) et 1 (bord droit). ray_dir = dir + plane * camera_x : combine direction du joueur et plan caméra pour obtenir la direction exacte du rayon de cette colonne. Pourquoi cette formule et pas un simple angle : évite de faire un sin/cos par rayon (1200 fois par frame), c'est une simple interpolation linéaire — bien plus performant, et une rotation se fait ensuite par une seule matrice de rotation sur dir/plane (pas besoin de recalculer 1200 angles).

ft_init_dda : calcule delta_dist (distance parcourue par le rayon pour traverser une case complète en x ou en y — dérivé de |1/ray_dir_x|) et side_dist (distance jusqu'au premier croisement de grille, car le joueur est à l'intérieur d'une case donc ce n'est jamais un delta complet). step_x/step_y = direction d'avancée (+1/-1).

ft_run_dda : boucle qui avance case par case, en choisissant toujours le côté (x ou y) dont le side_dist est le plus petit, jusqu'à taper un '1'. side=0 = mur vertical touché, side=1 = mur horizontal touché.

ft_calc_draw_bounds : perp_wall_dist = distance perpendiculaire (pas la distance euclidienne au joueur). C'est LA question qu'on te posera : pourquoi perpendiculaire ? Pour éviter l'effet fisheye — si on utilisait la distance réelle (euclidienne), les murs sur les bords de l'écran (rayons obliques, donc plus longs) paraîtraient plus proches qu'ils ne le sont, ce qui donnerait un mur bombé/déformé façon lentille fisheye. La distance perpendiculaire à la direction du joueur donne une hauteur de mur cohérente sur toute la largeur de l'écran.
line_height = HEIGHT / perp_wall_dist : plus le mur est proche, plus la colonne est haute. draw_start/draw_end centrent ça sur HEIGHT/2, clampés à l'écran.

Texture mapping (ft_select_texture + ft_draw_wall_pixel) :

Choix de texture selon side + step_x/step_y : le rayon touche toujours la face opposée à sa direction de déplacement (si le rayon va vers l'est, il touche la face ouest du mur suivant).
wall_x = position exacte d'impact sur le mur (entre 0 et 1) — on utilise pos_y si mur vertical, pos_x si mur horizontal, puis on ne garde que la partie décimale.
tex_x = wall_x * tex->width = colonne de la texture à afficher.
Le détail piège que tu as bien géré : tex_pos/tex_step sont calculés à partir du vrai line_height (non clampé) et du vrai centre du mur, pas depuis draw_start (qui peut être clampé à 0 si le mur dépasse l'écran). Si tu utilisais draw_start clampé, la texture glisserait verticalement quand tu es collé à un mur (le point de départ dans la texture serait faux). Sais expliquer ce point, c'est un détail fin que peu de candidats maîtrisent.
ft_put_pixel (render.c:15-23) : écrit directement dans le buffer mémoire de l'image via l'adresse retournée par mlx (addr + y*line_length + x*bpp/8), casté en unsigned int* pour écrire les 4 octets du pixel (couleur ARGB/RGB) d'un coup plutôt que 4 fois en char.

ft_render : hook appelé à chaque frame par mlx_loop_hook. Checke les flags de touches, applique mouvement/rotation, relance tout le raycaster + minimap, puis renvoie l'image avec mlx_put_image_to_window. Piège possible : pourquoi tout recalculer à chaque frame plutôt que ne redessiner que ce qui bouge ? Parce que le moindre mouvement du joueur change la perspective de toute l'image (tous les rayons), il n'y a pas de "delta" simple à appliquer.

4. src/movement/ — Déplacement et rotation
move.c : W/S avancent/reculent selon dir (pos += dir*SPEED / pos -= dir*SPEED), A/D sont les perpendiculaires au vecteur direction ((-dir_y, dir_x) pour la gauche, l'inverse pour la droite) — pas de recalcul d'angle, juste de la géométrie vectorielle.
Collision : avant d'appliquer le déplacement, on teste 8 points autour de la nouvelle position (pos ± MARGIN en x et y, plus les 4 coins combinés). Pourquoi 8 et pas juste 2 (x et y séparés) : comme tu l'as noté en commentaire (move.c:127-132), sans les 4 coins on pouvait "couper" un angle extérieur de mur en diagonale et se retrouver dans le mur — les coins ne sont couverts que si on teste aussi les combinaisons (x±MARGIN, y±MARGIN).

rotate.c : rotation par matrice de rotation 2D appliquée à la fois sur dir et plane (les deux doivent tourner ensemble car plane doit rester perpendiculaire à dir en permanence).


new_x = x*cos(rot) - y*sin(rot)
new_y = x*sin(rot) + y*cos(rot)
ft_rotate_player : angle fixe (ROT_SPEED) déclenché par flèches. ft_rotate_angle : même formule mais angle variable, utilisé pour la souris (angle proportionnel au déplacement de la souris).
Piège : pourquoi sauvegarder old_dir_x avant de calculer dir_y ? Parce que dir_x est écrasé par sa nouvelle valeur avant que dir_y en ait besoin dans son propre calcul — sans la sauvegarde, dir_y utiliserait la nouvelle valeur de dir_x au lieu de l'ancienne, ce qui fausserait la rotation.

5. src/minimap/minimap.c
Dessine une grille (MINI_RANGE*2+1)² centrée sur la case du joueur (pas sur la map entière), affichée en haut à droite. Le joueur est toujours au centre visuellement — c'est la minimap qui "suit" le joueur, pas l'inverse (map_x = (int)pos_x + j où j va de -MINI_RANGE à +MINI_RANGE).

Garde-fou anti-segfault dans ft_check_minimap_segfault : comme la map n'est pas forcément rectangulaire (lignes de tailles différentes autorisées tant que le contour est fermé), on vérifie les bornes (map_x/map_y négatifs, hors nombre de lignes, ligne plus courte que map_x) avant d'accéder au tableau, sinon on lit hors-limite. Couleurs : mur 0xAAAAAA, vide 0x333333, joueur toujours écrasé en rouge 0xFF0000 au centre.

Questions pièges génériques à anticiper
"Que se passe-t-il si perp_wall_dist vaut 0 ?" → division par zéro dans line_height. Ne devrait jamais arriver en pratique car le joueur ne peut jamais être exactement sur la case d'un mur grâce à la collision avec MARGIN, mais sois honnête si on te pousse là-dessus : ce n'est pas géré explicitement.
"Différence entre mlx_hook et mlx_loop_hook ?" → mlx_hook réagit à un événement X11 précis (touche, souris, fermeture fenêtre), mlx_loop_hook est appelé en boucle à chaque itération de la boucle d'événements — c'est ta boucle de jeu / rendu.
"Pourquoi stocker dir et plane plutôt qu'un simple angle en degrés/radians ?" → performance (pas de trig par rayon) + la rotation devient une simple multiplication matricielle appliquée une fois par frame sur 4 valeurs, au lieu de recalculer un angle absolu partout.