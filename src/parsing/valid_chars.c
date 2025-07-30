/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:23:37 by lguiet            #+#    #+#             */
/*   Updated: 2025/06/27 14:38:26 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"


int one_player(char **map)
{
    int player_count;
    int walkable_count;
    int i;
    int j;

    player_count = 0;
    walkable_count = 0;
    i = 0;
    while(map && map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (is_player(map[i][j]))
                player_count++;
            if (map[i][j] == '0')
                walkable_count++;
            j++;
        }
        i++;
    }
    if (player_count > 1 || player_count == 0 || walkable_count == 0)
        return (0);

    return (1);
}


int has_valid_char(char **map)
{
    int i;

    i = 0;
    if (!one_player(map))
    {
        write(2, "input 1 player max and at least 1 walkable\n", 44);
        free_map(map);
        return (0);
    }
    while (map && map[i])
    {
        if (!valid_char(map[i]))
        {
            write(2, "invalid char\n", 14);
            free_map(map);
            return (0);
        }
        i++;
    }
    return (1);
}


int end_of_line(char c)
{
    return ((c == '\0' || c == '\n'));
}
// int has_holes(char **map, int i, int j)
// {
//     if ((j == 0 && (map[i][j] != '1' && map[i][j] != HOLE))
//         || (i == 0 && map[0][j] != '1' && map[0][j] != HOLE))
//         {
//             printf("HELOO\n");
//         return (1);
//         }
//     if (map[i][j] == '0' || is_player(map[i][j]))
//     {
//         if ((map[i][j + 1] == HOLE) || (j > 0 && map[i][j - 1] == HOLE) || end_of_line(map[i][j + 1]))
//             return (1);
//         if ((i > 0 && map[i - 1][j] == HOLE)
//             || (map[i + 1] != NULL && map[i + 1][j] == HOLE)
//             || (map[i + 1] == NULL && map[i - 1][j] == '0'))
//             return (1);
//     }
//     return (0);
// }

int has_holes(char **map, int i, int j)
{
    if ((j == 0 && (map[i][j] != '1' && map[i][j] != HOLE && map[i][j] != '\n'))
        || (i == 0 && (map[0][j] != '1' && map[0][j] != HOLE && map[0][j] != '\n')))
    {
        printf("HELOO at [%d][%d] = '%c'\n", i, j, map[i][j]);
        return (1);
    }

    if (map[i][j] == '0' || is_player(map[i][j]))
    {
        if (map[i][j + 1] && map[i][j + 1] == HOLE)
            return (1);
        if (j > 0 && map[i][j - 1] == HOLE)
            return (1);
        if (i > 0 && map[i - 1][j] == HOLE)
            return (1);
        if (map[i + 1] && map[i + 1][j] == HOLE)
            return (1);
    }

    return (0);
}

int end_with_walls(char **map)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(map[i]);
    while(map && map[i])
    {
        if (map[i][len - 2] != '1' && map[i][len - 2] != HOLE)
        {
            write(2, "doesn't end with walls\n", 24);
            free_map(map);
            return (0);
        }
        i++;
    }
    return (1);
}
// check if player or 0 is next to a hole and that first colums is wall
int check_holes(char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (!end_with_walls(map))
        return (0);
    while (map && map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (has_holes(map, i, j))
            {
                write(2, "hole in the map\n", 17);
                free_map(map);
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

void map_is_valid(char ***map_rect, char *argv, t_param *param)
{
    (void)map_rect;
    char **infile;
    char    **map;

    param->map_index = -1;
    map = NULL;
    infile = NULL;
    infile = get_infile(argv, param);
    if (!infile)
        return ;
    //print_map(infile);
    init_params_flags(param);
    if (!check_param(infile, param, param->map_index))
    {
        free_param(param);
        free_map(infile);
        return ;
    }
    map = extract_map(infile, param->map_index);
    if (!map)
    {
        free_param(param);
        free_map(infile);
        return ;
    }
    free_map(infile);
    //print_map(map);
    *map_rect = map_to_rectangle(map);
    if (!*map_rect)
    {
        free_param(param);
        return ;
    }
    print_map(*map_rect);
    if (!has_valid_char(*map_rect) || !check_holes(*map_rect))
    {
        free_param(param);
        *map_rect = NULL;
        return ;
    }
    //free_map(map);
    //return (map_rect);
}
