/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_end.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 17:44:10 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/17 19:05:33 by bbrunet          ###   ########.fr       */
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
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int		destroy_sem(t_input *input, int num)
{
	if (close_unlink(input->prio, num) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (sem_close(input->display))
	{
		ft_putendl_fd("sem_close failed", 2);
		return (EXIT_FAILURE);
	}
	if (sem_unlink("display"))
		return (EXIT_FAILURE);
	if (input->stop_game)
	{
		if (sem_close(input->stop_game))
		{
			ft_putendl_fd("sem_close failed", 2);
			return (EXIT_FAILURE);
		}
		if (sem_unlink("stop game"))
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
	free(input->pid_tab);
	free(input);
}
