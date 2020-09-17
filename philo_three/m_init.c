/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:34:38 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/17 11:59:32 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

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

int		init_other(int num, t_input *input)
{
	// if (!(input->eat_num = malloc(num * sizeof(int))))
	// {
	// 	ft_putendl_fd("malloc failed", 2);
	// 	return (EXIT_FAILURE);
	// }
	// fill_eat_num(input->eat_num, num);
	// input->stop_all = NO;
	input->pid_tab = malloc(num * sizeof(pid_t));
	return (EXIT_SUCCESS);
}

int		init_input(int num_philo, t_input **input)
{
	*input = malloc(sizeof(t_input));
	if (init_sem_display(num_philo, *input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_sem_prio(num_philo, *input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_other(num_philo, *input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
