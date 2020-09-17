/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:34:38 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/17 18:32:45 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		init_pids(int num, t_input *input)
{
	if (!(input->pid_tab = malloc(num * sizeof(pid_t))))
	{
		ft_putendl_fd("malloc failed", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		init_input(int num_philo, t_input **input)
{
	*input = malloc(sizeof(t_input));
	if (init_sem_display(*input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_sem_stop(*input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_sem_prio(num_philo, *input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_pids(num_philo, *input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
