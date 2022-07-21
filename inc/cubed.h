/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:30:57 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/21 18:26:57 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "colors.h"
# include "mlx.h"
# include <fcntl.h>
# include "libft.h"
# include <stdbool.h>
# include <math.h>
# include <stdio.h>

# ifndef SCREEN_W
#  define PI 3.142857
# endif

# ifndef SCREEN_W
#  define SCREEN_W 320
# endif
# ifndef SCREEN_H
#  define SCREEN_H 200
# endif

# ifndef CUBE_SIZE
#  define CUBE_SIZE 64
# endif

# ifndef VIEW_HEIGHT
#  define VIEW_HEIGHT 32 // hauteur du point de vue (du player). En general 1/2 
# endif
/*
DIR			(x, y, z) in view et screen sys: (z vers ecran)	+------> x
NORTH	=	(0, 0, +1);										|
SOUTH	=	(0, 0, -1);										|
WEST	=	(-1, 0, 0);										|
EAST	=	(+1, 0, 0);										V y
*/
typedef enum e_orientation {south, north, west, east} t_orientation;
enum e_sys_ids {view, grid, map, sys_ids_size}; // nom des reperes; a rajouter si besoin d'un nouveau systeme;

typedef struct s_coord
{
	double				x;
	double				y;
	double				z;
}				t_pos, t_dir, t_vec;	// per;et d'exprimer soit une position, soit un vecteur de direction dans un systeme donne. ATTENTIONun dir ne peut prendre que des valeurs entre -1 et 1 compris

typedef struct s_ray
{
	t_pos	pos[sys_ids_size];
	t_dir	dir[sys_ids_size];
	t_pos	hit_point[sys_ids_size];
	double	length;		// en grid unit
}				t_ray;

typedef struct s_img
{
	void	*ptr;
	int		*data;		// filled by mlx_get_data_addr(); !!! Casted en int * au lieu de char *. Contient les bits de pixels;
	unsigned int		width;
	unsigned int		height;
	int		bpp;		// bits per pixel also called the depth of the image
	int		size_line;	// number of bytes used to store one line of the image in memor
	int		endian;		// little == 0; big endian == 1;
}				t_texture, t_screen;

typedef struct s_player
{
	double			fov;			// player filed of view in RADIANS;
	double	dist_screen;	// distance between screen and player view (fonction du FOV);
	t_pos			pos;			// position du jouer, dans systeme de map
	t_dir			dir;			// orientation du joueur, N/S/W/E;
	double			rot;			// rotation par rapport au sys grid, en radian
}				t_player;

typedef struct s_map
{
	char		**tab;
	int			width;
	int			height;
	void		*win;	// window pour afficher la grid avec les lignes et les rays
	t_screen	img;	// image pour la window map representation
}				t_map;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			width;
	int			height;
	int			cube_size;
	t_player	player;
	t_dir		plane;		// vecteur plan, ds le systeme grid
	t_screen	screen;		// de la taille de la win, image a remplir de pixels de texture selon calculs 
	t_texture	*text;		// tableau d'au moins 4 texture (Nord, Sud, Est, Ouest);
	char		*title;
	t_map		map;
}				t_game;

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

/*_____ MLX MANAGE __________*/
int	key_hook(int keycode, void *param);
int	init_mlx(t_game *game);
int	ft_exit(t_game *game);

/*_____ UTILS __________*/
void	ft_free_map(char **map);

/* ____ TEXTURE (tests)______*/
void	put_texture_origin(unsigned int x, unsigned int y, t_screen *screen, t_texture *text);
void	put_sized_texture(unsigned int width, unsigned int height, t_screen *screen, t_texture *text);

/* ______ MAP DRAWING ______ */
void	fill_cube(t_game *game, int y, int x, int color);
void	draw_grid(t_game *game);
void	draw_walls(t_game *game);
void	draw_player(t_game *game);
int		draw_map(t_game *game);

/* _________ RAYCASTING ________ */
t_ray	get_mid_ray(t_game *game);
t_ray*	raycasting(t_game *game);
void	draw_ray_until_first_Vline(t_game *game, t_ray ray, int color);
void	draw_ray(t_game *game, t_ray ray, int color);
struct s_coord	rotate_vector_angle(struct s_coord from, double angle);

#endif
