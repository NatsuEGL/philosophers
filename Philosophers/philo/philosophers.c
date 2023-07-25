/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:35:51 by akaabi            #+#    #+#             */
/*   Updated: 2023/07/25 07:06:00 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	checking_digit(char **s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (!ft_isdigit(s[i][j]))
			{
				write (2, "Error\n", 6);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int		i;
	int		r;
	int		s;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return (r * s);
}

t_philod	*fill_to_atoi(int ac, char **av)
{
	t_philod	*p;

	p = malloc(sizeof(t_philod));
	p->num_philo = ft_atoi(av[1]);
	p->timet_die = ft_atoi(av[2]);
	p->timet_eat = ft_atoi(av[3]);
	p->timet_sleep = ft_atoi(av[4]);
	if (ac == 6)
		p->mealste_philo = ft_atoi(av[5]);
	else
		p->mealste_philo = -1;
	return (p);
}

int	main(int ac, char **av)
{
	int			i;
	t_philod	*p;
	t_philos	*list;

	if (ac > 6 || ac < 5)
	{
		printf("some is wrong in ur ags\n");
	}
	i = 1;
	p = NULL;
	list = NULL;
	if (!checking_digit(&av[i]))
		return (0);
	p = fill_to_atoi(ac, av);
	fill_philos(&p);
	number_ofphilos(p, list);
	ft_free(p);
	return (0);
}
