/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init_sem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 15:06:49 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/17 15:48:29 by bbrunet          ###   ########.fr       */
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

/*
** Sem_prios will be dispatched among philosophers: one for each philo
** "Even" philos will start with a semaphore value = 2
** "Odd" philos will start with a sem value = 0
** Each time a philo eats:
**	- its sem value is decreased by 2
**	- sem value of each of its neighbour is increased by one
** This system allows a rotation among philosophers:
**		philo_X will wait for philo_X+1 and philo_X-1 to eat
**		before it is allowed to eat again
** In case of an odd number of philosophers,
**		the "last" philo will get a sem value of 1,
**		to make a correct rotation possible
*/

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

int		init_sem_eat(int num, t_input *input, char *eat_max)
{
	int eat;
	
	if (eat_max == NULL)
	{
		input->eat_total = NULL;
		return (EXIT_SUCCESS);
	}
	eat = ft_atoi(eat_max);
	sem_unlink("eat_num");
	input->eat_total = sem_open("display", O_CREAT | O_EXCL, S_IRWXU, eat * num);
	if (input->eat_total == SEM_FAILED)
	{
		ft_putendl_fd("sem_open failed", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}