/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:12:05 by qumiraud          #+#    #+#             */
/*   Updated: 2025/09/03 11:06:50 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

void	display_fps_on_screen(t_data *data, unsigned int background_color)
{
	int		x;
	int		y;
	char	*ascii;

	y = 5;
	if (data->fps_on_window)
	{
		while (y < 25)
		{
			x = 10;
			while (x < 70)
			{
				mlx_pixel_put(data->win->mlx_ptr, data->win->mlx_win,
					x, y, (background_color >> 1) & 8355711);
				x++;
			}
			y++;
		}
		mlx_string_put(data->win->mlx_ptr, data->win->mlx_win, 15, 19,
			WHITE, "FPS : ");
		ascii = ft_itoa((int)(round(1 / data->bigben->frame_time)));
		mlx_string_put(data->win->mlx_ptr, data->win->mlx_win, 50, 19,
			WHITE, ascii);
		free(ascii);
	}
}

void	fps_controler(t_data *data)
{
	int				y;
	int				line_length;
	char			*addr;
	unsigned int	background_color;

	y = 5;
	line_length = (int)(SCREEN_WIDTH * (data->bpp * 0.125));
	addr = mlx_get_data_addr(data->img_ptr, &data->bpp,
			&line_length, &data->endian);
	background_color = *(unsigned int *)(addr + y * line_length
			+ 40 * (data->bpp / 8));
	data->bigben->old_time = data->bigben->time;
	data->bigben->time = clock();
	data->bigben->frame_time = (data->bigben->time - data->bigben->old_time)
		/ CLOCKS_PER_SEC;
	data->player->move_speed = data->bigben->frame_time * 32.0;
	data->player->rot_speed = data->bigben->frame_time * 16.0;
	display_fps_on_screen(data, background_color);
}
