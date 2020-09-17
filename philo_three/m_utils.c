/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:52:01 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/17 18:11:50 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

long	ft_get_mstime(void)
{
	struct timeval current_t;

	gettimeofday(&current_t, NULL);
	return ((long)(current_t.tv_sec * 1000 + current_t.tv_usec / 1000));
}

void	ft_wait(int delay_ms)
{
	long int	start_sleep;

	start_sleep = ft_get_mstime();
	while (ft_get_mstime() - start_sleep < delay_ms)
	{
		usleep(T_SLEEP);
	}
}
