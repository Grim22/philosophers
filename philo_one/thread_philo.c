/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 18:19:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/07 15:30:10 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

// void	check_eat_number(int *counter, t_options *options)
// {
// 	if (options->num_of_time == UNSET)
// 		return ;
// 	(*counter)++;
// 	if (*counter >= options->num_of_time)
// 		options->enough_food = YES;
// }

int		ft_eat(t_options *options)
{
	if (lock_forks(options) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	options->latest_meal = ft_get_mstime();
	ft_print_status(EAT, options);
	// options->eat_num++;
	// check_eat_number(count_eat, options);
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
		ft_print_status(SLEEP, options);
		usleep(options->t_to_sleep * 1000);	
		ft_print_status(THINK, options);
	}
	return (NULL);
}