
#include "../../../header/parsing.h"



int has_all_params(t_param param)
{
    if (param.C_flag == 1 && param.F_flag == 1 && param.EA_flag == 1
        && param.NO_flag == 1 && param.SO_flag == 1 && param.WE_flag == 1)
        return (1);

    write(2,
        "Error\nmake sure all parameters are described and in correct position\n",
         70);
    return (0);
}

int map_is_last(t_param param, int map_index)
{
    int max;
    max = -1;

    if (param.C_index >= max)
        max = param.C_index;
    if (param.F_index >= max)
        max = param.F_index;
    if (param.SO_index >= max)
        max = param.SO_index;
    if (param.NO_index >= max)
        max = param.NO_index;
    if (param.WE_index >= max)
        max = param.WE_index;
    if (param.EA_index >= max)
        max = param.EA_index;
    if (max > map_index)
    {
        write(2, "Error\nmap description should be last\n", 38);
        return (0);
    }
    return (1);
}

// return 0 if alloc failed, comp = length of the ID + space
int	alloc_param_value(char *trimmed, char *id, char **target, int comp)
{
	if (ft_strncmp(trimmed, id, comp) == 0)
	{
		*target = ft_strtrim((trimmed + comp), " \n");
		if (!*target)
			return (0);
	}
	return (1);
}

//return 0 if alloc fails
int	alloc_param(char **infile, t_param *param)
{
	char	*trimmed;
	int		i = 0;

	while (infile && infile[i])
	{
		trimmed = skip_spaces(infile[i]);
		if (!alloc_param_value(trimmed, "SO ", &param->so_path, 3)
			|| !alloc_param_value(trimmed, "NO ", &param->no_path, 3)
			|| !alloc_param_value(trimmed, "WE ", &param->we_path, 3)
			|| !alloc_param_value(trimmed, "EA ", &param->ea_path, 3)
			|| !alloc_param_value(trimmed, "F ", &param->f_color_str, 2)
			|| !alloc_param_value(trimmed, "C ", &param->c_color_str, 2))
			return (0);
		i++;
	}
	return (1);
}
void    check_textures(char *trimmed, t_param *param, int i, int *flag)
{
        if (ft_strncmp(trimmed, "SO ", 3) == 0)
        {
            param->SO_flag++;
            param->SO_index = i;
            *flag = 1;
        }
        else if (ft_strncmp(trimmed, "NO ", 3) == 0)
        {
            param->NO_flag++;
            param->NO_index = i;
            *flag = 1;
        }
        else if (ft_strncmp(trimmed, "WE ", 3) == 0)
        {
            param->WE_flag++;
            param->WE_index = i;
            *flag = 1;
        }
        else if (ft_strncmp(trimmed, "EA ", 3) == 0)
        {
            param->EA_flag++;
            param->EA_index = i;
            *flag = 1;
        }
}

void    check_colors(char *trimmed, t_param *param, int i)
{
    if (ft_strncmp(trimmed, "F ", 2) == 0)
    {
        param->F_flag++;
        param->F_index = i;
    }
    else if (ft_strncmp(trimmed, "C ", 2) == 0)
    {
        param->C_flag++;
        param->C_index = i;
    }
}

//check if textures and colors are defined and allocate them in t_param
int    check_param(char **infile, t_param *param, int map_index)
{
    char *trimmed;
    int i;
    int flag;

    i = 0;
    if (map_index == -1)
        return(write(2, "Error\nmap not found\n", 21), 0);
    while(infile && infile[i])
    {
        flag = 0;
        trimmed = skip_spaces(infile[i]);
        check_textures(trimmed, param, i, &flag);
        if (flag == 0)
            check_colors(trimmed, param, i);
        i++;
    }
    if (!has_all_params(*param) || !map_is_last(*param, map_index)
     || !alloc_param(infile, param))
        return (0);

    return (1);
}
