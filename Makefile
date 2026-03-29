CC = cc
NAME = cub3D
SRC = src/main.c \
	  src/mlx.c

OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g -I./includes $(MLX_INC)
RM = rm -rf

define LOGO

\033[1;38;5;208m
______________________________/\\\____________/\\\\\\\\\\___/\\\\\\\\\\\\____        
 _____________________________\/\\\__________/\\\///////\\\_\/\\\////////\\\__       
  _____________________________\/\\\_________\///______/\\\__\/\\\______\//\\\_      
   _____/\\\\\\\\__/\\\____/\\\_\/\\\________________/\\\//___\/\\\_______\/\\\_     
    ___/\\\//////__\/\\\___\/\\\_\/\\\\\\\\\_________\////\\\__\/\\\_______\/\\\_    
     __/\\\_________\/\\\___\/\\\_\/\\\////\\\___________\//\\\_\/\\\_______\/\\\_   
      _\//\\\________\/\\\___\/\\\_\/\\\__\/\\\__/\\\______/\\\__\/\\\_______/\\\__  
       __\///\\\\\\\\_\//\\\\\\\\\__\/\\\\\\\\\__\///\\\\\\\\\/___\/\\\\\\\\\\\\/___ 
        ____\////////___\/////////___\/////////_____\/////////_____\////////////_____
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
LIBFT_DIR   = Libft
LIBFT       = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_A)
	@echo "$$LOGO"
	@echo "\033[1;32mLIASON DES OBJETS\033[0m"
	$(CC) $(OBJ) $(CFLAGS) -o $@ $(LIBFT) $(MLX_LINK)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) bonus

# .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
