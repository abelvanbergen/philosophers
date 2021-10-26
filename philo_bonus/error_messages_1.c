/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messages_1.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 09:49:29 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/09/17 14:18:47 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	error_argument_amount(void)
{
	printf("Error -----\nNot the right amount of arguments\n");
	printf("Give it in the following order:\n");
	printf("number_of_philosophers time_to_die time_to_eat time_to_sleep");
	printf(" [number_of_times_each_philosopher_must_eat]\n");
	exit(1);
}

void	error_argument_numbers(int index, char *arg)
{
	printf("Error -----\n");
	printf("Argument %i is not a number\nargument: %s\n", index, arg);
	exit(1);
}

void	error_philo_amount(unsigned int amount)
{
	printf("Error -----\n");
	if (amount == 0)
		printf("There are not enough philosophers\nYou need 1 or more\n");
	else
		printf("There are to many philosophers\nYou need 200 or less\n");
	exit(1);
}

void	error_time_to_low(char *time)
{
	printf("Error -----\n");
	printf("%s is to low. Make it at least 60 ms\n", time);
	exit(1);
}

void	error_amount_to_eat_zero(void)
{
	printf("Error -----\n");
	printf("You need to eat at least once.");
	printf("You can't think on a empty stomach\n");
	exit(1);
}
