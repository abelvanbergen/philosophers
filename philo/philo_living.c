/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_living.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 15:54:27 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/09/17 11:50:20 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "philo.h"

void	write_philo_message(t_philo *philo, char *msg, bool dead)
{
	unsigned long	time_ms;

	pthread_mutex_lock(&philo->info->print);
	time_ms = get_time_ms();
	if (dead == false)
	{
		if (philo_check(philo) == 1)
		{
			pthread_mutex_unlock(&philo->info->print);
			return ;
		}
	}
	if (time_ms - philo->info->time < 100)
		printf("time[%ld]\t\t%i %s\n", time_ms - philo->info->time, \
															philo->number, msg);
	else
		printf("time[%ld]\t%i %s\n", time_ms - philo->info->time, \
															philo->number, msg);
	pthread_mutex_unlock(&philo->info->print);
}

static int	philo_eat(t_philo *philo)
{
	if (philo_check(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
	if (philo_check(philo) == 1)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
		return (1);
	}
	write_philo_message(philo, "has taken a fork", false);
	pthread_mutex_lock(&philo->info->forks[philo->right_fork]);
	if (philo_check(philo) == 1)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->info->forks[philo->right_fork]);
		return (1);
	}
	write_philo_message(philo, "has taken a fork", false);
	write_philo_message(philo, "is eating", false);
	philo->time_last_eat = get_time_ms();
	ft_sleep(philo->info->t_eat);
	pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->right_fork]);
	return (0);
}

static int	philo_sleep(t_philo *philo)
{
	if (philo_check(philo) == 1)
		return (1);
	write_philo_message(philo, "is sleeping", false);
	ft_sleep(philo->info->t_sleep);
	if (philo_check(philo) == 1)
		return (1);
	return (0);
}

static void	set_philo_offset(t_philo *philo)
{
	if (philo->number % 2 == 0)
		usleep(100);
	if (philo->number % 2 == 1 && philo->number == philo->info->philo_amount)
		usleep(200);
}

void	*philo_being_philo(void *varg)
{
	unsigned int	turn;
	int				ret;
	t_philo			*philo;

	philo = (t_philo *)varg;
	set_philo_offset(philo);
	turn = 0;
	while (philo->done_eating == false)
	{
		if (turn != 0)
		{
			ret = philo_sleep(philo);
			if (ret == 1)
				return (NULL);
			write_philo_message(philo, "is thinking", false);
		}
		ret = philo_eat(philo);
		if (ret == 1)
			return (NULL);
		turn++;
		if (philo->info->must_eat == true && turn >= philo->info->nb_must_eat)
			philo->done_eating = true;
	}
	return (NULL);
}
