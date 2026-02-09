/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_coders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:44:09 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/09 16:19:07 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "codexion.h"
#include "coder.h"

int	start_coders(uint32_t size, t_coder coders[size], uint32_t stride)
{
	int			exit_status;
	uint32_t	offset;
	uint32_t	i;

	offset = -1;
	while (++offset < stride && offset < size)
	{
		i = offset;
		while (i < size)
		{
			exit_status = pthread_create(
				&coders[i].thread, NULL, (t_routine)coder_routine, &coders[i]
			);
			if (exit_status != 0)
				return (exit_status);
			i += stride;
		}
		usleep(START_INTERVAL_MS * 1000);
	}
	return (0);
}
