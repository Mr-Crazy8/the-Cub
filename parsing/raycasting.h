/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:11:13 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/14 16:15:41 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "parsing.h"

void			raycast(t_mlx_helper *mlx_utils,
					t_utils *utils, t_player *player);
char			find_player(char **map, int *player_place);
void			find_h_w_for_map(char **map, int *map_h_w);
void			draw_map_(t_utils *util, t_mlx_helper *mlx_utils);
void			check_derction_player(t_player *player, char der);
void			clear_img(t_mlx_helper *mlx);
void			handel_key(mlx_key_data_t keydata, void *param);
void			game_loop(void *param);
void			update_animation(t_sprite *anim);
void			animation_loop(void *param);
bool			is_door_blocking(t_mlx_helper *mlx, int x, int y, int type);
int				get_color(t_color_params *params);
void			clear_img_mini_map(t_mlx_helper *mlx);
bool			check_blocking_by_door(t_mlx_helper *mlx,
					int x, int y, float threshold);
bool			is_door_blocking(t_mlx_helper *mlx, int x, int y, int type);
void			update_doors_info(t_mlx_helper *mlx);
void			mini_map(t_mlx_helper *mlx);
int				check_hit(t_mlx_helper *mlx, int *did_we_hit_a_door);
void			draw_player(t_mlx_helper *mlx, t_player_draw_params *params);
mlx_texture_t	**texture_loader(t_mlx_helper *mlx_utils);
void			move_back(t_player *player, char **map, t_mlx_helper *mlx);
void			move_forward(t_player *player, char **map, t_mlx_helper *mlx);
void			mouse_rotate_hook(double xpos, double ypos, void *param);
void			rotate_left(t_player *player, double rot);
void			move_left(t_player *player, char **map, t_mlx_helper *mlx);
void			move_right(t_player *player, char **map, t_mlx_helper *mlx);
void			rotate_right(t_player *player, double rot);
t_mlx_helper	*init_mlx_helper(void);
void			init_mlx_images(t_mlx_helper *mlx_utils);
void			init_mlx_allocations(t_mlx_helper *mlx_utils);
void			setup_minimap_config(t_mlx_helper *mlx_utils);
void			setup_player(t_mlx_helper *mlx_utils,
					t_player *player, char helper);
#endif