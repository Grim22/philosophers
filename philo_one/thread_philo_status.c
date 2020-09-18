/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:47:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/18 10:39:00 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	prepare_message_end(char **message, int status)
{
	if (status == EAT)
		ft_strjoin_back(" is eating", message);
	if (status == SLEEP)
		ft_strjoin_back(" is sleeping", message);
	if (status == THINK)
		ft_strjoin_back(" is thinking", message);
	if (status == FORK)
		ft_strjoin_back(" has taken a fork", message);
	if (status == DIE)
		ft_strjoin_back(" died", message);
}

void	prepare_message(char **message, t_options *options, int status)
{
	long	elapsed;
	long	current_time;
	char	*identifier;

	current_time = ft_get_mstime();
	elapsed = current_time - options->timestamp_start;
	*message = ft_itoa(elapsed);
	ft_strjoin_back(" ", message);
	identifier = ft_itoa((long)options->identifier);
	ft_strjoin_back(identifier, message);
	free(identifier);
	prepare_message_end(message, status);
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
	char *message;

	prepare_message(&message, options, status);
	pthread_mutex_lock(options->display);
	if (*(options->stop_all) == YES)
	{
		pthread_mutex_unlock(options->display);
		free(message);
		return ;
	}
	ft_putendl_fd(message, 1);
	if (status == EAT)
		update_eat_count(options);
	check_stop(options, status);
	pthread_mutex_unlock(options->display);
	free(message);
}
