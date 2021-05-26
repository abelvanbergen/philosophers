/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 15:31:30 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/26 15:14:49 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "philo_two.h"

static void	set_philo_details(t_philo *philo, int philo_id, t_philo_info *info)
{
	philo->number = philo_id;
	philo->time_last_eat = get_time_ms();
	philo->done_eating = false;
	philo->info = info;
}

static t_philo	*create_philo(t_philo_info *info)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * info->philo_amount);
	if (philo == NULL)
	{
		close_all_semaphores(info);
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
	int	i;
	int	philo_done_eating;

	i = 0;
	philo_done_eating = 0;
	while (1)
	{
		if (philo[i % philo->info->philo_amount].done_eating == true)
			philo_done_eating++;
		else
			philo_done_eating = 0;
		if (is_philo_dead(&philo[i % philo->info->philo_amount]) == 1)
			break ;
		if (philo_done_eating == philo->info->philo_amount)
			break ;
		i++;
	}
}

int	create_threads(t_philo_info *info)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = create_philo(info);
	if (philo == NULL)
		return (1);
	while (i < info->philo_amount)
	{	
		printf("[%d]\n", i);
		if (pthread_create(&(philo[i].thread_id), NULL, philo_being_philo, &philo[i]) == 0)
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
	close_all_semaphores(info);
	free(philo);
	return (0);
}
