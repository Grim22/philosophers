/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:34:38 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/01 15:35:29 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	create_threads(pthread_t **thread, t_options **options, int num_philo)
{
	int i;
	
	*thread = malloc(num_philo * sizeof(pthread_t));
	i = 0;
	while (i < num_philo)
	{
		pthread_create(&thread[0][i], NULL, &cycle, (void*)options[i]);
		i++;
	}
}

void    init_mutexes(int num, pthread_mutex_t **fork, pthread_mutex_t *display)
{
	int i;

    pthread_mutex_init(display, NULL);
	*fork = malloc(num * sizeof(pthread_mutex_t)); // chaque fork[i] est un pthread_mutex
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&fork[0][i], NULL);
		i++;
	}
}