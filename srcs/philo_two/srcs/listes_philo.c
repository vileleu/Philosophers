/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listes_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:17:50 by vico              #+#    #+#             */
/*   Updated: 2021/05/27 05:07:14 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

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

int		free_p(t_phil *phil)
{
	free(phil->phil);
	return (0);
}

int		loop_thread(t_phil *phil, int i)
{
	pthread_t	thrd;

	phil->phil[i].phil = phil;
	phil->phil[i].time_ref = phil->time_ref;
	phil->phil[i].p_nb = phil->p_nb;
	phil->phil[i].nb = i + 1;
	phil->phil[i].t_die = phil->t_die;
	phil->phil[i].t_eat = phil->t_eat;
	phil->phil[i].t_sleep = phil->t_sleep;
	phil->phil[i].c_eat = 1;
	phil->phil[i].each_eat = 0;
	pthread_create(&(thrd), NULL, actions, &(phil->phil[i]));
	pthread_detach(thrd);
	usleep(100);
	return (1);
}

int		launch_phil(t_phil *phil)
{
	int	i;

	i = -1;
	if (!(phil->phil = (t_p*)malloc(sizeof(t_p) * phil->p_nb)))
		return (malloc_err());
	sem_unlink(FORK);
	if ((phil->fork = sem_open(FORK, O_CREAT | O_EXCL, 0644, phil->p_nb)) < \
	(sem_t*)0)
		return (sem_err());
	sem_unlink(BLOCK);
	if ((phil->block = sem_open(BLOCK, O_CREAT | O_EXCL, 0644, 1)) < (sem_t*)0)
		return (sem_err());
	sem_unlink(PRINT);
	if ((phil->print = sem_open(PRINT, O_CREAT | O_EXCL, 0644, 1)) < (sem_t*)0)
		return (sem_err());
	sem_unlink(DEAD);
	if ((phil->dead = sem_open(DEAD, O_CREAT | O_EXCL, 0644, 0)) < (sem_t*)0)
		return (sem_err());
	while (++i < phil->p_nb)
		loop_thread(phil, i);
	return (1);
}
