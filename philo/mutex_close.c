/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_close.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/26 13:53:27 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/09/06 12:17:15 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "philo.h"

void	close_all_forks(t_philo_info *info, int index)
{
	int	i;
	int	ret;

	i = 0;
	while (i < index)
	{
		ret = pthread_mutex_destroy(&info->forks[i]);
		if (ret != 0)
		{
			pthread_mutex_unlock(&info->forks[i]);
			pthread_mutex_destroy(&info->forks[i]);
		}
		i++;
	}
}

void	close_forks_death_mutex(t_philo_info *info)
{
	close_all_forks(info, info->philo_amount);
	free(info->forks);
	if (pthread_mutex_destroy(&info->m_philo_died) != 0)
	{
		pthread_mutex_unlock(&info->m_philo_died);
		pthread_mutex_destroy(&info->m_philo_died);
	}
}

void	close_all_mutex(t_philo_info *info)
{
	close_forks_death_mutex(info);
	if (pthread_mutex_destroy(&info->print) != 0)
	{
		pthread_mutex_unlock(&info->print);
		pthread_mutex_destroy(&info->print);
	}
}
