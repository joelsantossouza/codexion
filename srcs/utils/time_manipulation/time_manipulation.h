/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_manipulation.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:59:13 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/19 09:40:20 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_MANIPULATION_H
# define TIME_MANIPULATION_H

# include <stdint.h>

# define NOW	0

uint64_t	millis(void);
uint64_t	time_elapsed(uint64_t *new_start);

#endif
