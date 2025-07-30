/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:37:25 by qumiraud          #+#    #+#             */
/*   Updated: 2025/07/23 16:25:08 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// PARAMS = COLORS AND TEXTURES
// MAP = the map itself

#ifndef PARSING_H
# define PARSING_H

#include "../libft/libft.h"
#include "cub3d.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

//define the value used to make the map rectangle
# ifndef HOLE
#  define HOLE 'Q'

struct s_data;

typedef struct s_param
{
    int    NO_flag;
    int    SO_flag;
    int    WE_flag;
    int    EA_flag;

    int    F_flag;
    int    C_flag;

    int    NO_index;
    int    SO_index;
    int    WE_index;
    int    EA_index;

    int    F_index;
    int    C_index;

    char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;

    char	*f_color_str;
	char	*c_color_str;

    int     map_index;

}   t_param;

// GUARDIAN
int guardian(t_data *data, t_param *param, int argc, char **argv);


//get_params/extract_params
int     check_param(char **infile, t_param *param, int map_index);
int     is_color(char *color_str, int color_int[3]);
int     check_all_textures(t_data *data);

//get_infile/infile_to_tab : get the whole infile (map.cub) into a char **
char    **get_infile(char *filename, t_param *param);


//skip the textures lines and then copy into a **tab starting from the map index(where the map was found)
char	**extract_map(char **infile, int map_index);

//make the original map rectangle
char    **map_to_rectangle(char **map);

int     has_valid_char(char **map);
int     check_holes(char **map);

//valid_chars
void    map_is_valid(char ***map_rect, char *argv, t_param *param);


//free_stuff
void    free_map(char **map);
void    free_param(t_param *param);

//utils
void    print_map(char **map);
int     valid_char(char *line);
int     is_player(char c);
//int	    ft_strcmp(const char *s1, const char *s2);
char    *skip_spaces(char *line);

//params_utils in get_params
void    print_param(t_param param);
void    init_params_flags(t_param *param);
int     tab_size(char **tab, int map_index);


# endif
#endif
