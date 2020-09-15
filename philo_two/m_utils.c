/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 11:52:01 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/15 15:13:07 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

long int	ft_get_mstime(void)
{
	struct timeval current_t;

	gettimeofday(&current_t, NULL);
	return ((long)(current_t.tv_sec * 1000 + current_t.tv_usec / 1000));
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
