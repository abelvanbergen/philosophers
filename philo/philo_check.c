/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 15:57:05 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/09/17 13:12:33 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"

int	is_philo_dead(t_philo *philo)
{
	unsigned long	time;

	time = get_time_ms();
	if (time - philo->time_last_eat > philo->info->t_die)
	{
		pthread_mutex_lock(&philo->info->m_philo_died);
		philo->info->philo_died = true;
		pthread_mutex_unlock(&philo->info->m_philo_died);
		write_philo_message(philo, "died", true);
		return (1);
	}
	return (0);
}

int	philo_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->m_philo_died);
	if (philo->info->philo_died == true)
	{
		pthread_mutex_unlock(&philo->info->m_philo_died);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->m_philo_died);
	return (0);
}
