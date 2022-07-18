/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:30:57 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/18 16:12:21 by cdefonte         ###   ########.fr       */
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
// DIR			(x, y, z) in view et screen sys: (z vers ecran)	+------> x
// NORTH	=	(0, 0, +1);										|
// SOUTH	=	(0, 0, -1);										|
// WEST		=	(-1, 0, 0);										|
// EAST		=	(+1, 0, 0);										V y
typedef enum e_dir {south, north, west, east} t_dir;
typedef enum e_coord {x, y, z} t_coord;
enum e_sys_ids {screen, view, pixels, grid}; // nom des reperes; a rajouter si besoin d'un nouveau systeme;

typedef struct s_coord
{
	int				x;
	int				y;
	int				z;
	enum e_sysids	sys_id;		// identifie dans quel systeme de coordonnees les x,y et z sont exprimees;
}				t_pos, t_dir;	// permet d'exprimer une position, ou un vecteur unitaire de direction;

typedef struct s_img
{
	void	*ptr;
	int		*data;
	unsigned int		width;
	unsigned int		height;
	int		bpp;		// bits per pixel also called the depth of the image
	int		size_line;	// number of bytes used to store one line of the image in memor
	int		endian;		// little == 0; big endian == 1;
}				t_texture, t_screen;

typedef struct s_player
{
	unsigned int	fov;			// player filed of view in RADIANS;
	unsigned int	dist_screen;	// distance between screen and player view (fonction du FOV);
	t_pos			pos;			// position du jouer, dans systeme de grid?;
	t_dir			dir;			// orientation du joueur, N/S/W/E;
}				t_player;

typedef struct s_win
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			width;
	int			height;
	t_screen	screen;		// de la taille de la win, image a remplir de pixels de texture selon calculs 
	t_texture	*text;		// tableau d'au moins 4 texture (Nord, Sud, Est, Ouest);
	char		*title;
	char		**map;
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
