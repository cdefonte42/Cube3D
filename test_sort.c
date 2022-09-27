struct s_sprites {
	int x;
	int y;
	int dist;
};


// Sort distance
void sort_sprites(struct s_sprites *sprites, int *orders)
{
	int i;
	int j;
	int tmp;

	i = 0;
	while (i < 10)
	{
		j = i + 1;
		while (j < 10)
		{
			if (sprites[orders[i]].dist > sprites[orders[j]].dist)
			{
				tmp = orders[i];
				orders[i] = orders[j];
				orders[j] = tmp;
			}
			j++;
		}
		i++;
	}
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	srand(time(NULL));
	int *orders = calloc(sizeof(int), 10);
	struct s_sprites *sprites = malloc(sizeof(struct s_sprites) * 10);
	for (size_t i = 0; i < 10; i++)
	{
		sprites[i].dist = rand() % 1000;
		orders[i] = i;
	}

	sort_sprites(sprites, orders);

	for (size_t i = 0; i < 10; i++)
	{
		printf("%d: %d\n", orders[i], sprites[orders[i]].dist);
	}
	
}