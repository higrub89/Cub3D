NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft/include

# --- SRC PARA EL MOTOR ---
SRC	= \
	engine_graphics/src/engine/engine_main.c \
	engine_graphics/src/mocking/mock_init.c \
	code/cleanUp/cleanUp.c \
	code/parse/parse.c \ 

# --- SRC ORIGINAL ÁLEX---
# SRC	= \
# 	code/main.c \
# 	code/parse/parse.c \
# 	code/cleanUp/cleanUp.c \

OBJ	= $(SRC:.c=.o)

LIBFT = libft/libft.a
LDFLAGS	= -Llibft -lft

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C libft

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

# Ejecutar con un mapa de ejemplo
run: $(NAME)
	./$(NAME) maps/mapSubject.cub

.PHONY: all clean fclean re run