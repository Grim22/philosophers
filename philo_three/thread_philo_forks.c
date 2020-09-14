/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo_forks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 18:04:34 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/11 17:57:05 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int	unlock_forks(t_options *options)
{
	if (sem_post(options->sem))
	{
		ft_putendl_fd("unlock fork failed", 2);
		return (EXIT_FAILURE);
	}
	if (sem_post(options->sem))
	{
		ft_putendl_fd("unlock fork failed", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	lock_forks(t_options *options)
{
	if (sem_wait(options->sem))
	{
		ft_putendl_fd("lock fork failed", 2);
		return (EXIT_FAILURE);
	}
	ft_print_status(FORK, options);
	if (sem_wait(options->sem))
	{
		ft_putendl_fd("lock fork failed", 2);
		return (EXIT_FAILURE);
	}
	ft_print_status(FORK, options);
	return (EXIT_SUCCESS);
}
