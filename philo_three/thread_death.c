/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 12:10:02 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/17 11:52:51 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		check_death(t_options *options)
{
	int	max;
	int elapsed_time;

	max = options->t_to_die;
	if (options->latest_meal == UNSET)
		elapsed_time = ft_get_mstime() - options->timestamp_start;
	else
		elapsed_time = ft_get_mstime() - options->latest_meal;
	if (elapsed_time > max)
	{
		ft_print_status(DIE, options);
		return (YES);
	}
	else
		return (NO);
}

void	*death_alarm(void *void_options)
{
	t_options	*options;

	options = (t_options*)void_options;
	while (1)
	{
		if (check_death(options) == YES)
			return (NULL);
		usleep(T_CHECK_DEATH);
	}
	return (NULL);
}

int		create_death_thread(t_options *options)
{
	pthread_t death_thread;

	if (pthread_create(&death_thread, NULL, &death_alarm, options))
	{
		ft_putendl_fd("pthread_create failed", 2);
		return (EXIT_FAILURE);
	}
	pthread_detach(death_thread);
	return (EXIT_SUCCESS);
}
