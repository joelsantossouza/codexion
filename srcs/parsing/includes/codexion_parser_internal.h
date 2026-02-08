/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_parser_internal.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:21:57 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/08 16:22:11 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_PARSER_INTERNAL_H
# define CODEXION_PARSER_INTERNAL_H

# include <stdbool.h>
# include "codexion_parser.h"

# define INT_MAX_STR	"2147483647"

bool	is_str_numeric(const char *str);
int		nbrcmp(const char *nbr1, const char *nbr2);

#endif
