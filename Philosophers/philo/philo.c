/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:10:48 by akaabi            #+#    #+#             */
/*   Updated: 2023/09/04 16:47:58 by akaabi           ###   ########.fr       */
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
	if (philo->id % 2 != 0)
		usleep(500);
	philo->last_eat = get_time();
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

int	number_ofphilos(t_philod *p)
{
	int	i;

	initialise(p);
	i = 0;
	while (i < p->num_philo)
	{
		if (pthread_create(&p->philos[i].ph, NULL, &routine, \
		(void *)&p->philos[i]) != 0)
			return (-1);
		pthread_detach(p->philos[i].ph);
		i++;
	}
	my_loop(p);
	to_destroy(p);
	return (0);
}

t_philos	*fill_philos(t_philod **d)
{
	int			i;
	t_philod	*data;

	data = *d;
	i = 0;
	data->philos = malloc(sizeof(t_philos) * data->num_philo);
	if (!data->philos)
		return (0);
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
	return (data->philos);
}

void	ft_free(t_philod *data)
{
	free(data->forks);
	free(data->philos);
	free(data);
}
