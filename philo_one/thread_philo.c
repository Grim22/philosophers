/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 18:19:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/11 16:39:14 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		check_priority(t_options *options)
{
	int right;
	int left;

	if (options->latest_meal == UNSET)
		return (YES);
	right = options->identifier + 1;
	left = options->identifier - 1;
	if (options->identifier == 1)
		left = options->num_philo;
	if (options->identifier == options->num_philo)
		right = 1;
	right = options->eat_num[right - 1];
	left = options->eat_num[left - 1];
	// if (options->identifier == 1)
	// 	printf("id: %d, right: %d vs %d, left: %d vs %d\n", options->identifier, right, options->count_right, left, options->count_left);
	if (options->count_left < left &&
	options->count_right < right)
		return (YES);
	else
	{
		// printf("id: %d: BLOCKED\n", options->identifier);
		return (NO);
	}
}


int		ft_eat(t_options *options)
{
	while (options->stop_all == NO)
	{
		if (check_priority(options) == YES)
			break ;
		usleep(100);
	}
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

long	ft_get_diff(t_options *options)
{
	long int	elapsed;
	long int	theoretical;

	elapsed = ft_get_mstime() - options->latest_meal;
	theoretical = options->t_to_eat;
	if (elapsed - theoretical > 0)
		return (elapsed - theoretical);
	else
		return (0);
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
		usleep(options->t_to_sleep * 1000 - ft_get_diff(options) * 1000);
		if (ft_print_status(THINK, options) == EXIT_FAILURE)
			return (NULL);
	}
	return (NULL);
}
