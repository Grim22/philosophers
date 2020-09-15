/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:14:39 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/15 14:30:07 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ONE_H
# define ONE_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h> // usleep, write
# include <stdlib.h> //malloc
# include <string.h> // memset
# include "stdio.h" // printf

typedef struct	s_options
{
	int				identifier;
	int				num_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				eat_max;
	long int		latest_meal; //  timestamp du dernier repas
	long int		timestamp_start; // timestamp debut simulation
	int				*eat_num; // tableau qui contient le nombre de repas pris par chaque philo
	int				count_right; // après chaque repas du philosophe N, compte combien de repas a pris le philosophe N-1.
	int				count_left; // après chaque repas du philosophe N, compte combien de repas a pris le philosophe N+1.
	// permet de s'assurer que N-1 et N+1 aient bien pris un repas avant que ne N se resserve
	int				*stop_all; // signal pour les threads qu'il faut exit (un int partagé par l'ensemble des threads)
	pthread_mutex_t	*fork_l; // fourchette gauche: pointeur sur une des fourchettes
	pthread_mutex_t	*fork_r; // fourchette à droite: pointeur sur une des fourchettes
	pthread_mutex_t	*display; // pointeur sur le mutex qui gère l'affichage à l'écran
}				t_options;

typedef struct	s_input
{
	pthread_t		*threads_philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	display;
	int				*eat_num;
	int				stop_all;
}				t_input;

enum	e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
};

# define UNSET -1
# define YES 1
# define NO 0
# define ODD 0
# define EVEN 1

/*
** ---------------------- Main prototypes ---------------------
*/

int		init_input(int num_philo, t_input **input);
int		init_options(t_options ***opt, char **argv, t_input *in, int num);

int		create_threads(t_input *input, t_options **options, int num_philo);
int		create_death_thread(t_options **options);

int		destroy_mutexes(int num, t_input *input);
void	free_stuff(t_options **options, t_input *input);
int		join_threads(int num, pthread_t *threads);

/*
** ---------------------- Thread prototypes ---------------------
*/

void	*cycle(void *void_options);
void	*stop(void *void_options);

int		lock_forks(t_options *options);
int		unlock_forks(t_options *options);
int		ft_print_status(int status, t_options *options);
void	check_stop(t_options *options, int status);

long	ft_get_mstime();
void	ft_sleep(int delay_ms);
int		get_right_index(t_options *options);
int		get_left_index(t_options *options);

/*
** ---------------------- Libft prototypes ---------------------
*/

size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_itoa(long int nlong);
int		ft_isdigit_str(char *str);

#endif