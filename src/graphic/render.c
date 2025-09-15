/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:07:04 by qumiraud          #+#    #+#             */
/*   Updated: 2025/09/15 09:58:28 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

void	clean_window(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (y < SCREEN_HEIGHT * 0.5)
				data->ray->buffer[y][x] = 0x333366;
			else
				data->ray->buffer[y][x] = 0x444444;
			x++;
		}
		y++;
	}
}

// void	clean_window(t_data *data)
// {
// 	int	x;
// 	int	y;
// 	int	celling;
// 	int	floor;


// 	x = 0;
// 	y = 0;
// 	while (y < SCREEN_HEIGHT)
// 	{
// 		x = 0;
// 		while (x < SCREEN_WIDTH)
// 		{
// 			if (y < SCREEN_HEIGHT * 0.5)
// 				data->ray->buffer[y][x] = data->param->c_color_str;
// 			else
// 				data->ray->buffer[y][x] = data->param->f_color_str;
// 			x++;
// 		}
// 		y++;
// 	}
// 	printf ("\n\n\n\ncelling : %s\n\n\n\n", data->param->c_color_str);
// 	// printf ("\n\n\n\ncelling : %d\n\n\n\n", data->param->c_flag);
// }