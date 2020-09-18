/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:14:39 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/18 10:14:44 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ONE_H
# define ONE_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "stdio.h"

typedef struct	s_options
{
	int				identifier;
	int				num_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				eat_max;
	long int		latest_meal;
	long int		timestamp_start;
	int				*eat_num;
	int				count_right;
	int				count_left;
	int				*stop_all;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*display;
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
# define T_SLEEP 500
# define T_CHECK_DEATH 2000
# define T_CHECK_PRIO 200

/*
** ---------------------- Main prototypes ---------------------
*/

int				init_input(int num_philo, t_input **input);
int				init_options(t_options ***opt, char **av, t_input *in, int n);

int				create_threads(t_input *input, t_options **options, int num);
int				create_death_thread(t_options **options);

int				destroy_mutexes(int num, t_input *input);
void			free_stuff(t_options **options, t_input *input);
int				join_threads(int num, pthread_t *threads);

/*
** ---------------------- Thread prototypes ---------------------
*/

void			*cycle(void *void_options);
void			*stop(void *void_options);

void			lock_forks(t_options *options);
void			unlock_forks(t_options *options);
void			ft_print_status(int status, t_options *options);
void			check_stop(t_options *options, int status);

long			ft_get_mstime();
void			ft_wait(int delay_ms, int *stop_all);
int				get_right_index(t_options *options);
int				get_left_index(t_options *options);

/*
** ---------------------- Libft prototypes ---------------------
*/

size_t			ft_strlen(const char *s);
int				ft_atoi(const char *str);
void			ft_putendl_fd(char *s, int fd);
void			ft_putstr_fd(char *s, int fd);
char			*ft_itoa(long int nlong);
int				ft_isdigit_str(char *str);
void			ft_strjoin_back(char *back, char **src);

#endif
