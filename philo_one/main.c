/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 13:06:13 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/18 16:55:41 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	print_philo(t_philo_info* data)
{
	printf("philo +----------------------------+\n");
	printf("number of philosophers: 	%u\n", data->philo_amount);
	printf("time to die:			%u\n", data->t_die);
	printf("time to eat:			%u\n", data->t_eat);
	printf("time to sleep:			%u\n", data->t_sleep);
	printf("Must eat:			%i\n", (int)data->must_eat);
	printf("number to eat			%u\n", data->nb_must_eat);
}

int philo_info_init(int ac, char** av, t_philo_info* info)
{
	if (parse_input(ac, av, info) == 1)
		return (1);
	if (set_mutex(info) == 1)
		return (1);
	info->philo_died = false;
	info->time = get_time_ms();
	return (0);
}

int main(int ac, char **av)
{
	t_philo_info	info;
	
	if (ac == 5 || ac == 6)
	{
		if(philo_info_init(ac, av, &info))
			return(1);
		if (create_threads(&info) == 1)
			return (1);
	}
	else
		return(error_argument_amount());
	return (0);
}