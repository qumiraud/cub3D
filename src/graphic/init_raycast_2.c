/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:43:49 by pjurdana          #+#    #+#             */
/*   Updated: 2025/08/20 10:44:12 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

void	init_texture(t_ray *raycasting)
{
	raycasting->tex_num = 0;
	raycasting->tex_x = 0;
	raycasting->tex_y = 0;
	raycasting->tex_pos = 0;
	raycasting->color = 0;
}

void	init_ray_struct(t_ray *raycasting)
{
	raycasting->x = 0;
	raycasting->y = 0;
	raycasting->map_x = 0;
	raycasting->map_y = 0;
	raycasting->step_x = 0;
	raycasting->step_y = 0;
	raycasting->hit = 0;
	raycasting->side = 0;
	raycasting->line_height = 0;
	raycasting->draw_start = 0;
	raycasting->draw_end = 0;
	raycasting->side_dist_x = 0;
	raycasting->side_dist_y = 0;
	raycasting->delta_dist_x = 0;
	raycasting->delta_dist_y = 0;
	raycasting->perp_wall_dist = 0;
	raycasting->camera_x = 0;
	raycasting->ray_dir_x = 0;
	raycasting->ray_dir_y = 0;
	raycasting->wall_x = 0;
	raycasting->step = 0;
	init_texture(raycasting);
}
