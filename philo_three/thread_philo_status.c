/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:47:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/17 15:32:44 by bbrunet          ###   ########.fr       */
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
** This prevents outputs on stdout from being mixed:
** status will be print one after the other
** 
** All philo-processes will be stopped upon termination of the first philo-process
**
** When a process is ready to terminate (stop_process = YES):
** 	- it leaves semaphore display locked, so that no more display is made
**	- it unlocks its own forks, to make sure that it can terminate 
**  (else, process could be "blocked" in a sem_wait, waiting for a fork
**  that will never be freed, as display semaphore is locked,
**  "blocking" all other processes)
*/

void	ft_print_status(int status, t_options *options)
{
	if (options->stop_process == YES)
		return ;
	sem_wait(options->display);
	ft_print_status_start(options);
	ft_print_status_end(status);
	if (status == EAT)
		options->latest_meal = ft_get_mstime();
	check_stop(options, status);
	if (options->stop_process == NO)
		sem_post(options->display);
	else
	{
		sem_post(options->prio);
		sem_post(options->prio);
	}
}
