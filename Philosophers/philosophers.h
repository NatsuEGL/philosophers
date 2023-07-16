/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:43:37 by akaabi            #+#    #+#             */
/*   Updated: 2023/07/16 01:18:03 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct s_philos{
	struct s_philod *data;
	int 	id;
	int 	left_f;
	int 	right_f;
	int		num_eated;
	pthread_t ph;
} t_philos;

typedef struct s_philod{
	t_philos 		*philos;
	int 			num_philo;
	int 			timet_die;
	int 			timet_eat;
	int 			timet_sleep;
	int 			numte_philo;
	pthread_mutex_t	*forks;
} t_philod ;

//philosophers.c
void fill_to_atoi(int ac, char **av, t_philod *p);
int	ft_atoi(char *str);
int checking_digit(char **s);
int ft_isdigit(int c);
//philo.c
void *routine(void *arg);
void	number_ofphilos(t_philod *p);
void fill_philos(t_philod *data);
//some_utils.c
long getTimeInMilliseconds();


#endif