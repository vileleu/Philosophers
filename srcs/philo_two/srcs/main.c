/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 07:34:49 by vico              #+#    #+#             */
/*   Updated: 2021/05/27 05:01:10 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

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

int		check_count(t_phil *phil)
{
	int	i;
	int	som;

	while (1)
	{
		i = -1;
		som = 0;
		while (++i < phil->p_nb)
		{
			som += phil->phil[i].each_eat;
			if (phil->phil[i].each_eat == -1)
				return (1);
		}
		if (som >= phil->max_eat * phil->p_nb)
		{
			sem_wait(phil->print);
			print_time_end(phil, "each philosophers ate\n");
			return (1);
		}
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_phil	phil;

	if (!(little_parsing(ac, av)))
		return (arg_err());
	init_phil(&phil, av);
	if (!(launch_phil(&phil)))
		return (0);
	if (!phil.max_eat)
		sem_wait(phil.dead);
	else
		check_count(&phil);
	return (free_p(&phil));
}
