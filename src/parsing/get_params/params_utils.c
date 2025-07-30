
#include "../../../header/parsing.h"

void    print_param(t_param param)
{
    printf("SO = %d\n", param.SO_flag);
    printf("NO = %d\n", param.NO_flag);
    printf("WE = %d\n", param.WE_flag);
    printf("EA = %d\n", param.EA_flag);
    printf("F = %d\n", param.F_flag);
    printf("C = %d\n", param.C_flag);

}

void    init_params_flags(t_param *param)
{
    param->NO_flag = 0;
    param->NO_index = -1;
    param->SO_flag = 0;
    param->SO_index = -1;
    param->WE_flag = 0;
    param->WE_index = -1;
    param->EA_flag = 0;
    param->EA_index = -1;
    param->C_flag = 0;
    param->C_index = -1;
    param->F_flag = 0;
    param->F_index = -1;
    //print_param(*param);

    param->no_path = NULL;
	param->so_path = NULL;
	param->we_path = NULL;
	param->ea_path = NULL;
    param->c_color_str = NULL;
    param->f_color_str = NULL;

}


int tab_size(char **tab, int map_index)
{
    int i;
    int height;

    i = map_index;
    height = 0;
    while (tab && tab[i])
	{
        height++;
		i++;
	}
    return (height);

}