/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:14:39 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/04 12:35:40 by bbrunet          ###   ########.fr       */
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
    int             t_to_die;
    int             t_to_eat;
    int             t_to_sleep;
    int             num_of_time;
    long int        latest_meal; //  timestamp du dernier repas
    long int        timestamp_start; // timestamp debut simulation
    int             died; // booléen: YES or NO
    int             eat_num;
    int             stop_all; // signal pour les threads qu'il faut exit
    pthread_mutex_t *fork_l; // fourchette gauche: pointeur sur une des fourchettes
    pthread_mutex_t *fork_r; // fourchette à droite: pointeur sur une des fourchettes
    pthread_mutex_t *display; // pointeur sur le mutex qui gère l'affichage à l'écran
}               t_options;

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

int     init_mutexes(int num, pthread_mutex_t **fork, pthread_mutex_t *display);
int     create_threads(pthread_t **thread, pthread_t *thread_stop, t_options **options, int num_philo);
int     create_death_thread(t_options *options);

void	fill_options_args(t_options **options, int argc, char **argv);
int     malloc_options(t_options ***options, int num);
void	fill_options_mutexes(t_options **options, pthread_mutex_t *display, pthread_mutex_t *fork, int num);

long    ft_get_mstime();

void	*cycle(void *void_options);
void	*stop(void *void_options);

void    ft_print_status(int status, t_options *options);
int		lock_forks(t_options *options);
int		unlock_forks(t_options *options);

int     destroy_mutexes(int num, pthread_mutex_t *forks, pthread_mutex_t lock);
void	free_options(int num, t_options **options);
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
