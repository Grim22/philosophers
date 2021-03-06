/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_end.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 17:44:10 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/09 11:57:07 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		destroy_mutexes(int num, t_input *input)
{
	int i;

	i = 0;
	while (i < num)
	{
		if (pthread_mutex_destroy(&input->forks[i]))
		{
			ft_putendl_fd("pthread_mutex_destroy fork failed", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	free(input->forks);
	if (pthread_mutex_destroy(&input->display))
	{
		ft_putendl_fd("pthread_mutex_destroy display failed", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	free_stuff(t_options **options, t_input *input)
{
	int i;

	free(input->eat_num);
	free(input);
	i = 0;
	while (options[i])
	{
		free(options[i]);
		i++;
	}
	free(options);
}

int		join_threads(int num, pthread_t *threads)
{
	int i;

	i = 0;
	while (i < num)
	{
		if (pthread_join(threads[i], NULL))
		{
			ft_putendl_fd("pthread_join failed", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	free(threads);
	return (EXIT_SUCCESS);
}
