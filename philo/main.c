/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 13:06:13 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/09/06 12:17:15 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_info_init(int ac, char **av, t_philo_info *info)
{
	if (parse_input(ac, av, info) == 1)
		return (1);
	if (set_mutex(info) == 1)
		return (1);
	info->philo_died = false;
	info->time = get_time_ms();
	return (0);
}

int	main(int ac, char **av)
{
	t_philo_info	info;

	if (ac == 5 || ac == 6)
	{
		if (philo_info_init(ac, av, &info) == 1)
			return (1);
		if (create_threads(&info) == 1)
			return (1);
	}
	else
		return (error_argument_amount());
	return (0);
}
