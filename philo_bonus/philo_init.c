/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/28 08:45:14 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/09/17 13:23:43 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include "philo_bonus.h"

static void	kill_all_children(pid_t *children, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if (children[i] != 0)
			kill(children[i], 9);
		i++;
	}
	free(children);
}

void	creating_philo_processes(t_philo *info)
{
	pid_t				ret;
	unsigned int		i;

	i = 0;
	while (i < info->parse.philo_amount)
	{
		info->number = i + 1;
		info->time_last_eat = get_time_ms();
		ret = fork();
		if (ret == -1)
		{
			kill_all_children(info->children, info->parse.philo_amount);
			error_fork_failed();
		}
		else if (ret == 0)
			philo_being_philo(info);
		else
			info->children[i] = ret;
		i++;
	}
}

void	philo_died_or_threads_failed(t_philo *info, int status)
{
	kill_all_children(info->children, info->parse.philo_amount);
	if (status == 2)
		error_threads_failed();
	else
		exit(1);
}

void	philo_done_eating(t_philo *info, unsigned int *philo_done_eating,
																pid_t child_id)
{
	unsigned int	i;

	i = 0;
	while (i < info->parse.philo_amount)
	{
		if (info->children[i] == child_id)
			info->children[i] = 0;
		i++;
	}
	(*philo_done_eating)++;
}

void	philo_init(t_philo *info)
{
	pid_t			child_id;
	int				status;
	unsigned int	philos_done_eating;
	unsigned int	i;

	info->children = malloc(sizeof(pid_t) * info->parse.philo_amount);
	if (info->children == NULL)
		error_malloc_failed();
	creating_philo_processes(info);
	philos_done_eating = 0;
	i = 0;
	while (1)
	{
		child_id = waitpid(0, &status, 0);
		philo_done_eating(info, &philos_done_eating, child_id);
		if (WEXITSTATUS(status) == 2 || WEXITSTATUS(status) == 1)
			philo_died_or_threads_failed(info, WEXITSTATUS(status));
		if (philos_done_eating == info->parse.philo_amount)
			exit(0);
		i++;
	}
}
