/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 18:19:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/18 09:24:43 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		check_priority(t_options *options)
{
	int right;
	int left;

	if (options->latest_meal == UNSET)
		return (YES);
	right = options->eat_num[get_right_index(options)];
	left = options->eat_num[get_left_index(options)];
	if (options->count_left < left &&
	options->count_right < right)
		return (YES);
	else
		return (NO);
}

/*
** avant d'autoriser le philosophe a manger, on s'assure qu'il ne
** grille pas la priorité à ses voisins: avant de se resservir,
** il faut que ses deux voisins aient mangé !
*/

void	ft_eat(t_options *options)
{
	while (*(options->stop_all) == NO)
	{
		if (check_priority(options) == YES)
			break ;
		usleep(T_CHECK_PRIO);
	}
	lock_forks(options);
	ft_print_status(EAT, options);
	ft_wait(options->t_to_eat, options->stop_all);
	unlock_forks(options);
}

void	*cycle(void *void_options)
{
	t_options	*options;

	options = (t_options*)void_options;
	while (*(options->stop_all) == NO)
	{
		ft_eat(options);
		ft_print_status(SLEEP, options);
		ft_wait(options->t_to_sleep, options->stop_all);
		ft_print_status(THINK, options);
	}
	return (NULL);
}
