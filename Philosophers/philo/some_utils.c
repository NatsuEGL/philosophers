/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 07:04:49 by akaabi            #+#    #+#             */
/*   Updated: 2023/07/25 06:50:01 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

LL	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(t_philos *list, t_philod *data, \
LL current_time, int time_tosleep)
{
	while (get_time() - current_time < time_tosleep)
	{
		if (get_time() - list->last_eat >= data->timet_die)
		{
			pthread_mutex_lock(&data->print);
			printf ("%lld ms %d is dead\n", get_time() - list->last_eat, \
			list->id + 1);
			pthread_mutex_lock(&data->flag);
			data->flag1 = 1;
			pthread_mutex_unlock(&data->flag);
			return ;
		}
	}
}

void	my_printf(t_philod *data, int id, char *msg)
{
	pthread_mutex_lock(&data->print);
	printf("%lld\t%d\t%s\n", get_time() - data->time, id + 1, msg);
	pthread_mutex_unlock(&data->print);
}

void	my_loop(t_philod *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->flag);
		if (data->flag1 == 1)
			return ;
		pthread_mutex_lock(&data->meals);
		if (data->flag2 == data->num_philo)
		{
			pthread_mutex_unlock(&data->meals);
			break ;
		}
		pthread_mutex_unlock(&data->meals);
		pthread_mutex_unlock(&data->flag);
	}
}
