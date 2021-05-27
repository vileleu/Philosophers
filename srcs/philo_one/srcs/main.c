/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 20:38:40 by vico              #+#    #+#             */
/*   Updated: 2021/05/27 04:45:59 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

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

int		check_count(t_phil *phil)
{
	t_p		*tmp;
	int		som;

	while (1)
	{
		tmp = phil->l;
		som = 0;
		while (tmp)
		{
			som += tmp->each_eat;
			if (tmp->each_eat == -1)
				return (1);
			else
				tmp = tmp->next;
		}
		if (som >= phil->nb_eat * phil->p_nb)
		{
			pthread_mutex_lock(&(phil->l->print));
			print_time_end(phil, "each philosophers ate\n");
			break ;
		}
	}
	return (1);
}

int		main(int ac, char **av)
{
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
	if (!phil.nb_eat)
		pthread_mutex_lock(&(phil.l->dead));
	else
		check_count(&phil);
	return (free_p(&phil));
}
