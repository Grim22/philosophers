/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_end.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 17:44:10 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/01 16:51:30 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		destroy_mutexes(int num, pthread_mutex_t *forks, pthread_mutex_t display)
{
	int i;

	i = 0;
	while (i < num)
	{
		if (pthread_mutex_destroy(&forks[i]))
		{
			ft_putendl_fd("pthread_mutex_destroy failed", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	free(forks);
	if (pthread_mutex_destroy(&display))
	{
		ft_putendl_fd("pthread_mutex_destroy failed", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	free_options(int num, t_options **options)
{
	int i;

	i = 0;
	while (i < num)
	{
		free(options[i]);
		i++;
	}
	free(options);
}

int		join_threads(int num, pthread_t *threads)
{
	int i;

	i = 0;
	while (i < num)
	{
		if (pthread_join(threads[i], NULL))
		{
			ft_putendl_fd("pthread_join failed", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	free(threads);
	return (EXIT_SUCCESS);
}