/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:29:36 by bbrunet           #+#    #+#             */
/*   Updated: 2020/08/17 19:08:34 by bbrunet          ###   ########.fr       */
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
	
	pthread_mutex_lock(lock_out);
	gettimeofday(&current_t, NULL);
	timestamp = ft_itoa((long)(current_t.tv_usec / 1000));
	ft_putstr_fd(timestamp, 1);
	free(timestamp);
	ft_putstr_fd(" ", 1);
	identifier = ft_itoa((long)id);
	ft_putstr_fd(identifier, 1);
	free(identifier);
	if (status == EAT)
		ft_putendl_fd(" is eating", 1);
	if (status == SLEEP)
		ft_putendl_fd(" is sleeping", 1);
	if (status == THINK)
		ft_putendl_fd(" is thinking", 1);
	if (status == FORK)
		ft_putendl_fd(" has taken a fork", 1);
	if (status == DIE)
		ft_putendl_fd(" died", 1);
	pthread_mutex_unlock(lock_out);
}

void	*cycle(void *void_options)
{
	t_options	*options;
	
	options = (t_options*)void_options;
	ft_print_status(EAT, options->identifier);
	usleep(options->t_to_eat * 1000);	
	ft_print_status(SLEEP, options->identifier);
	usleep(options->t_to_sleep * 1000);	
	ft_print_status(THINK, options->identifier);
	return (NULL);
}

void	fill_options(t_options ***options, int num_philo, int argc, char **argv)
{
	int i;
	
	*options = malloc(num_philo * sizeof(t_options*));
	i = 0;
	while (i < num_philo)
	{
		options[0][i] = malloc(sizeof(t_options));
		fill_args(options[0][i], argc, argv, i);
		i++;
	}
}

int     main(int argc, char **argv)
{
	pthread_t	*thread;
	t_options	**options;
	int i;
	int num_philo;
	
	if (check_args(argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	lock_out = malloc(sizeof(*lock_out));
	pthread_mutex_init(lock_out, NULL);

	num_philo = ft_atoi(argv[1]);
	fill_options(&options, num_philo, argc, argv);
	
	thread = malloc(num_philo * sizeof(*thread));

	i = 0;
	while (i < num_philo)
	{
		pthread_create(&thread[i], NULL, &cycle, (void*)options[i]);
		i++;
	}
	i = 0;
	while (i < num_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	pthread_mutex_destroy(lock_out);
}