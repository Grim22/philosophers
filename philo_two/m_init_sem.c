/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init_sem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 15:06:49 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/15 15:20:17 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		init_firsts(t_input *in, int i)
{
	in->prio[i].name = ft_itoa((long)i);
	sem_unlink(in->prio[i].name);
	if (i % 2 == 0)
		in->prio[i].lock =
		sem_open(in->prio[i].name, O_CREAT | O_EXCL, S_IRWXU, 2);
	else
		in->prio[i].lock =
		sem_open(in->prio[i].name, O_CREAT | O_EXCL, S_IRWXU, 0);
	if (in->prio[i].lock == SEM_FAILED)
	{
		ft_putendl_fd("sem_open failed", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		init_last(t_input *in, int num)
{
	int i;

	i = num - 1;
	in->prio[i].name = ft_itoa((long)i);
	sem_unlink(in->prio[i].name);
	if (num % 2 == 0)
		in->prio[i].lock =
		sem_open(in->prio[i].name, O_CREAT | O_EXCL, S_IRWXU, 0);
	else
		in->prio[i].lock =
		sem_open(in->prio[i].name, O_CREAT | O_EXCL, S_IRWXU, 1);
	if (in->prio[i].lock == SEM_FAILED)
	{
		ft_putendl_fd("sem_open failed", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		init_sem_prio(int num, t_input *input)
{
	int i;

	if (!(input->prio = malloc(sizeof(t_priority) * num)))
	{
		ft_putendl_fd("malloc failed", 2);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < num - 1)
	{
		if (init_firsts(input, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	if (init_last(input, num) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		init_sem_display(int num, t_input *input)
{
	// sem_unlink("semaphore");
	// input->sem = sem_open("semaphore", O_CREAT | O_EXCL, S_IRWXU, num);
	// if (input->sem == SEM_FAILED)
	// {
	// 	ft_putendl_fd("sem_open failed", 2);
	// 	return (EXIT_FAILURE);
	// }
	(void)num;
	sem_unlink("display");
	input->display = sem_open("display", O_CREAT | O_EXCL, S_IRWXU, 1);
	if (input->display == SEM_FAILED)
	{
		ft_putendl_fd("sem_open failed", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
