/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 07:04:49 by akaabi            #+#    #+#             */
/*   Updated: 2023/07/27 07:56:48 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(t_philos *list, t_philod *data, \
long long current_time, int time_tosleep)
{
	while (get_time() - current_time < time_tosleep)
	{
		if (get_time() - list->last_eat >= data->timet_die)
		{
			sem_wait(data->print);
			printf ("%lld ms %d is dead\n", get_time() - list->last_eat, \
			list->id + 1);
			exit (1);
		}
	}
}

void	my_printf(t_philod *data, int id, char *msg)
{
	sem_wait(data->print);
	printf("%lld\t%d\t%s\n", get_time() - data->time, id + 1, msg);
	sem_post(data->print);
}
