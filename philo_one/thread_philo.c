/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 18:19:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/03 12:14:33 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	unlock_forks(t_options *options)
{
		if (pthread_mutex_unlock(options->fork_l))
			printf("error unlock\n");
		if (pthread_mutex_unlock(options->fork_r))
			printf("error unlock\n");
}

void	lock_forks(t_options *options)
{
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
		ft_print_status(FORK, options);
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
		ft_print_status(FORK, options);
}

void		check_eat_number(int *counter, t_options *options)
{
	if (options->num_of_time == UNSET)
		return ;
	(*counter)++;
	if (*counter >= options->num_of_time)
		options->enough_food = YES;
}

void	*cycle(void *void_options)
{
	t_options	*options;
	int			count_eat;
	
	options = (t_options*)void_options;
	count_eat = 0;
	if (create_death_thread(options) == EXIT_FAILURE)
		return (NULL);
	while (1)
	{
		lock_forks(options);
		options->latest_meal = ft_get_mstime();
		ft_print_status(EAT, options);
		check_eat_number(&count_eat, options);
		usleep(options->t_to_eat * 1000);	
		unlock_forks(options);
		ft_print_status(SLEEP, options);
		usleep(options->t_to_sleep * 1000);	
		ft_print_status(THINK, options);
	}
	return (NULL);
}