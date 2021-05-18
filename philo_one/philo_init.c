/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 15:31:30 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/18 19:20:51 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	set_philo_details(t_philo* philo, int philo_id, t_philo_info *info)
{
	philo->number = philo_id;
	if (philo_id == info->philo_amount)
		philo->right_fork = 0;
	else
		philo->right_fork = philo_id;
	philo->left_fork = philo_id - 1;
	philo->time_last_eat = get_time_ms();
    philo->info = info;                                                                           
}

t_philo*    create_philo(t_philo_info* info)
{
	t_philo*		philo;
	int		 i;

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

int	create_threads(t_philo_info* info)
{
	t_philo*		philo;
	int				i;

	i = 0;
	philo = create_philo(info);
	if (philo == NULL)
		return (1);
	while (i < info->philo_amount)
	{		
		pthread_create(&(philo[i].thread_id), NULL, philo_being_philo, &philo[i]);
		i++;
	}
	while(1)
	{
		if (is_philo_dead(&philo[i % philo->info->philo_amount]) == 1)
			break ;
		i++;
	}
	i = 0;
	while (i < info->philo_amount)
	{
		pthread_join(philo[i].thread_id, NULL);
		printf("%i\n", i);
		i++;
	}
	return (0);
}