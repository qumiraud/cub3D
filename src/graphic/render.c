/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:07:04 by qumiraud          #+#    #+#             */
/*   Updated: 2025/09/03 13:19:44 by pjurdana         ###   ########.fr       */
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
				data->ray->buffer[y][x] = 0x222222;
			x++;
		}
		y++;
	}
}
