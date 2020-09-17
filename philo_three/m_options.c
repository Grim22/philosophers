/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_options.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:02:42 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/17 11:58:33 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	fill_args(t_options *options, char **argv, int identifier)
{
	options->identifier = identifier + 1;
	options->num_philo = ft_atoi(argv[1]);
	options->t_to_die = ft_atoi(argv[2]);
	options->t_to_eat = ft_atoi(argv[3]);
	options->t_to_sleep = ft_atoi(argv[4]);
	options->latest_meal = UNSET;
	options->stop_process = NO;
	if (argv[5])
		options->eat_max = ft_atoi(argv[5]);
	else
		options->eat_max = UNSET;
}

void	init_options_other(t_options **options, char **argv, t_input *input)
{
	int		i;
	long	time;

	(void)input;
	time = ft_get_mstime();
	i = 0;
	while (options[i])
	{
		options[i]->timestamp_start = time;
		fill_args(options[i], argv, i);
		i++;
	}
}

int		malloc_options(t_options ***options, int num)
{
	int i;

	i = 0;
	if (!(*options = malloc((num + 1) * sizeof(t_options*))))
	{
		ft_putendl_fd("malloc failed", 2);
		return (EXIT_FAILURE);
	}
	while (i < num)
	{
		if (!(options[0][i] = malloc(sizeof(t_options))))
		{
			ft_putendl_fd("malloc failed", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	options[0][i] = NULL;
	return (EXIT_SUCCESS);
}

/*
** Each philos has its own semaphore "prio",
**	which is decreased every time he eats
** Each philo has access to semaphore prio of his neighbours,
**	which are increased every time he eats
** (see m_init_sem.c and thread_philo_forks.c)
*/

void	init_options_sem(t_options **options, t_input *input, int num)
{
	int i;

	i = 0;
	while (options[i])
	{
		// options[i]->sem = input->sem;
		options[i]->display = input->display;
		options[i]->prio = input->prio[i].lock;
		if (i == 0)
			options[i]->prio_left = input->prio[num - 1].lock;
		else
			options[i]->prio_left = input->prio[i - 1].lock;
		if (i == num - 1)
			options[i]->prio_right = input->prio[0].lock;
		else
			options[i]->prio_right = input->prio[i + 1].lock;
		i++;
	}
}

int		init_options(t_options ***options, char **argv, t_input *input, int num)
{
	if (malloc_options(options, num) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_options_other(*options, argv, input);
	init_options_sem(*options, input, num);
	return (EXIT_SUCCESS);
}
