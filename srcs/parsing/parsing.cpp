/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:12:47 by glions            #+#    #+#             */
/*   Updated: 2026/02/02 12:22:14 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"

static bool parseSolvable(std::ifstream &f, ParsingInfo &i)
{
	std::string	line;
	std::getline(f, line);
	if (line.size() == 0)
		return (f.close(), false);
	if (line == "# This puzzle is solvable")
		i.solvable = true;
	else if (line == "# This puzzle is unsolvable")
		i.solvable = false;
	else
		return (f.close(), false);
	return (true);
}

static bool parseGridSize(std::ifstream &f, ParsingInfo &i)
{
	std::string	line;
	std::getline(f, line);
	if (line.size() == 0)
		return (false);
	std::istringstream iss(line);
	if (!(iss >> i.size))
		return (f.close(), false);
	char test;
	if (iss >> test)
		return (f.close(), false);
	return (true);
}

static bool parseGrid(std::ifstream &f, ParsingInfo &i)
{
	std::string	line;
	while (std::getline(f, line))
	{
		std::istringstream ss(line);
		std::vector<int> row;
		int	n;
		while (ss >> n)
			row.push_back(n);
		i.grid.push_back(row);
	}
	f.close();
	if ((int)i.grid.size() != i.size)
		return (false);
	std::vector<int> mem;
	for (auto &row : i.grid) {
        for (auto val : row)
		{
			auto it = std::find(mem.begin(), mem.end(), val);
			if (it != mem.end())
				return (false);
			mem.push_back(val);
		}
    }
	auto it = std::find(mem.begin(), mem.end(), 0);
	if (it == mem.end())
		return (false);
	return (true);
}

bool parsing(char *pathFile, ParsingInfo &info)
{
	std::ifstream file(pathFile);
	if (!file.is_open())
		return (false);
	if (!parseSolvable(file, info))
		return (false);
	if (!parseGridSize(file, info))
		return (false);
	if (!parseGrid(file, info))
		return (false);
	return (true);
}
