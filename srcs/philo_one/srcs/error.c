/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 02:15:08 by vico              #+#    #+#             */
/*   Updated: 2021/05/27 04:45:22 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int		malloc_err(void)
{
	write(2, "Error Malloc\n", ft_strlen("Error Malloc\n"));
	return (0);
}

int		arg_err(void)
{
	write(2, "Bad arguments\n", ft_strlen("Bad arguments\n"));
	return (0);
}
