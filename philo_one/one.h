/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:14:39 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/09 11:21:39 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h> // usleep, write
#include <stdlib.h> //malloc
#include <string.h> // memset
#include "stdio.h" // printf

typedef struct  s_options
{
    int             identifier;
    int             num_philo;
    int             t_to_die;
    int             t_to_eat;
    int             t_to_sleep;
    int             eat_max;
    long int        latest_meal; //  timestamp du dernier repas
    long int        timestamp_start; // timestamp debut simulation
    int             *eat_num; // tableau qui contient le nombre de repas pris par chaque philo
    int             *stop_all; // signal pour les threads qu'il faut exit (un int partagé par l'ensemble des threads)
    pthread_mutex_t *fork_l; // fourchette gauche: pointeur sur une des fourchettes
    pthread_mutex_t *fork_r; // fourchette à droite: pointeur sur une des fourchettes
    pthread_mutex_t *display; // pointeur sur le mutex qui gère l'affichage à l'écran
}               t_options;

typedef struct  s_input
{
    pthread_t       *threads_philo;
    pthread_mutex_t *forks;
    pthread_mutex_t display;
    int             *eat_num;
    int             stop_all;
}               t_input;

enum	e_state
{
	FORK,
    EAT,
	SLEEP,
	THINK,
	DIE
};

#define UNSET -1
#define YES 1
#define NO 0

/*
** ---------------------- Philo prototypes ---------------------
*/

int     init(int num_philo, t_options **options, t_options *input);
int     init_mutexes(int num, t_input *input);
int     fill_vars(int num, t_input *input);
int     create_threads(t_input *input, t_options **options, int num_philo);
int     create_death_thread(t_options *options);

void	fill_options_args(t_options **options, char **argv, t_input *input);
int     malloc_options(t_options ***options, int num);
void	fill_options_mutexes(t_options **options, t_input *input);

long    ft_get_mstime();

void	*cycle(void *void_options);
void	*stop(void *void_options);

int     ft_print_status(int status, t_options *options);
int		lock_forks(t_options *options);
int		unlock_forks(t_options *options);

int     destroy_mutexes(int num, t_input *input);
void	free_stuff(t_options **options, t_input *input);
int     join_threads(int num, pthread_t *threads);

/*
** ---------------------- Libft prototypes ---------------------
*/

size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_itoa(long int nlong);
int     ft_isdigit_str(char *str);
