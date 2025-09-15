/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:15:56 by qumiraud          #+#    #+#             */
/*   Updated: 2025/09/15 11:10:30 by qumiraud         ###   ########.fr       */
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
# include <time.h>

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define TEXWIDTH 64
# define TEXHEIGHT 64

# define WHITE 0xFFFFFF
# define BLACK 0x00000000
# define GREEN 0x00FF00

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
	double	frame_time;
}	t_bigben;

typedef struct t_img
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
}		t_mlx_win;

typedef struct s_ray
{
	int			x;
	int			y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	int			tex_x;
	int			tex_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		wall_x;
	double		step;
	double		tex_pos;
	__uint32_t	buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	__uint32_t	color;
}	t_ray;

typedef struct s_data
{
	char			**map;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	int				f[3];
	int				c[3];
	struct s_param	*param;
	int				*texture_img[4];
	int				*texture[4];
	void			*img_ptr;
	char			*img_data;
	int				bpp;
	int				size_line;
	int				endian;
	int				fps_on_window;
	t_bigben		*bigben;
	t_mlx_win		*win;
	t_player		*player;
	t_img			img;
	t_ray			*ray;
}	t_data;

//############ GRAPHIC_DIR ############//
int		main(int argc, char **argv);
void	raycasting_loop(t_data *data);
void	copy_buffer_to_image(t_data *data,
			__uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH]);
void	init_ray_struct(t_ray *raycasting);
void	find_player_start(t_data *data);
void	dir_player(t_data *data, char c);
void	init_image(t_data *data);
void	fill_texture_tab(t_data *data);
void	clean_window(t_data *data, int x, int y);
void	copy_buffer_to_image(t_data *data,
			__uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH]);
void	init_time(t_bigben *bigben);

void	ray_dir_x(t_data *data);
void	step_and_sidedist_calcul(t_data *data);
void	check_hit(t_data *data);
void	draw_startend_definition(t_data *data);
void	texture_attribution(t_data *data);
void	fps_controler(t_data *data);

//########### INPUT_DIR ##############//
int		main(int argc, char **argv);

//########### INPUT_DIR ##############//
void	a_handler(t_data *data);
void	s_handler(t_data *data);
void	w_handler(t_data *data);
void	d_handler(t_data *data);
int		handle_key(int keycode, t_data *data);
int		free_all(t_data *data);

#endif