/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:09:15 by vico              #+#    #+#             */
/*   Updated: 2021/11/05 20:56:31 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) +(time.tv_usec / 1000));
}

void	sleep_better(long sleep)
{
	long	max;

	max = sleep + current_time();
	while (max > current_time())
		usleep(10);
}

int	max_min(char **av, char *max, char *min)
{
	int		i;
	int		j;

	i = -1;
	while (av[++i])
	{
		j = 0;
		if (ft_isdigit(av[i][0]) || (av[i][0] == '+' && !j++))
		{
			if ((int)ft_strlen(av[i]) > 10 + j)
				return (0);
			else if ((int)ft_strlen(av[i]) == 10 + j && \
			ft_strcmp(max + 1 - j, av[i]) < 0)
				return (0);
		}
		else if (av[i][0] == '-' && !j++)
		{
			if ((int)ft_strlen(av[i]) > 10 + j)
				return (0);
			else if ((int)ft_strlen(av[i]) == 10 + j && \
			ft_strcmp(min, av[i]) < 0)
				return (0);
		}
	}
	return (1);
}

int	little_parsing(int ac, char **av)
{
	int		i;
	int		j;

	if (ac < 5)
		return (0);
	else if (ac > 6)
		return (0);
	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (!(ft_isdigit(av[i][j])) && j > 0)
				return (0);
			else if (!(ft_isdigit(av[i][j])) && j == 0 && av[i][j] != '+')
				return (0);
		}
	}
	if (!(max_min(av, "+2147483647", "-2147483648")))
		return (0);
	return (1);
}
