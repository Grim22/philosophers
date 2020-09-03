/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:29:36 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/03 12:04:55 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		check_args(int argc, char **argv)
{
	int i;
	
	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("wrong number of args", 2);
		return (EXIT_FAILURE);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_isdigit_str(argv[i]) == 0)
		{
			ft_putendl_fd("non digit argument", 2);
			return (EXIT_FAILURE);
		}
		if (ft_strlen(argv[i]) > 9)
		{
			ft_putendl_fd("too big number", 2); // facon de protéger les ft_atoi
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}


int     main(int argc, char **argv)
{
	pthread_t		*thread; // tableau de pthreads: un thread par philo
	pthread_t		thread_stop;
	pthread_mutex_t	*forks; // tableau de mutex: chacun pour une fourchette
	pthread_mutex_t	display; // mutex pour l'affichage à l'écran des statuts
	t_options		**options; // tableau de t_options* (arguments envoyés aux threads)
	int				num_philo;
	
	if (check_args(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	num_philo = ft_atoi(argv[1]);
	
	if (init_mutexes(num_philo, &forks, &display) == EXIT_FAILURE
		|| malloc_options(&options, num_philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	fill_options_args(options, argc, argv);
	fill_options_mutexes(options, &display, forks, num_philo);
	if (create_threads(&thread, &thread_stop, options, num_philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	pthread_join(thread_stop, NULL); // on attend seulement le thread qui gère la fin du process (les autres threads sont detached)
	
	// if (destroy_mutexes(num_philo, forks, display) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	free_options(num_philo, options);
}
