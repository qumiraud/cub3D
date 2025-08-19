/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:07:04 by qumiraud          #+#    #+#             */
/*   Updated: 2025/08/19 13:48:25 by pjurdana         ###   ########.fr       */
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
				BUFFER[y][x] = 0x333366;
			else
				BUFFER[y][x] = 0x222222;
			x++;
		}
		y++;
	}
// ui
}

/*
if (y < SCREEN_HEIGHT * 0.5)
	BUFFER[y][x] = 0x333366; // couleur du ciel
else
	BUFFER[y][x] = 0x222222; // couleur du sol
*/