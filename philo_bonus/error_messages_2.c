/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messages_2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/03 13:03:17 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/06/03 13:04:11 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	error_argument_empty_string(int index)
{
	printf("Error -----\n");
	printf("Argument %i is a empty string\n", index);
	exit(1);
}

void	error_threads_failed(void)
{
	printf("Error -----\n");
	printf("The creation of threads failed\n");
	exit(1);
}

void	error_malloc_failed(void)
{
	printf("Error -----\n");
	printf("Malloc failed\n");
	exit(1);
}

void	error_fork_failed(void)
{
	printf("Error -----\n");
	printf("fork failed\n");
	exit(1);
}
