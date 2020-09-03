/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 18:19:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/03 14:31:42 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		unlock_forks(t_options *options)
{
	if (pthread_mutex_unlock(options->fork_l))
	{
		ft_putendl_fd("unlock failed", 2);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_unlock(options->fork_r))
	{
		ft_putendl_fd("unlock failed", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		lock_forks_even(t_options *options)
{
	if (pthread_mutex_lock(options->fork_l) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_print_status(FORK, options);
	if (pthread_mutex_lock(options->fork_r) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_print_status(FORK, options);
	return (EXIT_SUCCESS);
}

int		lock_forks_odd(t_options *options)
{
	if (pthread_mutex_lock(options->fork_r) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_print_status(FORK, options);
	if (pthread_mutex_lock(options->fork_l) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_print_status(FORK, options);
	return (EXIT_SUCCESS);
}

int		lock_forks(t_options *options)
{
	if (options->identifier % 2 == 0)
	{
		if (lock_forks_even(options) == EXIT_FAILURE)
		{
			ft_putendl_fd("lock failed", 2);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (lock_forks_odd(options) == EXIT_FAILURE)
		{
			ft_putendl_fd("lock failed", 2);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

void	check_eat_number(int *counter, t_options *options)
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
		if (lock_forks(options) == EXIT_FAILURE)
			return (NULL);
		options->latest_meal = ft_get_mstime();
		ft_print_status(EAT, options);
		check_eat_number(&count_eat, options);
		usleep(options->t_to_eat * 1000);	
		if (unlock_forks(options) == EXIT_FAILURE)
			return (NULL);
		ft_print_status(SLEEP, options);
		usleep(options->t_to_sleep * 1000);	
		ft_print_status(THINK, options);
	}
	return (NULL);
}