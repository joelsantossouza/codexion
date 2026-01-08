/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spend_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:47:52 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/08 18:24:12 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>

void	spend_time(uint32_t time, uint32_t *time_left)
{
	if (*time_left == 0)
		return ;
	if (time < *time_left)
	{
		*time_left -= time;
		usleep(time);
		return ;
	}
	usleep(*time_left);
	*time_left = 0;
}
