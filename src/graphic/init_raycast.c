/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:31:22 by qumiraud          #+#    #+#             */
/*   Updated: 2025/08/05 11:24:53 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

void	init_player_vector(t_data *data, double valuedir_xyplane_xy[4])
{
		data->player->dir_x = (int)valuedir_xyplane_xy[0];
		data->player->dir_y = (int)valuedir_xyplane_xy[1];
		data->player->plane_x = valuedir_xyplane_xy[2];
		data->player->plane_y = valuedir_xyplane_xy[3];
}
void	init_valuedir_xyplane_xy(double tab[4][4])
{
	tab[0][0] = 0;
	tab[0][1] = 1;
	tab[0][2] = -0.66;
	tab[0][3] = 0;
	tab[1][0] = 0;
	tab[1][1] = -1;
	tab[1][2] = 0.66;
	tab[1][3] = 0;
	tab[2][0] = 1;
	tab[2][1] = 0;
	tab[2][2] = 0;
	tab[2][3] = 0.66;
	tab[3][0] = -1;
	tab[3][1] = 0;
	tab[3][2] = 0;
	tab[3][3] = -0.66;
}
void	dir_player(t_data *data, char c)
{
	double	valuedir_xyplane_xy[4][4];

	init_valuedir_xyplane_xy(valuedir_xyplane_xy);
	if (c == 'S')
		init_player_vector(data, valuedir_xyplane_xy[0]);
	else if ( c == 'N')
		init_player_vector(data, valuedir_xyplane_xy[1]);
	else if ( c == 'E')
		init_player_vector(data, valuedir_xyplane_xy[2]);
	else if (c == 'W')
		init_player_vector(data, valuedir_xyplane_xy[3]);
}

void	find_player_start(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (is_player(data->map[y][x]))
			{
				dir_player(data, data->map[y][x]);
				data->player->pos_x = x + 0.5;
				data->player->pos_y = y + 0.5;
			}
			x++;
		}
		y++;
		x = 0;
	}
}

void	init_time(t_bigben *bigben)
{
	bigben->old_time = 0;
	bigben->time = 0;
}

void	init_texture(t_ray *raycasting)
{
	raycasting->tex_num = 0;
	raycasting->tex_x = 0;
	raycasting->tex_y = 0;
	raycasting->tex_pos = 0;
	raycasting->color = 0;
}

void	init_ray_struct(t_ray *raycasting)
{
	raycasting->x = 0;
	raycasting->y = 0;
	raycasting->map_x = 0;
	raycasting->map_y = 0;
	raycasting->step_x = 0;
	raycasting->step_y = 0;
	raycasting->hit = 0;
	raycasting->side = 0;
	raycasting->line_height = 0;
	raycasting->draw_start = 0;
	raycasting->draw_end = 0;
	raycasting->side_dist_x = 0;
	raycasting->side_dist_y = 0;
	raycasting->delta_dist_x = 0;
	raycasting->delta_dist_y = 0;
	raycasting->perp_wall_dist = 0;
	raycasting->camera_x = 0;
	raycasting->ray_dir_x = 0;
	raycasting->ray_dir_y = 0;
	raycasting->wall_x = 0;
	raycasting->step = 0;
	init_texture(raycasting);
}
