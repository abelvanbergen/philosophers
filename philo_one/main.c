/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 18:14:59 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/12 22:56:12 by abelfrancis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	print_philo(t_philo* data)
{
	printf("philo ---------------------\n");
	printf("number of philosophers: %u\n", data->nb_philo);
	printf("time to die:			%u\n", data->t_die);
	printf("time to eat:			%u\n", data->t_eat);
	printf("time to sleep:			%u\n", data->t_sleep);
	printf("Must eat:				%i\n", (int)data->must_eat);
	printf("number to eat			%u\n", data->nb_must_eat);
}

int	philo_init(int ac, char **av, t_philo* info)
{
	int i;

	i = 0;
	while (i < ac)
	{
		if (ft_isnumber(av[i]))
		{
			printf("Error:\nArgument %i is not a number\nargument: %s\n", i + 1, av[i]);
			return (1);
		}
		i++;
	}
	info->nb_philo = ft_atoui(av[1]);
	if (info->nb_philo < 2)
	{
		printf("Error:\nThere are not enough philosophers\n you need 2 or more\n");
		return (1);
	}
	info->t_die = ft_atoui(av[2]);
	info->t_eat = ft_atoui(av[3]);
	info->t_sleep = ft_atoui(av[4]);
	if (ac == 6)
	{
		info->must_eat = true;
		info->nb_must_eat= ft_atoui(av[4]);
	}
	else
		info->must_eat = false;
}

int main(int ac, char **av)
{
	t_philo	info;
	
	if (ac == 5 && ac == 6)
	{
		if(philo_init(ac, av, &info))
			return(1);
		print_philo(&info);
	}
	else
	{
		printf("Error: not the right amount of arguments\n");
		return (1);
	}
	return (0);
}