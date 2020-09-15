/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:52:01 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/15 14:31:06 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

long int	ft_get_mstime(void)
{
	struct timeval current_t;

	gettimeofday(&current_t, NULL);
	return ((long)(current_t.tv_sec * 1000 + current_t.tv_usec / 1000));
}

int			get_right_index(t_options *options)
{
	int ret;

	if (options->identifier == 1)
		ret = options->num_philo;
	else
		ret = options->identifier - 1;
	return (ret - 1);
}

int			get_left_index(t_options *options)
{
	int ret;

	if (options->identifier == options->num_philo)
		ret = 1;
	else
		ret = options->identifier + 1;
	return (ret - 1);
}

void		ft_sleep(int delay_ms)
{
	long int	start_sleep;

	start_sleep = ft_get_mstime();
	while (ft_get_mstime() - start_sleep < delay_ms)
	{
		usleep(100);
	}
}
