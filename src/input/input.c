/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:33:54 by pjurdana          #+#    #+#             */
/*   Updated: 2025/09/02 14:05:30 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

void free_all(t_data *data)
{
	mlx_clear_window(data->win->mlx_ptr, data->win->mlx_win);
	mlx_destroy_window(data->win->mlx_ptr, data->win->mlx_win);
	free_map(data->map);
	free_param(data->param);
	mlx_destroy_image(data->win->mlx_ptr, data->texture_img[0]);
	mlx_destroy_image(data->win->mlx_ptr, data->texture_img[1]);
	mlx_destroy_image(data->win->mlx_ptr, data->texture_img[2]);
	mlx_destroy_image(data->win->mlx_ptr, data->texture_img[3]);
	mlx_destroy_image(data->win->mlx_ptr, data->img_ptr);
	mlx_destroy_display(data->win->mlx_ptr);
	free(data->win->mlx_ptr);
	return ;
}

void	tab_handler(t_data *data)
{
	if (data->fps_on_window == 0)
		data->fps_on_window = 1;
	else
		data->fps_on_window = 0;
}

void	w_handler(t_data *data)
{
	// printf("Pos_x: %f | Pos_y : %f | Dir_x : %f\n\n", POS_X, POS_Y, DIR_X);
	if (data->map[(int)(POS_Y)][(int)(POS_X + DIR_X * (MOVE_SPEED + 0.1))]
		!= '1')
	{
		POS_X += DIR_X * MOVE_SPEED;
	}
	if (data->map[(int)(POS_Y + DIR_Y * (MOVE_SPEED + 0.1))][(int)
			(POS_X)] != '1')
	{
		// printf("\n POS_Y(%f) += DIR_Y(%f) * MOVE_SPEED(%f)\n", POS_Y, DIR_Y, MOVE_SPEED);
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

// void	ref_handle_key(int keycode, t_data *data)
// {

// 	if (keycode == 65307 || keycode == XK_Escape)
// 	{
// 		free_all(data);
// 		exit (0);
// 	}
// 	if (keycode == XK_Tab)
// 		tab_handler(data);
// 	if (keycode == 'w' || keycode == 119 || keycode == XK_Up)
// 		w_handler(data);
// 	if (keycode == 's' || keycode == 115 || keycode == XK_Down)
// 		s_handler(data);
// 	if (keycode == XK_Left || keycode == XK_a)
// 		a_handler(data);
// 	if (keycode == XK_Right || keycode == XK_d)
// 		d_handler(data);
// }

int	handle_key(int keycode, t_data *data)
{
	// printf("move_speed_at_first_keypress : %f", MOVE_SPEED);
	if (keycode == 65307 || keycode == XK_Escape)
	{
		free_all(data);
		exit (0);
	}
	if (keycode == XK_Tab)
		tab_handler(data);
	if (keycode == 'w' || keycode == 119 || keycode == XK_Up)
		w_handler(data);
	if (keycode == 's' || keycode == 115 || keycode == XK_Down)
		s_handler(data);
	if (keycode == XK_Left || keycode == XK_a)
		a_handler(data);
	if (keycode == XK_Right || keycode == XK_d)
		d_handler(data);
	raycasting_loop(data);
	return (0);
}
