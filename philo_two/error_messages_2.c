/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messages_2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/26 09:28:27 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/28 09:14:52 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo_two.h"

int	error_malloc_failed(void)
{
	printf("Error -----\n");
	printf("Malloc failed\n");
	return (1);
}

int	error_threads_failed(t_philo *philo)
{
	close_all_semaphores(philo->info);
	free(philo);
	printf("Error -----\n");
	printf("The creation of threads failed\n");
	return (1);
}

int	error_semaphore_failed(void)
{
	printf("Error -----\n");
	printf("Semaphore failed\n");
	return (1);
}

int	error_argument_numbers(int index, char *arg)
{
	printf("Error -----\n");
	printf("Argument %i is a empty string\n", index);
	return (1);
}
