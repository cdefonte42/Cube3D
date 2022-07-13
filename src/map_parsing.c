#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

struct s_map
{
	size_t height;
	size_t width;
	char **points;
};

typedef struct s_map t_map;

#define ft_strlen strlen

bool	map_getSize(char *file, t_map *map)
{
	FILE		*fd; // TODO: to file descriptor
	char	*line;
	size_t	len;
	size_t	i;

	fd = fopen(file, "r"); // O_RDWR);
	if (fd == NULL)
		return (false);
	i = 0;
	while (getline(&line, &len, fd) != -1) // TODO: get_next_line
	{
		printf("%s\n", line);
		if (i == 0 || map->width < ft_strlen(line))
			map->width = ft_strlen(line);
		i++;
	}
	map->height = i;
	fclose(fd);
	return (true);
}

bool	map_allocate(t_map	*map)
{
	size_t	i;

	map->points = (char **)malloc(sizeof(char *) * map->height);
	if (map->points == NULL)
		return (false);
	while (map->points[i])
	{
		map->points[i] = (char *)malloc(sizeof(char) * map->width);
		if (map->points[i] == NULL)
		{
			while (i > 0)
			{
				free(map->points[i]);
				i--;
			}
			free(map->points);
			return (false);
		}
		i++;
	}
	return (true);
}

void	map_print(t_map map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			printf("%d", (int)map.points[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
void	map_free(t_map map)
{
	size_t	i;

	i = 0;
	while (i < map.height)
	{
		free(map.points[i]);
		i++;
	}
	free(map.points);
}

int main(int ac, char **av)
{
	printf("%d\n", ac);
	if (ac != 2)
		return 1;
	t_map	map;
	
	memcpy(&map, &(t_map){0, 0, NULL}, sizeof(t_map)); //  TODO: ft_memcpy
	
	map.height = 10;
	map.width = 10;
	map_getSize(av[1], &map);
	printf("H:%d\nW:%d\n", map.height, map.width);
	map_allocate(&map);
	map_print(map);
	map_free(map);
}
