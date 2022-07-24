/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:30:57 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/24 14:23:29 by Cyrielle         ###   ########.fr       */
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
DIR			(x, y, z) in grid et map sys: (z vers ecran)	+------> x
NORTH	=	(0, 0, +1);										|
SOUTH	=	(0, 0, -1);										|
WEST	=	(-1, 0, 0);										|
EAST	=	(+1, 0, 0);										V y
*/

/* Type de l'element touche par le rayon: wall (vertical/horizontal), sprite, door*/
typedef enum e_element_type {apex, vline, vwall, hline, hwall, sprite, door} t_type;
typedef enum e_orientation {south = 'S', north = 'N', west = 'W', east = 'E'} t_orientation;
enum e_sys_ids {view, grid, map, sys_ids_size}; // nom des reperes; a rajouter si besoin d'un nouveau systeme (avant la size);

typedef struct s_coord
{
	double				x;
	double				y;
	double				z;
}				t_pos, t_dir, t_vec;	// permet d'exprimer soit une position, soit un vecteur de direction dans un systeme donne. ATTENTION une dir ne peut prendre que des valeurs entre -1 et 1 compris

typedef struct s_hit_point
{
	t_pos	pos[sys_ids_size];
	t_type	type;				// soit vertical soit horizontal wall/line; useless?
	double	dist;				// distance en grid unit entre le player (ou 
								// centre rayon c'est pareil) et le hitpoint. 
								// C'est CA qui permet de determiner combien de 
								// pixels de haut on va print sur l'ecran du game.
}				t_hit_point;

typedef struct s_ray
{
	t_pos	pos[sys_ids_size];
	t_dir	dir[sys_ids_size];
	double	stepX;		// longueur pour first vertical wall
	double	stepY;		// longueur, en grid unit, a faire sur le ray pour 
						// toucher le premier horizontal wall
	t_hit_point	hit_point;	// point qui touche une ligne, et a la fin du
							// calcul un wall
// Seul veritable truc qui nous interesse: la longueur du ray jusquau premier mur!
// Donc en vrai les hitpoints on s'en fou un peu. On veut juste le premier "bon"
// hit_point, et du coup en deduire la longueur: sqrt(pow2x + pow2y)
	double	len_to_wall;		// 'till wall touched. en grid unit
}				t_ray;

typedef struct s_player
{
	double			fov;	// player filed of view in RADIANS;
	double	dist_screen;	// distance between screen and player view 
							// (fonction du FOV);
	t_pos			pos;	// position du jouer, dans systeme de map
	t_dir			dir;	// orientation du joueur, N/S/W/E, en sys map & grid;
//	double			angle;	// son orientation (en radian) par rapport au 
							// repre de la map
	double			rot_speed;	// angle (en radian) increment pour une 
								// pression touche droite ou gauche
	double			mv_speed;	// inc (en map unit) pour le deplacement du jouer
	t_ray			*rays;	// tableau de rays;
}				t_player;

typedef struct s_img
{
	void	*ptr;		// ptr returned by mlx_new_img
	unsigned int		width; // en nombre de pixels (+1 par rapport a sa win?)
	unsigned int		height;	// en nombre de pixels (+1/win?)
	int		*data;		// filled by mlx_get_data_addr(); !!! Casted en int *
						// au lieu de char *. Contient les bits de pixels;
	int		bpp;		// bits per pixel also called the depth of the image
	int		size_line;	// number of bytes used to store one line of the image in memor
	int		endian;		// little == 0; big endian == 1;
}				t_texture, t_img;

typedef struct s_map	// AFFICHAGE DE LA MINIMAP
{
	char	**tab;	// tableau retourne par le parsing de fichier .cub
	int		width;	// nb de colonnes du tab
	int		height;	// nb de lignes du tab
	void	*win;	// window dans laquelle afficher la map
	t_img	img;	// image a remplir pour afficher mini map et rays. 
					// Prend toute la window.
	t_img	grid;	// img avec que la grille de remplit: permet d'eviter
					// de recalculer les pixels pour wall etc a chaque frame
}			t_map;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win;		// Window dans laquelle afficher le jeu
	int			width;		// taille de la window en pixels
	int			height;		// taille de la window en pixels
	int			cube_size;	// taille des murs en pixels
	t_img		img;		// image du jeu
	t_player	player;
	t_map		map;		// Tout ce qui est pour afficher la map
	t_texture	*text;		// tableau d'au moins 4 texture (Nord, Sud, Est, Ouest);
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
int	ft_exit(t_game *game);

/* ______ INITIALISATIONS ____ */
int	init_player(t_game *game);
int	init_game(t_game *game, int argc, char **argv);
int	init_map(t_game *game, int argc, char **argv);

/*_____ UTILS __________*/
void	ft_free_map(char **map);

/* ____ TEXTURE (tests)______*/
void	put_texture_origin(unsigned int x, unsigned int y, t_img *screen, t_texture *text);
void	put_sized_texture(unsigned int width, unsigned int height, t_img *screen, t_texture *text);

/*______ IMG UTILS _______ */
void	cpy_img_pixels(t_img from, t_img to);
void	draw_square(t_game *game, t_pos origin, int size, int color);

/* ______ MAP DRAWING ______ */
void	fill_cube(t_game *game, int y, int x, int color);
void	draw_grid(t_game *game);
void	draw_walls(t_game *game);
void	draw_map(t_game *game);
void	draw_player(t_game *game);

/*_______ COLISION _______*/
bool	check_for_colision(t_game *game, int keycode);

/* _________ RAYCASTING ________ */
t_ray	get_mid_ray(t_game *game);
void	raycasting(t_game *game);
bool	check_hit_point_is_wall(t_game *game, t_ray ray);

/* _________ VECTORS UTILS _______*/
struct s_coord	rotate_vector_angle(struct s_coord from, double angle);

/*__________ RAYTRACING (DEBUG) _______*/
void	draw_ray_until_first_Hline(t_game *game, t_ray ray, int color);
void	draw_ray_until_first_Vline(t_game *game, t_ray ray, int color);
void	draw_ray(t_game *game, t_ray ray, int color);

/* _____________ TESTS (DEBUG) __________ */
void	ray_tests(t_game *game);

#endif
