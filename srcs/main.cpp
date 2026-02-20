/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:43:31 by glions            #+#    #+#             */
/*   Updated: 2026/02/20 11:48:57 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "parsing.hpp"
#include "nPuzzle.hpp"
#include "AStar.hpp"
#include <cmath>
#include <iomanip>

bool parity(const std::vector<int> &grid1D, int n)
{
    std::vector<int> list;
    int row = 0;

    for (int val : grid1D)
        if (val != 0)
            list.push_back(val);

    int nbInvers = 0;
    for (size_t i = 0; i < list.size(); i++)
        for (size_t j = i + 1; j < list.size(); j++)
            if (list[i] > list[j])
                nbInvers++;

    if (n % 2 == 0)
    {
        auto it = std::find(grid1D.begin(), grid1D.end(), 0);
        int zeroPos = std::distance(grid1D.begin(), it);
        row = n - (zeroPos / n);
    }

    if (n % 2 != 0)
        return nbInvers % 2 == 0 ? false : true;
    return (nbInvers + row) % 2 == 0 ? false : true;
}

std::vector<int> genFinalGrid(const std::vector<int> &grid)
{
    int n = std::sqrt(grid.size());
    std::vector<int> values;
    std::vector<int> g(n * n, -1);

    // Récupérer toutes les valeurs sauf 0
    for (const auto &val : grid)
            if (val != 0)
                values.push_back(val);

    std::sort(values.begin(), values.end());
    values.push_back(0);

    int dir[4] = {0, n - 1, 0, n - 1};
    int idx = 0;

    while (dir[0] <= dir[1] && dir[2] <= dir[3])
    {
        // ligne du haut
        for (int x = dir[2]; x <= dir[3]; x++)
            g[dir[0] * n + x] = values[idx++];
        dir[0]++;

        // colonne de droite
        for (int y = dir[0]; y <= dir[1]; y++)
            g[y * n + dir[3]] = values[idx++];
        dir[3]--;

        // ligne du bas
        for (int x = dir[3]; x >= dir[2]; x--)
            g[dir[1] * n + x] = values[idx++];
        dir[1]--;

        // colonne de gauche
        for (int y = dir[1]; y >= dir[0]; y--)
            g[y * n + dir[2]] = values[idx++];
        dir[2]++;
    }

    return g;
}

void printState(const NPuzzleState& s)
{
    for (int row = 0; row < s.size; ++row)
    {
        for (int col = 0; col < s.size; ++col)
        {
            int value = s.board[row * s.size + col];

            if (value == 0)
                std::cout << "   ";   // case vide
            else
                std::cout << std::setw(3) << value;

        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int	main(int ac, char **av)
{
	ParsingInfo	parsingInfo;
	if (ac != 3)
	{
		std::cout << "args missing : ./nPuzzle [file] [heuristic]" << std::endl;
		return (1);
	}
	if (!parsing(av[1], parsingInfo))
	{
		std::cerr << "File not conform : " << av[1] << std::endl;
		return (1);
	}
	std::vector<int> finalGrid = genFinalGrid(parsingInfo.grid);
	NPuzzleState start{parsingInfo.grid, parsingInfo.size};
	NPuzzleState dest{finalGrid, parsingInfo.size};
	if (parity(start.board, start.size) != parity(dest.board, start.size))
	{
		std::cout << "Grid unsolvable" << std::endl;
		return (0);
	}

	printState(start);
	printState(dest);

	std::vector<NPuzzleState> path = AStar(
		start,
		dest,
		[](const NPuzzleState &s){ return s.genNeighbors(); },
		[](const NPuzzleState &s, const NPuzzleState &g){ (void)s; (void)g; return (1); },
		manhattan
	);
	std::cout << std::endl;
	for (auto s : path)
		printState(s);
	return (0);
}
