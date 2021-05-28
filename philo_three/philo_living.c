/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_living.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/28 10:40:21 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/28 15:07:04 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo_three.h"

static void	write_philo_message(t_philo *info, char *msg)
{
	unsigned long	time_ms;

	time_ms = get_time_ms();
	sem_wait(info->print);
	if (time_ms - info->time < 100)
		printf("time[%ld]\t\t%i %s\n", time_ms - info->time, info->number, msg);
	else
		printf("time[%ld]\t%i %s\n", time_ms - info->time, info->number, msg);
	sem_post(info->print);
}

static void	*monitor(void *varg)
{
	t_philo			*philo;
	
	philo = (t_philo *)varg;
	while (1)
	{
		if (get_time_ms() - philo->time_last_eat > philo->parse.t_die)
		{
			write_philo_message(philo, "died");
			exit(1);
		}
	}
}

static void	philo_sleep_and_thinking(t_philo *info)
{
	write_philo_message(info, "is sleeping");
	ft_sleep(info->parse.t_sleep);
	write_philo_message(info, "is thinking");
}

static void	philo_eat(t_philo *info)
{
	sem_wait(info->forks);
	write_philo_message(info, "has taken a fork");
	write_philo_message(info, "has taken a fork");
	sem_wait(info->forks);
	write_philo_message(info, "is eating");
	info->time_last_eat = get_time_ms();
	ft_sleep(info->parse.t_eat);
	sem_post(info->forks);
	sem_post(info->forks);
}

void	philo_being_philo(t_philo *info)
{
	int pilo_done_eating;
	int	turn;

	if (pthread_create(&(info->monitor), NULL, monitor, info) != 0)
		exit(2);
	turn = 0;
	while (1)
	{
		if (turn != 0)
			philo_sleep_and_thinking(info);
		philo_eat(info);
		turn++;
		if (info->parse.must_eat == true && turn >= info->parse.nb_must_eat)
		{
			printf("hij gaat hier uit\n");
			exit(0);
		}
	}
}