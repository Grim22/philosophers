/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:29:36 by bbrunet           #+#    #+#             */
/*   Updated: 2020/08/31 18:22:25 by bbrunet          ###   ########.fr       */
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

void	fill_args(t_options *options, int argc, char **argv, int identifier)
{
	options->identifier = identifier + 1;
	options->t_to_die = ft_atoi(argv[2]);
	options->t_to_eat = ft_atoi(argv[3]);
	options->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		options->num_of_time = ft_atoi(argv[5]);
}

void	fill_options(t_options ***options, int num_philo, int argc, char **argv, pthread_mutex_t *fork)
{
	int i;
	
	*options = malloc(num_philo * sizeof(t_options*)); // malloc du tableau de t_option*
	
	i = 0;
 	// malloc du premier t_option*
	options[0][i] = malloc(sizeof(t_options));
	// fill du premier t_option
	fill_args(options[0][i], argc, argv, i); 
	options[0][i]->fork_l = &fork[i];
	if (num_philo > 1)
		options[0][i]->fork_r = &fork[i + 1];
	else
		options[0][i]->fork_r = &fork[i]; // c'est la meme fourchette a gauche et a droite
	
	i++;
	while (i < num_philo - 1)
	{
		options[0][i] = malloc(sizeof(t_options));
		fill_args(options[0][i], argc, argv, i);
		options[0][i]->fork_l = &fork[i];
		options[0][i]->fork_r = &fork[i + 1];
		i++;
	}
	
	// malloc et fill du dernier t_option
	if (num_philo > 1)
	{
		options[0][i] = malloc(sizeof(t_options));
		fill_args(options[0][i], argc, argv, i);
		options[0][i]->fork_l = &fork[i];
		options[0][i]->fork_r = &fork[0];
	}
}

int     main(int argc, char **argv)
{
	pthread_t	*thread; // tableau de pthreads
	pthread_mutex_t	*fork; // tableau de phtread_mutexs
	t_options	**options; // tableau de t_options*
	int i;
	int num_philo;
	
	if (check_args(argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);


	num_philo = ft_atoi(argv[1]);
	
	fork = malloc(num_philo * sizeof(pthread_mutex_t)); // chaque fork[i] est un pthread_mutex
	init_mutexes(num_philo, fork, lock_out);
	
	thread = malloc(num_philo * sizeof(pthread_t)); // Chaque thread[i] est un pthread_t

	fill_options(&options, num_philo, argc, argv, fork);
	
	i = 0;
	while (i < num_philo)
	{
		pthread_create(&thread[i], NULL, &cycle, (void*)options[i]);
		i++;
	}
	join_threads(num_philo, thread);
	free_options(num_philo, options);
	destroy_mutexes(num_philo, fork, lock_out);
}
