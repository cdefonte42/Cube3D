/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:30:57 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/10/04 15:05:02 by cdefonte         ###   ########.fr       */
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

# ifndef PI
#  ifndef M_PI
#   define PI 3.14159265358979323846
#  else
#   define PI M_PI
#  endif
# endif

# if !BONUS
#  define BONUS 0
# endif

# ifndef LEAK
#  define LEAK 0
# endif

# ifndef SCREEN_W
#  define SCREEN_W 1280
# endif
# ifndef SCREEN_H
#  define SCREEN_H 720
# endif

# ifndef CUBE_SIZE
#  define CUBE_SIZE 64
# endif

# define COINS_NB 10

# define PLAYERS_NB 4

/*
DIR			(x, y, z) in grid et map sys: (z vers ecran)	+------> x
NORTH	=	(0, -1, 0);										|
SOUTH	=	(0, 1, 0);										|
WEST	=	(-1, 0, 0);										|
EAST	=	(+1, 0, 0);										V y
*/

/* Type de l'element touche par le rayon: wall (vertical/horizontal), 
sprite, door etc.. ATTENTION "nb_textures" a un emplacement important: il
determine la taille d'allocation du tableau de texures (pour l'instant que les
murs de texturises, plus tard si bonus portes et sprites il faudra les deplacer
avant nb_textures). */
typedef enum e_element_type
{
	wwall,
	ewall,
	nwall,
	swall,
	door,
	nb_textures,
	sprite,
	hline,
	vline,
	apex,
}			t_type;

typedef enum e_orientation
{
	south = 'S',
	north = 'N',
	west = 'W',
	east = 'E'
}			t_orientation;

/*	Nom des reperes; a rajouter si besoin d'un nouveau systeme (avant la size)*/
enum e_sys_ids {view, grid, map, sys_ids_size};
# define SYS_IDS_SIZE 3  

typedef enum e_type_sprites
{
	player,
	coin,
}			t_sp_type;

/* Enum pour une paire de int (int[2]) avec interval inf index 0 etc. */
typedef struct s_interval
{
	int	inf;
	int	sup;
}				t_interval;

// z[view]=0 z[map]=0.5 et z[grid] = 1/2 * cube_size
// permet d'exprimer soit une position, soit un vecteur de direction dans
// un systeme donne. ATTENTION une dir ne peut prendre que des valeurs
// entre -1 et 1 compris
struct s_coord
{
	double	x;
	double	y;
	double	z;
};

typedef struct s_coord	t_pos;
typedef struct s_coord	t_dir;

// type soit vertical soit horizontal wall/line; useless?
// distance en grid unit entre le player (ou 
// centre rayon c'est pareil) et le hitpoint. 
// C'est CA qui permet de determiner combien de 
// pixels de haut on va print sur l'ecran du game.
typedef struct s_hit_point
{
	t_pos	pos[SYS_IDS_SIZE];
	t_type	type;
	double	dist;
}				t_hit_point;

// step_x: longueur pour first vertical wall
// step_y: longueur, en grid unit, a faire sur le ray pour 
// toucher le premier horizontal wall
// hit_point: point qui touche une ligne, et a la fin du calcul un wall
// angle (en radian): representant la rotation du ray
							// par rapport a la VIEW, cad angle entre ce ray et
							// le "ray du mid"
typedef struct s_ray
{
	t_pos		pos[SYS_IDS_SIZE];
	t_dir		dir[SYS_IDS_SIZE];
	double		step_x;
	double		step_y;
	t_hit_point	hit_point;
	double		angle;
}				t_ray;

typedef struct s_keyboard
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	shift;
	bool	left;
	bool	right;
	bool	mouse;
}			t_keyboard;

/*
	fov:			player field of view (en radian)
	dist_screen:	distance in grid unit between camera plane/screen and player
	pos:			player position, en map unit
	dir:			orientation du joueur, par rapport aux map et grid systemes
	rot_speed:		angle effectue pour 1 pression fleche droite/gauche (radian)
	mv_speed:		incrementation en map unit pour deplacement
	rays:			tableau de rays
*/
typedef struct s_player
{
	double			fov;
	double			dist_screen;
	t_pos			pos;
	t_dir			dir;
	double			rot_speed;
	double			mv_speed;
	t_ray			*rays;
	t_keyboard		keyboard;
}				t_player;

/* Structure contenant toutes les donnees d'une image mlx: 
	ptr		:	pointeur retourne par mlx_new_img() ou mlx_xpm_file_to_image().
	width	:	en nombre de pixels (+1 par rapport a sa win?)
	height	:	en nombre de pixels (+1/win?)
	data	:	filled by mlx_get_data_addr(); !!! Casted en int * au lieu de 
				char *. Contient les bits de pixels;
	bpp		:	bits per pixel also called the depth of the image
    :x
	endian		: little == 0; big endian == 1;
NOTE: Peut etre ajouter un char *filename? Ne serait utile que pour les textures
*/
struct s_img
{
	void	*ptr;
	int		width;
	int		height;
	int		*data;
	int		bpp;
	int		size_line;
	int		endian;
	char	*path;
};
typedef struct s_img	t_img;
typedef struct s_img	t_texture;

/*
	AFFICHAGE DE LA MINIMAP
char	**tab	// tableau retourne par le parsing de fichier .cub
int 	width	// nb de colonnes du tab
int 	height	// nb de lignes du tab
t_img	img		// image a remplir pour afficher map et rays. 
				// Prend toute la window.
t_img	grid	// img avec que la grille de remplit: permet d'eviter
				// de recalculer les pixels pour wall etc a chaque frame
double	ratio	// Taille des cubes de la map par rapport aux vrais cubes
				// Permet de reduire taille de la map
int 	rcube_size
bool	state	// Permet de cacher / afficher si on / off la grde map
*/
typedef struct s_map
{
	char	**tab;
	int		width;
	int		height;
	t_img	img;
	t_img	grid;
	double	ratio;
	int		rcube_size;
	bool	state;
}			t_map;

typedef struct s_sprite
{
	t_pos		pos;
	double		dist;
	int			screen_size;
	double		dir;
	t_sp_type	type;
	int			anim_id;
	int			anim_size;
}				t_sprite;

typedef struct s_bonus
{
	int			sock;
	fd_set		rdfs;
	char		*buf;

	t_sprite	*sps;
	t_texture	text_sp[2][COINS_NB];
	int			nb_sp;
	int			*sort_sp;
}				t_bonus;

/*
	win;		// Window dans laquelle afficher le jeu
	width;		// taille de la window en pixels
	height;		// taille de la window en pixels
	cube_size;	// taille des murs en pixels
	img;		// image du jeu
	player;
	map;		// Tout ce qui est pour afficher la map
	minimap;	// Copie de map mais en mini: centre sur le 
				// joueur. A une taille de fenetre maxi!
	*text;		// tableau d'au moins 4 texture (Nord, Sud, Est, Ouest);
	colision;	// distance max en map unit a laquelle le player
				// peut s'approcher des murss
*/
typedef struct s_game
{
	void		*mlx_ptr;
	void		*win;
	int			width;
	int			height;	
	int			cube_size;
	t_img		img;
	t_player	player;
	t_map		map;
	t_img		minimap;
	t_texture	*text;
	double		colision;
	int			floor_color;
	int			ceiling_color;

	t_bonus		bonus;

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
#  define SPACE 			49
#  define TAB				48

# else
#  define L_ARW				65361
#  define R_ARW				65363
#  define UP_ARW			65362
#  define DOWN_ARW			65364
#  define A_KEY				97
#  define W_KEY				119
#  define S_KEY				115
#  define D_KEY				100
#  define ESC				65307
#  define TAB				0xff09
#  define SPACE				0x0020
#  define SHIFT				0xffe1
# endif

/*____ PARSING ____ */
int		ft_isok_len(char **map);
int		ft_isok_char(char **map);
int		ft_nb_line(char *filename);
char	**ft_clean_map(char **argv);
int		ft_check_walls(char **map);
char	**ft_new_map(char *filename, int nb_line);
char	**ft_remove_n(char **map);

/*_____ MLX MANAGE __________*/
int		key_hook(int keycode, void *param);
int		tab_hook(int keycode, void *param);
void	refresh_game(t_game *game);

/* ______ INITIALISATIONS ____ */
int		init_player(t_game *game);
int		init_game(t_game *game, char **argv);

/*_____ UTILS __________*/
void	ft_free_map(char **map);
void	ft_free_map_i(char **map, int height);
int		ft_exit(t_game *game);
void	exit_bonus(t_game *game);

/*______ IMG UTILS _______ */
void	cpy_img_pixels(t_img from, t_img to);
void	draw_player(t_game *game);

/* __________ DISPLAY GAME ________ */
void	draw_game(t_game *game);

/* ______ MAP DRAWING ______ */
void	fill_cube_grid(t_game *game, int y, int x, int color);
void	draw_grid_walls(t_game *game);
void	draw_map(t_game *game);
void	draw_minimap(t_game *game);

/*_______ COLISION _______*/
void	back_front_mvx(t_game *game, int keycode, double limit);
void	back_front_mvy(t_game *game, int keycode, double limit);
void	stepaside_mvx(t_game *game, int keycode, double limit);
void	stepaside_mvy(t_game *game, int keycode, double limit);

/* _________ RAYCASTING ________ */
t_ray	get_mid_ray(t_game *game);
void	raycasting(t_game *game);
void	set_ray_steps(t_game *game, t_ray *ray);

/*____________ HIT POINTS CALCULS _______*/
void	set_wall_hit_point(t_game *game, t_ray *ray);
void	set_htpt_dist(t_ray *ray);
void	next_hit_point(t_ray *ray);

/*____________ HIT POINTS UTILS _______*/
bool	check_hit_point_is_wall(t_game *game, t_ray ray);
bool	check_hit_point_is_door(t_game *game, t_ray ray);

/* _________ VECTORS UTILS _______*/
t_pos	rotate_vector(struct s_coord from, double angle);

/*__________ RAYTRACING (DEBUG) _______*/
void	draw_all_rays(t_game *game);

/* ____ TEXTURE (tests)______*/
void	draw_buff_texture(t_game *game, int col_screen, t_interval interval, \
double hpwall);

/* ____ PARSING ______*/
bool	error(char *str, const char *n);
bool	map_parsing(t_game *game, char *str);

/*			UTILS 		 */
bool	cb_load_mlx_image(void *mlx_ptr, char *path, t_texture *texture);

/* 			FOG			*/

/* Applied black by dist */
int		fog_texture(int texture_color, float dist);
/* Applied black by percentage */
int		fog_percentage(int color, double percentage);

/*______ TEXTURE UTILS ________ */
bool	cb_load_mlx_image(void *mlx_ptr, char *path, t_texture *texture);
void	revert_texture(t_game *game, int i);
void	cb_put_pixel(t_img *data, int x, int y, int color);

/* 			BONUS		*/

void	handle_use_key(t_game *game);

/*_____ INIT MAP BONUS __________*/
int		init_minimap(t_game *game);
int		init_map(t_game *game);

/* ______ Init bonus ____*/
bool	init_sprites_text(t_game *game);
/* _____ Parsing bonus ____*/
void	count_sprite(t_game *game, char *line);
bool	init_sprite(t_game *game);
/* _____ Draw bonus ____*/
bool	init_texture_door(t_game *game);

int		draw_sprites_bonus(t_game *game);
void	draw_sprite(t_game *game, t_sprite *sprite, double angle);
void	set_sprites_datas(t_game *game, double angle);
void	sort_sprites(t_game *game);
#endif
