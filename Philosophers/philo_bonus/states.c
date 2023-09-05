/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 23:57:16 by akaabi            #+#    #+#             */
/*   Updated: 2023/09/04 16:46:41 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	taking_forks(t_philod *data, t_philos *list)
{
	sem_wait(data->forks);
	my_printf(data, list->id, "has taken a fork");
	if (data->num_philo == 1)
	{
		ft_usleep(list, data, get_time(), data->timet_die + 1);
	}
	sem_wait(data->forks);
	my_printf(data, list->id, "has taken a fork");
}

void	eating(t_philod *data, t_philos *list)
{
	my_printf(data, list->id, "is eating");
	ft_usleep(list, data, get_time(), data->timet_eat);
	list->last_eat = get_time();
	list->num_eaten--;
	sem_post(data->forks);
	sem_post(data->forks);
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
		sem_close(&data->forks[i]);
		i++;
	}
	sem_close(data->print);
	exit (0);
}

int	initialise(t_philod *data)
{
	sem_unlink("forks");
	sem_unlink("print");
	data->forks = sem_open("forks", O_CREAT, 777, data->num_philo);
	data->print = sem_open("print", O_CREAT, 777, 1);
	data->pid = malloc(sizeof(pid_t) * (data->num_philo + 1));
	if (!data->pid)
		return (-1);
	data->pid[data->num_philo] = 0;
	return (0);
}
