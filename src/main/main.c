/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:07:54 by qumiraud          #+#    #+#             */
/*   Updated: 2025/09/03 11:19:50 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

void	init_textures(t_data *data, t_param param)
{
	data->ea_path = param.ea_path;
	data->no_path = param.no_path;
	data->so_path = param.so_path;
	data->we_path = param.we_path;
}

int	guardian(t_data *data, t_param *param, int argc, char **argv)
{
	char	**map_rect;

	map_rect = NULL;
	if (argc != 2)
	{
		write(2, "Error\nenter an infile .cub\n", 28);
		return (0);
	}
	map_is_valid(&map_rect, argv[1], param);
	if (!map_rect)
		return (0);
	data->map = map_rect;
	init_textures(data, *param);
	if (!is_color(param->f_color_str, data->f)
		|| !is_color(param->c_color_str, data->c)
		|| !check_all_textures(data))
	{
		free_map(data->map);
		free_param(param);
		return (0);
	}
	return (1);
}

void	ref_main(t_data data)
{
	find_player_start(&data);
	init_time(data.bigben);
	init_image(&data);
	fill_texture_tab(&data);
	raycasting_loop(&data);
	fps_controler(&data);
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
