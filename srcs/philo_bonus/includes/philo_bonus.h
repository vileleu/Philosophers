/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 20:05:49 by vico              #+#    #+#             */
/*   Updated: 2021/11/11 04:42:06 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

# define FORK "semaphore_fork"
# define PRINT "semaphore_print"
# define EAT "semaphore_eat"
# define DEAD "semaphore_dead"

struct	s_phil;

typedef struct s_p
{
	struct s_phil	*phil;
	pid_t			proc;
	struct timeval	time_ref;
	pthread_mutex_t	samet;
	int				p_nb;
	int				nb;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				c_eat;
	int				each_eat;
}					t_p;

typedef struct s_phil
{
	t_p				*phil;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*eat;
	sem_t			*dead;
	struct timeval	time_ref;
	int				p_nb;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_eat;
}					t_phil;

/*
** FONCTIONS ERREURS
*/

int					malloc_err(void);
int					arg_err(void);
int					sem_err(void);

/*
** FONCTIONS PARSING
*/

int					little_parsing(int ac, char **av);

/*
** FONCTIONS UTILS
*/

int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strlen(const char *s);
void				sleep_better(long sleep);
long				current_time(void);

/*
** FONCTIONS PHILO
*/

void				init_phil(t_phil *phil, char **av);
int					free_p(t_phil *phil);

/*
** FONCTIONS THREAD
*/

void				*check_count(void *arg);
int					launch_phil(t_phil *phil);
void				*actions(void *arg);
void				print_time(t_p *p, char *prtf, int die);

#endif
