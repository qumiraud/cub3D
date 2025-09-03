/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:48:27 by pjurdana          #+#    #+#             */
/*   Updated: 2025/09/03 11:07:22 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

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

void	ray_dir_x(t_data *data)
{
	STEP_X = -1;
	SIDE_DIST_X = (POS_X - MAP_X) * DELTA_DIST_X;
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
		ray_dir_x(data);
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
		if (RAY_DIR_X < 0)
			TEX_NUM = 0;
		else
			TEX_NUM = 1;
	}
	else
	{
		if (RAY_DIR_Y < 0)
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
