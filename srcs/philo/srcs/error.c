/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 02:15:08 by vico              #+#    #+#             */
/*   Updated: 2021/11/04 19:52:04 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
