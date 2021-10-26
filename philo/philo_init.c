/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 15:31:30 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/09/17 11:54:24 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "philo.h"
#include <stdio.h>

static void	set_philo_details(t_philo *philo, unsigned int philo_id,
															t_philo_info *info)
{
	philo->number = philo_id;
	if (philo_id == info->philo_amount)
		philo->right_fork = 0;
	else
		philo->right_fork = philo_id;
	philo->left_fork = philo_id - 1;
	philo->time_last_eat = get_time_ms();
	philo->done_eating = false;
	philo->info = info;
}

static t_philo	*create_philo(t_philo_info *info)
{
	t_philo			*philo;
	unsigned int	i;

	philo = malloc(sizeof(t_philo) * info->philo_amount);
	if (philo == NULL)
	{
		close_all_mutex(info);
		error_malloc_failed();
		return (NULL);
	}
	i = 0;
	while (i < info->philo_amount)
	{
		set_philo_details(&philo[i], i + 1, info);
		i++;
	}
	return (philo);
}

static void	start_play(t_philo *philo)
{
	unsigned int	i;
	unsigned int	philo_done_eating;

	i = 0;
	philo_done_eating = 0;
	while (1)
	{
		if (philo[i % philo->info->philo_amount].done_eating == true)
			philo_done_eating++;
		else
			philo_done_eating = 0;
		if (is_philo_dead(&philo[i % philo->info->philo_amount]) == 1)
		{
			if (philo->info->philo_amount == 1)
				pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
			break ;
		}
		if (philo_done_eating == philo->info->philo_amount)
			break ;
		i++;
	}
}

int	create_threads(t_philo_info *info)
{
	t_philo			*philo;
	unsigned int	i;

	i = 0;
	philo = create_philo(info);
	if (philo == NULL)
		return (1);
	while (i < info->philo_amount)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, philo_being_philo, \
																&philo[i]) != 0)
			return (error_threads_failed(philo));
		i++;
	}
	i = 0;
	start_play(philo);
	while (i < info->philo_amount)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	close_all_mutex(info);
	free(philo);
	return (0);
}
