
#include "../../header/parsing.h"

//extract de map from **infile, removing all parameters lines
//return the new map
char	**extract_map(char **infile, int map_index)
{
	int		height;
	int		i;
	char	**map_lines;

    height = tab_size(infile, map_index);
	map_lines = ft_calloc(height + 1, sizeof(char *));
	if (!map_lines)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map_lines[i] = ft_strdup(infile[map_index + i]);
		if (!map_lines[i])
		{
			free_map(map_lines);
			return (NULL);
		}
		i++;
	}
	map_lines[i] = NULL;
	return (map_lines);
}