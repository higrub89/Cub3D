NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft/include

SRC	= \
	code/main.c \
	code/parse/parse.c \
	code/cleanUp/cleanUp.c \

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