/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:43:31 by glions            #+#    #+#             */
/*   Updated: 2026/02/05 16:30:22 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AlgoStar.hpp"
#include "parsing.hpp"
#include "heuristics.hpp"

bool parity(std::vector<std::vector<int>> grid)
{
	std::vector<int> 	list;
	int				 	row = 0;
	for (size_t i = 0; i < grid.size(); i++)
	{
		for (size_t j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] != 0)
				list.push_back(grid[i][j]);
		}
	}
	int	nbInvers = 0;
	for (size_t i = 0; i < list.size(); i++)
	{
		for (size_t j = i + 1; j < list.size(); j++)
		{
			if (list[i] > list[j])
				nbInvers++;
		}
	}
	if (grid.size() % 2 == 0)
	{
		for (int i = grid.size() - 1; i >= 0; i--)
		{
			row++;
			for (size_t j = 0; j < grid[i].size(); j++)
			{
				if (grid[i][j] == 0)
				{
					i = -1;
					break ;
				}
			}
		}
	}
	if (grid.size() % 2 != 0)
		return (nbInvers % 2);
	return ((nbInvers + row) % 2);
}

std::vector<std::vector<int>> genFinalGrid(std::vector<std::vector<int>> &grid)
{
	int	n = grid.size();
	std::vector<int> values;
	std::vector<std::vector<int>> g(n, std::vector<int>(n, -1));

	for (const auto &row : grid)
		for (int val : row)
		{
			if (val != 0)
				values.push_back(val);
		}
	std::sort(values.begin(), values.end());
	values.push_back(0);
	int	dir[4] = {0, n - 1, 0, n - 1};
	int	idx = 0;
	while (dir[0] <= dir[1] && dir[2] <= dir[3])
	{
		for (int x = dir[2]; x <= dir[3]; x++)
			g[dir[0]][x] = values[idx++];
		dir[0]++;
		for (int y = dir[0]; y <= dir[1]; y++)
			g[y][dir[3]] = values[idx++];
		dir[3]--;
		for (int x = dir[3]; x >= dir[2]; x--)
			g[dir[1]][x] = values[idx++];
		dir[1]--;
		for (int y = dir[1]; y >= dir[0]; y--)
			g[y][dir[2]] = values[idx++];
		dir[2]++;
	}
	return (g);
}

int	main(int ac, char **av)
{
	ParsingInfo	parsingInfo;
	if (ac != 2)
	{
		std::cout << "File missing -> use ./npuzzle-gen.py [-s] [-u] [-i]" << std::endl;
		return (1);
	}
	
	if (!parsing(av[1], parsingInfo))
	{
		std::cerr << "File not conform : " << av[1] << std::endl;
		return (1);
	}

	std::vector<std::vector<int>> finalGrid = genFinalGrid(parsingInfo.grid);

	Node start(parsingInfo.grid, 0, 0, nullptr);
	Node dest(finalGrid, -1, -1, nullptr);

	for (auto &row : start.getGrid()) {
        for (auto val : row)
			std::cout << " " << val;
		std::cout << std::endl;
    }
	std::cout << std::endl << std::endl;
	for (auto &row : dest.getGrid()) {
        for (auto val : row)
			std::cout << " " << val;
		std::cout << std::endl;
    }

	if (parity(start.getGrid()) != parity(dest.getGrid()))
	{
		std::cout << "Grille non solvable" << std::endl;
		return (0);
	}
	
	AlgoStar algo(start, dest);
	algo.start(HeuristicType::Manhattan);
	return (0);
}