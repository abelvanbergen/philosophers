/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messages.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 13:59:08 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/17 14:22:56 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int error_argument_amount(void)
{
    printf("Error -----\nNot the right amount of arguments\n");
    printf("Give it in the following order:\n");
    printf("number_of_philosophers time_to_die time_to_eat time_to_sleep");
    printf(" [number_of_times_each_philosopher_must_eat]\n");
    return (1);
}

int error_argument_numbers(int index, char* arg)
{
    printf("Error -----\n");
	printf("Argument %i is not a number\nargument: %s\n", index, arg);
    return (1);
}

int error_philo_amount(int amount)
{
	printf("Error -----\n");
	if (amount < 2)
		printf("There are not enough philosophers\n you need 2 or more\n");
	else
		printf("There are to many philosophers\n you need 200 or less\n");
	return (1);
}

int error_time_to_low(char* time)
{
	printf("Error -----\n");
	printf("%s is to low. Make it at least 60 ms\n", time);
	return (1);
}

int error_amount_to_eat_zero()
{
	printf("Error -----\n");
	printf("You need to eat at least once.");
	printf("You can't think on a emty stomach\n");
	return (1);
}

int error_malloc_failed()
{
	printf("Error -----\n");
	printf("Malloc failed\n");
	return (1);
}

int error_mutex_failed()
{
	printf("Error -----\n");
	printf("Mutex failed\n");
	return (1);
}