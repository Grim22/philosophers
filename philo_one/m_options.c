/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_options.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:02:42 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/01 11:02:44 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	fill_args(t_options *options, int argc, char **argv, int identifier)
{
	options->identifier = identifier + 1;
	options->t_to_die = ft_atoi(argv[2]);
	options->t_to_eat = ft_atoi(argv[3]);
	options->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		options->num_of_time = ft_atoi(argv[5]);
}

void	fill_options(t_options ***options, int num_philo, int argc, char **argv, pthread_mutex_t *fork)
{
	int i;
	
	*options = malloc(num_philo * sizeof(t_options*)); // malloc du tableau de t_option*
	
	i = 0;
 	// malloc du premier t_option*
	options[0][i] = malloc(sizeof(t_options));
	// fill du premier t_option
	fill_args(options[0][i], argc, argv, i); 
	options[0][i]->fork_l = &fork[i];
	if (num_philo > 1)
		options[0][i]->fork_r = &fork[i + 1];
	else
		options[0][i]->fork_r = &fork[i]; // c'est la meme fourchette a gauche et a droite
	
	i++;
	while (i < num_philo - 1)
	{
		options[0][i] = malloc(sizeof(t_options));
		fill_args(options[0][i], argc, argv, i);
		options[0][i]->fork_l = &fork[i];
		options[0][i]->fork_r = &fork[i + 1];
		i++;
	}
	
	// malloc et fill du dernier t_option
	if (num_philo > 1)
	{
		options[0][i] = malloc(sizeof(t_options));
		fill_args(options[0][i], argc, argv, i);
		options[0][i]->fork_l = &fork[i];
		options[0][i]->fork_r = &fork[0];
	}
}