
#include "../../../header/parsing.h"

//better than strchr because avoid finding the occurence anywhere
int	ft_strspn(const char *s, const char *accept)
{
	int i;
	int j;
	int	match;

    i = 0;
	while (s[i])
	{
		match = 0;
		j = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
			{
				match = 1;
				break;
			}
			j++;
		}
		if (!match)
			break;
		i++;
	}
	return (i);
}

int	is_map_line(char *line)
{
	int	i = 0;

	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
			return (0);
		i++;
	}

	if (i == 0 || ft_strspn(line, " \n") == i)
		return (0);
	return (1);
}

//malloc of new line in **tab, 1 for line 1 for \0
static char **add_line(char **map, char *line, int *count)
{
    int i;
    i = 0;
    if (line && (line[0] == '\0'))
        return (NULL);
    char **new_map = malloc(sizeof(char *) * (*count + 2));
    if (!new_map)
    {
        perror("malloc");
        return (NULL);
    }
    // copy what was already in map
    while (i < *count)
    {
        new_map[i] = map[i];
        i++;
    }
    // copy the new line
    new_map[*count] = line;
    new_map[*count + 1] = NULL;
    //free what was in the old map
    if (map)
        free(map);
    (*count)++;
    return (new_map);
}


int valid_name(char *name)
{
    int len;
    len = ft_strlen(name);
    char *extension;
    if (len < 5)
    {
        write(2, "input must be : <name.cub>\n", 28);
        return (0);
    }
    len = len - 4;
    extension = name + len;
    if (ft_strcmp(extension, ".cub") != 0)
    {
        write(2, "extension format : <.cub>\n", 27);
        return (0);
    }
    return (1);
}
int    open_fd(char *filename, int *fd)
{
    if (!valid_name(filename))
        return (0);
    *fd = open(filename, O_RDONLY);
    if (*fd < 0)
    {
        write(2, "error opening map\n", 19);
        return (0);
    }
    return (1);
}

void    free_line_close_fd(char *line, int *fd)
{
    line = get_next_line(*fd);
    while (line)
    {
        free(line);
        line = get_next_line(*fd);
    }
    close(*fd);
}

void find_map(int *map_found, char *line, t_param *param, int count)
{
    if (*map_found == 0 && is_map_line(line))
    {
        param->map_index = count;
        *map_found = 1;
    }
}

void    copy_content_find_map(char *line, int fd, t_param *param, char ***map)
{
    int count;
    int map_found;

    count = 0;
    map_found = 0;
    line = get_next_line(fd);
    while (line)
    {
        find_map(&map_found, line, param, count);
        if (map_found)
        {
            if (line[0] == '\n' || line[0] == '\0' || line[0] == '\t')
            {
                free(line);
                line = NULL;
                break;
            }
            *map = add_line(*map, line, &count);
        }
        else if (line)
            *map = add_line(*map, line, &count);
        line = get_next_line(fd);
    }
}
//skip the textures lines and then copy into a **tab starting from the first valid char found (1 / 0 / N / S etc)
char **get_infile(char *filename, t_param *param)
{
    int fd;
    char    *line;
    char    **map;

    line = NULL;
    map = NULL;
    if (!open_fd(filename, &fd))
        return (0);
    copy_content_find_map(line, fd, param, &map);
    free_line_close_fd(line, &fd);
    if (!map)
        write(2, "Error\ninfile is empty\n", 23);
    return (map);
}
