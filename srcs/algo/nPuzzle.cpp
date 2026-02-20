/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:29:50 by glions            #+#    #+#             */
/*   Updated: 2026/02/20 13:00:24 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nPuzzle.hpp"

int manhattan(const NPuzzleState &s, const NPuzzleState &g)
{
	int	h = 0;
	for (size_t i = 0; i < s.board.size(); i++)
	{
		if (s.board[i] == 0) continue;
		size_t goalIndex = std::find(g.board.begin(),
			g.board.end(), s.board[i]) - g.board.begin();
		int curRow = i / s.size, curCol = i % s.size;
		int	goalRow = goalIndex / s.size, goalCol = goalIndex % s.size;
		h += std::abs(curRow - goalRow) + std::abs(curCol - goalCol);
	}	
	return (h);
}

int linearConflict(const NPuzzleState &s, const NPuzzleState &goal)
{
	int n = s.size;
	int	conflicts = 0;
	std::unordered_map<int, int> goalPos;
	for (int i = 0; i < n * n; i++)
		goalPos[goal.board[i]] = i;
	// ROWS
	for (int row = 0; row < n; row++)
	{
		for (int col1 = 0; col1 < row; col1++)
		{
			int tile1 = s.board[row * n + col1];
			if (tile1 == 0)
				continue ;
			if (goalPos[tile1] / n != row)
				continue ;
			for (int col2 = col1 + 1; col2 < n; col2++)
			{
				int tile2 = s.board[row * n + col2];
				if (tile2 == 0)
					continue ;
				if (goalPos[tile2] / n)
					continue ;
				if (goalPos[tile1] % n > goalPos[tile2] % n)
					conflicts++;
			}

		}
	}
	// COL
	for (int col = 0; col < n; col++)
	{
		for (int row1 = 0; row1 < col; row1++)
		{
			int tile1 = s.board[row1 * n + col];
			if (tile1 == 0)
				continue ;
			if (goalPos[tile1] % n != col)
				continue ;
			for (int row2 = row1 + 1; row2 < n; row2++)
			{
				int tile2 = s.board[row2 * n + col];
				if (tile2 == 0)
					continue ;
				if (goalPos[tile2] % n)
					continue ;
				if (goalPos[tile1] / n > goalPos[tile2] / n)
					conflicts++;
			}
		}
	}
	return (manhattan(s, goal) + 2 * conflicts);
}

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

void printNPuzzleState(const NPuzzleState& s)
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
