/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo_stop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 17:10:38 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/09 17:13:35 by bbrunet          ###   ########.fr       */
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
	if (options->eat_max != UNSET && status == EAT)
	{
		eat_num = options->eat_num;
		eat_num[options->identifier - 1]++;
		if (check_eat(options->num_philo, eat_num, options->eat_max) == YES)
			*(options->stop_all) = YES;
	}
}
