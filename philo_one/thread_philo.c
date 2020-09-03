/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 18:19:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/03 11:47:50 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	unlock_forks(t_options *options)
{
		if (pthread_mutex_unlock(options->fork_l))
			printf("error unlock\n");
		if (pthread_mutex_unlock(options->fork_r))
			printf("error unlock\n");
}

void	lock_forks(t_options *options)
{
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
		ft_print_status(FORK, options);
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
		ft_print_status(FORK, options);
}

void	*death_alarm(void *void_options)
{
	int	max;
	t_options *options;
	long int current_time;
	int elapsed_time;
	struct timeval current_t;
	
	options = (t_options*)void_options;
	max = options->t_to_die;
	// printf("max: %d\n", max);
	while (1)
	{
		gettimeofday(&current_t, NULL);
		current_time = current_t.tv_sec * 1000 + current_t.tv_usec / 1000; // en ms
		if (options->latest_meal)
			elapsed_time = current_time - options->latest_meal;
		else
			elapsed_time = current_time - options->timestamp_start;
		// printf("id: %d elapsed: %d\n", options->identifier, elapsed_time);
		if (elapsed_time > max)
		{
			options->died = YES;
			ft_print_status(DIE, options);
			return (NULL);
		}
		usleep(1000); // 1 ms (pas plus de 10ms entre la mort et l'affichage de la mort)
	}
}

void	set_latest_meal_time(t_options *options)
{
	struct timeval current_t;
	
	gettimeofday(&current_t, NULL);
	options->latest_meal = current_t.tv_sec * 1000 + current_t.tv_usec / 1000;
}
int		create_death_thread(t_options *options)
{
	pthread_t death_thread;

	if (pthread_create(&death_thread, NULL, &death_alarm, options))
	{
		ft_putendl_fd("pthread_create failed", 2);
		return (EXIT_FAILURE);
	}
	pthread_detach(death_thread);
	return (EXIT_SUCCESS);
}

void	check_eat_number(int *counter, t_options *options)
{
	if (options->num_of_time == UNSET)
		return ;
	(*counter)++;
	if (*counter >= options->num_of_time)
		options->enough_food = YES;
}

void	*cycle(void *void_options)
{
	t_options	*options;
	int			count_eat;
	
	options = (t_options*)void_options;
	count_eat = 0;
	if (create_death_thread(options) == EXIT_FAILURE)
		return (NULL);
	while (1)
	{
		lock_forks(options);
		set_latest_meal_time(options);
		ft_print_status(EAT, options);
		check_eat_number(&count_eat, options);
		usleep(options->t_to_eat * 1000);	
		unlock_forks(options);
		ft_print_status(SLEEP, options);
		usleep(options->t_to_sleep * 1000);	
		ft_print_status(THINK, options);
	}
	return (NULL);
}