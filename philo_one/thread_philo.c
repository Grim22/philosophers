/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 18:19:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/08 10:36:11 by bbrunet          ###   ########.fr       */
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
		unlock_forks(options);
		return (EXIT_SUCCESS);
	}
	usleep(options->t_to_eat * 1000);
	if (unlock_forks(options) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

long int	ft_get_differential(t_options *options)
{
	long int	elapsed;
	long int	theoretical;
	
	elapsed = ft_get_mstime() - options->latest_meal;
	theoretical = options->t_to_eat;
	// printf("id: %d : diff: %ld\n", options->identifier, elapsed - theoretical);
	if (elapsed - theoretical > 0)
		return (elapsed - theoretical);
	else
		return (0);
}

void	*cycle(void *void_options)
{
	t_options	*options;
	
	options = (t_options*)void_options;
	if (create_death_thread(options) == EXIT_FAILURE)
		return (NULL);
	while (*(options->stop_all) == NO)
	{
		if (ft_eat(options) == EXIT_FAILURE)
			return (NULL);
		if (*(options->stop_all) == YES) // permet de terminer le thread plus rapidement (ne pas attendre le usleep du dessous)
			return (NULL);
		if (ft_print_status(SLEEP, options) == EXIT_FAILURE)
			return (NULL);
		usleep(options->t_to_sleep * 1000 - ft_get_differential(options) * 1000);	
		if (ft_print_status(THINK, options) == EXIT_FAILURE)
			return (NULL);
	}
	return (NULL);
}