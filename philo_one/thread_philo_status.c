/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:47:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/16 12:15:51 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

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

void	ft_print_status_start(t_options *options)
{
	char	*timestamp;
	long	elapsed;
	long	current_time;
	char	*identifier;

	current_time = ft_get_mstime();
	elapsed = current_time - options->timestamp_start;
	timestamp = ft_itoa(elapsed);
	ft_putstr_fd(timestamp, 1);
	free(timestamp);
	ft_putstr_fd(" ", 1);
	identifier = ft_itoa((long)options->identifier);
	ft_putstr_fd(identifier, 1);
	free(identifier);
}

void	update_eat_count(t_options *options)
{
	int *eat_num;

	options->latest_meal = ft_get_mstime();
	eat_num = options->eat_num;
	eat_num[options->identifier - 1]++;
	options->count_right = eat_num[get_right_index(options)];
	options->count_left = eat_num[get_left_index(options)];
}

void	ft_print_status(int status, t_options *options)
{
	pthread_mutex_lock(options->display);
	if (*(options->stop_all) == YES)
	{
		pthread_mutex_unlock(options->display);
		return ;
	}
	ft_print_status_start(options);
	ft_print_status_end(status);
	if (status == EAT)
		update_eat_count(options);
	check_stop(options, status);
	pthread_mutex_unlock(options->display);
}
