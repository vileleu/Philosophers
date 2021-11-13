/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listes_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:17:50 by vico              #+#    #+#             */
/*   Updated: 2021/11/11 04:42:55 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	init_phil(t_phil *phil, char **av)
{
	phil->p_nb = ft_atoi(av[1]);
	phil->t_die = ft_atoi(av[2]);
	phil->t_eat = ft_atoi(av[3]);
	phil->t_sleep = ft_atoi(av[4]);
	phil->max_eat = 0;
	gettimeofday(&(phil->time_ref), NULL);
	phil->time_ref.tv_usec /= 1000;
	if (av[5])
		phil->max_eat = ft_atoi(av[5]);
}

int	free_p(t_phil *phil)
{
	free(phil->phil);
	return (0);
}

int	loop_thread(t_phil *phil, int i)
{
	phil->phil[i].phil = phil;
	phil->phil[i].time_ref = phil->time_ref;
	phil->phil[i].p_nb = phil->p_nb;
	phil->phil[i].nb = i + 1;
	phil->phil[i].t_die = phil->t_die;
	phil->phil[i].t_eat = phil->t_eat;
	phil->phil[i].t_sleep = phil->t_sleep;
	phil->phil[i].c_eat = 1;
	phil->phil[i].each_eat = 0;
	pthread_mutex_init(&(phil->phil[i].samet), NULL);
	phil->phil[i].proc = fork();
	if (phil->phil[i].proc == 0)
	{
		actions(&(phil->phil[i]));
		exit(EXIT_SUCCESS);
	}
	usleep(100);
	return (1);
}

int	launch_phil_bis(t_phil *phil)
{
	int	i;

	i = -1;
	phil->dead = sem_open(DEAD, O_CREAT | O_EXCL, 0644, 0);
	if (phil->dead < (sem_t *)0)
		return (sem_err());
	while (++i < phil->p_nb)
		loop_thread(phil, i);
	return (1);
}

int	launch_phil(t_phil *phil)
{
	phil->phil = (t_p *)malloc(sizeof(t_p) * phil->p_nb);
	if (!(phil->phil))
		return (malloc_err());
	sem_unlink(FORK);
	phil->fork = sem_open(FORK, O_CREAT | O_EXCL, 0644, phil->p_nb);
	if (phil->fork < (sem_t *)0)
		return (sem_err());
	sem_unlink(PRINT);
	phil->print = sem_open(PRINT, O_CREAT | O_EXCL, 0644, 1);
	if (phil->print < (sem_t *)0)
		return (sem_err());
	sem_unlink(EAT);
	phil->eat = sem_open(EAT, O_CREAT | O_EXCL, 0644, 0);
	if (phil->eat < (sem_t *)0)
		return (sem_err());
	sem_unlink(DEAD);
	return (launch_phil_bis(phil));
}
