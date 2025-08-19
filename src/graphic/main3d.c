/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:29:43 by qumiraud          #+#    #+#             */
/*   Updated: 2025/08/19 14:45:18 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

void	fill_texture_tab(t_data *data)
{
	int	width;
	int	height;
	int	size_line;
	int	endian;
	int	i;

	i = 0;
	width = TEXWIDTH;
	height = TEXHEIGHT;
	data->texture_img[0] = mlx_xpm_file_to_image(data->win->mlx_ptr,
			data->NO, &width, &height);
	data->texture_img[1] = mlx_xpm_file_to_image(data->win->mlx_ptr,
			data->SO, &width, &height);
	data->texture_img[2] = mlx_xpm_file_to_image(data->win->mlx_ptr,
			data->EA, &width, &height);
	data->texture_img[3] = mlx_xpm_file_to_image(data->win->mlx_ptr,
			data->WE, &width, &height);
	while (i < 4)
	{
		if (!data->texture_img[i])
		{
			fprintf(stderr, "Erreur lors du chargement de la texture %d\n", i);
			exit(1);
		}
		data->texture[i] = (int *)mlx_get_data_addr(data->texture_img[i],
				&data->bpp, &size_line, &endian);
		if (!data->texture[i])
		{
			fprintf(stderr, "mlx_get_data_addr failed for texture %d\n", i);
			exit(1);
		}
		i++;
	}
}

void	copy_buffer_to_image(t_data *data,
	__uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH])
{
	int	pixel_index;
	int	x;
	int	y;

	x = 0;
	mlx_clear_window(data->win->mlx_ptr, data->win->mlx_win);
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			pixel_index = y * data->size_line + x * (data->bpp / 8);
			if (pixel_index < 0 || pixel_index >= SCREEN_HEIGHT
				* data->size_line)
			{
				fprintf(stderr, " pixel_index hors limites: %d\n", pixel_index);
				exit(1);
			}
			*((unsigned int *)(data->img_data + pixel_index)) = buffer[y][x];
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->mlx_win,
		data->img_ptr, 0, 0);
}

void	init_image(t_data *data)
{
	data->img_ptr = mlx_new_image(data->win->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->img_ptr)
	{
		fprintf(stderr, "mlx_new_image failed\n");
		exit(1);
	}
	data->img_data = mlx_get_data_addr(data->img_ptr, &data->bpp,
			&data->size_line, &data->endian);
	if (!data->img_data)
	{
		fprintf(stderr, "mlx_get_data_addr for main image failed\n");
		exit(1);
	}
}

// void	dir_player(t_data *data, char c)
// {
// 	if (c == 'S')
// 	{
// 		data->player->dir_x = 0;
// 		data->player->dir_y = 1;
// 		data->player->plane_x = -0.66;
// 		data->player->plane_y = 0;
// 	}
// 	else if ( c == 'N')
// 	{
// 		data->player->dir_x = 0;
// 		data->player->dir_y = -1;
// 		data->player->plane_x = 0.66;
// 		data->player->plane_y = 0;
// 	}
// 	else if ( c == 'E')
// 	{
// 		data->player->dir_x = 1;
// 		data->player->dir_y = 0;
// 		data->player->plane_x = 0;
// 		data->player->plane_y = 0.66;
// 	}
// 	else if (c == 'W')
// 	{
// 		data->player->dir_x = -1;
// 		data->player->dir_y = 0;
// 		data->player->plane_x = 0;
// 		data->player->plane_y = -0.66;
// 	}
// }

// void	find_player_start(t_data *data)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	while (data->map[y])
// 	{
// 		while (data->map[y][x])
// 		{
// 			if (is_player(data->map[y][x]))
// 			{
// 				dir_player(data, data->map[y][x]);
// 				data->player->pos_x = x + 0.5;
// 				data->player->pos_y = y + 0.5;
// 			}
// 			x++;
// 		}
// 		y++;
// 		x = 0;
// 	}
// }

// void	init_time(t_bigben *bigben)
// {
// 	bigben->old_time = 0;
// 	bigben->time = 0;
// }
