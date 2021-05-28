/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 13:06:13 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/28 09:28:29 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include "philo_two.h"

static int	philo_info_init(int ac, char **av, t_philo_info *info)
{
	if (parse_input(ac, av, info) == 1)
		return (1);
	sem_unlink("fork-semaphore");
	info->forks = sem_open("fork-semaphore", O_CREAT, 0644, info->philo_amount);
	if (info->forks == SEM_FAILED)
		return (error_semaphore_failed());
	sem_unlink("death-semaphore");
	info->s_philo_died = sem_open("death-semaphore", O_CREAT, 0644, 1);
	if (info->s_philo_died == SEM_FAILED)
	{
		sem_close(info->forks);
		return (error_semaphore_failed());
	}
	sem_unlink("print-semaphore");
	info->s_philo_died = sem_open("print-semaphore", O_CREAT, 0644, 1);
	if (info->s_philo_died == SEM_FAILED)
	{
		sem_close(info->forks);
		sem_close(info->s_philo_died);
		return (error_semaphore_failed());
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
		if (philo_info_init(ac, av, &info) == 1)
			return (1);
		if (create_threads(&info) == 1)
			return (1);
	}
	else
		return (error_argument_amount());
	return (0);
}
