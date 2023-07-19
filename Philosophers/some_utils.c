/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 23:57:16 by akaabi            #+#    #+#             */
/*   Updated: 2023/07/19 06:17:26 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

LL get_Time() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void ft_usleep(t_philos *list, t_philod *data, LL current_time, int time_tosleep)
{
    while (get_Time() - current_time < time_tosleep)
    {
        if (get_Time() - list->last_eat >= data->timet_die)
        {
            pthread_mutex_lock(data->print);
            printf ("%lld ms %d is dead\n", get_Time() - list->last_eat ,list->id + 1);
            list->flag = 1;
            return ;
        }
    }
}
