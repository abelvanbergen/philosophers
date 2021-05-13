/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 18:14:59 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/13 14:33:51 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	print_philo(t_philo* data)
{
	printf("philo +----------------------------+\n");
	printf("number of philosophers: 	%u\n", data->nb_philo);
	printf("time to die:			%u\n", data->t_die);
	printf("time to eat:			%u\n", data->t_eat);
	printf("time to sleep:			%u\n", data->t_sleep);
	printf("Must eat:			%i\n", (int)data->must_eat);
	printf("number to eat			%u\n", data->nb_must_eat);
}

int are_all_numbers(char **numbers, int amount)
{
	int i;

	i = 1;
	while (i < amount)
	{
		if (ft_isnumber(numbers[i]) == 0)
			return (error_argument_numbers(i, numbers[i]));
		i++;
	}
	return (0);
}

int	philo_init(int ac, char **av, t_philo* info)
{
	if (are_all_numbers(av, ac) == 1)
		return (1);
	info->nb_philo = ft_atoui(av[1]);
	if (info->nb_philo < 2 || info->nb_philo > 200)
		return (error_philo_amount());
	info->t_die = ft_atoui(av[2]);
	if (info->t_die < 60)
		return(error_time_to_low("Time to die"));
	info->t_eat = ft_atoui(av[3]);
	if (info->t_eat < 60)
		return(error_time_to_low("Time to eat"));
	info->t_sleep = ft_atoui(av[4]);
	if (info->t_sleep < 60)
		return(error_time_to_low("Time to sleep"));
	if (ac == 6)
	{
		info->must_eat = true;
		info->nb_must_eat= ft_atoui(av[4]);
		if (info->nb_must_eat == 0)
			return (error_amount_to_eat_zero());
	}
	else
		info->must_eat = false;
	return (0);
}

int main(int ac, char **av)
{
	t_philo	info;
	
	if (ac == 5 || ac == 6)
	{
		if(philo_init(ac, av, &info))
			return(1);
		print_philo(&info);
	}
	else
		return(error_argument_amount());
	return (0);
}