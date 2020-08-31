/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:14:39 by bbrunet           #+#    #+#             */
/*   Updated: 2020/08/31 11:00:19 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h> // usleep, write
#include <stdlib.h> //malloc
#include <string.h> // memset
#include "stdio.h" // printf


size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_itoa(long int nlong);

typedef struct  s_options
{
    int identifier;
    int t_to_die;
    int t_to_eat;
    int t_to_sleep;
    int num_of_time;
    pthread_mutex_t *fork_l; // fourchette gauche: pointeur sur une des fourchettes
    pthread_mutex_t *fork_r; // fourchette à droite: pointeur sur une des fourchettes
}               t_options;

enum	e_state
{
	FORK,
    EAT,
	SLEEP,
	THINK,
	DIE
};

pthread_mutex_t lock_out;