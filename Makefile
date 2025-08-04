
NAME = cub3D

# Dossiers
PARS = parsing
OBJDIR = obj
LIBFTDIR = libft

# Sources
SRC := src/graphic/main3d.c \
		src/main/main.c\
		src/graphic/raycasting.c\
		src/$(PARS)/get_infile/infile_to_tab.c \
		src/$(PARS)/map_to_rectangle.c \
		src/$(PARS)/utils/free_stuff.c \
		src/$(PARS)/utils/map_utils.c \
		src/$(PARS)/extract_map.c \
		src/$(PARS)/valid_chars.c \
		src/$(PARS)/get_params/extract_params.c \
		src/$(PARS)/check_params/check_colors.c \
		src/$(PARS)/check_params/check_textures.c \
		src/$(PARS)/get_params/params_utils.c \
		src/input/input.c\
		src/main_test.c \

# Objets : transforme chaque .c en obj/chemin/vers/fichier.o
OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

TOTAL := $(words $(SRC))
COUNT = 0

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I$(LIBFTDIR)

LIBFT = $(LIBFTDIR)/libft.a
MLX_FLAGS = -Lmlx -lmlx -Lminilibx-linux -lXext -lX11	#|
MLX_LIB = minilibx-linux/libmlx_Linux.a				#|<----pour activer la mlx

# Couleurs
GREEN =\033[0;32m
RED =\033[0;31m
END =\033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_LIB) -lX11 -lXext -lm -o $(NAME)
	@echo "$(GREEN) Cub3D is ready to play $(END)"

# Compilation des .o avec création auto des dossiers
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@COUNT=$$(expr $$(find $(OBJDIR) -name '*.o' | wc -l) + 1); \
	echo "$(GREEN)[$$COUNT/$(TOTAL)]$(END) Compilation of $<"; \
	$(CC) $(CFLAGS) -c $< -o $@


$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFTDIR)
	@echo "Libft successfully created"

clean:
	@$(MAKE) clean --no-print-directory -C $(LIBFTDIR)
	@rm -rf $(OBJDIR)

fclean: clean
	@$(MAKE) fclean --no-print-directory -C $(LIBFTDIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
