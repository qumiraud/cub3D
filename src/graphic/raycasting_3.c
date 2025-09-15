/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:48:27 by pjurdana          #+#    #+#             */
/*   Updated: 2025/09/15 12:12:48 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

void	check_hit(t_data *data)
{
	while (data->ray->hit == 0)
	{
		if (data->ray->side_dist_x < data->ray->side_dist_y)
		{
			data->ray->side_dist_x += data->ray->delta_dist_x;
			data->ray->map_x += data->ray->step_x;
			data->ray->side = 0;
		}
		else
		{
			data->ray->side_dist_y += data->ray->delta_dist_y;
			data->ray->map_y += data->ray->step_y;
			data->ray->side = 1;
		}
		if (data->map[data->ray->map_y][data->ray->map_x] == '1')
		{
			data->ray->hit = 1;
		}
	}
	return ;
}

void	ray_dir_x(t_data *data)
{
	data->ray->step_x = -1;
	data->ray->side_dist_x = (data->player->pos_x - data->ray->map_x)
		* data->ray->delta_dist_x;
}

void	texture_attribution(t_data *data)
{
	if (data->ray->side == 0)
	{
		if (data->ray->ray_dir_x < 0)
			data->ray->tex_num = 0;
		else
			data->ray->tex_num = 1;
	}
	else
	{
		if (data->ray->ray_dir_y < 0)
			data->ray->tex_num = 2;
		else
			data->ray->tex_num = 3;
	}
}

void	draw_startend_definition(t_data *data)
{
	data->ray->line_height = (int)(SCREEN_HEIGHT / data->ray->perp_wall_dist);
	data->ray->draw_start = -data->ray->line_height * 0.5 + SCREEN_HEIGHT * 0.5;
	if (data->ray->draw_start < 0)
		data->ray->draw_start = 0;
	data->ray->draw_end = data->ray->line_height * 0.5 + SCREEN_HEIGHT * 0.5;
	if (data->ray->draw_end >= SCREEN_HEIGHT)
		data->ray->draw_end = SCREEN_HEIGHT;
}
