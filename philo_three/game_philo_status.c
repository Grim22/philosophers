/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_philo_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:47:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/17 19:08:37 by bbrunet          ###   ########.fr       */
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

void	sem_post_multi(t_options *options)
{
	int i;

	i = 0;
	while (i < options->num_philo)
	{
		sem_post(options->stop_game);
		i++;
	}
}

/*
** Case 1: philo X dies
** 		sem_post_multi will send the signal to main that all process
**		can be killed
**		options->display will remain locked, so that there can be no
**		display in the meantime
** Case 2: a philo has eaten enough
**		stop_process is set to yes so process will stop by itself,
**		and display no more
**		stop_game will be incremented -> main will kill all processes
**		when every process has incremented stop philo
**
**		Note: once it has eaten enough, the philo is out of the game.
**		no more status from that philo will appear.
**		This is a possible interpretation from the subject, resulting
**		in a different implementation than in philo_one and philo_two
**		(philo was kept in the game until all philos have eaten)
*/

void	ft_print_status(int status, t_options *options)
{
	if (options->stop_process == YES)
		return ;
	sem_wait(options->display);
	ft_print_status_start(options);
	ft_print_status_end(status);
	if (status == EAT)
	{
		options->eat_num++;
		options->latest_meal = ft_get_mstime();
		if (options->eat_max != UNSET && (options->eat_num >= options->eat_max))
		{
			sem_post(options->stop_game);
			options->stop_process = YES;
		}
	}
	if (status == DIE)
		sem_post_multi(options);
	else
		sem_post(options->display);
}
