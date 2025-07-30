

#include "../../../header/parsing.h"


/*int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}*/

int is_player(char c)
{
	return (((c) == 'N' || (c) == 'S' || (c) == 'E' || (c) == 'W'));
}

int valid_char(char *line)
{
    int i;
    i = 0;

    while (line[i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
            && line[i] != 'E' && line[i] != 'W'
            && line[i] != HOLE && line[i] != '\0' && line[i] != '\n')

            return (0);
        i++;
    }
    return (1);
}

void    print_map(char **map)
{
    int i;

    i = 0;
    while (map && map[i])
    {
        ft_printf("%s", map[i]);
        i++;
    }
}

char *skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}
