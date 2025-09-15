/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:33:54 by pjurdana          #+#    #+#             */
/*   Updated: 2025/09/15 09:37:24 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"
#include "../../header/parsing.h"

int	free_all(t_data *data)
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
	exit (0);
}

void	tab_handler(t_data *data)
{
	if (data->fps_on_window == 0)
		data->fps_on_window = 1;
	else
		data->fps_on_window = 0;
}

int	handle_key(int keycode, t_data *data)
{
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
