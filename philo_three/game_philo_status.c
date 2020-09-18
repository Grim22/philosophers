/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_philo_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:47:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/18 10:50:15 by bbrunet          ###   ########.fr       */
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
	char *message;

	if (options->stop_process == YES)
		return ;
	prepare_message(&message, options, status);
	sem_wait(options->display);
	ft_putendl_fd(message, 1);
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
	free(message);
}
