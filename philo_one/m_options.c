/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_options.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:02:42 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/01 14:55:46 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	fill_args(t_options *options, int argc, char **argv, int identifier)
{
	options->identifier = identifier + 1;
	options->t_to_die = ft_atoi(argv[2]);
	options->t_to_eat = ft_atoi(argv[3]);
	options->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		options->num_of_time = ft_atoi(argv[5]);
}

void	fill_options_args(t_options **options, int argc, char **argv, int num_philo)
{
	int i;

	i = 0;
	while (i < num_philo)
	{
		fill_args(options[i], argc, argv, i);
		i++;
	}
}

void	malloc_options(t_options ***options, int num)
{
	int i;
	
	*options = malloc(num * sizeof(t_options*)); // malloc du tableau de t_option*
	i = 0;
	while (i < num)
	{
		options[0][i] = malloc(sizeof(t_options));
		i++;
	}
}

void	fill_options_mutexes(t_options **options, pthread_mutex_t *display, pthread_mutex_t *fork, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		if (i == num - 1)
			options[i]->fork_r = &fork[0];
		else
			options[i]->fork_r = &fork[i + 1];
		options[i]->fork_l = &fork[i];
		options[i]->display = display;
		i++;
	}
}
