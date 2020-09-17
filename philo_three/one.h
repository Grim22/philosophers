/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:14:39 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/17 15:45:38 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ONE_H
# define ONE_H

# include <pthread.h>
# include <errno.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>
# include <unistd.h> // usleep, write
# include <stdlib.h> //malloc
# include <string.h> // memset
# include "stdio.h" // printf
# include <fcntl.h> // for sem_open flags
# include <sys/stat.h> // for sem_open modes

/*
** Options is the argument given to every philosopher thread
** Stop_all is a pointer on an int shared by all threads.
**	When int value is YES, all threads stop
** Eat_num is an array of int. It is shared by all threads.
**	Eat_num[i] represents the number of time philo i has eaten
** Semaphores prio are shared between a philo and his neighbours
** Semaphore display is shared by all philosophers
** Latest_meal and timestamp_start are timestamps
*/

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
	int				stop_process;
	sem_t			*prio_left;
	sem_t			*prio;
	sem_t			*prio_right;
	sem_t			*display;
	sem_t			*eat_total;
}				t_options;

/*
** T_PRIORITY contains a semaphore and the name of this semaphore
** We need to keep the name stored somewhere in order to unlink the semaphore,
**	at the end of the programm
*/

typedef struct	s_priority
{
	char	*name;
	sem_t	*lock;
}				t_priority;

/*
** Input contains:
** 	- an array of pthread_t (one thread for each philo)
**	- some variables that will be shared among philosophers
** In main, input is first initialised, then it is used to fill t_options
*/

typedef struct	s_input
{
	sem_t			*display;
	sem_t			*eat_total;
	t_priority		*prio;
	pid_t			*pid_tab;
}				t_input;

enum	e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
};

/*
** T_SLEEP: every T_SLEEP ms, program will check
**	if it has been on hold for enough time
** Used in ft_sleep, that replaces usleep:
**	as usleep(time) sometimes sleeps more thant "time", ft_sleep is more precise
** The smaller T_SLEEP is, the better
**	in terms of precisions = programm will not run "late"
** Yes the smaller T_SLEEP, the more expensive it is in terms of CPU load
** T_CHECK_DEATH: interval at which thread_death will check
**	if any philo has died.
** Small interval: better precision but more expensive in terms of CPU
*/

# define UNSET -1
# define YES 1
# define NO 0
# define ODD 0
# define EVEN 1
# define T_SLEEP 500
# define T_CHECK_DEATH 2000

/*
** ---------------------- Main prototypes ---------------------
*/

int				init_input(int num_philo, t_input **input, char *eat_max);
int				init_options(t_options ***op, char **av, t_input *in, int n);
int				init_sem_display(int num, t_input *input);
int				init_sem_eat(int num, t_input *input, char *eat_max);
int				init_sem_prio(int num, t_input *input);

int				create_death_thread(t_options *options);

int				destroy_sem(t_input *input, int num);
void			free_stuff(t_options **options, t_input *input, int num);
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
void			ft_wait(int delay_ms, int stop_all);

/*
** ---------------------- Libft prototypes ---------------------
*/

size_t			ft_strlen(const char *s);
int				ft_atoi(const char *str);
void			ft_putendl_fd(char *s, int fd);
void			ft_putstr_fd(char *s, int fd);
char			*ft_itoa(long int nlong);
int				ft_isdigit_str(char *str);

#endif
