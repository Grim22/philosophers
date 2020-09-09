/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_options.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:02:42 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/09 11:44:36 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"



void	fill_args(t_options *options, char **argv, int identifier)
{
	options->identifier = identifier + 1;
	options->num_philo = ft_atoi(argv[1]);
	options->t_to_die = ft_atoi(argv[2]);
	options->t_to_eat = ft_atoi(argv[3]);
	options->t_to_sleep = ft_atoi(argv[4]);
	options->latest_meal = UNSET;
	if (argv[5])
		options->eat_max = ft_atoi(argv[5]);
	else
		options->eat_max = UNSET;
}

void	fill_options_args(t_options **options, char **argv, t_input *input)
{
	int i;
	long int time;
	
	time = ft_get_mstime();
	i = 0;
	while (options[i])
	{
		options[i]->timestamp_start = time;
		options[i]->eat_num = input->eat_num;
		options[i]->stop_all = &input->stop_all;
		fill_args(options[i], argv, i);
		i++;
	}
}

int		malloc_options(t_options ***options, int num)
{
	int i;
	
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

void	fill_options_mutexes(t_options **options, t_input *input)
{
	int i;

	i = 0;
	while (options[i])
	{
		if (options[i + 1] == NULL)
			options[i]->fork_r = &input->forks[0];
		else
			options[i]->fork_r = &input->forks[i + 1];
		options[i]->fork_l = &input->forks[i];
		options[i]->display = &input->display;
		i++;
	}
}

int		init_options(t_options ***options, char **argv, t_input *input, int num_philo)
{
	if (malloc_options(options, num_philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	fill_options_args(*options, argv, input);
	fill_options_mutexes(*options, input);
	return (EXIT_SUCCESS);
}