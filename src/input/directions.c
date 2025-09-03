/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:09:21 by qumiraud          #+#    #+#             */
/*   Updated: 2025/09/03 13:42:04 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"
#include "../../header/parsing.h"

void	w_handler(t_data *data)
{
	if (data->map[(int)(data->player->pos_y)][(int)(data->player->pos_x
		+ data->player->dir_x * (data->player->move_speed + 0.1))]
		!= '1')
	{
		data->player->pos_x += data->player->dir_x * data->player->move_speed;
	}
	if (data->map[(int)(data->player->pos_y + data->player->dir_y
			* (data->player->move_speed + 0.1))][(int)
			(data->player->pos_x)] != '1')
	{
		data->player->pos_y += data->player->dir_y * data->player->move_speed;
	}
}

void	s_handler(t_data *data)
{
	if (data->map[(int)data->player->pos_y][(int)(data->player->pos_x
		- data->player->dir_x * (data->player->move_speed + 0.1))]
		!= '1')
	{
		data->player->pos_x -= data->player->dir_x * data->player->move_speed;
	}
	if (data->map[(int)(data->player->pos_y - data->player->dir_y
			* (data->player->move_speed + 0.1))][(int)data->player->pos_x]
		!= '1')
		data->player->pos_y -= data->player->dir_y * data->player->move_speed;
}

void	a_handler(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player->dir_x;
	data->player->dir_x = data->player->dir_x * cos(-data->player->rot_speed)
		- data->player->dir_y * sin(-data->player->rot_speed);
	data->player->dir_y = old_dir_x * sin(-data->player->rot_speed)
		+ data->player->dir_y * cos(-data->player->rot_speed);
	old_plane_x = data->player->plane_x;
	data->player->plane_x = data->player->plane_x
		* cos(-data->player->rot_speed) - data->player->plane_y
		* sin(-data->player->rot_speed);
	data->player->plane_y = old_plane_x * sin(-data->player->rot_speed)
		+ data->player->plane_y * cos(-data->player->rot_speed);
}

void	d_handler(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player->dir_x;
	data->player->dir_x = data->player->dir_x * cos(data->player->rot_speed)
		- data->player->dir_y * sin(data->player->rot_speed);
	data->player->dir_y = old_dir_x * sin(data->player->rot_speed)
		+ data->player->dir_y * cos(data->player->rot_speed);
	old_plane_x = data->player->plane_x;
	data->player->plane_x = data->player->plane_x
		* cos(data->player->rot_speed) - data->player->plane_y
		* sin(data->player->rot_speed);
	data->player->plane_y = old_plane_x * sin(data->player->rot_speed)
		+ data->player->plane_y * cos(data->player->rot_speed);
}
