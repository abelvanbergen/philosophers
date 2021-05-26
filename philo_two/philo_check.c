/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 15:57:05 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/26 15:14:50 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include "philo_two.h"

static int	is_other_philo_dead(t_philo *philo)
{
	sem_wait(philo->info->s_philo_died);
	if (philo->info->philo_died == true)
	{
		sem_post(philo->info->s_philo_died);
		return (1);
	}
	sem_post(philo->info->s_philo_died);
	return (0);
}

int	is_philo_dead(t_philo *philo)
{
	unsigned long	time;

	time = get_time_ms();
	if (time - philo->time_last_eat > philo->info->t_die)
	{
		sem_wait(philo->info->forks);
		philo->info->philo_died = true;
		sem_post(philo->info->s_philo_died);
		write_philo_message(philo, "died", true);
		return (1);
	}
	return (0);
}

int	philo_check(t_philo *philo)
{
	if (is_other_philo_dead(philo) == 1)
		return (1);
	if (is_philo_dead(philo) == 1)
		return (1);
	return (0);
}
