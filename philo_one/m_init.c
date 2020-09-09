/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:34:38 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/09 11:43:27 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		create_threads(t_input *in, t_options **options, int num_philo)
{
	int i;

	in->threads_philo = malloc(num_philo * sizeof(pthread_t));
	i = 0;
	while (i < num_philo)
	{
		if (pthread_create(&in->threads_philo[i], NULL, &cycle, options[i]))
		{
			ft_putendl_fd("pthread_create failed", 2);
			return (EXIT_FAILURE);
		}
		i = i + 2;
	}
	usleep(500 * num_philo); // pour optimiser le jeu, on lance en décallé les philo paires et impairs (plus il y a de philo plus il faut que le décalage soit grand)
	i = 1;
	while (i < num_philo)
	{
		if (pthread_create(&in->threads_philo[i], NULL, &cycle, options[i]))
		{
			ft_putendl_fd("pthread_create failed", 2);
			return (EXIT_FAILURE);
		}
		i = i + 2;
	}
	return (EXIT_SUCCESS);
}

int		init_mutexes(int num, t_input *input)
{
	int i;

	pthread_mutex_init(&input->display, NULL);
	if (!(input->forks = malloc(num * sizeof(pthread_mutex_t))))
	{
		ft_putendl_fd("malloc failed", 2);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < num)
	{
		if (pthread_mutex_init(&input->forks[i], NULL))
		{
			ft_putendl_fd("mutex_init failed", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

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

int		fill_vars(int num, t_input *input)
{
	if (!(input->eat_num = malloc(num * sizeof(int))))
	{
		ft_putendl_fd("malloc failed", 2);
		return (EXIT_FAILURE);
	}
	fill_eat_num(input->eat_num, num);
	input->stop_all = NO;
	return (EXIT_SUCCESS);
}

int		init_input(int num_philo, t_input **input)
{
	*input = malloc(sizeof(t_input));
	if (init_mutexes(num_philo, *input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (fill_vars(num_philo, *input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
