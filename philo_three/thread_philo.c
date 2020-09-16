/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 18:19:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/16 12:35:39 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	ft_eat(t_options *options)
{
	lock_forks(options);
	ft_print_status(EAT, options);
	ft_wait(options->t_to_eat, options->stop_all);
	unlock_forks(options);
}

/*
** After game has ended (philo died or all philo have eaten enough):
** - Nothing must be displayed anymore (cf thread_philo_status)
** - Threads must exit (thanks to stop_all variable)
** - There can be a delay between the end of the game
**		(last status displayed) and thread exit
** 	-> ex: if a philo is eating or sleeping when game ends,
**		thread will wait until he's done
**	-> threads will exit ASPAP, meaning that there should be a check
**		before philo starts to eat / sleep (cf ft_wait)
** - At exit, all locks must be unlocked (else leaks)
*/

void	*cycle(void *void_options)
{
	t_options	*options;

	options = (t_options*)void_options;
	while (*(options->stop_all) == NO)
	{
		ft_eat(options);
		ft_print_status(SLEEP, options);
		ft_wait(options->t_to_sleep, options->stop_all);
		ft_print_status(THINK, options);
	}
	return (NULL);
}
