/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 23:57:16 by akaabi            #+#    #+#             */
/*   Updated: 2023/07/24 07:26:49 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	taking_forks(t_philod *data, t_philos *list)
{
	list->last_eat = get_time();
	pthread_mutex_lock(&data->forks[list->right_f]);
	my_printf(data, list->id, "has taken a fork");
	if (data->num_philo == 1)
	{
		ft_usleep(list, data, get_time(), data->timet_die + 1);
	}
	pthread_mutex_lock(&data->forks[list->left_f]);
	my_printf(data, list->id, "has taken a fork");
}

void	eating(t_philod *data, t_philos *list)
{
	my_printf(data, list->id, "is eating");
	ft_usleep(list, data, get_time(), data->timet_eat);
	list->last_eat = get_time();
	list->num_eaten--;
	pthread_mutex_unlock(&data->forks[list->right_f]);
	pthread_mutex_unlock(&data->forks[list->left_f]);
}

void	sleeping(t_philod *data, t_philos *list)
{
	my_printf(data, list->id, "is sleeping");
	ft_usleep(list, data, get_time(), data->timet_sleep);
	my_printf(data, list->id, "is thinking");
}

void	to_destroy(t_philod *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(data->print);
	pthread_mutex_destroy(data->flag);
	pthread_mutex_destroy(&data->meals);
	return ;
}

void	initialise(t_philod *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	data->print = malloc(sizeof(pthread_mutex_t));
	data->flag = malloc(sizeof(pthread_mutex_t));
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(data->print, NULL);
	pthread_mutex_init(data->flag, NULL);
	pthread_mutex_init(&data->meals, NULL);
}
