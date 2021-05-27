/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listes_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:17:50 by vico              #+#    #+#             */
/*   Updated: 2021/05/27 04:46:19 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	init_phil(t_phil *phil, char **av)
{
	phil->t_die = ft_atoi(av[2]);
	phil->t_eat = ft_atoi(av[3]);
	phil->t_sleep = ft_atoi(av[4]);
	phil->t_sec = 0;
	phil->nb = 1;
	phil->p_nb = ft_atoi(av[1]);
	phil->nb_eat = 0;
	if (av[5])
	{
		phil->nb_eat = ft_atoi(av[5]);
	}
	gettimeofday(&(phil->time_ref), NULL);
	phil->time_ref.tv_usec /= 1000;
}

int		free_p(t_phil *phil)
{
	t_p	*tmp;

	while (phil->l->next)
	{
		tmp = phil->l;
		phil->l = phil->l->next;
		pthread_mutex_destroy(&(tmp->fork));
		free(tmp);
		tmp = NULL;
	}
	pthread_mutex_destroy(&(phil->l->fork));
	free(phil->l);
	return (0);
}

void	give_thread(t_phil *phil, t_p *tmp)
{
	tmp->t_die = phil->t_die;
	tmp->t_eat = phil->t_eat;
	tmp->t_sec = phil->t_sec;
	tmp->t_sleep = phil->t_sleep;
	tmp->p_nb = phil->p_nb;
	tmp->time_ref = phil->time_ref;
	tmp->c_die = 1;
	tmp->c_eat = 1;
	tmp->each_eat = 0;
	tmp->beg = phil->l;
	if (tmp->next == NULL)
	{
		tmp->afork = &(tmp->fork);
		tmp->bfork = &(phil->l->fork);
		pthread_create(&(tmp->thrd), NULL, actions, tmp);
		pthread_detach(tmp->thrd);
	}
	else
	{
		tmp->afork = &(tmp->fork);
		tmp->bfork = &(tmp->next->fork);
		pthread_create(&(tmp->thrd), NULL, actions, tmp);
		pthread_detach(tmp->thrd);
	}
	usleep(100);
}

int		loop_thread(t_phil *phil)
{
	t_p		*tmp;

	tmp = phil->l;
	pthread_mutex_init(&(phil->l->block), NULL);
	pthread_mutex_init(&(phil->l->print), NULL);
	pthread_mutex_init(&(phil->l->dead), NULL);
	pthread_mutex_lock(&(phil->l->dead));
	while (tmp)
	{
		give_thread(phil, tmp);
		tmp = tmp->next;
	}
	return (1);
}

int		create_phil(t_phil *phil)
{
	t_p		*tmp;

	if (phil->l)
	{
		tmp = phil->l;
		while (phil->l->next)
			phil->l = phil->l->next;
		if (!(phil->l->next = malloc(sizeof(t_p))))
			return (0);
		pthread_mutex_init(&(phil->l->next->fork), NULL);
		phil->l->next->nb = phil->nb++;
		phil->l->each_eat = 0;
		phil->l->next->next = NULL;
		phil->l = tmp;
	}
	else if (phil->l == NULL)
	{
		if (!(phil->l = malloc(sizeof(t_p))))
			return (0);
		pthread_mutex_init(&(phil->l->fork), NULL);
		phil->l->nb = phil->nb++;
		phil->l->each_eat = 0;
		phil->l->next = NULL;
	}
	return (1);
}
