/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 18:46:14 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/17 18:52:57 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int     create_processes(t_input *input, t_options **options)
{
	int i;
	
    i = 0;
	while (options[i])
	{
		input->pid_tab[i] = fork();
		if (input->pid_tab[i] == -1)
        {
            ft_putendl_fd("fork() failed", 2);
            return (EXIT_FAILURE);
        }
        if (input->pid_tab[i] == 0)
		{
			cycle(options[i]);
			return (0);
		}
		i++;
	}
    return (EXIT_SUCCESS);
    
}

void    wait_end(t_input *input, int num)
{
    int i;
       
	i = 0;
	while (i < num)
	{
		sem_wait(input->stop_game);
		i++;
	}
}

void    kill_processes(t_options **options, t_input *input)
{
	int i;
    
    i = 0;
	while (options[i])
	{
		kill(input->pid_tab[i], SIGKILL);
		i++;
	}
}

int     play_game(t_input *input, t_options **options, int num)
{
	
	if (create_processes(input, options) == EXIT_FAILURE)
		return (EXIT_FAILURE);
    wait_end(input, num);
    kill_processes(options, input);
	return (EXIT_SUCCESS);
}
