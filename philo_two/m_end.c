/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_end.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 17:44:10 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/16 12:26:32 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		close_unlink(t_priority *tab_prio, int num)
{
	int			i;
	t_priority	prio;

	i = 0;
	while (i < num)
	{
		prio = tab_prio[i];
		if (sem_close(prio.lock))
		{
			ft_putendl_fd("sem_close failed", 2);
			return (EXIT_FAILURE);
		}
		if (sem_unlink(prio.name))
		{
			ft_putstr_fd("sem_unlink prio failed with code:", 2);
			// ft_putendl_fd(ft_itoa(errno), 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int		destroy_sem(t_input *input, int num)
{
	if (close_unlink(input->prio, num) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// if (sem_close(input->sem))
	// {
	// 	ft_putendl_fd("sem_close failed", 2);
	// 	return (EXIT_FAILURE);
	// }
	// if (sem_unlink("semaphore"))
	// {
	// 	ft_putendl_fd("sem_unlink failed", 2);
	// 	return (EXIT_FAILURE);
	// }
	if (sem_close(input->display))
	{
		ft_putendl_fd("sem_close failed", 2);
		return (EXIT_FAILURE);
	}
	if (sem_unlink("display"))
	{
		ft_putstr_fd("sem_unlink display failed with code:", 2);
		// ft_putendl_fd(ft_itoa(errno), 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	free_stuff(t_options **options, t_input *input, int num)
{
	int i;

	i = 0;
	while (options[i])
	{
		free(options[i]);
		i++;
	}
	free(options);
	i = 0;
	while (i < num)
	{
		free(input->prio[i].name);
		i++;
	}
	free(input->prio);
	free(input->eat_num);
	free(input);
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
