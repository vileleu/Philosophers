/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 02:15:08 by vico              #+#    #+#             */
/*   Updated: 2021/11/04 19:53:00 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	malloc_err(void)
{
	write(2, "Error Malloc\n", ft_strlen("Error Malloc\n"));
	return (0);
}

int	arg_err(void)
{
	write(2, "Bad arguments\n", ft_strlen("Bad arguments\n"));
	return (0);
}

int	sem_err(void)
{
	write(2, "Error semaphore\n", ft_strlen("Error semaphore\n"));
	return (0);
}
