/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:29:36 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/01 12:21:08 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		check_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("wrong number of args", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int     main(int argc, char **argv)
{
	pthread_t	*thread; // tableau de pthreads
	pthread_mutex_t	*forks; // tableau de phtread_mutexs
	pthread_mutex_t display;
	t_options	**options; // tableau de t_options*
	int i;
	int num_philo;
	
	if (check_args(argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	num_philo = ft_atoi(argv[1]);
	
	forks = malloc(num_philo * sizeof(pthread_mutex_t)); // chaque fork[i] est un pthread_mutex
	init_mutexes(num_philo, forks, display);
	
	thread = malloc(num_philo * sizeof(pthread_t)); // Chaque thread[i] est un pthread_t

	malloc_options(&options, num_philo);
	fill_options_args(options, argc, argv, num_philo);
	fill_options_mutexes(options, display, forks, num_philo);
	
	i = 0;
	while (i < num_philo)
	{
		pthread_create(&thread[i], NULL, &cycle, (void*)options[i]);
		i++;
	}
	join_threads(num_philo, thread);
	free_options(num_philo, options);
	destroy_mutexes(num_philo, forks, lock_out);
}
