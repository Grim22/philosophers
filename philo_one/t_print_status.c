/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_print_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:47:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/03 17:17:40 by bbrunet          ###   ########.fr       */
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

void	ft_print_status(int status, t_options *options)
{
	char *timestamp;
	char *identifier;
	long int elapsed;
	long int current_time;
	
	if (pthread_mutex_lock(options->display))
		printf("lock display failed\n");
	
	current_time = ft_get_mstime();
	elapsed = current_time - options->timestamp_start;
	if (options->stop_all == YES)
	{
		pthread_mutex_unlock(options->display);
		return ;
	}
	timestamp = ft_itoa(elapsed);
	ft_putstr_fd(timestamp, 1);
	free(timestamp);
	ft_putstr_fd(" ", 1);
	identifier = ft_itoa((long)options->identifier);
	ft_putstr_fd(identifier, 1);
	free(identifier);
	ft_print_status_end(status);

	if (pthread_mutex_unlock(options->display))
		printf("unlock display failed\n");
}