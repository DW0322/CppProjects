#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

const int ROW{5};
const int COL{5};
bool found{false};

struct PathfindingState
{

    std::vector<std::vector<int>> grid{ROW, std::vector<int>(COL)};
    std::queue<std::pair<int, int>> queue;
    std::set<std::pair<int, int>> visited;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> parent;
    const std::vector<std::pair<int, int>> directions{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::stack<std::pair<int, int>> path;
};

int randomBlock()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(0, ROW - 1);

    return distrib(gen);
}

void blockPath(std::vector<std::vector<int>> &grid)
{
    for (int i{}; i < (ROW * 2); ++i)
        grid[randomBlock()][randomBlock()] = 1;
}

void printGrid(std::vector<std::vector<int>> &grid, int r, int c)
{
    for (int i{}; i < r; ++i)
    {
        for (int j{}; j < c; ++j)
            if (grid[i][j] == 0)
                std::cout << " * ";
            else
                std::cout << " # ";
        std::cout << std::endl;
    }
}

void BSF(const std::pair<int, int> &source, const std::pair<int, int> &end,
         std::queue<std::pair<int, int>> &queue, const std::vector<std::pair<int, int>> &directions,
         std::set<std::pair<int, int>> &visited,
         std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &parent,
         const std::vector<std::vector<int>> &grid)
{

    while (!queue.empty() && !found)
    {
        std::pair current = queue.front();
        queue.pop();

        if (current == end)
        {
            std::cout << "Found the end!" << std::endl;
            break;
        }
        for (const auto &dir : directions)
        {
            int NewX = current.first + dir.first;
            int NewY = current.second + dir.second;
            std::pair NewNode{NewX, NewY};
            if (NewX < ROW && NewX >= 0 && NewY < COL && NewY >= 0 &&
                visited.find(NewNode) == visited.end())
            {
                if (!grid[NewX][NewY])
                {
                    queue.push(NewNode);
                    visited.insert(NewNode);
                    parent.push_back({current, NewNode});

                    if (NewNode == end)
                    {
                        found = true;
                        break;
                    }
                }
            }
        }
    }
    if (!found)
        std::cout << "Can't fint the end. The way must be blocked." << std::endl;
}

void pathReconstruction(std::stack<std::pair<int, int>> &path, const std::pair<int, int> &source,
                        const std::pair<int, int> &end,
                        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &parent)
{
    std::pair<int, int> current{end};
    while (current != source)
    {
        path.push(current);
        for (int i{}; i < path.size(); ++i)
        {
            for (const auto &c : parent)
            {
                if (current == c.second)
                {
                    current = c.first;
                    break;
                }
            }
            break;
        }
    }
    path.push(source);

    while (!path.empty())
    {
        std::pair<int, int> step = path.top();
        path.pop();
        std::cout << step.first << ',' << step.second << std::endl;
    }
}

int main()
{

    constexpr std::pair<int, int> source{0, 0};
    constexpr std::pair<int, int> end{4, 4};

    PathfindingState ps;

    // INITIAL STEPS
    ps.queue.push(source);
    ps.visited.insert(source);
    ps.parent.push_back({source, source});

    // PATHFINDING BSF START
    blockPath(ps.grid);
    printGrid(ps.grid, ROW, COL);
    if (ps.grid[source.first][source.second] == 1)
    {
        std::cout << "The source is blocked" << std::endl;
        return 0;
    }
    BSF(source, end, ps.queue, ps.directions, ps.visited, ps.parent, ps.grid);
    if (found)
        pathReconstruction(ps.path, source, end, ps.parent);

    return 0;
}
