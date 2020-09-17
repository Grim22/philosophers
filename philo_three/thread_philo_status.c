/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:47:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/17 11:41:09 by bbrunet          ###   ########.fr       */
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

/*
** Print_status is protected by lock "display", shared by all threads
** Which means that threads will enter print_status one by one
** ->This prevents outputs on stdout from being mixed:
**		status will be print one after the other
** All philo-processes will be stopped upon exit of the first philo-process
** When it exits, the first philo_process will leave semaphore display locked,
** so that no more display is made
*/

void	ft_print_status(int status, t_options *options)
{
	if (*(options->stop_all) == YES)
		return ;
	sem_wait(options->display);
	if (*(options->stop_all) == YES)
	{
		sem_post(options->display);
		return ;
	}
	ft_print_status_start(options);
	ft_print_status_end(status);
	if (status == EAT)
	{
		options->eat_num[options->identifier - 1]++;
		options->latest_meal = ft_get_mstime();
	}
	check_stop(options, status);
	if (*(options->stop_all) == NO)
		sem_post(options->display);
}
