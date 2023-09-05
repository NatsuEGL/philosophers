/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:10:48 by akaabi            #+#    #+#             */
/*   Updated: 2023/09/05 15:09:46 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
	exit (0);
}

void	states(pid_t *pid, int philo_num)
{
	int	i;
	int	status;

	if (!philo_num)
		return ;
	i = 0;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		while (pid[i])
			kill(pid[i++], SIGKILL);
	}
	else
		states(pid, philo_num--);
}

void	number_ofphilos(t_philod *p, t_philos *list)
{
	int	i;

	list = NULL;
	initialise(p);
	i = 0;
	p->time = get_time();
	while (i < p->num_philo)
	{
		p->pid[i] = fork();
		if (p->pid[i] == 0)
		{
			routine(&p->philos[i]);
		}
		i++;
	}
	states(p->pid, p->num_philo);
	to_destroy(p);
}

t_philos	*fill_philos(t_philod **d)
{
	int			i; 
	t_philod	*data;

	data = *d;
	i = 0;
	data->philos = malloc(sizeof(t_philos) * data->num_philo);
	while (i < data->num_philo)
	{
		data->philos[i].id = i;
		data->philos[i].num_eaten = data->mealste_philo;
		data->philos[i].data = data;
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
