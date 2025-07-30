/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:15:56 by qumiraud          #+#    #+#             */
/*   Updated: 2025/07/30 11:50:21 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//####### includes ########//
# include "parsing.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <math.h>
# include <X11/keysym.h>
#include <time.h>


#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define GREEN 0x00FF00


//Binding touch//
// enum e_keycode
// {
// 	KEY_A = XK_a,
// 	KEY_B = XK_b,
// 	KEY_C = XK_c,
// 	KEY_D = XK_d,
// 	KEY_E = XK_e,
// 	KEY_F = XK_f,
// 	KEY_G = XK_g,
// 	KEY_H = XK_h,
// 	KEY_I = XK_i,
// 	KEY_J = XK_j,
// 	KEY_K = XK_k,
// 	KEY_L = XK_l,
// 	KEY_M = XK_m,
// 	KEY_N = XK_n,
// 	KEY_O = XK_o,
// 	KEY_P = XK_p,
// 	KEY_Q = XK_q,
// 	KEY_R = XK_r,
// 	KEY_S = XK_s,
// 	KEY_T = XK_t,
// 	KEY_U = XK_u,
// 	KEY_V = XK_v,
// 	KEY_W = XK_w,
// 	KEY_X = XK_x,
// 	KEY_Y = XK_y,
// 	KEY_Z = XK_z,
// 	KEY_SPACE = XK_space,
// 	KEY_ENTER = XK_Return,
// 	KEY_ESCAPE = XK_Escape,
// 	KEY_BACKSPACE = XK_BackSpace,
// 	KEY_TAB = XK_Tab,
// 	KEY_SHIFT_L = XK_Shift_L,
// 	KEY_SHIFT_R = XK_Shift_R,
// 	KEY_CTRL_L = XK_Control_L,
// 	KEY_CTRL_R = XK_Control_R,
// 	KEY_ALT_L = XK_Alt_L,
// 	KEY_ALT_R = XK_Alt_R
// };

//####### structures ######//

typedef struct s_player
{
	void	*player_img;

	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	move_speed;
	double	rot_speed;
	double	plane_x;
	double	plane_y;
	char	p_dir;

}	t_player;

typedef struct s_bigben
{
	double	time;
	double	old_time;
	double frame_time;
}	t_bigben;

typedef struct	t_img
{
	void	*img_ptr;

	int		bpp;
	int		line_size;
	int		endian;

	char	*img_addr;


}	t_img;

typedef struct s_mlx_win
{
	void	*mlx_ptr;
	void	*mlx_win;


	int		img_width;
	int		img_height;

	// char	*img_ptr;
	// char	*img_data;


	// int		width;
	// int		height;
	// void	*time_value; //Permettra d'avoir un timer de fps afin d'appler les refresh au nombre d'image par seconde pour eviter d'avoir a le faire a chaque mlx_loop;

}		t_mlx_win;

typedef struct s_data
{
	char		**map;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;

	int			F[3];
	int			C[3];
	struct s_param		*param;
	int				*texture_img[4];
	int					*texture[4];
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;

	t_bigben	*bigben;
	t_mlx_win	*win;
	t_player	*player;
	t_img		img;

}	t_data;

#define DIR_X data->player->dir_x
#define DIR_Y data->player->dir_y
#define POS_X data->player->pos_x
#define POS_Y data->player->pos_y
#define PLANE_X data->player->plane_x
#define PLANE_Y data->player->plane_y
#define MOVE_SPEED data->player->move_speed
#define ROT_SPEED data->player->rot_speed
#define MAP data->map


//############ GRAPHIC_DIR ############//
int		main(int argc, char **argv);
void	raycasting_loop(t_data *data);

void	render_map(t_data *data);


//########### INPUT_DIR ##############//
int	handle_key(int keycode, t_data *data);

#endif
