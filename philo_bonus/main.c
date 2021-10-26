/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 09:46:56 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/09/06 12:12:28 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //
#include <semaphore.h>
#include <stdlib.h>
#include "philo_bonus.h"

static int	philo_info_init(int ac, char **av, t_philo *info)
{
	parse_input(ac, av, &info->parse);
	info->forks = sem_open("fork-semaphore", O_CREAT, 0644, \
													info->parse.philo_amount);
	if (info->forks == SEM_FAILED)
		exit(1);
	sem_unlink("fork-semaphore");
	info->print = sem_open("print-semaphore", O_CREAT, 0644, 1);
	if (info->print == SEM_FAILED)
	{
		sem_close(info->forks);
		exit(1);
	}
	sem_unlink("print-semaphore");
	info->philo_died = false;
	info->time = get_time_ms();
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	info;

	if (ac == 5 || ac == 6)
	{
		philo_info_init(ac, av, &info);
		philo_init(&info);
	}
	else
		error_argument_amount();
	return (0);
}
