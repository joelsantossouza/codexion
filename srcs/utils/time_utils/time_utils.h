/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 11:27:27 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/02 13:46:24 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_UTILS_H
# define TIME_UTILS_H

# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>

static inline
__attribute__((always_inline))
uint64_t	millis(void)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == -1)
		return (0);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

uint64_t	timestamp_ms(uint64_t set_start);

#endif
