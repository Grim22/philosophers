/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:47:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/15 14:43:18 by bbrunet          ###   ########.fr       */
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

// void	update_eat_count(t_options *options)
// {
// 	int *eat_num;

// 	eat_num = options->eat_num;
// 	eat_num[options->identifier - 1]++;
// 	options->count_right = eat_num[get_right_index(options)];
// 	options->count_left = eat_num[get_left_index(options)];
// }

int		ft_print_status(int status, t_options *options)
{
	if (*(options->stop_all) == YES)
		return (EXIT_SUCCESS);
	if (sem_wait(options->display))
	{
		ft_putendl_fd("wait display failed", 1);
		return (EXIT_FAILURE);
	}
	if (*(options->stop_all) == YES)
	{
		sem_post(options->display);
		return (EXIT_SUCCESS);
	}
	ft_print_status_start(options);
	ft_print_status_end(status);
	if (status == EAT)
		options->eat_num[options->identifier - 1]++;
	check_stop(options, status);
	if (sem_post(options->display))
	{
		ft_putendl_fd("post display failed", 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
