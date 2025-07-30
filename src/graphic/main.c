/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:02:19 by qumiraud          #+#    #+#             */
/*   Updated: 2025/07/04 15:46:38 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minilibx-linux/mlx.h"
#include "../../header/cub3d.h"
# include "../../header/parsing.h"

#define map_width 24
#define map_height 24
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define PLAYER_SIZE 10
// #define MOVE_SPEED 20

void	end_game(t_data *data)
{
	// loop end, destroy window, destroy display, free mlx,  free like mlx_ptr etc
	free_map(data->map);
	free_param(data->param);
	exit (0);
}

int	handle_key(int keycode, t_data *data)
{

// need to protect the map limit for the player
	int	new_x = data->player->pos_x;
	int	new_y = data->player->pos_y;
	
	if (keycode == 65307)
	{
		end_game(data);
		//return (0);
	}
		//exit (0); // need to go to a free function

	if (keycode == 'w' || keycode == 119 || keycode == XK_Up)
		new_y = data->player->pos_y - data->player->move_speed;
		// data->player->pos_y -= data->player->move_speed;

	if (keycode == 's' || keycode == 115 || keycode == XK_Down)
		new_y = data->player->pos_y + data->player->move_speed;	
		// data->player->pos_y += data->player->move_speed;
	
	if (keycode == 'a' || keycode == 97 || keycode == XK_Left)
		new_x = data->player->pos_x - data->player->move_speed;
		// data->player->pos_x -= data->player->move_speed;
		
	if (keycode == 'd' || keycode == 100 || keycode == XK_Right)
		new_x = data->player->pos_x + data->player->move_speed;
		// data->player->pos_x += data->player->move_speed;
	if (data->map[new_y][new_x] != '1')
	{
		data->player->pos_y = new_y;
		data->player->pos_x = new_x;
	}
	// mlx_clear_window(data->win->mlx_ptr, data->win->mlx_win);
	render_map(data);
	// mlx_put_image_to_window(data->win->mlx_ptr, data->win->mlx_win, data->player->player_img, data->player->pos_x, data->player->pos_y);

	return (0);

}



void	find_player_start(t_data *data)
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	
	while (data->map[y])
	{
		
		while (data->map[y][x])
		{
			if (is_player(data->map[y][x]))
			{
				data->player->pos_x = x;
				data->player->pos_y = y;
			}
			x++;
		}
		y++;
		x = 0;
	}
}

void	home_made_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	dest = img->img_addr + (y * img->line_size + x * (img->bpp / 8));
	*(unsigned int *)dest = color;

}

void draw_img(t_data *data, int color, int x, int y)
{
	int px = 0;
	int py = 0;
	// int color = 0x00FF0000;

	while (py < 24)
	{
		while (px < 24)
		{
			home_made_pixel_put(&data->img, x * 24 + px, y * 24 + py, color);
			px++;
		}
		px = 0;
		// home_made_pixel_put(&data->img, x, y, color);

		py++;
	}
}

void draw_img_player(t_data *data, int x, int y, char dir)
{
	int px, py;
	int tx = x * 24;
	int ty = y * 24;

	for (py = 0; py < 24; py++)
	{
		for (px = 0; px < 24; px++) // ACHTUNG pas l'EFFORT
		{
			int rx = px;
			int ry = py;

			int draw = 0;
			if (dir == 'N' && ry < 24 / 2 && abs(rx - 24 / 2) < ry)
				draw = 1;
			else if (dir == 'S' && ry > 24 / 2 && abs(rx - 24 / 2) < 24 - ry)
				draw = 1;
			else if (dir == 'E' && rx > 24 / 2 && abs(ry - 24 / 2) < 24 - rx)
				draw = 1;
			else if (dir == 'W' && rx < 24 / 2 && abs(ry - 24 / 2) < rx)
				draw = 1;
			if (draw)
				home_made_pixel_put(&data->img, tx + px, ty + py, 0x00FF0000); // RED
		}
	}
}

t_img	create_img(t_data data)
{
	t_img	img;
	
	img.img_ptr = mlx_new_image(data.win->mlx_ptr, SCREEN_HEIGHT * 24, SCREEN_WIDTH * 24); // ACHTUNG 
	
	// printf ("HALLLOOO???\n\n\n\n\n");
	img.img_addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_size, &img.endian);

	return (img);
}

void	render_map(t_data *data)
{
	int	color;
	int	x;
	int	y;

	(void)color;
	x = 0;
	y = 0;
	if (data->img.img_ptr != NULL)
		mlx_destroy_image(data->win->mlx_ptr, data->img.img_ptr);
	// color = 0x00FF0000;

	data->img = create_img(*data);
	
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				color = WHITE;
			else if (data->map[y][x] == '0' || is_player(data->map[y][x]))
				color = BLACK;
			else
				color = GREEN;
			if (is_player(data->map[y][x]))
				data->player->p_dir = data->map[y][x];
			draw_img(data, color, x, y); // x * 24, y * 24);
			x++;
			// printf ("UIIIIIII???\n\n\n\n\n");

		}
		x = 0;
		y++;
	// printf ("HALLLOOO???\n\n\n\n\n");

	}
	
	draw_img_player(data, data->player->pos_x, data->player->pos_y, data->player->p_dir);
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->mlx_win, data->img.img_ptr, 0, 0);
	// printf ("HALLLOOO???\n\n\n\n\n");
	// sleep (2);
}






#include <stdio.h>

// int main(int argc, char **argv)
// {
// 	t_mlx_win win;
// 	t_player player;
// 	t_data data;
// 	t_param param;

// 	data.map = NULL;

// 	if (!guardian(&data, &param, argc, argv))
// 		return (1);
// 	data.param = &param;
// 	// printf ("HALLLOOO???\n\n\n\n\n");

// 	data.img.img_ptr = NULL;
// 	data.player = &player;
// 	data.win = &win;


// 	data.win->mlx_ptr = mlx_init();
// 	data.player->move_speed = 1;
	
// 	if (data.win->mlx_ptr == NULL)
// 		return (1);
		
// 	data.win->mlx_win = mlx_new_window(data.win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub2D");
// 	if (data.win->mlx_win == NULL)
// 		return (1);

// 	// data.player->player_img = mlx_xpm_file_to_image(data.win->mlx_ptr, "H_I_F.xpm", &data.win->img_width, &data.win->img_height);
// 	// if(!data.player->player_img)
// 	// {
// 	// 	return (printf("Broken IMG"));
// 	// }
// 	find_player_start(&data);
// 	// printf ("\n\n\n pos_x : %f\n\n\npos_y : %f", data.player->pos_x, data.player->pos_y);
	
// 	// data.player->pos_x = screen_width / 2;
// 	// data.player->pos_y = screen_height / 2;
	
// 	render_map(&data);
	
	
// 	// draw_player(&data);
// 	// mlx_put_image_to_window(data.win->mlx_ptr, data.win->mlx_win, data.player->player_img, data.player->pos_x, data.player->pos_y);
// 	// mlx_destroy_image(data.mlx_ptr, data.player_img);
	
// 	//mlx_key_hook(data.win->mlx_win, handle_key, &data);
// 	//mlx_loop_hook(data.win->mlx_ptr, handle_key, &data);
// 	mlx_hook(data.win->mlx_win, KeyPress, KeyPressMask, &handle_key, &data);
// 	mlx_loop(data.win->mlx_ptr);
	
	
// 	// c'est la fing
	
// 	// free_map(data.map);
// 	// free_param(&param);
	
// 	return (0);
	
// 	// printf ("HALLOO???\n\n\n");
// }

// clear && make && ./guardian map.cub






// void draw_player(t_mlx_win *window)
// {
// 	int x = 0;
// 	int y = 0;
// 	int color = 0x00FF0000;

// 	while (y < PLAYER_SIZE)
// 	{
// 		while (x < PLAYER_SIZE)
// 		{
// 			mlx_pixel_put(window->mlx_ptr, window->mlx_win, window->pos_x + x, window->pos_y + y, color);
// 			x++;
// 		}
// 		x = 0;
// 		mlx_pixel_put(window->mlx_ptr, window->mlx_win, window->pos_x + x, window->pos_y + y, color);

// 		y++;
// 	}
	
// }

// int	handle_key(int keycode, t_mlx_win *window)
// {

// // need to protect the map limit for the player

	
// 	if (keycode == 65307)
// 		exit (0); // need to go to a free function

// 	if (keycode == 'w' || keycode == 119)
// 		window->pos_y -= MOVE_SPEED;

// 	if (keycode == 's' || keycode == 115)
// 		window->pos_y += MOVE_SPEED;
	
// 	if (keycode == 'a' || keycode == 97)
// 		window->pos_x -= MOVE_SPEED;
		
// 	if (keycode == 'd' || keycode == 100)
// 		window->pos_x += MOVE_SPEED;

// 	mlx_clear_window(window->mlx_ptr, window->mlx_win);
// 	mlx_put_image_to_window(window->mlx_ptr, window->mlx_win, window->player_img, window->pos_x, window->pos_y);

	
// 	// draw_player(window);?
	

// 	return (0);

	
// }

// #include <stdio.h>


// int main(void)
// {
// 	t_mlx_win window;

// 	window.mlx_ptr = mlx_init();
// 	if (window.mlx_ptr == NULL)
// 		return (1);
// 	window.mlx_win = mlx_new_window(window.mlx_ptr, screen_width, screen_height, "Cub2D");
// 	if (window.mlx_win == NULL)
// 		return (1);

// 	window.player_img = mlx_xpm_file_to_image(window.mlx_ptr, "H_I_F.xpm", &window.img_width, &window.img_height);
// 	if(!window.player_img)
// 	{
// 		return (printf("Broken IMG"));
// 	}


// 	window.pos_x = screen_width / 2;
// 	window.pos_y = screen_height / 2;

// 	// draw_player(&window);
// 	mlx_put_image_to_window(window.mlx_ptr, window.mlx_win, window.player_img, window.pos_x, window.pos_y);

	
// 	mlx_key_hook(window.mlx_win, handle_key, &window);

	
// 	mlx_loop(window.mlx_ptr);

// 	return (0);

// }


// double pos_x = 22, pos_y = 12;  //_x and _y start position
// double dir_x = -1, dir_y = 0; //initial direction vector
// double plane_x = 0, plane_y = 0.66; //the 2d raycaster version of camera plane

// double time = 0; //time of current frame
// double oldTime = 0; //time of previous frame

// screen(screen_width, screen_height, 0, "Raycaster");




// int world_map[map_width][map_height]=
// {
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };