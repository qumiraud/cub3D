/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:12:05 by qumiraud          #+#    #+#             */
/*   Updated: 2025/08/01 14:13:54 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"


void ft_init_ray_struct(t_ray *raycasting)
{
	raycasting->x = 0;
	raycasting->y = 0;
	raycasting->map_x = 0;
	raycasting->map_y = 0;
	raycasting->step_x = 0;
	raycasting->step_y = 0;
	raycasting->hit = 0;
	raycasting->side = 0;
	raycasting->line_height = 0;
	raycasting->draw_start = 0;
	raycasting->draw_end = 0;
	raycasting->tex_num = 0;
	raycasting->tex_x = 0;
	raycasting->tex_y = 0;
	raycasting->side_dist_x = 0;
	raycasting->side_dist_y = 0;
	raycasting->delta_dist_x = 0;
	raycasting->delta_dist_y = 0;
	raycasting->perp_wall_dist = 0;
	raycasting->camera_x = 0;
	raycasting->ray_dir_x = 0;
	raycasting->ray_dir_y = 0;
	raycasting->wall_x = 0;
	raycasting->step = 0;
	raycasting->tex_pos = 0;
	// raycasting->buffer = 0;
	raycasting->color = 0;
}

void	raycasting_loop(t_data *data)
{
	// https://www.notion.so/Ray-Casting-220938a31f20806a8dd4c3dec8392e20?source=copy_link
	t_ray	raycasting;
	
	ft_init_ray_struct(&raycasting);
	data->ray = &raycasting;
	
	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			if (y < SCREEN_HEIGHT / 2)
				BUFFER[y][x] = 0x333366; // couleur du ciel
			else
				BUFFER[y][x] = 0x222222; // couleur du sol
		}
	}
	
	while (X < SCREEN_WIDTH)
	{
		CAMERA_X = 2.00 * (double)X / SCREEN_WIDTH - 1;
		// printf("camera_x : %2.f", camera_x);
		RAY_DIR_X = DIR_X + PLANE_X * CAMERA_X;
		RAY_DIR_Y = DIR_Y + PLANE_Y * CAMERA_X;
		MAP_X = (int)POS_X;
		MAP_Y = (int)POS_Y;
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
		// printf("BEFOREside_dist_x: %2.f, side_dist_y : %2.f\n\n", side_dist_x, side_dist_y);
		// printf("BEFOREdelta_dist_x: %2.f, delta_dist_y : %2.f\n\n", delta_dist_x, delta_dist_y);
		HIT = 0;
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
				HIT = 1;
		}
		if (SIDE == 0)
			PERP_WALL_DIST = (SIDE_DIST_X - DELTA_DIST_X);
		else
			PERP_WALL_DIST = (SIDE_DIST_Y - DELTA_DIST_Y);
		LINE_HEIGHT = (int)(SCREEN_HEIGHT / PERP_WALL_DIST);
		DRAW_START = -LINE_HEIGHT * 0.5 + SCREEN_HEIGHT * 0.5;
		if (DRAW_START < 0)
			DRAW_START = 0;
		DRAW_END = LINE_HEIGHT * 0.5 + SCREEN_HEIGHT * 0.5;
		if (DRAW_END >= SCREEN_HEIGHT)
			DRAW_END = SCREEN_HEIGHT - 1;
	// 	//DEBUT TEXTURING

		if (SIDE == 0)
		{
			TEX_NUM = (RAY_DIR_X < 0) ? 0 : 1; // 0 = NO (Nord), 1 = SO (Sud)
		}
		else
		{
			TEX_NUM = (RAY_DIR_Y < 0) ? 2 : 3; // 2 = EA (Est), 3 = WE (Ouest)
		}
		if (SIDE == 0)
			WALL_X = POS_Y + PERP_WALL_DIST * RAY_DIR_Y; // modif
		// wall_x = POS_Y + perp_wall_dist * ray_dir_y;
		else
			WALL_X = POS_X + PERP_WALL_DIST * RAY_DIR_X; // modif
			// wall_x = POS_X + perp_wall_dist * ray_dir_x;
		printf("wall_x before : %f |", WALL_X);
		WALL_X -= floor((WALL_X));
		printf("wall_x after : %f\n", WALL_X);
		printf("tex_x before : %d\n", TEX_X);
		TEX_X = (int)(WALL_X * (double)TEXWIDTH);
		printf("tex_x after : %d\n", TEX_X);
		if (SIDE == 0 && RAY_DIR_X > 0)
			TEX_X = TEXWIDTH - TEX_X - 1;
		if (SIDE == 1 && RAY_DIR_Y < 0)
			TEX_X = TEXWIDTH -TEX_X - 1;
		printf("tex_x after : %d\n", TEX_X);
		STEP = 1.0 * TEXHEIGHT / (double)LINE_HEIGHT;
		TEX_POS = ((double)DRAW_START - SCREEN_HEIGHT * 0.5 + (double)LINE_HEIGHT * 0.5) * STEP;
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
		X++;
	}
	copy_buffer_to_image(data, BUFFER);
		//AFFICHAGE AVEC LA MLX EN PIXEL
		// while (draw_start <= draw_end)
		// {
		// mlx_put_image_to_window(data->win->mlx_ptr, data->win->mlx_win, data->texture[0], x, draw_end);

		// ddddddddraw_start++;
		// }
	data->bigben->old_time = data->bigben->time;
	data->bigben->time = clock();
	data->bigben->frame_time = (data->bigben->time - data->bigben->old_time) / CLOCKS_PER_SEC;
	data->player->move_speed = data->bigben->frame_time * 16.0;
	printf ("FPS : %.2f\n", 1 / data->bigben->frame_time);
	data->player->rot_speed = data->bigben->frame_time * 8.0;
}