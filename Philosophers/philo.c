/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:10:48 by akaabi            #+#    #+#             */
/*   Updated: 2023/07/21 02:00:33 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *arg)
{
    t_philos *philo = (t_philos *)arg;
    t_philod *data = philo->data;
	
	if (philo->id == 0)
		data->time = get_Time();
	if (philo->id % 2)
		usleep(200);
    while (philo->num_eaten) 
	{
        // Taking Forks
		philo->last_eat = get_Time();
        pthread_mutex_lock(&data->forks[philo->right_f]);
        my_printf(data, philo->id,"has taken a fork");
        pthread_mutex_lock(&data->forks[philo->left_f]);
        my_printf(data, philo->id,"has taken a fork");
        // Eating
        my_printf(data, philo->id,"is eating");
		ft_usleep(philo, data, get_Time(), data->timet_eat);
		philo->last_eat = get_Time();
		philo->num_eaten--;
        pthread_mutex_unlock(&data->forks[philo->right_f]);
        pthread_mutex_unlock(&data->forks[philo->left_f]);
        // Sleeping
        my_printf(data, philo->id,"is sleeping");
		ft_usleep(philo, data, get_Time(), data->timet_sleep);
        // Thinking
        my_printf(data, philo->id,"is thinking");
    }
	pthread_mutex_lock(&data->meals);
	data->flag2++;
	pthread_mutex_unlock(&data->meals);
    return NULL;
}


void	number_ofphilos(t_philod *p, t_philos *list)
{
	int i;
	int k;

	i = 0;
	list = NULL;
    p->forks = malloc(sizeof(pthread_mutex_t) * p->num_philo);
    p->print = malloc(sizeof(pthread_mutex_t));
    p->flag = malloc(sizeof(pthread_mutex_t));
	while (i < p->num_philo)
	{
   	 	pthread_mutex_init(&p->forks[i], NULL);
		i++;	
	}
   	pthread_mutex_init(p->print, NULL);
   	pthread_mutex_init(p->flag, NULL);
   	pthread_mutex_init(&p->meals, NULL);
	k = 0;
	i = 0;
	while (i < p->num_philo)
	{
		if (pthread_create(&p->philos[i].ph , NULL, &routine , (void *)&p->philos[i]) != 0)
			return ;
		i++;
	}
	while(1)
	{
		pthread_mutex_lock(p->flag);
		if (p->flag1 == 1)
			return ;
		pthread_mutex_lock(&p->meals);
		if (p->flag2 == p->num_philo)
		{
			pthread_mutex_unlock(&p->meals);
			break ;
		}
		pthread_mutex_unlock(&p->meals);
		pthread_mutex_unlock(p->flag);
	}
	while(k < p->num_philo)
	{
		pthread_mutex_destroy(&p->forks[k]);
		k++;
	}
	pthread_mutex_destroy(p->print);
	pthread_mutex_destroy(p->flag);
	pthread_mutex_destroy(&p->meals);
	return ;
}

void fill_philos(t_philod *data)
{
	int i;

	i = 0;
	data->philos = malloc(sizeof(t_philos) * data->num_philo);
	while (i < data->num_philo)
	{
		data->philos[i].id = i;
		data->flag1= 0;
		data->flag2= 0;
		data->philos[i].num_eaten = data->mealste_philo;
		data->philos[i].data = data;
		data->philos[i].left_f = i; 
		data->philos[i].right_f = (i + 1) % data->num_philo;
		i++;
	}
	number_ofphilos(data, data->philos);
}
