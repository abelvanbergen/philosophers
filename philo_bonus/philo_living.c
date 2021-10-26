/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_living.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/28 10:40:21 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/09/17 13:25:17 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "philo_bonus.h"

static void	write_philo_message(t_philo *info, char *msg)
{
	unsigned long	time_ms;

	sem_wait(info->print);
	time_ms = get_time_ms();
	if (time_ms - info->time < 100)
		printf("time[%ld]\t\t%i %s\n", time_ms - info->time, info->number, msg);
	else
		printf("time[%ld]\t%i %s\n", time_ms - info->time, info->number, msg);
	if (info->philo_died == false)
		sem_post(info->print);
}

static void	*monitor(void *varg)
{
	t_philo			*info;

	info = (t_philo *)varg;
	while (1)
	{
		usleep(100);
		if (get_time_ms() - info->time_last_eat > info->parse.t_die)
		{
			info->philo_died = true;
			write_philo_message(info, "died");
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
	sem_wait(info->forks);
	write_philo_message(info, "has taken a fork");
	info->time_last_eat = get_time_ms();
	write_philo_message(info, "is eating");
	ft_sleep(info->parse.t_eat);
	sem_post(info->forks);
	sem_post(info->forks);
}

void	philo_being_philo(t_philo *info)
{
	unsigned int	turn;

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
			exit(0);
	}
}
