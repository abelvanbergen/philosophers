/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_living.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 15:54:27 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/18 18:59:15 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	write_philo_message(t_philo* philo, char *msg, bool dead)
{
	unsigned long	time_ms;
	
	pthread_mutex_lock(&philo->info->print);
	time_ms = get_time_ms();
	if (dead == false)
		if (philo_check(philo) == 1)
		{
			pthread_mutex_unlock(&philo->info->print);
			return ;
		}
	if (time_ms - philo->info->time < 100)
		printf("time[%ld]\t\t%i %s\n", time_ms - philo->info->time, philo->number, msg);
	else
		printf("time[%ld]\t%i %s\n", time_ms - philo->info->time, philo->number, msg);
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
	ft_sleep(philo->info->t_sleep);
	if (philo_check(philo) == 1)
		return (1);
	return (0);
}

void	*philo_being_philo(void *varg)
{
	int turn;
	int	ret;
	t_philo *philo;

	philo = (t_philo *)varg;
	if (philo->number % 2 == 0)
		usleep(100);
	if (philo->number % 2 == 1 && philo->number == philo->info->philo_amount)
		usleep(200);
	turn = 0;
	while (!(philo->info->must_eat == true && turn >= philo->info->nb_must_eat))
	{
		ret = philo_eat(philo);
		if (ret == 1)
			return NULL;
		ret = philo_sleep(philo);
		if (ret == 1)
			return NULL;
		if (philo_check(philo) == 1)
			return (NULL);
		write_philo_message(philo, "is thinking", false);
		turn++;
	}
	return NULL;
}