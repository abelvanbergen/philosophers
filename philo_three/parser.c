/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 09:47:10 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/27 13:42:07 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	are_all_numbers(char **numbers, int amount)
{
	int	i;

	i = 1;
	while (i < amount)
	{
		if (ft_isnumber(numbers[i]) == 0)
			error_argument_numbers(i, numbers[i]);
		i++;
	}
	return (0);
}

static int	parse_times(int ac, char **av, t_philo_info *info)
{
	info->t_die = ft_atoui(av[2]);
	if (info->t_die < 60)
		error_time_to_low("Time to die");
	info->t_eat = ft_atoui(av[3]);
	if (info->t_eat < 60)
		error_time_to_low("Time to eat");
	info->t_sleep = ft_atoui(av[4]);
	if (info->t_sleep < 60)
		error_time_to_low("Time to sleep");
}

int	parse_input(int ac, char **av, t_philo_info *info)
{
	are_all_numbers(av, ac);
	info->philo_amount = ft_atoui(av[1]);
	if (info->philo_amount < 2 || info->philo_amount > 200)
		error_philo_amount(info->philo_amount);
	parse_times(ac, av, info);
	if (ac == 6)
	{
		info->must_eat = true;
		info->nb_must_eat = ft_atoui(av[5]);
		if (info->nb_must_eat == 0)
			error_amount_to_eat_zero();
	}
	else
		info->must_eat = false;
	return (0);
}
