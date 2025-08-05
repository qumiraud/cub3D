//
///
//
//
//
//
//
/////////////////////////////////////////////////////////////////////////////

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

int	handle_key(int keycode, t_data *data)
{
	printf("Test Handle_key :begin\n\n\n");
	double	old_dir_x;
	double	old_plane_x;
	// double	old_plane_y;
// need to protect the map limit for the player
	// double	new_x = data->player->pos_x;
	// double	new_y = data->player->pos_y;
	// (void)data;
	if (keycode == 65307 || keycode == XK_Escape)
	{
		// end_game(data);
		exit (0);
		//exit (0); // need to go to a free function
	}
	if (keycode == XK_Tab )
	{
		if (data->fps_on_window == 0)
			data->fps_on_window = 1;
		else
			data->fps_on_window = 0;
	}
	if (keycode == 'w' || keycode == 119 || keycode == XK_Up)
	{
			// new_y = data->player->pos_y + data->player->move_speed;
			printf("Pos_x: %f | Pos_y : %f | Dir_x : %f\n\n", POS_X, POS_Y, DIR_X);
			if (data->map[(int)(POS_Y)][(int)(POS_X + DIR_X * (MOVE_SPEED + 0.1))] != '1')
			{
				printf("espoir \n\n\n");
				POS_X += DIR_X * MOVE_SPEED;

			}
			if (data->map[(int)(POS_Y + DIR_Y * (MOVE_SPEED + 0.1)) ][(int)(POS_X)] != '1')
				POS_Y += DIR_Y * MOVE_SPEED;
	}
	if (keycode == 's' || keycode == 115 || keycode == XK_Down)
	{
		// new_y = POS_Y - MOVE_SPEED;
		if (data->map[(int)POS_Y][(int)(POS_X - DIR_X * (MOVE_SPEED + 0.1))] != '1')
		{
			printf("desespoir \n\n\n");
			POS_X -= DIR_X * MOVE_SPEED;
			// printf("Pos_x: %f | Pos_y : %f | Dir_x : %f\n\n", POS_X, POS_Y, DIR_X);

		}
		if (data->map[(int)(POS_Y - DIR_Y * (MOVE_SPEED + 0.1))][(int)POS_X] != '1')
			POS_Y -= DIR_Y * MOVE_SPEED;
	}
	if (keycode == XK_Left || keycode == XK_a)
	{
		old_dir_x = DIR_X;
		DIR_X = DIR_X * cos(-ROT_SPEED) - DIR_Y * sin(-ROT_SPEED);
		DIR_Y = old_dir_x * sin(-ROT_SPEED) + DIR_Y * cos(-ROT_SPEED);
		old_plane_x = PLANE_X;
		PLANE_X = PLANE_X * cos(-ROT_SPEED) - PLANE_Y * sin(-ROT_SPEED);
		PLANE_Y = old_plane_x * sin(-ROT_SPEED) + PLANE_Y * cos(-ROT_SPEED);
	}
	if (keycode == XK_Right || keycode == XK_d)
	{
		// new_x = data->player->pos_x + data->player->move_speed;
		old_dir_x = DIR_X;
		DIR_X = DIR_X * cos(ROT_SPEED) - DIR_Y * sin(ROT_SPEED);
		DIR_Y = old_dir_x * sin(ROT_SPEED) + DIR_Y * cos(ROT_SPEED);
		old_plane_x = PLANE_X;
		PLANE_X = PLANE_X * cos(ROT_SPEED) - PLANE_Y * sin(ROT_SPEED);
		PLANE_Y = old_plane_x * sin(ROT_SPEED) + PLANE_Y * cos(ROT_SPEED);
	}
	if (keycode == 'd' /*|| keycode == 100 || keycode == XK_Right*/)
	{
		;	// new_x = data->player->pos_x - data->player->move_speed;
	}
	// if (data->map[(int)data->player->pos_x][(int)data->player->pos_Y] != '1')
	// {
	// data->player->pos_y = new_y;
	// data->player->pos_x = new_x;
	// }
	// mlx_clear_window(data->win->mlx_ptr, data->win->mlx_win);
	// render_map(data);
	// mlx_put_image_to_window(data->win->mlx_ptr, data->win->mlx_win, data->player->player_img, data->player->pos_x, data->player->pos_y);
	// printf("pos_x_update : %f\n\n", POS_X);
	// printf("pos_y_update : %f\n\n", POS_Y);
	// mlx_clear_window(data->win->mlx_ptr, data->win->mlx_win);
	raycasting_loop(data);

	// printf("Test Handle_key :end\n\n\n");

	return (0);

}