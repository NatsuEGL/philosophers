/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:10:48 by akaabi            #+#    #+#             */
/*   Updated: 2023/07/19 06:19:37 by akaabi           ###   ########.fr       */
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
		usleep(800);
    while (1) 
	{
        // Taking Forks
        pthread_mutex_lock(&data->forks[philo->right_f]);
        pthread_mutex_lock(data->print);
        printf("%lld\t%d\thas taken a fork\n", get_Time() - data->time, philo->id + 1);
		pthread_mutex_unlock(data->print);
        pthread_mutex_lock(&data->forks[philo->left_f]);
        pthread_mutex_lock(data->print);
        printf("%lld\t%d\thas taken a fork\n", get_Time() - data->time, philo->id + 1);
		pthread_mutex_unlock(data->print);
        // Eating
        pthread_mutex_lock(data->print);
        printf("%lld\t%d\tis eating\n", get_Time() - data->time, philo->id + 1);
		pthread_mutex_unlock(data->print);
		philo->last_eat = get_Time();
		ft_usleep(philo, data, get_Time(), data->timet_eat);
        pthread_mutex_unlock(&data->forks[philo->right_f]);
        pthread_mutex_unlock(&data->forks[philo->left_f]);
		// pthread_mutex_lock(data->mealste_philo);
		// pthread_mutex_lock(data->mealste_philo);
		// data->mealste_philo--;
		// if (data->mealste_philo == 0)
		// 	return 0;
        // Sleeping
        pthread_mutex_lock(data->print);
        printf("%lld\t%d\tis sleeping\n",get_Time() - data->time, philo->id + 1);
		pthread_mutex_unlock(data->print);
		ft_usleep(philo, data, get_Time(), data->timet_sleep);
        // Thinking
        pthread_mutex_lock(data->print);
        printf("%lld\t%d\tis thinking\n",get_Time() - data->time, philo->id + 1);
        pthread_mutex_unlock(data->print);
    }
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
	while (i < p->num_philo)
	{
   	 	pthread_mutex_init(&p->forks[i], NULL);
   	 	pthread_mutex_init(&p->print[i], NULL);
		i++;	
	}
	k = 0;
	i = 0;
	while (i < p->num_philo)
	{
		if (pthread_create(&p->philos[i].ph , NULL, &routine , (void *)&p->philos[i]) != 0)
			return ;
		pthread_detach(p->philos[i].ph);
		i++;
	}
	// while (i < p->num_philo)
	// {
	// 	i++;
	// }
	// while (k < p->num_philo)
	// {
	// 	//  if (pthread_join(p->philos[k].ph, NULL) != 0)
	// 	if (pthread_detach(p->philos[k].ph) != 0)
	// 		return ;
	// 	k++;
	// }
	int markik = 0;
	while(1)
	{
		if (p->philos[markik].flag == 0)
			return ;
		else if (markik >= p->num_philo - 1)
			markik = -1;
		markik++;
	}
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
		data->philos[i].flag = 0;
		data->philos[i].data = data;
		data->philos[i].num_eated = 0;
		data->philos[i].left_f = i; 
		data->philos[i].right_f = (i + 1) % data->num_philo;
		i++;
	}
	number_ofphilos(data, data->philos);
}

