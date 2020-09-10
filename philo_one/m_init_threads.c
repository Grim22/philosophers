/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 17:33:22 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/09 18:08:05 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		create_odd_even(t_input *in, t_options **options, int num_philo, int start)
{
	int i;

	if (start == EVEN)
		i = 1;
	if (start == ODD)
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
	return (EXIT_SUCCESS);
}

int		create_threads(t_input *in, t_options **options, int num_philo)
{
	in->threads_philo = malloc(num_philo * sizeof(pthread_t));
    if (create_odd_even(in, options, num_philo, ODD) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (num_philo <= 10)
		usleep(2000); // pour optimiser le jeu, on lance en décallé les philo paires et impairs (plus il y a de philo plus il faut que le décalage soit grand)
	else
		usleep(5000);
    if (create_odd_even(in, options, num_philo, EVEN) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_death_thread(options) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
