/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 09:46:56 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/27 14:05:53 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include "philo_three.h"

static int	philo_info_init(int ac, char **av, t_philo_info *info)
{
	parse_input(ac, av, info);
	sem_unlink("fork-semaphore");
	info->forks = sem_open("fork-semaphore", O_CREAT, 0644, info->philo_amount);
	if (info->forks == SEM_FAILED)
		return (1);
	sem_unlink("death-semaphore");
	info->s_philo_died = sem_open("death-semaphore", O_CREAT, 0644, 1);
	if (info->s_philo_died == SEM_FAILED)
	{
		sem_close(info->forks);
		return (1);
	}
	sem_unlink("print-semaphore");
	info->s_philo_died = sem_open("print-semaphore", O_CREAT, 0644, 1);
	if (info->s_philo_died == SEM_FAILED)
	{
		sem_close(info->forks);
		sem_close(info->s_philo_died);
		return (1);
	}
	info->philo_died = false;
	info->time = get_time_ms();
	return (0);
}

int	main(int ac, char **av)
{
	t_philo_info	info;

	if (ac == 5 || ac == 6)
	{
		philo_info_init(ac, av, &info);

	}
	else
		error_argument_amount();
	return (0);
}