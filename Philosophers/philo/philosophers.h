/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:43:37 by akaabi            #+#    #+#             */
/*   Updated: 2023/09/04 16:14:17 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philos{
	struct s_philod	*data;
	int				id;
	int				left_f;
	int				right_f;
	int				num_eaten;
	int				flag;
	long long		last_eat;
	pthread_t		ph;
}	t_philos;

typedef struct s_philod{
	t_philos		*philos;
	int				num_philo;
	int				flag1;
	int				flag2;
	int				timet_die;
	int				timet_eat;
	int				timet_sleep;
	int				mealste_philo;
	long long		time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	flag;
	pthread_mutex_t	meals;
}	t_philod;

//philosophers.c
t_philod	*fill_to_atoi(int ac, char **av);
int			ft_atoi(char *str);
int			checking_digit(char **s);
int			ft_isdigit(int c);
//philo.c
void		*routine(void *arg);
int			number_ofphilos(t_philod *p);
t_philos	*fill_philos(t_philod **d);
void		ft_free(t_philod *data);
//some_utils.c
long long	get_time(void);
void		ft_usleep(t_philos *list, t_philod *data, long long current_time, \
int time_to);
void		my_printf(t_philod *data, int id, char *msg);
void		my_loop(t_philod *data);
//states.c
void		taking_forks(t_philod *data, t_philos *list);
void		eating(t_philod *data, t_philos *list);
void		sleeping(t_philod *data, t_philos *list);
void		to_destroy(t_philod *data);
void		initialise(t_philod *data);
#endif