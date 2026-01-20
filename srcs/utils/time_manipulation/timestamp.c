/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:40:43 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/20 09:54:48 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdint.h>
#include <unistd.h>

uint64_t	timestamp(const uint64_t *new_start)
{
	static struct timeval	tv;
	static uint64_t			start_saved;

	if (new_start)
		start_saved = *new_start;
	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000 + tv.tv_usec * 0.001) - start_saved);
}
