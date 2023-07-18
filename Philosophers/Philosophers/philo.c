/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:10:48 by akaabi            #+#    #+#             */
/*   Updated: 2023/07/18 02:09:32 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *arg)
{
    t_philos *philo = (t_philos *)arg;
    t_philod *data = philo->data;

	if (philo->id == 0)
		data->time = getTimeInMilliseconds();
	if (philo->id % 2 != 0)
		usleep(200);
    while (1) {
        // Step 1: Take forks
        pthread_mutex_lock(&data->forks[philo->right_f]);
        pthread_mutex_lock(&data->forks[philo->left_f]);
        printf("%lld  %d is taking forks\n",(getTimeInMilliseconds() - data->time), philo->id + 1);
        printf("%lld  %d is taking forks\n",(getTimeInMilliseconds() - data->time), philo->id + 1);
        // Step 2: Eat
        printf("%lld %d is eating\n", (getTimeInMilliseconds() - data->time),philo->id + 1);
		ft_usleep(getTimeInMilliseconds(), data->timet_eat);
		data->mealste_philo--;
		if ((getTimeInMilliseconds() - data->time) >= data->timet_die)
		{
			printf("died\n");
			exit(1);
		}
		if (data->mealste_philo == 0)
			exit (0);
        // Step 3: Sleep
        printf("%lld %d is sleeping\n",(getTimeInMilliseconds() - data->time), philo->id + 1);
		ft_usleep(getTimeInMilliseconds(), data->timet_sleep);
        pthread_mutex_unlock(&data->forks[philo->right_f]);
        pthread_mutex_unlock(&data->forks[philo->left_f]);
        // Step 5: Think
        printf("%lld %d is thinking\n",(getTimeInMilliseconds() - data->time), philo->id + 1);
    } 

    return NULL;
}


void	number_ofphilos(t_philod *p)
{
	int i;
	int k;

	i = 0;
    p->forks = malloc(sizeof(pthread_mutex_t) * p->num_philo);
	while (i < p->num_philo)
	{
   	 	pthread_mutex_init(&p->forks[i], NULL);
		i++;	
	}
	k = 0;
	i = 0;
	while (i < p->num_philo)
	{
		if (pthread_create(&p->philos[i].ph , NULL, &routine , (void *)&p->philos[i]) != 0)
			return ;
		i++;
	}
	while (k < p->num_philo)
	{
		if (pthread_join((p->philos[k].ph) , NULL) != 0)
			return ;
		k++;
	}
}

void fill_philos(t_philod *data)
{
	int i;

	i = 0;
	data->philos = malloc(sizeof(t_philos) * data->num_philo);
	while (i < data->num_philo)
	{
		data->philos[i].id = i;
		data->philos[i].data = data;
		data->philos[i].num_eated = 0;
		data->philos[i].left_f = i; 
		data->philos[i].right_f = (i + 1) % data->num_philo;
		i++;
	}
	number_ofphilos(data);
}
