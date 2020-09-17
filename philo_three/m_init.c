/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:34:38 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/17 15:45:22 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		init_other(int num, t_input *input)
{
	input->pid_tab = malloc(num * sizeof(pid_t));
	return (EXIT_SUCCESS);
}

int		init_input(int num_philo, t_input **input, char *eat_max)
{
	*input = malloc(sizeof(t_input));
	if (init_sem_display(num_philo, *input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_sem_eat(num_philo, *input, eat_max) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_sem_prio(num_philo, *input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_other(num_philo, *input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
