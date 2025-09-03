/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:47:31 by pjurdana          #+#    #+#             */
/*   Updated: 2025/09/03 13:49:28 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

void	perp_wall_dist_definition(t_data *data)
{
	if (data->ray->side == 0)
		data->ray->perp_wall_dist = (data->ray->side_dist_x
				- data->ray->delta_dist_x);
	else
		data->ray->perp_wall_dist = (data->ray->side_dist_y
				- data->ray->delta_dist_y);
}

void	put_texture_on_walls(t_data *data)
{
	data->ray->y = data->ray->draw_start;
	while (data->ray->y < data->ray->draw_end)
	{
		data->ray->tex_y = (int)data->ray->tex_pos & (TEXHEIGHT - 1);
		data->ray->tex_pos += data->ray->step;
		data->ray->color = data->texture[data->ray->tex_num][TEXHEIGHT
			* data->ray->tex_y + data->ray->tex_x];
		if (data->ray->side == 1)
			data->ray->color = (data->ray->color >> 1) & 8355711;
		data->ray->buffer[data->ray->y][data->ray->x] = data->ray->color;
		data->ray->y++;
	}
}

void	texture_pos_definition(t_data *data)
{
	if (data->ray->side == 0)
		data->ray->wall_x = data->player->pos_y + data->ray->perp_wall_dist
			* data->ray->ray_dir_y;
	else
		data->ray->wall_x = data->player->pos_x + data->ray->perp_wall_dist
			* data->ray->ray_dir_x;
	data->ray->wall_x -= floor((data->ray->wall_x));
	data->ray->tex_x = (int)(data->ray->wall_x * (double)TEXWIDTH);
	if (data->ray->side == 0 && data->ray->ray_dir_x > 0)
		data->ray->tex_x = TEXWIDTH - data->ray->tex_x - 1;
	if (data->ray->side == 1 && data->ray->ray_dir_y < 0)
		data->ray->tex_x = TEXWIDTH - data->ray->tex_x - 1;
	data->ray->step = 1.0 * TEXHEIGHT / (double)data->ray->line_height;
	data->ray->tex_pos = ((double)data->ray->draw_start - SCREEN_HEIGHT * 0.5
			+ (double)data->ray->line_height * 0.5) * data->ray->step;
}

void	define_camx_raydir_and_map(t_data *data)
{
	data->ray->camera_x = 2.00 * (double)data->ray->x / SCREEN_WIDTH - 1;
	data->ray->ray_dir_x = data->player->dir_x + data->player->plane_x
		* data->ray->camera_x;
	data->ray->ray_dir_y = data->player->dir_y + data->player->plane_y
		* data->ray->camera_x;
	data->ray->map_x = (int)data->player->pos_x;
	data->ray->map_y = (int)data->player->pos_y;
}

void	raycasting_loop(t_data *data)
{
	t_ray	raycasting;

	init_ray_struct(&raycasting);
	data->ray = &raycasting;
	clean_window(data);
	while (data->ray->x < SCREEN_WIDTH)
	{
		define_camx_raydir_and_map(data);
		step_and_sidedist_calcul(data);
		data->ray->hit = 0;
		check_hit(data);
		perp_wall_dist_definition(data);
		draw_startend_definition(data);
		texture_attribution(data);
		texture_pos_definition(data);
		put_texture_on_walls(data);
		data->ray->x++;
	}
	copy_buffer_to_image(data, data->ray->buffer);
	fps_controler(data);
}
