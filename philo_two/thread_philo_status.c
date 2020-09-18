/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:47:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/18 10:44:41 by bbrunet          ###   ########.fr       */
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

/*
** Print_status is protected by lock "display", shared by all threads
** Which means that threads will enter print_status one by one
** ->This prevents outputs on stdout from being mixed:
**		status will be print one after the other
** ->This also prevents that any status is displayed after the game has ended:
** 		When the game ends, stop_all is set to yes
**			(after the last status (philoX dies / has eaten) has been displayed)
** 		As stop_all is set inside print_status (check_stop function),
**			it is protected by lock
** 		A check on stop_all is performed at the begining of print_status.
**			If stop_all = yes, print_status returns (no status is displayed)
*/

void	ft_print_status(int status, t_options *options)
{
	char *message;
	
	prepare_message(&message, options, status);
	sem_wait(options->display);
	if (*(options->stop_all) == YES)
	{
		sem_post(options->display);
		free(message);
		return ;
	}
	ft_putendl_fd(message, 1);
	if (status == EAT)
	{
		options->eat_num[options->identifier - 1]++;
		options->latest_meal = ft_get_mstime();
	}
	check_stop(options, status);
	sem_post(options->display);
	free(message);
}
