/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:10:48 by akaabi            #+#    #+#             */
/*   Updated: 2023/07/24 07:27:18 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philos	*philo;
	t_philod	*data;

	philo = (t_philos *)arg;
	data = philo->data;
	if (philo->id == 0)
		data->time = get_time();
	if (philo->id % 2)
		usleep(200);
	while (philo->num_eaten)
	{
		taking_forks(data, philo);
		eating(data, philo);
		sleeping(data, philo);
	}
	pthread_mutex_lock(&data->meals);
	data->flag2++;
	pthread_mutex_unlock(&data->meals);
	return (NULL);
}

void	number_ofphilos(t_philod *p, t_philos *list)
{
	int	i;
	int	k;

	list = NULL;
	initialise(p);
	k = 0;
	i = 0;
	while (i < p->num_philo)
	{
		if (pthread_create(&p->philos[i].ph, NULL, &routine, \
		(void *)&p->philos[i]) != 0)
			return ;
		i++;
	}
	my_loop(p);
	to_destroy(p);
}

void	fill_philos(t_philod *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philos) * data->num_philo);
	while (i < data->num_philo)
	{
		data->philos[i].id = i;
		data->flag1 = 0;
		data->flag2 = 0;
		data->philos[i].num_eaten = data->mealste_philo;
		data->philos[i].data = data;
		data->philos[i].left_f = i;
		data->philos[i].right_f = (i + 1) % data->num_philo;
		i++;
	}
	number_ofphilos(data, data->philos);
}
