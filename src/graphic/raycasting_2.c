/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:47:31 by pjurdana          #+#    #+#             */
/*   Updated: 2025/08/20 10:56:37 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

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
	while (Y < DRAW_END)
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
		WALL_X = POS_Y + PERP_WALL_DIST * RAY_DIR_Y;
	else
		WALL_X = POS_X + PERP_WALL_DIST * RAY_DIR_X;
	WALL_X -= floor((WALL_X));
	TEX_X = (int)(WALL_X * (double)TEXWIDTH);
	if (SIDE == 0 && RAY_DIR_X > 0)
		TEX_X = TEXWIDTH - TEX_X - 1;
	if (SIDE == 1 && RAY_DIR_Y < 0)
		TEX_X = TEXWIDTH - TEX_X - 1;
	STEP = 1.0 * TEXHEIGHT / (double)LINE_HEIGHT;
	TEX_POS = ((double)DRAW_START - SCREEN_HEIGHT * 0.5
			+ (double)LINE_HEIGHT * 0.5) * STEP;
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
