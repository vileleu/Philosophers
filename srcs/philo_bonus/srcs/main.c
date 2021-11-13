/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 07:34:49 by vico              #+#    #+#             */
/*   Updated: 2021/11/04 19:53:08 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	print_time_end(t_phil *phil, char *prtf)
{
	struct timeval	time_cur;
	int				diff;
	int				usec;
	int				print_sec;

	print_sec = 0;
	gettimeofday(&(time_cur), NULL);
	time_cur.tv_usec /= 1000;
	diff = time_cur.tv_sec - phil->time_ref.tv_sec;
	if (diff > 0)
	{
		if (time_cur.tv_usec < phil->time_ref.tv_usec)
			print_sec = diff - 1;
		else if (time_cur.tv_usec >= phil->time_ref.tv_usec)
			print_sec = diff;
	}
	usec = time_cur.tv_usec - phil->time_ref.tv_usec;
	if (usec < 0)
		usec += 1000;
	printf("%01d%03d %s", print_sec, usec, prtf);
}

void	*check_count(void *arg)
{
	t_phil	*phil;
	int		i;

	phil = (t_phil *)arg;
	i = -1;
	while (++i < phil->p_nb * phil->max_eat)
		sem_wait(phil->eat);
	sem_wait(phil->print);
	sem_post(phil->dead);
	print_time_end(phil, "each philosophers ate\n");
	return ((void *)0);
}

int	main(int ac, char **av)
{
	pthread_t	c_maxeat;
	t_phil		phil;
	int			i;

	if (!(little_parsing(ac, av)))
		return (arg_err());
	init_phil(&phil, av);
	if (!(launch_phil(&phil)))
		return (0);
	if (phil.max_eat)
	{
		pthread_create(&c_maxeat, NULL, check_count, &phil);
		pthread_detach(c_maxeat);
	}
	sem_wait(phil.dead);
	i = -1;
	while (++i < phil.p_nb)
		kill(phil.phil[i].proc, SIGKILL);
	return (free_p(&phil));
}
