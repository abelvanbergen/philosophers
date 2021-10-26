/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 15:09:16 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/09/17 11:29:08 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "philo.h"

static int	set_forks(t_philo_info *info)
{
	unsigned int	i;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->philo_amount);
	if (info->forks == NULL)
		return (error_malloc_failed());
	i = 0;
	while (i < info->philo_amount)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL) != 0)
		{
			close_all_forks(info, i);
			free(info->forks);
			return (error_mutex_failed());
		}
		i++;
	}
	return (0);
}

static int	set_death_mutex(t_philo_info *info)
{
	if (pthread_mutex_init(&info->m_philo_died, NULL) != 0)
	{
		close_all_forks(info, info->philo_amount);
		free(info->forks);
		return (error_mutex_failed());
	}
	return (0);
}

int	set_mutex(t_philo_info *info)
{
	if (set_forks(info) == 1 || set_death_mutex(info) == 1)
		return (1);
	if (pthread_mutex_init(&info->print, NULL) != 0)
	{
		close_forks_death_mutex(info);
		return (error_mutex_failed());
	}
	return (0);
}
