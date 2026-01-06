
NAME = cub3d

FLAGS = -Wall #-g3 -fsanitize=address#-Werror -Wextra

SRC = 	parsing/animation_system.c                              parsing/minimap_func01.c                                parsing/parsing_utiles01.c   			\
		parsing/animation_system01.c                            parsing/parsing.c                                       parsing/parsing_utiles02.c	 			\
		parsing/door_system.c                                   parsing/parsing_floor_and_ceiling_color.c               parsing/parsing_utiles03.c   			\
		parsing/door_system01.c                                 parsing/parsing_floor_and_ceiling_color_helper00.c      parsing/player_and_direction.c  		\
		parsing/door_system02.c                                 parsing/parsing_floor_and_ceiling_color_helper01.c      parsing/player_and_direction01.c 		\
		parsing/drawing.c                                       parsing/parsing_map.c                                   parsing/ray_calculation.c				\
		parsing/drawing_01.c                                    parsing/parsing_map_helper00.c                          parsing/ray_calculation01.c				\
		parsing/drawing_02.c                                    parsing/parsing_map_helper01.c                          parsing/raycasting_and_collision.c  	\
		parsing/ft_split.c                                      parsing/parsing_map_helper02.c                          parsing/raycasting_and_collision01.c 	\
		parsing/game_loop_and_input.c                           parsing/parsing_map_helper03.c                          parsing/rotation_and_movement.c 		\
		parsing/get_next_line.c                                 parsing/parsing_map_helper04.c                          parsing/rotation_and_movement01.c 		\
		parsing/get_next_line_utils.c                           parsing/parsing_texture.c                               parsing/texture_and_color.c 			\
		parsing/main.c                                          parsing/parsing_texture_helper00.c                      parsing/texture_and_color01.c 			\
		parsing/main_helper.c                                   parsing/parsing_texture_helper01.c                      parsing/texture_loading.c 				\
		parsing/minimap_func.c                                  parsing/parsing_utiles.c

OBJ = $(SRC:.c=.o)

LIB_MLX = parsing/libmlx42_mac.a

MLX_FLAG = -L/mnt/homes/$(USER)/.brew/opt/glfw/lib -I/mnt/homes/$(USER)/.brew/opt/glfw/include -lglfw -framework Cocoa -framework OpenGL -framework IOKit

all: ${NAME}

${NAME}: ${OBJ} ${LIB_MLX}
	cc ${FLAGS}  ${MLX_FLAG}  ${OBJ} ${LIB_MLX} -o $@

%.o: %.c parsing.h
	cc ${FLAGS}  -c $< -o $@

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}

re: fclean ${NAME}









# NAME := cub3d
# CC := cc
# CFLAGS := -fsanitize=address -g
# LDFLAGS := -fsanitize=address  # ← ADD THIS

# # Where MLX42 headers are installed
# INCS := -I. -I/usr/local/include/MLX42

# SRC := parsing/ft_split.c parsing/get_next_line.c parsing/get_next_line_utils.c \
#        parsing/parsing.c parsing/parsing_floor_and_ceiling_color.c \
#        parsing/parsing_map.c parsing/parsing_texture.c parsing/parsing_utiles.c
# OBJ := $(SRC:.c=.o)

# # MLX42 library path
# LIB_MLX := /usr/local/lib/libmlx42.a

# # Linux link libs (GLFW static needs X11 libs + BSD for strnstr)
# LIBS := $(LIB_MLX) -L/usr/local/lib -lglfw3 -lGL -ldl -lpthread -lm \
#         -lX11 -lXrandr -lXinerama -lXcursor -lXi -lXxf86vm -lbsd

# all: $(NAME)

# $(NAME): $(OBJ)
# 	$(CC) $(LDFLAGS) $(OBJ) $(LIBS) -o $@  # ← ADD $(LDFLAGS) HERE

# %.o: %.c parsing.h  # ← Changed from cub3d.h to parsing.h (check your header name)
# 	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# clean:
# 	rm -f $(OBJ)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: all clean fclean re