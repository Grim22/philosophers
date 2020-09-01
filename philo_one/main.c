/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:29:36 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/01 15:37:20 by bbrunet          ###   ########.fr       */
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
	pthread_t	*thread; // tableau de pthreads: un thread par philo
	pthread_mutex_t	*forks; // tableau de mutex: chacun pour une fourchette
	pthread_mutex_t display; // mutex pour l'affichage à l'écran des statuts
	t_options	**options; // tableau de t_options* (arguments envoyés aux threads)
	int num_philo;
	
	if (check_args(argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	num_philo = ft_atoi(argv[1]);
	
	init_mutexes(num_philo, &forks, &display);

	malloc_options(&options, num_philo);
	fill_options_args(options, argc, argv, num_philo);
	fill_options_mutexes(options, &display, forks, num_philo);
	
	create_threads(&thread, options, num_philo);
	
	join_threads(num_philo, thread);
	free_options(num_philo, options);
	destroy_mutexes(num_philo, forks, display);
}
