/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo_forks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 18:04:34 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/16 12:11:57 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	unlock_forks(t_options *options)
{
	pthread_mutex_unlock(options->fork_l);
	pthread_mutex_unlock(options->fork_r);
}

void	lock_forks(t_options *options)
{
	pthread_mutex_lock(options->fork_l);
	ft_print_status(FORK, options);
	pthread_mutex_lock(options->fork_r);
	ft_print_status(FORK, options);
}
