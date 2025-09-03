/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:12:05 by qumiraud          #+#    #+#             */
/*   Updated: 2025/09/03 13:50:10 by pjurdana         ###   ########.fr       */
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

void	ref_if_sasc(t_data *data)
{
	data->ray->step_y = -1;
	data->ray->side_dist_y = (data->player->pos_y - data->ray->map_y)
		* data->ray->delta_dist_y;
}

void	ref_else_sasc(t_data *data)
{
	data->ray->step_y = 1;
	data->ray->side_dist_y = (data->ray->map_y + 1.0
			- data->player->pos_y) * data->ray->delta_dist_y;
}

void	step_and_sidedist_calcul(t_data *data)
{
	if (data->ray->ray_dir_x == 0)
		data->ray->delta_dist_x = 1e30;
	else
		data->ray->delta_dist_x = fabs(1 / data->ray->ray_dir_x);
	if (data->ray->ray_dir_y == 0)
		data->ray->delta_dist_y = 1e30;
	else
		data->ray->delta_dist_y = fabs(1 / data->ray->ray_dir_y);
	if (data->ray->ray_dir_x < 0)
		ray_dir_x(data);
	else
	{
		data->ray->step_x = 1;
		data->ray->side_dist_x = (data->ray->map_x + 1.0 - data->player->pos_x)
			* data->ray->delta_dist_x;
	}
	if (data->ray->ray_dir_y < 0)
		ref_if_sasc(data);
	else
		ref_else_sasc(data);
}
