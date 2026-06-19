.SILENT:

CC = cc
NAME = cub3D
SRC = src/main.c \
	  src/parsing/mlx.c \
	  src/parsing/events.c \
	  src/parsing/free.c \
	  src/parsing/args.c \
	  src/parsing/texture.c \
	  src/parsing/color.c \
	  src/parsing/maps.c \
	  src/parsing/maps2.c \
	  src/parsing/maps3.c \
	  src/init/init.c \
	  src/init/init_textures.c \
	  src/init/init_colors.c \
	  src/render/render.c \
	  src/render/raycaster.c \
	  src/render/raycaster2.c \
	  src/movement/move.c \
	  src/movement/rotate.c \
	  src/minimap/minimap.c

OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g -I./includes $(MLX_INC)
RM = rm -rf

define LOGO

\033[1;38;5;208m
                   ▄▄▄▄▄    ▄▄▄▄▄▄   
             █▄   ██▀▀▀██  █▀██▀▀██  
             ██   ▀   ▄█▀    ██   ██ 
 ▄███▀ ██ ██ ████▄  ▀▀▀█▄    ██   ██ 
 ██    ██ ██ ██ ██▄    ██  ▄ ██   ██ 
▄▀███▄▄▀██▀█▄████▀▀█████▀  ▀██▀███▀  
\033[0m

endef
export LOGO

# Détection OS
UNAME_S = $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	OS = LINUX
	MLX_DIR = minilibx-linux
	MLX_A = $(MLX_DIR)/libmlx_Linux.a
	MLX_INC = -I$(MLX_DIR)
	MLX_LINK = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
else
	OS = MAC
	MLX_DIR = minilibx_opengl_20191021
	MLX_A = $(MLX_DIR)/libmlx.a
	MLX_INC = -I$(MLX_DIR)
	MLX_LINK = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

# Libft
LIBFT_DIR   = Libsriee
LIBFT       = $(LIBFT_DIR)/libsriee.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_A)
	@printf "$$LOGO\n"
	@$(CC) $(OBJ) $(CFLAGS) -o $@ $(LIBFT) $(MLX_LINK)
	@printf "\033[1;32mCOMPILATION REUSSIE\033[0m\n"
	@printf "\033[1;36mUSAGE : ./$(NAME) maps/votre_map.cub\033[0m\n"

$(MLX_A):
	$(MAKE) -s -C $(MLX_DIR) > /dev/null 2>&1

$(LIBFT):
	$(MAKE) -s -C $(LIBFT_DIR) > /dev/null 2>&1

# .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "\033[1;31mSUPPRESSION DES .O\033[0m\n"
	$(MAKE) -s -C $(LIBFT_DIR) clean > /dev/null 2>&1
	$(MAKE) -s -C $(MLX_DIR) clean > /dev/null 2>&1
	$(RM) $(OBJ)

fclean: clean
	@printf "\033[1;31mSUPPRESSION DU BINAIRE\033[0m\n"
	$(MAKE) -s -C $(LIBFT_DIR) fclean  
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re 
