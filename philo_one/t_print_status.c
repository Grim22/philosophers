/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_print_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:47:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/07 11:23:15 by bbrunet          ###   ########.fr       */
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
	
	if (options->stop_all == YES)
		return ;
	
	if (pthread_mutex_lock(options->display))
		printf("lock display failed\n");
	
	current_time = ft_get_mstime();
	elapsed = current_time - options->timestamp_start;
	timestamp = ft_itoa(elapsed);
	
	// usleep(1); // pour éviter qu'un thread aille "trop vite" et affiche du contenu alors que le jeu est déja terminé
	if (options->stop_all == YES)
	{
		pthread_mutex_unlock(options->display);
		free(timestamp);
		return ;
	}
	
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