/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:34:38 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/03 15:23:31 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int	create_threads(pthread_t **thread, pthread_t *thread_stop, t_options **options, int num_philo)
{
	int i;
	
	if (pthread_create(thread_stop, NULL, &stop, (void*)options))
	{
		ft_putendl_fd("pthread_create failed", 2);
		return (EXIT_FAILURE);
	}
	pthread_detach(*thread_stop);
	*thread = malloc(num_philo * sizeof(pthread_t));
	i = 0;
	while (i < num_philo)
	{
		if (pthread_create(&thread[0][i], NULL, &cycle, (void*)options[i]))
		{
			ft_putendl_fd("pthread_create failed", 2);
			return (EXIT_FAILURE);
		}
		// pthread_detach(thread[0][i]);
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