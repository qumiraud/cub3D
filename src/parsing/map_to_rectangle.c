#include "../../header/parsing.h"

int get_height(char **map)
{
    int i;
    i = 0;
    while (map && map[i])
        i++;
    return(i);
}


int get_biggest_line(char **map)
{
    size_t max;
    max = 0;
    int i;
    i = 0;
    while (map && map[i])
    {
        if (ft_strlen(map[i]) > max)
        {
            max = ft_strlen(map[i]);
        }
        i++;
    }
    return (max);
}

void rm_newline(char **map)
{
    size_t len;
    int i;
    i = 0;
    while (map && map[i])
    {
        len = ft_strlen(map[i]);
        if (len > 0 && map[i][len - 1] == '\n')
            map[i][len - 1] = '\0';
        i++;
    }
}


char **map_to_rectangle(char **map)
{
    int max_width;
    int height;
    int i;
    int j;
    i = 0;
    j = 0;
    int k =0;
    char    **new_map;

    rm_newline(map);
    max_width = get_biggest_line(map);
    if (max_width <= 1)
    {
        write (2, "map should have more than one column\n", 38);
        free_map(map);
        return NULL;
    }
    height = get_height(map);

    new_map = ft_calloc((height + 1), sizeof(char *));
    if (!new_map)
    {
        write(2, "error allocating map\n", 22);
        free_map(map);
        return (NULL);
    }
    while(i < height)
    {
        new_map[i] = ft_calloc(max_width + 2, sizeof(char));
        if (!new_map[i])
        {
            write(2, "error allocating line\n", 23);
            free_map(new_map);
            free_map(map);
            return (NULL);
        }
        ft_strlcpy(new_map[i], map[i], ft_strlen(map[i]) + 1);
        j = ft_strlen(map[i]);
        //checking for space and replacing with HOLE
        k = 0;
        while(new_map[i] && new_map[i][k])
        {
            if (new_map[i][k] == ' ')
                new_map[i][k] = HOLE;
            k++;
        }
        //Filling shorter lines with HOLE
        while(j < max_width)
        {
            new_map[i][j] = HOLE;
            j++;
        }
        new_map[i][max_width] = '\n';
        new_map[i][max_width + 1] = '\0';
        i++;
    }
    new_map[height] = NULL;
    free_map(map);
    return (new_map);
}
