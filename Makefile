NAME = cub3d
NAME_BONUS = cub3d_bonus

FLAGS = #-Wall -Wextra -Werror #-g3 -fsanitize=address

# Mandatory sources
SRC_DIR = mandatory/
SRC = 	animation_system.c                              minimap_func01.c                                parsing_utiles01.c   			\
		animation_system01.c                            parsing.c                                       parsing_utiles02.c	 			\
		door_system.c                                   parsing_floor_and_ceiling_color.c               parsing_utiles03.c   			\
		door_system01.c                                 parsing_floor_and_ceiling_color_helper00.c      player_and_direction.c  		\
		door_system02.c                                 parsing_floor_and_ceiling_color_helper01.c      player_and_direction01.c 		\
		drawing.c                                       parsing_map.c                                   ray_calculation.c				\
		drawing_01.c                                    parsing_map_helper00.c                          ray_calculation01.c				\
		drawing_02.c                                    parsing_map_helper01.c                          raycasting_and_collision.c  	\
		ft_split.c                                      parsing_map_helper02.c                          raycasting_and_collision01.c 	\
		game_loop_and_input.c                           parsing_map_helper03.c                          rotation_and_movement.c 		\
		get_next_line.c                                 parsing_map_helper04.c                          rotation_and_movement01.c 		\
		get_next_line_utils.c                           parsing_texture.c                               texture_and_color.c 			\
		main.c                                          parsing_texture_helper00.c                      texture_and_color01.c 			\
		main_helper.c                                   parsing_texture_helper01.c                      texture_loading.c 				\
		minimap_func.c                                  parsing_utiles.c

# Bonus sources
BONUS_DIR = bonus/
SRC_BONUS = animation_system_bonus.c                            minimap_func01_bonus.c                              parsing_utiles01_bonus.c   			\
			animation_system01_bonus.c                          parsing_bonus.c                                     parsing_utiles02_bonus.c	 		\
			door_system_bonus.c                                 parsing_floor_and_ceiling_color_bonus.c             parsing_utiles03_bonus.c   			\
			door_system01_bonus.c                               parsing_floor_and_ceiling_color_helper00_bonus.c    player_and_direction_bonus.c  		\
			door_system02_bonus.c                               parsing_floor_and_ceiling_color_helper01_bonus.c    player_and_direction01_bonus.c 		\
			drawing_bonus.c                                     parsing_map_bonus_bonus.c                           ray_calculation_bonus.c				\
			drawing_01_bonus.c                                  parsing_map_helper00_bonus.c                        ray_calculation01_bonus.c			\
			drawing_02_bonus.c                                  parsing_map_helper01_bonus.c                        raycasting_and_collision_bonus.c  	\
			ft_split_bonus.c                                    parsing_map_helper02_bonus.c                        raycasting_and_collision01_bonus.c 	\
			game_loop_and_input_bonus.c                         parsing_map_helper03_bonus.c                        rotation_and_movement_bonus.c 		\
			get_next_line_bonus.c                               parsing_map_helper04_bonus.c                        rotation_and_movement01_bonus.c 	\
			get_next_line_utils_bonus.c                         parsing_texture_bonus_bonus.c                       texture_and_color_bonus.c 			\
			main_bonus.c                                        parsing_texture_helper00_bonus.c                    texture_and_color01_bonus.c 		\
			main_helper_bonus.c                                 parsing_texture_helper01_bonus.c                    texture_loading_bonus.c 			\
			minimap_func_bonus.c                                parsing_utiles_bonus.c

OBJ = $(addprefix $(SRC_DIR), $(SRC:.c=.o))
OBJ_BONUS = $(addprefix $(BONUS_DIR), $(SRC_BONUS:.c=.o))

LIB_MLX = libmlx42_mac.a

MLX_FLAG = -L/mnt/homes/$(USER)/.brew/opt/glfw/lib -I/mnt/homes/$(USER)/.brew/opt/glfw/include -lglfw -framework Cocoa -framework OpenGL -framework IOKit

all: ${NAME}

${NAME}: ${OBJ} ${LIB_MLX}
	cc ${FLAGS} ${MLX_FLAG} ${OBJ} ${LIB_MLX} -o $@

bonus: ${NAME_BONUS}

${NAME_BONUS}: ${OBJ_BONUS} ${LIB_MLX}
	cc ${FLAGS} ${MLX_FLAG} ${OBJ_BONUS} ${LIB_MLX} -o $@

$(SRC_DIR)%.o: $(SRC_DIR)%.c $(SRC_DIR)parsing.h
	cc ${FLAGS} -c $< -o $@

$(BONUS_DIR)%.o: $(BONUS_DIR)%.c $(BONUS_DIR)parsing_bonus.h
	cc ${FLAGS} -c $< -o $@

clean:
	rm -rf ${OBJ} ${OBJ_BONUS}

fclean: clean
	rm -rf ${NAME} ${NAME_BONUS}

re: fclean all

.PHONY: all clean fclean re bonus
