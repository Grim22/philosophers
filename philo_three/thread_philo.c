/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 18:19:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/17 15:21:59 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	ft_eat(t_options *options)
{
	lock_forks(options);
	ft_print_status(EAT, options);
	ft_wait(options->t_to_eat, options->stop_process);
	unlock_forks(options);
}

/*
** One death thread for each philo
*/

void	*cycle(void *void_options)
{
	t_options	*options;

	options = (t_options*)void_options;
	create_death_thread(options);
	while (options->stop_process == NO)
	{
		ft_eat(options);
		ft_print_status(SLEEP, options);
		ft_wait(options->t_to_sleep, options->stop_process);
		ft_print_status(THINK, options);
	}
	return (NULL);
}
