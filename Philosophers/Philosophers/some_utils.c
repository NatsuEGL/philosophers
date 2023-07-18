/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 23:57:16 by akaabi            #+#    #+#             */
/*   Updated: 2023/07/17 23:51:27 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

LL getTimeInMilliseconds() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void ft_usleep(LL current_time, int time_tosleep)
{

    while (1)
    {
        if (getTimeInMilliseconds() - current_time >= time_tosleep)
        {
            return ;
        }
    }
}
