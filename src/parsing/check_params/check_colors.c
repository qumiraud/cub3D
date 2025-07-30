/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:04:25 by lguiet            #+#    #+#             */
/*   Updated: 2025/06/27 14:39:11 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parsing.h"
#include "../../../header/cub3d.h"

int color_valid_char(char *trimmed)
{
    int i;

    i = 0;
    while(trimmed[i])
    {
        if (!ft_isdigit(trimmed[i]) && trimmed[i] != ',' && trimmed[i] != '\n')
        {
            free(trimmed);
            write(2, "Error\ncolors should be described as [R,G,B]\n", 45);
            return (0);
        }
        i++;
    }
    return (1);
}
int ft_split_colors(char ***split_clr, char *trimmed)
{
    int i;

    *split_clr = ft_split(trimmed, ',');
    if(!*split_clr)
    {
        free(trimmed);
        return(0);
    }
    i = 0;
    while((*split_clr)[i])
        i++;
    if (i != 3)
    {
        write(2, "Error\ncolors should be [R,G,B]\n", 32);
        free_map(*split_clr);
        free(trimmed);
        return (0);
    }
    return (1);
}
int get_colors_int(char **split_clr, char *trimmed, int color_int[3])
{
    int i;
    int res;

    res = -1;
    i = 0;
    while(split_clr && split_clr[i])
    {
        res = ft_atoi(split_clr[i]);
        if (res < 0 || res > 255)
        {
            free_map(split_clr);
            free(trimmed);
            write(2, "Error\ncolors not within range\n", 31);
            return (0);
        }
        color_int[i] = res;
        i++;
    }
    return (1);
}

int    is_color(char *color_str, int color_int[3])
{
    char *trimmed;
    char    **split_clr;

    split_clr = NULL;
    trimmed = ft_strtrim(color_str, " \t \n");
    if (!trimmed)
    {
        perror("malloc");
        return (0);
    }
    //printf("trimmed :%s\n", trimmed);
    if(!color_valid_char(trimmed)
        || !ft_split_colors(&split_clr, trimmed)
        || !get_colors_int(split_clr, trimmed, color_int))
        return (0);
    free(trimmed);
    free_map(split_clr);
    return (1);
}
