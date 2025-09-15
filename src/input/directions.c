/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:09:21 by qumiraud          #+#    #+#             */
/*   Updated: 2025/09/15 12:15:00 by qumiraud         ###   ########.fr       */
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

void	a_handler(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x + data->player->dir_y
		* data->player->move_speed;
	new_y = data->player->pos_y - data->player->dir_x
		* data->player->move_speed;
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->player->pos_x = new_x;
		data->player->pos_y = new_y;
	}
}

void	d_handler(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x - data->player->dir_y
		* data->player->move_speed;
	new_y = data->player->pos_y + data->player->dir_x
		* data->player->move_speed;
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->player->pos_x = new_x;
		data->player->pos_y = new_y;
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
