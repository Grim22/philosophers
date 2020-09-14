/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo_stop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 17:10:38 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/14 11:27:42 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		check_eat(int num, int *eat_num, int max)
{
	int i;

	i = 0;
	while (i < num)
	{
		if (eat_num[i] < max)
			return (NO);
		i++;
	}
	return (YES);
}

void	check_stop(t_options *options, int status)
{
	int	*eat_num;

	if (status == DIE)
		*(options->stop_all) = YES;
	if (status == EAT && options->eat_max != UNSET)
	{
		eat_num = options->eat_num;
		if (check_eat(options->num_philo, eat_num, options->eat_max) == YES)
			*(options->stop_all) = YES;
	}
}
