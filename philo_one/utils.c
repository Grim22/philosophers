/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 17:44:10 by bbrunet           #+#    #+#             */
/*   Updated: 2020/08/31 17:44:15 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	destroy_mutexes(int num, pthread_mutex_t *forks, pthread_mutex_t lock)
{
	int i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	pthread_mutex_destroy(&lock);
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

void	join_threads(int num, pthread_t *threads)
{
	int i;

	i = 0;
	while (i < num)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
}