/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/28 08:45:14 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/28 14:46:23 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include "philo_three.h"

static void	kill_all_children(pid_t *children, int amount)
{
	int i;

	i = 0;
	while (i < amount)
	{
		if (children[i] != 0)
			kill(children[i], 9);
		i++;
	}
	free(children);
}

void	philo_init(t_philo *info)
{
	int	i;
	int j;
	pid_t	child_id;
	int ret;
	int status;
	int philo_done_eating;

	info->children = malloc(sizeof(pid_t) * info->parse.philo_amount);
	if (info->children == NULL)
		error_malloc_failed();
	i = 0;
	while (i < info->parse.philo_amount)
	{
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
	philo_done_eating = 0;
	while (1)
	{
		child_id = waitpid(info->children[i % info->parse.philo_amount], &status, 0);
		if (WEXITSTATUS(status) == 2 || WEXITSTATUS(status) == 1)
		{
			kill_all_children(info->children, info->parse.philo_amount);
			if (WEXITSTATUS(status) == 2)
				error_threads_failed();
			else
				exit(1);
		}
		else
		{
			j = 0;
			while  (j < info->parse.philo_amount)
			{
				if (info->children[j] == child_id)
					info->children[j] = 0;
				j++;
			}
			philo_done_eating++;
		}
		if (philo_done_eating == info->parse.philo_amount)
			exit(0);
		i++;
	}
}