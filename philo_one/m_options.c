/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_options.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:02:42 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/07 15:13:04 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"


void	fill_eat_num(int *eat_num, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		eat_num[i] = 0;
		i++;
	}
}

void	fill_args(t_options *options, int argc, char **argv, int identifier)
{
	options->identifier = identifier + 1;
	options->num_philo = ft_atoi(argv[1]);
	options->t_to_die = ft_atoi(argv[2]);
	options->t_to_eat = ft_atoi(argv[3]);
	options->t_to_sleep = ft_atoi(argv[4]);
	options->died = NO;
	options->stop_all = NO;
	options->latest_meal = 0;
	fill_eat_num(options->eat_num, options->num_philo);
	if (argc == 6)
		options->eat_max = ft_atoi(argv[5]);
	else
		options->eat_max = UNSET;
}

void	fill_options_args(t_options **options, int argc, char **argv, int *eat_num)
{
	int i;
	long int time;
	
	time = ft_get_mstime();
	i = 0;
	while (options[i])
	{
		options[i]->timestamp_start = time;
		options[i]->eat_num = eat_num;
		fill_args(options[i], argc, argv, i);
		i++;
	}
}

int		malloc_options(t_options ***options, int num, int **eat_num)
{
	int i;
	
	if (!(*eat_num = malloc(num * sizeof(int))))
	{
		ft_putendl_fd("malloc failed", 2);
		return (EXIT_FAILURE);
	}
	i = 0;
	if (!(*options = malloc((num + 1) * sizeof(t_options*))))
	{
		ft_putendl_fd("malloc failed", 2);
		return (EXIT_FAILURE);
	}
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

void	fill_options_mutexes(t_options **options, pthread_mutex_t *display, pthread_mutex_t *fork)
{
	int i;

	i = 0;
	while (options[i])
	{
		if (options[i + 1] == NULL)
			options[i]->fork_r = &fork[0];
		else
			options[i]->fork_r = &fork[i + 1];
		options[i]->fork_l = &fork[i];
		options[i]->display = display;
		i++;
	}
}
