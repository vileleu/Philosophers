/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 20:05:49 by vico              #+#    #+#             */
/*   Updated: 2021/11/11 04:34:56 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef struct s_p
{
	pthread_t		thrd;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	fork;
	pthread_mutex_t	*afork;
	pthread_mutex_t	*bfork;
	pthread_mutex_t	samet;
	struct timeval	time_ref;
	int				p_nb;
	int				nb;
	int				each_eat;
	int				t_sec;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				c_die;
	int				c_eat;
	struct s_p		*beg;
	struct s_p		*next;
}					t_p;

typedef struct s_phil
{
	t_p				*l;
	struct timeval	time_ref;
	int				nb_eat;
	int				p_nb;
	int				nb;
	int				t_sec;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				c_die;
	int				c_eat;
}					t_phil;

/*
** FONCTIONS ERREURS
*/

int					malloc_err(void);
int					arg_err(void);

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
** FONCTIONS LISTES PHILO
*/

void				init_phil(t_phil *phil, char **av);
int					create_phil(t_phil *phil);
int					create_phil_bis(t_phil *phil);
int					free_p(t_phil *phil);

/*
** FONCTIONS THREAD
*/

void				*actions(void *arg);
void				print_time(t_p *p, char *prtf, int die);
int					loop_thread(t_phil *phil);

#endif
