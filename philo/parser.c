/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 15:42:29 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/09/17 13:16:50 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static int	are_all_numbers(char **numbers, int amount)
{
	int	i;

	i = 1;
	while (i < amount)
	{
		if (ft_isnumber(numbers[i]) == 0)
			return (error_argument_numbers(i, numbers[i]));
		if (ft_strlen(numbers[i]) == 0)
			return (error_argument_empty_string(i));
		i++;
	}
	return (0);
}

static int	parse_times(char **av, t_philo_info *info)
{
	info->t_die = ft_atoui(av[2]);
	if (info->t_die < 60)
		return (error_time_to_low("Time to die"));
	info->t_eat = ft_atoui(av[3]);
	if (info->t_eat < 60)
		return (error_time_to_low("Time to eat"));
	info->t_sleep = ft_atoui(av[4]);
	if (info->t_sleep < 60)
		return (error_time_to_low("Time to sleep"));
	return (0);
}

int	parse_input(int ac, char **av, t_philo_info *info)
{
	if (are_all_numbers(av, ac) == 1)
		return (1);
	info->philo_amount = ft_atoui(av[1]);
	if (info->philo_amount == 0 || info->philo_amount > 200)
		return (error_philo_amount(info->philo_amount));
	if (parse_times(av, info) == 1)
		return (1);
	if (ac == 6)
	{
		info->must_eat = true;
		info->nb_must_eat = ft_atoui(av[5]);
		if (info->nb_must_eat == 0)
			return (error_amount_to_eat_zero());
	}
	else
		info->must_eat = false;
	return (0);
}
