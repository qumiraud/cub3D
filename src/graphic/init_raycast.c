/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:31:22 by qumiraud          #+#    #+#             */
/*   Updated: 2025/09/03 11:06:30 by qumiraud         ###   ########.fr       */
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
	else if (c == 'N')
		init_player_vector(data, valuedir_xyplane_xy[1]);
	else if (c == 'E')
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
