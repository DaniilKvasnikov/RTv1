NAME = RTv1
COMMAND = gcc
FLAGS = -Wall -Wextra -Werror
SRC_DIR = src/
SRC_FIL = $(shell ls src | grep -E "ft_.+\.c")
SRCS = $(addprefix  $(SRC_DIR), $(SRC_FIL))
OBJ	= $(SRCS:.c=.o)
INCLUDE = -I libft/src -I includes -Iminilibx_macos
MLX = -framework OpenCL -L./minilibx_macos -lmlx -framework OpenGL -framework AppKit
LIB = ./libft/libft.a
FLAGS_LINUX = -I ./includes_linux/ /usr/X11/lib/libmlx.a  -lXext -lX11 -lm -lpthread

all: $(NAME)

$(LIB):
	make -C libft

$(NAME): $(LIB) $(OBJ)
	$(COMMAND) $(FLAGS) -g -o $(NAME) $(INCLUDE) $(OBJ) $(LIB) $(MLX)

linux: $(LIB) $(OBJ)
	$(COMMAND) $(FLAGS) -g -o $(NAME) $(OBJ) $(LIB) $(FLAGS_LINUX)

.c.o:
	$(COMMAND) $(FLAGS) $(INCLUDE) -g -c -o $@ $<

clean:
	make -C libft clean
	/bin/rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re

