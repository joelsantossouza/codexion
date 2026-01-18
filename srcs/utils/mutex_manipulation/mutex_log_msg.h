/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_log_msg.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:57:14 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 12:29:25 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_MESSAGE_H
# define LOG_MESSAGE_H

#include <stdint.h>
#include <pthread.h>
#include <stdio.h>

static inline
void	mutex_log_msg(uint64_t timestamp_in_ms, uint32_t coder_id, const char *msg, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%lu %d %s\n", timestamp_in_ms, coder_id, msg);
	pthread_mutex_unlock(mutex);
}

#endif
