/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:29:36 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/17 14:48:17 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int	check_args(int argc, char **argv)
{
	int i;

	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("wrong number of args", 2);
		return (EXIT_FAILURE);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_isdigit_str(argv[i]) == 0)
		{
			ft_putendl_fd("non digit or zero argument", 2);
			return (EXIT_FAILURE);
		}
		if (ft_strlen(argv[i]) > 9)
		{
			ft_putendl_fd("too big number", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_num_philo(int *num, char *argv1)
{
	*num = ft_atoi(argv1);
	if (*num == 1)
	{
		ft_putendl_fd("philo need to be at least two to play", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int create_processes(t_input *input, t_options **options, int num)
{
	int i;
	int status;
	int	ret;
	
	(void)num;
	i = 0;
	while (options[i])
	{
		input->pid_tab[i] = fork();
		if (input->pid_tab[i] == 0)
		{
			cycle(options[i]);
			return (0);
		}
		i++;
	}
	ret = wait(&status);
	printf("post wait\n");
	i = 0;
	while (options[i])
	{
		kill(input->pid_tab[i], SIGKILL);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_options		**options;
	int				num_philo;
	t_input			*input;

	if (check_args(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_num_philo(&num_philo, argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_input(num_philo, &input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_options(&options, argv, input, num_philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_processes(input, options, num_philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (destroy_sem(input, num_philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	free_stuff(options, input, num_philo);
}
