/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timed_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:27:17 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/08 18:42:33 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	timed_wait(uint8_t *is_ready_flag, uint32_t *time_left)
{
	size_t	last_time;
	size_t	current_time;
	size_t	elapsed_time;

	if (*time_left == 0)
		return (FALSE);
	last_time = millis();
	while (*is_ready_flag == FALSE)
	{
		current_time = millis();
		elapsed_time = current_time - last_time;
		if (*time_left <= elapsed_time)
		{
			*time_left = 0;
			return (FALSE);
		}
		*time_left -= elapsed_time;
		last_time = current_time;
	}
	return (TRUE);
}
