/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_stop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:57:56 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/04 12:42:08 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"


int     check_stop(t_options **options)
{
    int enough_food;
    int i;

    i = 0;
    if (options[i]->eat_max == UNSET)
        enough_food = NO;
    else
        enough_food = YES;
    while (options[i])
    {
        if (options[i]->died == YES)
            return (YES);
        if (options[i]->eat_max != UNSET)
        {
            if (options[i]->eat_num < options[i]->eat_max)
                enough_food = NO;
        }
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