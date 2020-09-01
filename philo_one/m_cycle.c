/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cycle.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 18:19:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/01 15:52:25 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	ft_print_status(int status, int id, pthread_mutex_t *display)
{
	struct timeval current_t;
	char *timestamp;
	char *identifier;
	
	pthread_mutex_lock(display); // partie locked pour que les threads n'affichent pas les statuts en meme temps
	
	gettimeofday(&current_t, NULL);
	timestamp = ft_itoa((long)(current_t.tv_sec * 1000 + current_t.tv_usec / 1000));
	// timestamp = ft_itoa((long)(current_t.tv_usec / 1000));
	ft_putstr_fd(timestamp, 1);
	free(timestamp);
	
	ft_putstr_fd(" ", 1);
	identifier = ft_itoa((long)id);
	ft_putstr_fd(identifier, 1);
	free(identifier);
	
	if (status == EAT)
		ft_putendl_fd(" is EATING !", 1);
	if (status == SLEEP)
		ft_putendl_fd(" is sleeping", 1);
	if (status == THINK)
		ft_putendl_fd(" is thinking", 1);
	if (status == FORK)
		ft_putendl_fd(" has taken a fork", 1);
	if (status == DIE)
		ft_putendl_fd(" died", 1);
	
	pthread_mutex_unlock(display);
}

void	*cycle(void *void_options)
{
	// struct timeval current_t;
	t_options	*options;
	int count_eat;
	// long int	timestart;
	// long int	timestamp;
	// long int	counter;
	
	options = (t_options*)void_options;
	count_eat = 0;
	// counter = 0;
	// gettimeofday(&current_t, NULL);
	// timestart = (long)(current_t.tv_sec * 1000 + current_t.tv_usec / 1000);
	
	while (options->num_of_time == UNSET || count_eat < options->num_of_time) // si num_of_time n'est pas donné, on boucle a l'infini
	{
		// LOCK FORKS
		if (options->identifier % 2 == 0) // pour eviter que tous les philo se jettent en premier sur leur fourchette droite, ce qui cause un deadlock: chaque philo a une fourchette dans la main, qu'il ne libère jamais 
		{
			if (pthread_mutex_lock(options->fork_l))
				printf("error lock\n");
		}
		else
		{
			if (pthread_mutex_lock(options->fork_r))
				printf("error lock\n");
		}
		ft_print_status(FORK, options->identifier, options->display);
		
		if (options->identifier % 2 == 0)
		{
			if (pthread_mutex_lock(options->fork_r))
				printf("error lock\n");
		}
		else
		{
			if (pthread_mutex_lock(options->fork_l))
				printf("error lock\n");
		}
		ft_print_status(FORK, options->identifier, options->display);
		
		// EAT
		ft_print_status(EAT, options->identifier, options->display);
		count_eat++;
		// timestamp = 0;
		usleep(options->t_to_eat * 1000);	
		
		// UNLOCK FORKS
		if (pthread_mutex_unlock(options->fork_l))
			printf("error unlock\n");
		if (pthread_mutex_unlock(options->fork_r))
			printf("error unlock\n");
		
		// SLEEP
		ft_print_status(SLEEP, options->identifier, options->display);
		usleep(options->t_to_sleep * 1000);	
		
		//THINK
		ft_print_status(THINK, options->identifier, options->display);
	}
	return (NULL);
}