/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo_forks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 18:04:34 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/09 09:29:27 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		unlock_forks(t_options *options)
{
	if (pthread_mutex_unlock(options->fork_l))
	{
		ft_putendl_fd("unlock fork failed", 2);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_unlock(options->fork_r))
	{
		ft_putendl_fd("unlock fork failed", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		lock_forks(t_options *options)
{
	if (pthread_mutex_lock(options->fork_l) == EXIT_FAILURE)
	{
		ft_putendl_fd("lock fork failed", 2);
		return (EXIT_FAILURE);
	}
	ft_print_status(FORK, options);
	if (pthread_mutex_lock(options->fork_r) == EXIT_FAILURE)
	{
		ft_putendl_fd("lock fork failed", 2);
		return (EXIT_FAILURE);
	}
	ft_print_status(FORK, options);
	return (EXIT_SUCCESS);
}

// int		lock_forks_odd(t_options *options)
// {
// 	if (pthread_mutex_lock(options->fork_r) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	ft_print_status(FORK, options);
// 	if (pthread_mutex_lock(options->fork_l) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	ft_print_status(FORK, options);
// 	return (EXIT_SUCCESS);
// }

// int		lock_forks(t_options *options)
// {
// 	if (options->identifier % 2 == 0)
// 	{
// 		if (lock_forks_even(options) == EXIT_FAILURE)
// 		{
// 			ft_putendl_fd("lock fork failed", 2);
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	else
// 	{
// 		if (lock_forks_odd(options) == EXIT_FAILURE)
// 		{
// 			ft_putendl_fd("lock fork failed", 2);
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	return (EXIT_SUCCESS);
// }
