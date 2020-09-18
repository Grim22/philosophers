/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo_forks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 18:04:34 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/18 09:17:14 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	unlock_forks(t_options *options)
{
	sem_post(options->prio_left);
	sem_post(options->prio_right);
}

void	lock_forks(t_options *options)
{
	sem_wait(options->prio);
	sem_wait(options->prio);
	ft_print_status(FORK, options);
	ft_print_status(FORK, options);
}
