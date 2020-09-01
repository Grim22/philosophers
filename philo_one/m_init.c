/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:34:38 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/01 16:40:29 by bbrunet          ###   ########.fr       */
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
		if (pthread_create(&thread[0][i], NULL, &cycle, (void*)options[i]))
		{
			ft_putendl_fd("pthread_create failed", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
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