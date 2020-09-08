/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:34:38 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/08 15:37:50 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int	create_threads(pthread_t **thread, t_options **options, int num_philo)
{
	int i;
	
	*thread = malloc(num_philo * sizeof(pthread_t));
	i = 0;
	while (i < num_philo)
	{
		// if (i % 2 == 0)
			if (pthread_create(&thread[0][i], NULL, &cycle, (void*)options[i]))
			{
				ft_putendl_fd("pthread_create failed", 2);
				return (EXIT_FAILURE);
			}
		i++;
	}
	// i = 0;
	// while (i < num_philo)
	// {
	// 	if (i % 2 == 1)
	// 		if (pthread_create(&thread[0][i], NULL, &cycle, (void*)options[i]))
	// 		{
	// 			ft_putendl_fd("pthread_create failed", 2);
	// 			return (EXIT_FAILURE);
	// 		}
	// 	i++;
	// }
	return (EXIT_SUCCESS);
}

int	init_mutexes(int num, pthread_mutex_t **fork, pthread_mutex_t *display)
{
	int i;

    pthread_mutex_init(display, NULL);
	if (!(*fork = malloc(num * sizeof(pthread_mutex_t))))
	{
		ft_putendl_fd("malloc failed", 2);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < num)
	{
		if (pthread_mutex_init(&fork[0][i], NULL))
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

int	fill_vars(int num, int **eat_num, int *stop_all)
{
	if (!(*eat_num = malloc(num * sizeof(int))))
	{
		ft_putendl_fd("malloc failed", 2);
		return (EXIT_FAILURE);
	}
	fill_eat_num(*eat_num, num);
	*stop_all = NO;
	return (EXIT_SUCCESS);
}