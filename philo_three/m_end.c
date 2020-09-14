/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_end.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 17:44:10 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/11 11:37:52 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		destroy_sem(t_input *input)
{
	if (sem_close(input->sem))
	{
		ft_putendl_fd("sem_close failed", 2);
		return (EXIT_FAILURE);
	}
	if (sem_unlink("semaphore"))
	{
		ft_putendl_fd("sem_unlink failed", 2);
		return (EXIT_FAILURE);
	}
	if (sem_close(input->display))
	{
		ft_putendl_fd("sem_close failed", 2);
		return (EXIT_FAILURE);
	}
	if (sem_unlink("display"))
	{
		ft_putendl_fd("sem_unlink failed", 2);
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
