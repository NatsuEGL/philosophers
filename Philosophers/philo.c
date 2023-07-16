/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:10:48 by akaabi            #+#    #+#             */
/*   Updated: 2023/07/16 01:26:33 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *arg)
{
    t_philos *philo = (t_philos *)arg;
    t_philod *data = philo->data;

    // Accessing the forks (assumed to be global variables)
    pthread_mutex_t *leftFork = &(data->forks[philo->left_f]);
    pthread_mutex_t *rightFork = &(data->forks[philo->right_f]);

	if (philo->id == 0)
		getTimeInMilliseconds();
	if (philo->id % 2 == 0)
		usleep(200);
    while (1) {
        // Step 1: Take forks
        printf("Philosopher %d is taking forks\n", philo->id);
        pthread_mutex_lock(leftFork);
        pthread_mutex_lock(rightFork);

        // Step 2: Eat
        printf("Philosopher %d is eating\n", philo->id);

        // Step 3: Sleep
        printf("Philosopher %d is sleeping\n", philo->id);

        // Step 4: Release forks
        printf("Philosopher %d is releasing forks\n", philo->id);
        pthread_mutex_unlock(leftFork);
        printf("Philosopher %d released left fork\n", philo->id);
        pthread_mutex_unlock(rightFork);
        printf("Philosopher %d released right fork\n", philo->id);

        // Step 5: Think
        printf("Philosopher %d is thinking\n", philo->id);
    }

    return NULL;
}


void	number_ofphilos(t_philod *p)
{
	int i;
	int k;

	k = 0;
	i = 0;
	while (i < p->num_philo)
	{
		if (pthread_create(&p->philos[i].ph , NULL, &routine , (void *)&p->philos[i]) != 0)
		{
			puts("zab");
			return ;
		}
		i++;
	}
	while (k < p->num_philo)
	{
		if (pthread_join((p->philos[k].ph) , NULL) != 0)
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
