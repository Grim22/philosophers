/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:29:36 by bbrunet           #+#    #+#             */
/*   Updated: 2020/08/31 18:12:47 by bbrunet          ###   ########.fr       */
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

void	ft_print_status(int status, int id)
{
	struct timeval current_t;
	char *timestamp;
	char *identifier;
	
	pthread_mutex_lock(&lock_out); // partie locked pour que les threads n'affichent pas les statuts en meme temps
	
	gettimeofday(&current_t, NULL);
	timestamp = ft_itoa((long)(current_t.tv_sec * 1000 + current_t.tv_usec / 1000));
	// timestamp = ft_itoa((long)(current_t.tv_usec / 1000));
	ft_putstr_fd(timestamp, 1);
	free(timestamp);
	
	ft_putstr_fd(" ", 1);
	identifier = ft_itoa((long)id);
	ft_putstr_fd(identifier, 1);
	free(identifier);
	
	if (status == EAT)
		ft_putendl_fd(" is EATING !", 1);
	if (status == SLEEP)
		ft_putendl_fd(" is sleeping", 1);
	if (status == THINK)
		ft_putendl_fd(" is thinking", 1);
	if (status == FORK)
		ft_putendl_fd(" has taken a fork", 1);
	if (status == DIE)
		ft_putendl_fd(" died", 1);
	
	pthread_mutex_unlock(&lock_out);
}

void	*cycle(void *void_options)
{
	// struct timeval current_t;
	t_options	*options;
	// long int	timestart;
	// long int	timestamp;
	// long int	counter;
	
	options = (t_options*)void_options;
	
	// counter = 0;
	// gettimeofday(&current_t, NULL);
	// timestart = (long)(current_t.tv_sec * 1000 + current_t.tv_usec / 1000);
	
	while (1)
	{
		// LOCK FORKS
		if (options->identifier % 2 == 0) // pour eviter que tous les philo se jettent en premier sur leur fourchette droite, ce qui cause un deadlock: chaque philo a une fourchette dans la main, qu'il ne libère jamais 
		{
			if (pthread_mutex_lock(options->fork_l))
				printf("error lock\n");
		}
		else
		{
			if (pthread_mutex_lock(options->fork_r))
				printf("error lock\n");
		}
		ft_print_status(FORK, options->identifier);
		
		if (options->identifier % 2 == 0)
		{
			if (pthread_mutex_lock(options->fork_r))
				printf("error lock\n");
		}
		else
		{
			if (pthread_mutex_lock(options->fork_l))
				printf("error lock\n");
		}
		ft_print_status(FORK, options->identifier);
		
		// EAT
		ft_print_status(EAT, options->identifier);
		// timestamp = 0;
		usleep(options->t_to_eat * 1000);	
		
		// UNLOCK FORKS
		if (pthread_mutex_unlock(options->fork_l))
			printf("error unlock\n");
		if (pthread_mutex_unlock(options->fork_r))
			printf("error unlock\n");
		
		// SLEEP
		ft_print_status(SLEEP, options->identifier);
		usleep(options->t_to_sleep * 1000);	
		
		//THINK
		ft_print_status(THINK, options->identifier);
	}
	return (NULL);
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
