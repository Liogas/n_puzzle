/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:11:52 by glions            #+#    #+#             */
/*   Updated: 2026/02/19 14:53:27 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
# define PARSING_HPP

# include <vector>
# include <sstream>
# include <fstream>
# include <algorithm>

struct ParsingInfo
{
	std::vector<int> 				grid;
	bool							solvable;
	int								size;
};

bool parsing(char *pathFile, ParsingInfo &info);

#endif