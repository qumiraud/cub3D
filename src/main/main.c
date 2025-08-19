/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:07:54 by qumiraud          #+#    #+#             */
/*   Updated: 2025/08/19 14:49:12 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

void	ref_main(t_data data)
{
	find_player_start(&data);
	init_time(data.bigben);
	init_image(&data);
	fill_texture_tab(&data);
	raycasting_loop(&data);
	mlx_hook(data.win->mlx_win, KeyPress, KeyPressMask, &handle_key, &data);
	mlx_loop(data.win->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_mlx_win	win;
	t_player	player;
	t_data		data;
	t_param		param;
	t_bigben	tardis;

	data.map = NULL;
	if (!guardian(&data, &param, argc, argv))
		return (1);
	data.img.img_ptr = NULL;
	data.win = &win;
	data.player = &player;
	data.bigben = &tardis;
	data.param = &param;
	data.fps_on_window = 0;
	data.win->mlx_ptr = mlx_init();
	if (data.win->mlx_ptr == NULL)
		return (1);
	data.win->mlx_win = mlx_new_window(data.win->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (data.win->mlx_win == NULL)
		return (1);
	ref_main(data);
	return (0);
}
