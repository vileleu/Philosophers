/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 06:27:40 by vico              #+#    #+#             */
/*   Updated: 2021/05/27 07:27:05 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

void	print_time(t_p *p, char *prtf, int die)
{
	struct timeval	time_cur;
	int				diff;
	int				usec;
	int				print_sec;

	print_sec = 0;
	gettimeofday(&(time_cur), NULL);
	time_cur.tv_usec /= 1000;
	diff = time_cur.tv_sec - p->time_ref.tv_sec;
	if (diff > 0)
	{
		if (time_cur.tv_usec < p->time_ref.tv_usec)
			print_sec = diff - 1;
		else if (time_cur.tv_usec >= p->time_ref.tv_usec)
			print_sec = diff;
	}
	usec = time_cur.tv_usec - p->time_ref.tv_usec;
	if (usec < 0)
		usec += 1000;
	if (!die)
		sem_wait(p->phil->print);
	printf("%01d%03d %d %s", print_sec, usec, p->nb, prtf);
	if (!die)
		sem_post(p->phil->print);
}

int		check_time(t_p *p, struct timeval *time_check)
{
	int				c_cur;
	int				c_ref;
	struct timeval	time_cur;

	c_ref = (time_check->tv_sec * 1000) + \
	(time_check->tv_usec / 1000) + p->t_die;
	gettimeofday(&time_cur, NULL);
	c_cur = (time_cur.tv_sec * 1000) + (time_cur.tv_usec / 1000);
	if (c_cur >= c_ref)
	{
		sem_wait(p->phil->print);
		print_time(p, "died\n", 1);
		p->each_eat = -1;
		sem_post(p->phil->dead);
		return (1);
	}
	return (0);
}

void	*check_eat(void *arg)
{
	t_p				*p;
	struct timeval	time_check;

	p = (t_p*)arg;
	while (1)
	{
		sem_wait(p->phil->block);
		if (p->c_eat == 1)
		{
			gettimeofday(&time_check, NULL);
			p->c_eat = 0;
		}
		else if (!p->c_eat && check_time(p, &time_check))
			return ((void*)0);
		sem_post(p->phil->block);
		usleep(100);
	}
	return ((void*)0);
}

void	*actions(void *arg)
{
	pthread_t	c_eat;
	t_p			*p;

	p = (t_p*)arg;
	pthread_create(&c_eat, NULL, check_eat, p);
	pthread_detach(c_eat);
	while (1)
	{
		sem_wait(p->phil->fork);
		print_time(p, "has taken a fork\n", 0);
		sem_wait(p->phil->fork);
		print_time(p, "has taken a fork\n", 0);
		p->c_eat = 2;
		print_time(p, "is eating\n", 0);
		usleep(p->t_eat * 1000);
		p->c_eat = 1;
		p->each_eat++;
		sem_post(p->phil->fork);
		sem_post(p->phil->fork);
		print_time(p, "is sleeping\n", 0);
		usleep(p->t_sleep * 1000);
		print_time(p, "is thinking\n", 0);
	}
	return ((void*)0);
}
