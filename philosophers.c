/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/06 11:08:23 by avan-ber      #+#    #+#                 */
/*   Updated: 2020/12/06 14:53:00 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

void	print_data(t_data data)
{
	printf("nb_of_philo: %d\n", data.nb_of_philo);
	printf("time_to_die: %d\n", data.time_to_die);
	printf("time_to_eat: %d\n", data.time_to_eat);
	printf("time_to_sleep: %d\n", data.time_to_sleep);
	if (data.must_eat)
		printf("times_must_eat: %d\n", data.times_must_eat);
}

int	get_nbr(int *nbr, char *str)
{
	if (!(is_nbr(str)))
	{
		write(1, "Error\nNumber is not a valid number: ", 36);
		write(1, &str, ft_strlen(str));
		write(1, "\n", 1);
		return (0);
	}
	*nbr = simple_atoi(str);
	return (1);
}

int	get_data(t_data *data, int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		write(1, FORMAT_ERROR, 36);
		return (0);
	}
	if (!(get_nbr(&data->nb_of_philo, av[1])))
		return (0);
	if (data->nb_of_philo <= 1)
	{
		write(1, "Error\nThere are not enough philosophers\n", 40);
		return (0);
	}
	if (!(get_nbr(&data->time_to_die, av[2])))
		return (0);
	if (!(get_nbr(&data->time_to_eat, av[3])))
		return (0);
	if (!(get_nbr(&data->nb_of_philo, av[4])))
		return (0);
	if (ac == 6)
	{
		data->must_eat = true;
		if (!(get_nbr(&data->times_must_eat, av[5])))
			return (0);
	}
	else
		data->must_eat = false;
	return (1);
}

int main(int ac, char **av)
{
	t_data		data;

	if (!(get_data(&data, ac, av)))
		return (0);
	print_data(data);
}
