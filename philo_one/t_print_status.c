/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_print_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:47:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/07 17:19:59 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		check_enough_eat(int num, int *eat_num, int max)
{
	int i;

	i = 0;
	while (i < num)
	{
		if (eat_num[i] < max)
			return (NO);
		i++;
	}
	return (YES);
}

void	check_stop(t_options *options, int status)
{
	int	*eat_num;
	
	if (status == DIE)
		*(options->stop_all) = YES;
	if (options->eat_max != UNSET && status == EAT)
	{
		eat_num = options->eat_num;
		eat_num[options->identifier - 1]++;
		if (check_enough_eat(options->num_philo, eat_num, options->eat_max) == YES)
			*(options->stop_all) = YES;
	}
}

void	ft_print_status_end(int status)
{
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
}

void	ft_print_timestamp(t_options *options)
{
	char *timestamp;
	long int elapsed;
	long int current_time;
	
	current_time = ft_get_mstime();
	elapsed = current_time - options->timestamp_start;
	timestamp = ft_itoa(elapsed);
	ft_putstr_fd(timestamp, 1);
	free(timestamp);
}

void	ft_print_identifier(t_options *options)
{
	char *identifier;
	
	ft_putstr_fd(" ", 1);
	identifier = ft_itoa((long)options->identifier);
	ft_putstr_fd(identifier, 1);
	free(identifier);
}

int		ft_print_status(int status, t_options *options)
{
	
	if (*(options->stop_all) == YES)
		return (EXIT_SUCCESS);
	if (pthread_mutex_lock(options->display) == EXIT_FAILURE)
	{
		ft_putendl_fd("lock display failed", 1);
		return (EXIT_FAILURE);
	}
	if (*(options->stop_all) == YES)
	{
		if (pthread_mutex_unlock(options->display) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	ft_print_timestamp(options);
	ft_print_identifier(options);
	ft_print_status_end(status);
	check_stop(options, status);
	if (pthread_mutex_unlock(options->display))
	{
		ft_putendl_fd("unlock display failed", 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}