/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 18:19:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/15 14:46:14 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		ft_eat(t_options *options)
{
	if (lock_forks(options) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	options->latest_meal = ft_get_mstime();
	if (ft_print_status(EAT, options) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (*(options->stop_all) == YES)
	{
		if (unlock_forks(options) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	ft_sleep(options->t_to_eat);
	if (unlock_forks(options) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*cycle(void *void_options)
{
	t_options	*options;

	options = (t_options*)void_options;
	while (*(options->stop_all) == NO)
	{
		if (ft_eat(options) == EXIT_FAILURE)
			return (NULL);
		if (*(options->stop_all) == YES)
			return (NULL);
		if (ft_print_status(SLEEP, options) == EXIT_FAILURE)
			return (NULL);
		ft_sleep(options->t_to_sleep);
		if (ft_print_status(THINK, options) == EXIT_FAILURE)
			return (NULL);
	}
	return (NULL);
}
