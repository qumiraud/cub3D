/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:07:04 by qumiraud          #+#    #+#             */
/*   Updated: 2025/09/15 11:11:13 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

int	rgb_to_int(char **color)
{
	int	rgb;

	rgb = (ft_atoi(color[0]) << 16) | (ft_atoi(color[1]) << 8)
		| ft_atoi(color[2]);
	return (rgb);
}

void	clean_window(t_data *data, int x, int y)
{
	int		c_color;
	int		f_color;
	char	**c_rgb;
	char	**f_rgb;

	c_rgb = ft_split(data->param->c_color_str, ',');
	f_rgb = ft_split(data->param->f_color_str, ',');
	c_color = rgb_to_int(c_rgb);
	f_color = rgb_to_int(f_rgb);
	free_map(c_rgb);
	free_map(f_rgb);
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (y < SCREEN_HEIGHT * 0.5)
				data->ray->buffer[y][x] = c_color;
			else
				data->ray->buffer[y][x] = f_color;
			x++;
		}
		y++;
	}
}
