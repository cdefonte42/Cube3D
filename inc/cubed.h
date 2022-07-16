/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:30:57 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/15 20:12:41 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include <fcntl.h>
# include "libft.h"
# include "mlx.h"

# ifndef SCREEN_W
#  define SCREEN_W 320
# endif
# ifndef SCREEN_H
#  define SCREEN_H 200
# endif

# ifndef WALL_SIZE
#  define WALL_SIZE 64 // taille des walls
# endif

# ifndef VIEW_HEIGHT
#  define VIEW_HEIGHT 32 // hauteur du point de vue (du player). En general 1/2 
# endif
// DIR			(x, y)
// NORTH	=	(0, -1);
// SOUTH	=	(0, 1);
// WEST		=	(-1, 0);
// EAST		=	(1, 0);
typedef enum e_dir {south, north, west, east} t_dir;
typedef enum e_coord {x, y, z} t_coord;

typedef struct	s_player
{
	unsigned int	x;		//position (grid unit) sur x; ex: si = 1, pixel pos = 1xgrid_size
	unsigned int	y;		//position (grid unit) sur y;
	int				dir[2];	//direction;
	unsigned int	fov;	//field of view en °C;
}				t_player;

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
	char	*title;
	char	**map;
}				t_win;

# if defined(__APPLE__) && defined(__MACH__)
#  define L_ARW				123	
#  define R_ARW				124	
#  define UP_ARW			126
#  define DOWN_ARW			125	
#  define A_KEY				0
#  define S_KEY				1
#  define D_KEY				2
#  define W_KEY				13
#  define ESC 				53

# else
#  define L_ARW				65361
#  define R_ARW				65363
#  define UP_ARW				65362
#  define DOWN_ARW				65364
#  define A_KEY					97
#  define W_KEY				119
#  define S_KEY					115
#  define D_KEY					100
#  define ESC					65307
# endif

/*____ PARSING ____ */
int	ft_isok_len(char **map);
int	ft_isok_char(char **map);
int	ft_nb_line(char *filename);
char	**ft_clean_map(int argc, char **argv);
int	ft_check_walls(char **map);
char	**ft_new_map(char *filename, int nb_line);
char	**ft_remove_n(char **map);

/*_____ UTILS __________*/
void	ft_free_map(char **map);

#endif
