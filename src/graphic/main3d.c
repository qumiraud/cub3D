/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:29:43 by qumiraud          #+#    #+#             */
/*   Updated: 2025/07/30 15:58:39 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TEXWIDTH 64
#define TEXHEIGHT 64


// void	fill_texture_tab(t_data *data)
// {
// 	int	width = TEXWIDTH;
// 	int	height = TEXHEIGHT;
// 	int	bpp;
// 	int	size_line;
// 	int	endian;

// 	data->texture_img[0] = mlx_xpm_file_to_image(data->win->mlx_ptr, data->NO, &width, &height);
// 	data->texture_img[1] = mlx_xpm_file_to_image(data->win->mlx_ptr, data->SO, &width, &height);
// 	data->texture_img[2] = mlx_xpm_file_to_image(data->win->mlx_ptr, data->EA, &width, &height);
// 	data->texture_img[3] = mlx_xpm_file_to_image(data->win->mlx_ptr, data->WE, &width, &height);

// 	if (!data->texture_img[0] || !data->texture_img[1] || !data->texture_img[2] || !data->texture_img[3])
// 	{
// 		printf("Erreur lors du chargement des textures\n");
// 		exit(1);
// 	}

// 	for (int i = 0; i < 4; i++)
// 	{
// 		data->texture[i] = (int *)mlx_get_data_addr(data->texture_img[i], &bpp, &size_line, &endian);
// 	}
// }
void    fill_texture_tab(t_data *data)
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

void    copy_buffer_to_image(t_data *data, __uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH])
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

    // mlx_put_image_to_window(data->win->mlx_ptr, data->win->mlx_win, data->img_ptr, 0, 0);
}

void    init_image(t_data *data)
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

void	raycasting_loop(t_data *data)
{
	// https://www.notion.so/Ray-Casting-220938a31f20806a8dd4c3dec8392e20?source=copy_link
	int		x;
	int		y;
	int		map_x;
	int		map_y;
	int		step_x = 0;
	int		step_y = 0;
	int		hit = 0;
	int		side = 0;
	int		line_height = 0;
	int		draw_start = 0;
	int		draw_end = 0;
	int		tex_num; //permet de designer la texture choisi a afficher
	int		tex_x;
	int		tex_y;
	double	side_dist_x = 0;
	double	side_dist_y = 0;
	double	delta_dist_x = 0;
	double	delta_dist_y = 0;
	double	perp_wall_dist = 0;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	wall_x;
	double	step;
	double	tex_pos; //position de depart dans la texture pour commencer a draw
	__uint32_t	buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	__uint32_t	color;

	x = 0;
	side_dist_x = 0;
	side_dist_y = 0;
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2.00 * (double)x / SCREEN_WIDTH - 1;
		// printf("camera_x : %2.f", camera_x);
		ray_dir_x = data->player->dir_x + data->player->plane_x * camera_x;
		ray_dir_y = data->player->dir_y + data->player->plane_y * camera_x;
		map_x = (int)data->player->pos_x;
		map_y = (int)data->player->pos_y;
		if (ray_dir_x == 0)
			delta_dist_x = 1e30;
		else
			delta_dist_x = fabs(1 / ray_dir_x);
		if (ray_dir_y == 0)
			delta_dist_y = 1e30;
		else
			delta_dist_y = fabs(1 / ray_dir_y);
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->player->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->player->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->player->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->player->pos_y) * delta_dist_y;
		}
		// printf("BEFOREside_dist_x: %2.f, side_dist_y : %2.f\n\n", side_dist_x, side_dist_y);
		// printf("BEFOREdelta_dist_x: %2.f, delta_dist_y : %2.f\n\n", delta_dist_x, delta_dist_y);
		hit = 0;
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (data->map[map_y][map_x] == '1')
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);
		line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
		draw_start = -line_height * 0.5 + SCREEN_HEIGHT * 0.5;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height * 0.5 + SCREEN_HEIGHT * 0.5;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;
	// 	//DEBUT TEXTURING

		if (side == 0)
		{
			tex_num = (ray_dir_x < 0) ? 0 : 1; // 0 = NO (Nord), 1 = SO (Sud)
		}
		else
		{
			tex_num = (ray_dir_y < 0) ? 2 : 3; // 2 = EA (Est), 3 = WE (Ouest)
		}
		if (side == 0)
			wall_x = POS_Y + perp_wall_dist * ray_dir_y;
		else
			wall_x = POS_X + perp_wall_dist * ray_dir_x;
		printf("wall_x before : %f |", wall_x);
		wall_x -= floor((wall_x));
		printf("wall_x after : %f\n", wall_x);
		printf("tex_x before : %d\n", tex_x);
		tex_x = (int)(wall_x * (double)TEXWIDTH);
		printf("tex_x after : %d\n", tex_x);
		if (side == 0 && ray_dir_x > 0)
			tex_x = TEXWIDTH - tex_x - 1;
		if (side == 1 && ray_dir_y < 0)
			tex_x = TEXWIDTH -tex_x - 1;
		printf("tex_x after : %d\n", tex_x);
		step = 1 * TEXHEIGHT / line_height;
		tex_pos = ((double)draw_start - SCREEN_HEIGHT * 0.5 + (double)line_height * 0.5) * step;
		y = draw_start;
		while(y < draw_end)
		{
			tex_y = (int)tex_pos & (TEXHEIGHT - 1);
			tex_pos += step;
			color = data->texture[tex_num][TEXHEIGHT * tex_y + tex_x];
	// 		// exit(0);
			if (side == 1)
				color = (color >> 1) & 8355711;
			buffer[y][x] = color;
			y++;
		}
			// printf("color : %d, text_num : %d, TEXHEIGHT : %d, tex_y :%d, tex_x : %d\n\n", color, tex_num, TEXHEIGHT, tex_y, tex_x);

	// 	// x++;
	// 	// mlx_put_image_to_window(data->win->mlx_ptr, data->win->mlx_win, data->texture[0], x, draw_end);
	// // }
	// 	for (int y = 0; y < SCREEN_HEIGHT; y++)
	// 	{
	// 		for (int x = 0; x < SCREEN_WIDTH; x++)
	// 		{
	// 			int pixel_index = y * data->size_line + x * (data->bpp / 8);
	// 			*((unsigned int *)(data->img_data + pixel_index)) = buffer[y][x];
	// 		}
	// 	}
	// // mlx_put_image_to_window(data->win->mlx_ptr, data->win->mlx_win, data->texture[0], x, draw_end);

		x++;
	}
	// mlx_clear_window(data->win->mlx_ptr, data->win->mlx_win);
	// mlx_pixel_put(data->win->mlx_ptr, data->win->mlx_win, SCREEN_WIDTH, SCREEN_HEIGHT, GREEN);
	copy_buffer_to_image(data, buffer);

		//AFFICHAGE AVEC LA MLX EN PIXEL
		// while (draw_start <= draw_end)
		// {
		// mlx_put_image_to_window(data->win->mlx_ptr, data->win->mlx_win, data->texture[0], x, draw_end);

		// ddddddddraw_start++;
		// }
	data->bigben->old_time = data->bigben->time;
	data->bigben->time = clock();
	data->bigben->frame_time = (data->bigben->time - data->bigben->old_time) / CLOCKS_PER_SEC;
	data->player->move_speed = data->bigben->frame_time * 5.0;
	printf ("FPS : %.2f\n", 1 / data->bigben->frame_time);
	data->player->rot_speed = data->bigben->frame_time * 3.0;
}

int main(int argc, char **argv)
{
	t_mlx_win	win;
	t_player	player;
	t_data		data;
	t_param		param;
	t_bigben	tardis;

	data.map = NULL;
	if (!guardian(&data, &param, argc, argv))
		return (1);
//initialisation
	data.img.img_ptr = NULL;
	data.win = &win;
	data.player = &player;
	data.bigben = &tardis;
	data.param = &param;
	data.win->mlx_ptr = mlx_init();
	if (data.win->mlx_ptr == NULL)
		return (1);
	data.win->mlx_win = mlx_new_window(data.win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub2D");
	if (data.win->mlx_win == NULL)
		return (1);
	// 	data.player->move_speed = 1;

	find_player_start(&data);
	init_time(data.bigben);
	init_image(&data);
	fill_texture_tab(&data);
	raycasting_loop(&data);
	mlx_hook(data.win->mlx_win, KeyPress, KeyPressMask, &handle_key, &data);
	mlx_loop(data.win->mlx_ptr);

	//raycasting

	return (0);
}
