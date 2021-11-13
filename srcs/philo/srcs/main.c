/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 20:38:40 by vico              #+#    #+#             */
/*   Updated: 2021/11/10 01:25:04 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_phil_bis(t_phil *phil)
{
	phil->l = malloc(sizeof(t_p));
	if (!(phil->l))
		return (0);
	pthread_mutex_init(&(phil->l->fork), NULL);
	pthread_mutex_init(&(phil->l->samet), NULL);
	phil->l->nb = phil->nb++;
	phil->l->each_eat = 0;
	phil->l->next = NULL;
	return (1);
}

void	print_time_end(t_phil *phil, char *prtf)
{
	struct timeval	time_cur;
	int				diff;
	int				usec;

	gettimeofday(&(time_cur), NULL);
	time_cur.tv_usec /= 1000;
	diff = time_cur.tv_sec - phil->time_ref.tv_sec;
	if (diff > 0)
	{
		if (time_cur.tv_usec < phil->time_ref.tv_usec)
			phil->t_sec = diff - 1;
		else if (time_cur.tv_usec >= phil->time_ref.tv_usec)
			phil->t_sec = diff;
	}
	usec = time_cur.tv_usec - phil->time_ref.tv_usec;
	if (usec < 0)
		usec += 1000;
	printf("%01d%03d %s", phil->t_sec, usec, prtf);
}

void	*check_count(void *arg)
{
	t_phil	*phil;
	t_p		*tmp;
	int		som;

	phil = (t_phil *)arg;
	while (1)
	{
		tmp = phil->l;
		som = 0;
		while (tmp)
		{
			som += tmp->each_eat;
			if (tmp->each_eat == -1)
				return ((void *)0);
			else
				tmp = tmp->next;
		}
		if (som >= phil->nb_eat * phil->p_nb)
		{
			pthread_mutex_lock(&(phil->l->print));
			print_time_end(phil, "each philosophers ate\n");
			pthread_mutex_unlock(&(phil->l->dead));
		}
	}
	return ((void *)0);
}

int	main(int ac, char **av)
{
	pthread_t		check_nb;
	t_phil			phil;
	int				i;

	if (!(little_parsing(ac, av)))
		return (arg_err());
	init_phil(&phil, av);
	phil.l = NULL;
	i = -1;
	while (++i < phil.p_nb)
	{
		if (!(create_phil(&phil)))
			return (malloc_err());
	}
	loop_thread(&phil);
	if (phil.nb_eat)
	{
		pthread_create(&check_nb, NULL, check_count, &phil);
		pthread_detach(check_nb);
	}
	pthread_mutex_lock(&(phil.l->dead));
	return (free_p(&phil));
}
