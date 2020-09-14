/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:34:38 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/14 17:06:45 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

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
		input->prio[i].name = ft_itoa((long)i);
		sem_unlink(input->prio[i].name);
		input->prio[i].lock = sem_open(input->prio[i].name, O_CREAT | O_EXCL, S_IRWXU, 1);
		if (input->prio[i].lock == SEM_FAILED)
		{
			ft_putendl_fd("sem_open failed", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int		init_sem(int num, t_input *input)
{
	sem_unlink("semaphore");
	sem_unlink("display");
	input->sem = sem_open("semaphore", O_CREAT | O_EXCL, S_IRWXU, num);
	if (input->sem == SEM_FAILED)
	{
		ft_putendl_fd("sem_open failed", 2);
		return (EXIT_FAILURE);
	}
	input->display = sem_open("display", O_CREAT | O_EXCL, S_IRWXU, 1);
	if (input->display == SEM_FAILED)
	{
		ft_putendl_fd("sem_open failed", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	fill_eat_num(int *eat_num, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		eat_num[i] = 0;
		i++;
	}
}

int		fill_vars(int num, t_input *input)
{
	if (!(input->eat_num = malloc(num * sizeof(int))))
	{
		ft_putendl_fd("malloc failed", 2);
		return (EXIT_FAILURE);
	}
	fill_eat_num(input->eat_num, num);
	input->stop_all = NO;
	return (EXIT_SUCCESS);
}

int		init_input(int num_philo, t_input **input)
{
	*input = malloc(sizeof(t_input));
	if (init_sem(num_philo, *input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_sem_prio(num_philo, *input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (fill_vars(num_philo, *input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
