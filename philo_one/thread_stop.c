/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_stop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:57:56 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/03 15:56:03 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"


int     check_stop(t_options **options)
{
    int enough_food;
    int i;

    i = 0;
    enough_food = YES;
    while (options[i])
    {
        if (options[i]->died == YES)
            return (YES);
        if (options[i]->enough_food == NO)
            enough_food = NO;
        i++;
    }
    if (enough_food == YES)
        return (YES);
    else
        return (NO);
}

void    stop_all(t_options **options)
{
    int i;

    i = 0;
    while (options[i])
    {
        options[i]->stop_all = YES;
        i++;
    }
}

void    *stop(void *void_options)
{
    t_options   **options;

    options = (t_options **)void_options;
    while (1)
    {
        if (check_stop(options) == YES)
        {
            stop_all(options); 
            return (NULL);
        }
        usleep(1);
    }
    return (NULL);
}