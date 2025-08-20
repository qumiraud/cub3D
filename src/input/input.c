/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:33:54 by pjurdana          #+#    #+#             */
/*   Updated: 2025/08/20 12:49:31 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

void	tab_handler(t_data *data)
{
	if (data->fps_on_window == 0)
		data->fps_on_window = 1;
	else
		data->fps_on_window = 0;
}

void	w_handler(t_data *data)
{
	printf("Pos_x: %f | Pos_y : %f | Dir_x : %f\n\n", POS_X, POS_Y, DIR_X);
	if (data->map[(int)(POS_Y)][(int)(POS_X + DIR_X * (MOVE_SPEED + 0.1))]
		!= '1')
	{
		POS_X += DIR_X * MOVE_SPEED;
	}
	if (data->map[(int)(POS_Y + DIR_Y * (MOVE_SPEED + 0.1))][(int)
			(POS_X)] != '1')
		POS_Y += DIR_Y * MOVE_SPEED;
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

void	ref_handle_key(int keycode, t_data *data)
{
	if (keycode == 65307 || keycode == XK_Escape)
	{
		// free necessaire ici !!!!
		exit (0);
	}
	if (keycode == XK_Tab)
		tab_handler(data);
	if (keycode == 'w' || keycode == 119 || keycode == XK_Up)
		w_handler(data);
	if (keycode == 's' || keycode == 115 || keycode == XK_Down)
		s_handler(data);
}

int	handle_key(int keycode, t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	ref_handle_key(keycode, data);
	if (keycode == XK_Left || keycode == XK_a)
	{
		old_dir_x = DIR_X;
		DIR_X = DIR_X * cos(-ROT_SPEED) - DIR_Y * sin(-ROT_SPEED);
		DIR_Y = old_dir_x * sin(-ROT_SPEED) + DIR_Y * cos(-ROT_SPEED);
		old_plane_x = PLANE_X;
		PLANE_X = PLANE_X * cos(-ROT_SPEED) - PLANE_Y * sin(-ROT_SPEED);
		PLANE_Y = old_plane_x * sin(-ROT_SPEED) + PLANE_Y * cos(-ROT_SPEED);
	}
	if (keycode == XK_Right || keycode == XK_d)
	{
		old_dir_x = DIR_X;
		DIR_X = DIR_X * cos(ROT_SPEED) - DIR_Y * sin(ROT_SPEED);
		DIR_Y = old_dir_x * sin(ROT_SPEED) + DIR_Y * cos(ROT_SPEED);
		old_plane_x = PLANE_X;
		PLANE_X = PLANE_X * cos(ROT_SPEED) - PLANE_Y * sin(ROT_SPEED);
		PLANE_Y = old_plane_x * sin(ROT_SPEED) + PLANE_Y * cos(ROT_SPEED);
	}
	raycasting_loop(data);
	return (0);
}
