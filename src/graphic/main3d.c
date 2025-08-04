/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:29:43 by qumiraud          #+#    #+#             */
/*   Updated: 2025/08/04 14:08:49 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

// #define MAP_WIDTH 24
// #define MAP_HEIGHT 24
// #define SCREEN_WIDTH 640
// #define SCREEN_HEIGHT 480
// #define TEXWIDTH 64
// #define TEXHEIGHT 64

void	fill_texture_tab(t_data *data)
{
	int width = TEXWIDTH;
	int height = TEXHEIGHT;
	int size_line, endian;

	data->texture_img[0] = mlx_xpm_file_to_image(data->win->mlx_ptr, data->NO, &width, &height);
	data->texture_img[1] = mlx_xpm_file_to_image(data->win->mlx_ptr, data->SO, &width, &height);
	data->texture_img[2] = mlx_xpm_file_to_image(data->win->mlx_ptr, data->EA, &width, &height);
	data->texture_img[3] = mlx_xpm_file_to_image(data->win->mlx_ptr, data->WE, &width, &height);

	for (int i = 0; i < 4; i++)
	{
		if (!data->texture_img[i])
		{
			fprintf(stderr, "Erreur lors du chargement de la texture %d\n", i);
			exit(1);
		}
		data->texture[i] = (int *)mlx_get_data_addr(data->texture_img[i], &data->bpp, &size_line, &endian);
		if (!data->texture[i])
		{
			fprintf(stderr, "mlx_get_data_addr failed for texture %d\n", i);
			exit(1);
		}
	}
}

void	copy_buffer_to_image(t_data *data, __uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH])
{
	mlx_clear_window(data->win->mlx_ptr, data->win->mlx_win);
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			int pixel_index = y * data->size_line + x * (data->bpp / 8);
			if (pixel_index < 0 || pixel_index >= SCREEN_HEIGHT * data->size_line)
			{
				fprintf(stderr, " pixel_index hors limites: %d\n", pixel_index);
				exit(1);
			}
			*((unsigned int *)(data->img_data + pixel_index)) = buffer[y][x];

		}
	}
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->mlx_win, data->img_ptr, 0, 0);
}

void	init_image(t_data *data)
{
	data->img_ptr = mlx_new_image(data->win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->img_ptr)
	{
		fprintf(stderr, "mlx_new_image failed\n");
		exit(1);
	}
	data->img_data = mlx_get_data_addr(data->img_ptr, &data->bpp, &data->size_line, &data->endian);
	if (!data->img_data)
	{
		fprintf(stderr, "mlx_get_data_addr for main image failed\n");
		exit(1);
	}
}

void	dir_player(t_data *data, char c)
{
	if (c == 'S')
	{
		data->player->dir_x = 0;
		data->player->dir_y = 1;
		data->player->plane_x = -0.66;
		data->player->plane_y = 0;
	}
	else if ( c == 'N')
	{
		data->player->dir_x = 0;
		data->player->dir_y = -1;
		data->player->plane_x = 0.66;
		data->player->plane_y = 0;
	}
	else if ( c == 'E')
	{
		data->player->dir_x = 1;
		data->player->dir_y = 0;
		data->player->plane_x = 0;
		data->player->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		data->player->dir_x = -1;
		data->player->dir_y = 0;
		data->player->plane_x = 0;
		data->player->plane_y = -0.66;
	}
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

// int main(int argc, char **argv)
// {
// 	t_mlx_win	win;
// 	t_player	player;
// 	t_data		data;
// 	t_param		param;
// 	t_bigben	tardis;

// 	data.map = NULL;
// 	if (!guardian(&data, &param, argc, argv))
// 		return (1);
// //initialisation
// 	data.img.img_ptr = NULL;
// 	data.win = &win;
// 	data.player = &player;
// 	data.bigben = &tardis;
// 	data.param = &param;
// 	data.win->mlx_ptr = mlx_init();
// 	if (data.win->mlx_ptr == NULL)
// 		return (1);
// 	data.win->mlx_win = mlx_new_window(data.win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub2D");
// 	if (data.win->mlx_win == NULL)
// 		return (1);
// 	// 	data.player->move_speed = 1;

// 	find_player_start(&data);
// 	init_time(data.bigben);
// 	init_image(&data);
// 	fill_texture_tab(&data);
// 	raycasting_loop(&data);
// 	mlx_hook(data.win->mlx_win, KeyPress, KeyPressMask, &handle_key, &data);
// 	mlx_loop(data.win->mlx_ptr);

// 	//raycasting

// 	return (0);
// }
