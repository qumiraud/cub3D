/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:12:05 by qumiraud          #+#    #+#             */
/*   Updated: 2025/08/05 15:39:16 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

void	display_fps_on_screen(t_data *data, unsigned int background_color)
{
	int	x;
	int	y;

	y = 5;
	if (data->fps_on_window)
	{
		while (y < 25)
		{
			x = 10;
			while (x < 70)
			{
				mlx_pixel_put(data->win->mlx_ptr, data->win->mlx_win, x, y, (background_color >> 1) & 8355711);
				x++;
			}
			y++;
		}
		mlx_string_put(data->win->mlx_ptr, data->win->mlx_win, 15, 19, WHITE,"FPS : ");
		mlx_string_put(data->win->mlx_ptr, data->win->mlx_win, 50, 19, WHITE, ft_itoa((int)(round(1 / data->bigben->frame_time))));
	}
}

void	fps_controler(t_data *data)
{
	// int	x;
	int	y;
	int	line_length;
	char    *addr;
	unsigned int	background_color;

	y = 5;
	line_length = (int)(SCREEN_WIDTH * (data->bpp * 0.125));
	addr = mlx_get_data_addr(data->img_ptr, &data->bpp, &line_length, &data->endian);
	background_color = *(unsigned int *)(addr + y * line_length + 40 * (data->bpp / 8));
	data->bigben->old_time = data->bigben->time;
	data->bigben->time = clock();
	data->bigben->frame_time = (data->bigben->time - data->bigben->old_time) / CLOCKS_PER_SEC;
	data->player->move_speed = data->bigben->frame_time * 16.0;
	printf ("FPS : %.2f\n", 1 / data->bigben->frame_time);
	data->player->rot_speed = data->bigben->frame_time * 8.0;
	display_fps_on_screen(data, background_color);
}

void	check_hit(t_data *data)
{
	while (HIT == 0)
	{
		if (SIDE_DIST_X < SIDE_DIST_Y)
		{
			SIDE_DIST_X += DELTA_DIST_X;
			MAP_X += STEP_X;
			SIDE = 0;
		}
		else
		{
			SIDE_DIST_Y += DELTA_DIST_Y;
			MAP_Y += STEP_Y;
			SIDE = 1;
		}
		if (MAP[MAP_Y][MAP_X] == '1')
		{
			HIT = 1;
		}
	}
	return ;
}
void	step_and_sidedist_calcul(t_data *data)
{
	if (RAY_DIR_X == 0)
		DELTA_DIST_X = 1e30;
	else
		DELTA_DIST_X = fabs(1 / RAY_DIR_X);
	if (RAY_DIR_Y == 0)
		DELTA_DIST_Y = 1e30;
	else
		DELTA_DIST_Y = fabs(1 / RAY_DIR_Y);
	if (RAY_DIR_X < 0)
	{
		STEP_X = -1;
		SIDE_DIST_X = (POS_X - MAP_X) * DELTA_DIST_X;
	}
	else
	{
		STEP_X = 1;
		SIDE_DIST_X = (MAP_X + 1.0 - POS_X) * DELTA_DIST_X;
	}
	if (RAY_DIR_Y < 0)
	{
		STEP_Y = -1;
		SIDE_DIST_Y = (POS_Y - MAP_Y) * DELTA_DIST_Y;
	}
	else
	{
		STEP_Y = 1;
		SIDE_DIST_Y = (MAP_Y + 1.0 - POS_Y) * DELTA_DIST_Y;
	}
}

void	texture_attribution(t_data *data)
{
	if (SIDE == 0)
	{
		if (RAY_DIR_X < 0) // 0 = NO (Nord), 1 = SO (Sud)
			TEX_NUM = 0;
		else
			TEX_NUM = 1;
	}
	else
	{
		if (RAY_DIR_Y < 0) // 2 = EA (Est), 3 = WE (Ouest)
			TEX_NUM = 2;
		else
			TEX_NUM = 3;
	}
}

void	draw_startend_definition(t_data *data)
{
	LINE_HEIGHT = (int)(SCREEN_HEIGHT / PERP_WALL_DIST);
	DRAW_START = -LINE_HEIGHT * 0.5 + SCREEN_HEIGHT * 0.5;
	if (DRAW_START < 0)
		DRAW_START = 0;
	DRAW_END = LINE_HEIGHT * 0.5 + SCREEN_HEIGHT * 0.5;
	if (DRAW_END >= SCREEN_HEIGHT)
		DRAW_END = SCREEN_HEIGHT - 1;
}

void	perp_wall_dist_definition(t_data *data)
{
	if (SIDE == 0)
		PERP_WALL_DIST = (SIDE_DIST_X - DELTA_DIST_X);
	else
		PERP_WALL_DIST = (SIDE_DIST_Y - DELTA_DIST_Y);
}

void	put_texture_on_walls(t_data *data)
{
	Y = DRAW_START;
	while(Y < DRAW_END)
	{
		TEX_Y = (int)TEX_POS & (TEXHEIGHT - 1);
		TEX_POS += STEP;
		COLOR = data->texture[TEX_NUM][TEXHEIGHT * TEX_Y + TEX_X];
		if (SIDE == 1)
			COLOR = (COLOR >> 1) & 8355711;
		BUFFER[Y][X] = COLOR;
		Y++;
	}
}

void	texture_pos_definition(t_data *data)
{
	if (SIDE == 0)
		WALL_X = POS_Y + PERP_WALL_DIST * RAY_DIR_Y; // modif
	else
		WALL_X = POS_X + PERP_WALL_DIST * RAY_DIR_X; // modif
	WALL_X -= floor((WALL_X));
	TEX_X = (int)(WALL_X * (double)TEXWIDTH);
	if (SIDE == 0 && RAY_DIR_X > 0)
		TEX_X = TEXWIDTH - TEX_X - 1;
	if (SIDE == 1 && RAY_DIR_Y < 0)
		TEX_X = TEXWIDTH -TEX_X - 1;
	STEP = 1.0 * TEXHEIGHT / (double)LINE_HEIGHT;
	TEX_POS = ((double)DRAW_START - SCREEN_HEIGHT * 0.5 + (double)LINE_HEIGHT * 0.5) * STEP;
}

void	define_camx_raydir_and_map(t_data *data)
{
	CAMERA_X = 2.00 * (double)X / SCREEN_WIDTH - 1;
	RAY_DIR_X = DIR_X + PLANE_X * CAMERA_X;
	RAY_DIR_Y = DIR_Y + PLANE_Y * CAMERA_X;
	MAP_X = (int)POS_X;
	MAP_Y = (int)POS_Y;
}

void	raycasting_loop(t_data *data)
{
	// https://www.notion.so/Ray-Casting-220938a31f20806a8dd4c3dec8392e20?source=copy_link
	t_ray	raycasting;

	init_ray_struct(&raycasting);
	data->ray = &raycasting;
	clean_window(data);
	while (X < SCREEN_WIDTH)
	{
		define_camx_raydir_and_map(data);
		step_and_sidedist_calcul(data);
		HIT = 0;
		check_hit(data);
		perp_wall_dist_definition(data);
		draw_startend_definition(data);
		texture_attribution(data);
		texture_pos_definition(data);
		put_texture_on_walls(data);
		X++;
	}
	copy_buffer_to_image(data, BUFFER);
	fps_controler(data);
}
