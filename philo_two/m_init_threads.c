/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 17:33:22 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/15 14:36:43 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		create_philo_threads(t_input *in, t_options **options, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		if (pthread_create(&in->threads_philo[i], NULL, &cycle, options[i]))
		{
			ft_putendl_fd("pthread_create failed", 2);
			return (EXIT_FAILURE);
		}
		i = i + 1;
	}
	return (EXIT_SUCCESS);
}

int		create_threads(t_input *in, t_options **options, int num_philo)
{
	in->threads_philo = malloc(num_philo * sizeof(pthread_t));
	if (create_philo_threads(in, options, num_philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_death_thread(options) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
