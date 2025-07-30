
#include "../header/parsing.h"
#include "../header/cub3d.h"

void    init_textures(t_data *data, t_param param)
{
    data->EA = param.ea_path;
    data->NO = param.no_path;
    data->SO = param.so_path;
    data->WE = param.we_path;
}

int guardian(t_data *data, t_param *param, int argc, char **argv)
{
    char **map_rect;
    map_rect = NULL;
    if (argc != 2)
    {
        write(2, "Error\nenter an infile .cub\n", 28);
        return (0);
    }
    map_is_valid(&map_rect, argv[1], param);
    if (!map_rect)
        return (0);
    data->map = map_rect;
    init_textures(data, *param);
    //print_map(data.map);
    if (!is_color(param->f_color_str, data->F)
    || !is_color(param->c_color_str, data->C) 
    || !check_all_textures(data))
    {
        free_map(data->map);
        free_param(param);
        return (0);
    }
    return (1);
}




// int main(int argc, char **argv)
// {
//     t_param param;
//     t_data data;
//     data.map = NULL;

//     //desactivez ca si vous ne testez pas avec des vrais parametres
//     if (!guardian(&data, &param, argc, argv))
//         return (1);
    
//     //inserer l'exec ici

//     free_map(data.map);
//     free_param(&param);
//     return (0);
// }