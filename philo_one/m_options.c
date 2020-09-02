/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_options.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:02:42 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/02 18:14:10 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	fill_args(t_options *options, int argc, char **argv, int identifier)
{
	options->identifier = identifier + 1;
	options->t_to_die = ft_atoi(argv[2]);
	options->t_to_eat = ft_atoi(argv[3]);
	options->t_to_sleep = ft_atoi(argv[4]);
	options->died = NO;
	options->enough_food = NO;
	options->latest_meal = 0;
	if (argc == 6)
		options->num_of_time = ft_atoi(argv[5]);
	else
		options->num_of_time = UNSET;
}

void	fill_options_args(t_options **options, int argc, char **argv)
{
	int i;

	struct timeval current_t;
	long int time;
	
	gettimeofday(&current_t, NULL);
	time = current_t.tv_sec * 1000 + current_t.tv_usec / 1000; // en ms
	i = 0;
	while (options[i])
	{
		options[i]->timestamp_start = time;
		fill_args(options[i], argc, argv, i);
		i++;
	}
}

int		malloc_options(t_options ***options, int num)
{
	int i;
	
	if (!(*options = malloc((num + 1) * sizeof(t_options*))))
	{
		ft_putendl_fd("malloc failed", 2);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < num)
	{
		if (!(options[0][i] = malloc(sizeof(t_options))))
		{
			ft_putendl_fd("malloc failed", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	options[0][i] = NULL;
	return (EXIT_SUCCESS);
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
