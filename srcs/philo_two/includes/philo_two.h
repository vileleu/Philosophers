/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 20:05:49 by vico              #+#    #+#             */
/*   Updated: 2021/05/27 05:04:34 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define FORK "semaphore_fork"
# define BLOCK "semaphore_block"
# define PRINT "semaphore_print"
# define DEAD "semaphore_dead"

struct s_phil;

typedef struct		s_p
{
	struct s_phil	*phil;
	struct timeval	time_ref;
	int				p_nb;
	int				nb;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				c_eat;
	int				each_eat;
}					t_p;

typedef struct		s_phil
{
	t_p				*phil;
	sem_t			*fork;
	sem_t			*block;
	sem_t			*print;
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

/*
** FONCTIONS PHILO
*/

void				init_phil(t_phil *phil, char **av);
int					free_p(t_phil *phil);

/*
** FONCTIONS THREAD
*/

int					launch_phil(t_phil *phil);
void				*actions(void *arg);
void				print_time(t_p *p, char *prtf, int die);

#endif
