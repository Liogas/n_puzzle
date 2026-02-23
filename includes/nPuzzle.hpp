/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nPuzzle.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:54:44 by glions            #+#    #+#             */
/*   Updated: 2026/02/23 13:38:27 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

# include <algorithm>
# include <vector>
# include <unordered_map>
# include <iostream>
# include <iomanip>
# include <cmath>

struct	NPuzzleState
{
    using TileType = int;
    std::vector<int>	board;
    int					size;
    
    bool operator==(const NPuzzleState &other) const
    {
        return (board == other.board);
    }

    std::vector<NPuzzleState> genNeighbors() const
    {
        std::vector<NPuzzleState> result;
        int zeroPos = 0;
        while (board[zeroPos] != 0) zeroPos++;

        auto swapAndAdd = [&](int i, int j) {
            NPuzzleState next = *this;
            next.size = this->size;
            std::swap(next.board[i], next.board[j]);
            result.push_back(next);
        };

        int row = zeroPos / size;
        int col = zeroPos % size;

        if (row > 0) swapAndAdd(zeroPos, zeroPos - size);       // up
        if (row < size - 1) swapAndAdd(zeroPos, zeroPos + size); // down
        if (col > 0) swapAndAdd(zeroPos, zeroPos - 1);         // left
        if (col < size - 1) swapAndAdd(zeroPos, zeroPos + 1);  // right

        return (result);
    }
};

namespace	std 
{
    template<>
    struct hash<NPuzzleState>
    {
        size_t operator()(const NPuzzleState &s) const noexcept
        {
            size_t h = 0;
            for (auto v : s.board)
                h = h * 31 + std::hash<int>{}(v);
            return (h);
        }
    };
}

int					manhattan(const NPuzzleState &s, const NPuzzleState &goal);
int					linearConflict(const NPuzzleState &s, const NPuzzleState &goal);
bool				parity(const std::vector<int> &grid1D, int n);
std::vector<int>	genFinalGrid(const std::vector<int> &grid);
void 				printNPuzzleState(const NPuzzleState& s);

#endif