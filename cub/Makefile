NAME = cub3D
CC = cc

# --- CONFIGURACIÓN DE RUTAS ---
# Le decimos a GCC que busque headers en TU include y en libft
CFLAGS = -Wall -Wextra -Werror -g -pthread
CFLAGS += -Iengine_graphics/include 
CFLAGS += -Ilibft/include
CFLAGS += -Iminilibx-linux/include
# Añadimos la librería de Mates (la necesitarás)
LDFLAGS	= -Llibft -lft -lm
LDFLAGS += -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm
# --- ARCHIVOS DE TU MÓDULO (ENGINE) ---
# Compilamos tu main, tu mock, y el cleanUp de Álex
SRC	= \
	engine_graphics/src/engine/engine_main.c \
	engine_graphics/src/mocking/mock_init.c \
	engine_graphics/src/engine/engine_init.c \
	engine_graphics/src/engine/engine_hooks.c \
	code/cleanUp/cleanUp.c \

# --- ARCHIVOS DE ÁLEX (Ignorados por ahora) ---
# SRC_ALEX = \
# 	code/main.c \
# 	code/parse/parse.c \
# 	code/cleanUp/cleanUp.c \


OBJ	= $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "Enlazando cub3D (Motor de Rubén)..."
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

$(LIBFT):
	@$(MAKE) -C libft

# Regla genérica para compilar C en O
# (Esta regla no funcionaba bien en tu Makefile anterior)
%.o: %.c
	@echo "Compilando: $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C libft clean
	@rm -f $(OBJ)
	@echo "Borrando archivos objeto..."

fclean: clean
	@$(MAKE) -C libft fclean
	@rm -f $(NAME)
	@echo "Borrando ejecutable $(NAME)..."

re: fclean all
	@echo "Recompilación completada."

run: $(NAME)
	./$(NAME) maps/mapSubject.cub

.PHONY: all clean fclean re run