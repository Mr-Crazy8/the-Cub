/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:59:04 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/08 20:35:02 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "get_next_line.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"
# include "../.MLX42.h"
#include <stdlib.h>
#include <unistd.h>

# define FIRE_FRAMES 8
# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 800
# define PI 3.14
# define MAX_LINE_HEIGHT 10000

typedef struct s_texture_coord
{
	int	tx;
	int	ty;
}	t_texture_coord;

typedef struct s_texture_coords_params
{
	mlx_texture_t	*tex;
	double			wx;
	int				y;
	int				draw_start;
	int				line_height;
}	t_texture_coords_params;

typedef struct s_color_params
{
	mlx_texture_t	**texture;
	int				side;
	double			raydir_y;
	double			raydir_x;
	int				x;
	int				y;
	double			dist_to_wall;
	double			pos_x;
	double			pos_y;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				did_we_hit_a_door;
}	t_color_params;

typedef struct s_wall_x_params
{
	int		side;
	double	pos_x;
	double	pos_y;
	double	dist_to_wall;
	double	raydir_x;
	double	raydir_y;
}	t_wall_x_params;

typedef struct s_minimap_bounds
{
	int	min_x;
	int	max_x;
	int	min_y;
	int	max_y;
}	t_minimap_bounds;

typedef struct s_minimap_pixel_params
{
	int	map_x;
	int	map_y;
	int	min_x;
	int	min_y;
	int	px;
	int	py;
}	t_minimap_pixel_params;

typedef struct s_minimap_tile_params
{
	int	map_x;
	int	map_y;
	int	min_x;
	int	min_y;
}	t_minimap_tile_params;

typedef struct s_player_draw_params
{
	int	player_x;
	int	player_y;
	int	min_x;
	int	min_y;
}	t_player_draw_params;

typedef struct s_wall_params
{
	int	x;
	int	side;
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	real_draw_start;
	int	real_draw_end;
	int	did_we_hit_a_door;
}	t_wall_params;

typedef struct s_line_params
{
	int	x;
	int	side;
	int	did_we_hit_a_door;
}	t_line_params;

typedef struct s_wall_data
{
	int	x;
	int	side;
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	real_draw_start;
	int	real_draw_end;
	int	did_we_hit_a_door;
}	t_wall_data;

typedef struct doors
{
	int		map_x;
	int		map_y;
	int		state; //0 == closed; 1 == openning; 2 == fully open;
	float	animation_progress;
	float	activation_distance;
}	t_doors_info;

typedef struct s_texture_flags
{
	int	done_no;
	int	done_so;
	int	done_we;
	int	done_ea;
}	t_texture_flags;

typedef struct s_sprite
{
	xpm_t		*frames[FIRE_FRAMES];// mlx image pointers
	mlx_image_t	*images[FIRE_FRAMES];// actual mlx images to draw
	int			current_frame;// index of current frame
	int			frame_delay;// how many loops before switching
	int			frame_counter;// counts frames
	double		last_frame_time;
}	t_sprite;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	int		mapx;//mapX
	int		mapy;//mapY
	double	dir_x;
	double	dir_y;
	double	deltax; //deltaX
	double	deltay; // deltaY
	double	raydir_x;
	double	raydir_y;
	double	move_speed;
	double	plane_x;
	double	fov_angle;
	double	rotation_angle;
	double	plane_y;
	double	camera_x;
	int		side_flag;
}	t_player;

typedef struct s_utils
{
	int				is_hit;
	int				tile;
	int				*c_color;
	int				*f_color;
	char			**map;
	char			**file;
	char			*no_path;
	char			*so_path;
	char			*ea_path;
	char			*we_path;
	int				total_doors;
	t_doors_info	*doors;
}	t_utils;

typedef struct s_mlx_helper
{
	t_sprite		*sprit;
	t_utils			*utils;
	t_player		*player;
	mlx_texture_t	**texture;
	double			dist_to_wall;
	int				stepx; //stepX
	int				stepy; //stepy
	double			dist_rayx; //dist_rayX
	double			dist_rayy; //dist_rayy
	void			*mlx_ptr;
	void			*win;
	mlx_image_t		*img;
	mlx_image_t		*mlx_img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				tile;
	int				*player_place;
	int				*map_h_w;
	int				doors_count;
	t_doors_info	*doors;
	mlx_image_t		*mini_map_img;
	int				minimap_size;
	int				minimap_x;
	int				minimap_y;
	int				minimap_zone;
	float			minimap_scale;
}	t_mlx_helper;

void				free_string_array(char **array);
void				init_sprite_arrays(t_sprite *sprit);
void				clean_up_utils(t_utils *util);
void				cleanup_textures(t_mlx_helper *mlx);
void				free_string_array(char **array);
void				print_error(int fd);
void				check_if_it_texture(char *line);
void				check_floor_and_ceiling_color(char *line);
void				check_line(char *line);
void				read_map(int fd);
void				check_if_in_range(int color, t_utils *util);
void				extract_and_pars_the_floor_and_ceiling_color(t_utils *util,
						char **file);
void				free_normalized(char **normalized, int i);
void				extract_and_pars_the_map(t_utils *util, char **file);
void				check_for_valid_character_in_map(char str, t_utils *util);
void				check_first_line(char **str, t_utils *util);
void				check_the_last_line(char **str, t_utils *util);
void				pars_the_map_helper(t_utils *util);
void				pars_the_map(t_utils *util);
void				extract_and_pars_the_texture(t_utils *util, char **file);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				clear_img(t_mlx_helper *mlx);
void				free_string_array(char **array);
void				free_partial_map(char **map, int lines_allocated);
void				handle_strdup_error(char **map, int map_line);
void				copy_map_line(char **map, char *source,
						int map_line, t_utils *util);
void				validate_map_start(long long map_start, t_utils *util);
void				extract_and_pars_the_map(t_utils *util, char **file);
void				skip_leading_whitespace(char *line, int *j);
void				validate_map_boundaries(char *line, int j, int last_char);
void				pars_the_map_helper(t_utils *util);
void				init_texture_flags(t_texture_flags *flags);
void				check_duplicate(char *id, int done,
						char **texture, t_utils *util);
void				cleanup_failed_animation(t_mlx_helper *mlx,
						t_sprite *sprit, int img_count);
void				handle_no_texture(t_utils *util,
						char **texture, t_texture_flags *flags);
void				handle_so_texture(t_utils *util,
						char **texture, t_texture_flags *flags);
void				handle_ea_texture(t_utils *util,
						char **texture, t_texture_flags *flags);
void				handle_we_texture(t_utils *util,
						char **texture, t_texture_flags *flags);
void				validate_comma_count(int counter, t_utils *util);
void				set_color_values(int *color, char **split1, t_utils *util);
void				assign_color_to_util(t_utils *util,
						char type, char **split1);
void				draw_wall_slice(t_mlx_helper *mlx_utils, t_player *player,
						t_wall_params *params);
void				draw_floor(t_mlx_helper *mlx_utils, int x, int drawEnd);
void				draw_ceiling(t_mlx_helper *mlx_utils, int x, int drawStart);
void				draw_vertical_line(t_mlx_helper *mlx_utils,
						t_player *player, t_line_params *params);
void				draw_pixel_if_in_bounds(t_mlx_helper *mlx_utils,
						int screen_x, int screen_y, int color);
void				calculate_draw_bounds(int *drawStart,
						int *drawEnd, int lineHeight);
void				clear_img(t_mlx_helper *mlx);
void				draw_player(t_mlx_helper *mlx,
						t_player_draw_params *params);
void				draw_map_(t_utils *util, t_mlx_helper *mlx_utils);
void				draw_map_row(t_utils *util,
						t_mlx_helper *mlx_utils, int map_y);
void				draw_tile_pixels(t_mlx_helper *mlx_utils,
						int map_x, int map_y, int color);
void				clear_img_mini_map(t_mlx_helper *mlx);
void				draw_minimap_pixel(t_mlx_helper *mlx,
						t_minimap_pixel_params *params);
void				draw_minimap_tile(t_mlx_helper *mlx,
						t_minimap_tile_params *params);
void				move_right(t_player *player, char **map, t_mlx_helper *mlx);
void				rotate_right(t_player *player, double rot);
void				rotate_left(t_player *player, double rot);
void				move_forward(t_player *player,
						char **map, t_mlx_helper *mlx);
void				move_back(t_player *player,
						char **map, t_mlx_helper *mlx);
void				move_left(t_player *player,
						char **map, t_mlx_helper *mlx);
void				calculate_texture_coords(t_texture_coords_params *params,
						t_texture_coord *coord);
void				clean_mlx_helper(t_mlx_helper *mlx_utils);
void				handle_texture_error(char *message);
void				update_animation(t_sprite *anim);
void				setup_player(t_mlx_helper *mlx_utils,
						t_player *player, char helper);
void				delete_previous_frame(t_mlx_helper *mlx, int last_drawn);
void				ensure_current_frame_exists(t_mlx_helper *mlx);
void				calculate_sprite_position(t_mlx_helper *mlx,
						int *x, int *y);
void				draw_current_frame(t_mlx_helper *mlx, int x, int y);
void				animation_loop(void *param);
void				cleanup_sprite(t_mlx_helper *mlx);
void				raycast(t_mlx_helper *mlx_utils,
						t_utils *utils, t_player *player);
void				find_h_w_for_map(char **map, int *map_h_w);
void				check_derction_player(t_player *player, char der);
void				step_ray_x(t_mlx_helper *mlx, int *side);
void				step_ray_y(t_mlx_helper *mlx, int *side);
void				advance_ray(t_mlx_helper *mlx, int *side);
void				free_string_array(char **array);
void				process_single_ray(t_mlx_helper *mlx_utils,
						t_player *player, int x);
void				clean_mlx_helper(t_mlx_helper *mlx);
void				init_ray_direction(t_player *player, int x);
void				calculate_delta_dist(t_player *player);
void				init_step_and_dist_x(t_mlx_helper *mlx_utils,
						t_player *player);
void				init_step_and_dist_y(t_mlx_helper *mlx_utils,
						t_player *player);
void				calculate_wall_distance(t_mlx_helper *mlx_utils,
						t_player *player, int side);
void				calculate_door_position(t_mlx_helper *mlx,
						int i, float *door_x, float *door_y);
void				reset_door_if_far(t_mlx_helper *mlx, int i, float distance);
void				set_direction_north(t_player *player);
void				set_direction_east(t_player *player);
void				set_direction_south(t_player *player);
void				set_direction_west(t_player *player);
void				calculate_ray_direction(t_player *player, int screen_column,
						float *ray_dir_x, float *ray_dir_y);
void				init_door_info(t_doors_info *door, int x, int y);
void				populate_doors_array(char **map, t_doors_info *doors);
int					check_file(char *str);
int					print_failed(void);
int					cleanup_sprite_frames(t_sprite *sprit,
						int count);
int					count_lines(char *str);
int					load_sprite_frames(t_sprite *sprit);
int					f_c_color_helpr(t_utils *util, char *file);
int					ft_atoi(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					lent(char **str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isdigit(int c);
int					check_hit(t_mlx_helper *mlx, int *did_we_hit_a_door);
int					lent(char **str);
int					count_rows(char **map);
int					get_tile_color(char tile_type);
int					trim_trailing_whitespace(char *line, int len);
int					is_player_char(char c);
int					check_boundaries_exist(t_utils *util,
						unsigned long i, unsigned long j);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					is_texture_line(char *line);
int					is_valid_color_prefix(char c);
int					skip_whitespace(char *str);
int					count_commas(char *file);
int					f_c_color_helpr(t_utils *util, char *file);
int					get_minimap_tile_color(char tile);
int					get_tile_color(char tile_type);
int					get_minimap_tile_color(char tile);
int					clean_textures_in_case_error(mlx_texture_t **texture,
						int i);
int					get_texture_index_vertical(int did_we_hit_a_door,
						double raydir_y);
int					get_texture_index_horizontal(int did_we_hit_a_door,
						double raydir_x);
int					get_texture_index(int side, int did_we_hit_a_door,
						double raydir_y, double raydir_x);
int					get_color(t_color_params *params);
int					count_map_lines(char **file, long long map_start);
int					max_len_finder(char **map);
int					check_collision_at(char **map,
						double x, double y, t_mlx_helper *mlx);
int					load_wall_textures(mlx_texture_t **texture, t_utils *utils);
int					check_collision_at(char **map, double x,
						double y, t_mlx_helper *mlx);
int					load_door_texture(mlx_texture_t **texture);
int					validate_animation_params(t_mlx_helper *mlx);
int					check_wall_hit(t_mlx_helper *mlx);
int					check_door_hit(t_mlx_helper *mlx, int *did_we_hit_a_door);
int					count_lines(char *str);
int					count_doors_in_row(char *row);
int					count_total_doors(char **map);
int					fill_doors_in_row(char *row, int row_y,
						t_doors_info *doors, int start_index);
char				*ft_strnstr(const char *big,
						const char *little, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				*add_spaces(char *row, int target_len);
char				**read_file(int fd, char *str);
char				**ft_split(char const *s, char c);
char				**allocate_map_array(int total_lines);
char				**extract_map_lines(char **file,
						long long map_start, int total_lines, t_utils *util);
char				**parse_texture_line(char *line);
char				**parse_and_validate_split(char *file, t_utils *util);
char				**parse_color_components(char **split, t_utils *util);
char				**free_split(char **split, size_t j);
char				**fix_row_size(char **map);
char				**read_file(int fd, char *str);
long long			start_of_map(char **file);
bool				is_door_blocking(t_mlx_helper *mlx, int x, int y, int type);
bool				check_blocking_by_door(t_mlx_helper *mlx,
						int x, int y, float threshold);
bool				is_door_blocking(t_mlx_helper *mlx, int x, int y, int type);
double				calculate_wall_x(t_wall_x_params *params);
float				calculate_distance_to_door(t_mlx_helper *mlx,
						float door_x, float door_y);
char				find_player(char **map, int *player_place);
mlx_texture_t		*load_texture_with_check(char *path, char *error_msg);
mlx_texture_t		**allocate_texture_array(void);
uint32_t			get_pixel_color(mlx_texture_t *texture, int x, int y);
mlx_texture_t		**texture_loader(t_mlx_helper *mlx_utils);
uint32_t			convert_rgba_to_int(uint8_t r,
						uint8_t g, uint8_t b, uint8_t a);
t_utils				*parser(char *str);
t_utils				*init_utils(void);
t_doors_info		*allocate_doors_array(int count);
t_doors_info		*extract_doors_info(t_utils *util);
#endif