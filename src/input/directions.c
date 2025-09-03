/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:09:21 by qumiraud          #+#    #+#             */
/*   Updated: 2025/09/03 11:11:57 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"
#include "../../header/parsing.h"

void	w_handler(t_data *data)
{
	if (data->map[(int)(POS_Y)][(int)(POS_X + DIR_X * (MOVE_SPEED + 0.1))]
		!= '1')
	{
		POS_X += DIR_X * MOVE_SPEED;
	}
	if (data->map[(int)(POS_Y + DIR_Y * (MOVE_SPEED + 0.1))][(int)
			(POS_X)] != '1')
	{
		POS_Y += DIR_Y * MOVE_SPEED;
	}
}

void	s_handler(t_data *data)
{
	if (data->map[(int)POS_Y][(int)(POS_X - DIR_X * (MOVE_SPEED + 0.1))]
		!= '1')
	{
		POS_X -= DIR_X * MOVE_SPEED;
	}
	if (data->map[(int)(POS_Y - DIR_Y * (MOVE_SPEED + 0.1))][(int)POS_X]
		!= '1')
		POS_Y -= DIR_Y * MOVE_SPEED;
}

void	a_handler(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = DIR_X;
	DIR_X = DIR_X * cos(-ROT_SPEED) - DIR_Y * sin(-ROT_SPEED);
	DIR_Y = old_dir_x * sin(-ROT_SPEED) + DIR_Y * cos(-ROT_SPEED);
	old_plane_x = PLANE_X;
	PLANE_X = PLANE_X * cos(-ROT_SPEED) - PLANE_Y * sin(-ROT_SPEED);
	PLANE_Y = old_plane_x * sin(-ROT_SPEED) + PLANE_Y * cos(-ROT_SPEED);
}

void	d_handler(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = DIR_X;
	DIR_X = DIR_X * cos(ROT_SPEED) - DIR_Y * sin(ROT_SPEED);
	DIR_Y = old_dir_x * sin(ROT_SPEED) + DIR_Y * cos(ROT_SPEED);
	old_plane_x = PLANE_X;
	PLANE_X = PLANE_X * cos(ROT_SPEED) - PLANE_Y * sin(ROT_SPEED);
	PLANE_Y = old_plane_x * sin(ROT_SPEED) + PLANE_Y * cos(ROT_SPEED);
}
