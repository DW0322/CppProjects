#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <set>
#include <vector>

const int ROW{5};
const int COL{5};
bool found{false};

int randomBlock()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(0, ROW - 1);

    return distrib(gen);
}

void blockPath(std::vector<std::vector<int>> &grid)
{
    for (int i{}; i < 10; ++i)
        grid[randomBlock()][randomBlock()] = 1;
}

void printGrid(int r, int c)
{
    for (int i{}; i < r; ++i)
    {
        for (int j{}; j < c; ++j)
            std::cout << '[' << i << ',' << j << ']';
        std::cout << std::endl;
    }
}

void BSF(std::pair<int, int> &source, std::pair<int, int> &end,
         std::queue<std::pair<int, int>> &queue, std::vector<std::pair<int, int>> &directions,
         std::set<std::pair<int, int>> &visited,
         std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &parent,
         std::vector<std::vector<int>> grid)
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

void pathReconstruction(std::vector<std::pair<int, int>> &path, std::pair<int, int> &current,
                        std::pair<int, int> &source,
                        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &parent)
{
    while (current != source)
    {
        path.push_back(current);
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
    path.push_back(source);
    std::reverse(path.begin(), path.end());

    for (auto const &step : path)
    {
        std::cout << step.first << ',' << step.second << std::endl;
    }
}

int main()
{
    // PATH: START & END
    std::pair<int, int> source{0, 0};
    std::pair<int, int> end{4, 4};
    // GRID (GRAPH DS)
    std::vector<std::vector<int>> grid(ROW, std::vector<int>(COL));
    // QUEUE
    std::queue<std::pair<int, int>> queue;
    // VISITED
    std::set<std::pair<int, int>> visited;
    // PARENT
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> parent;
    // DIRECTIONS
    std::vector<std::pair<int, int>> directions{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    // PATH
    std::vector<std::pair<int, int>> path;
    std::pair<int, int> current{end};

    // INITIAL STEPS
    queue.push(source);
    visited.insert(source);
    parent.push_back({source, source});
    // PATHFINDING BSF START
    printGrid(ROW, COL);
    blockPath(grid);
    BSF(source, end, queue, directions, visited, parent, grid);
    if (found)
        pathReconstruction(path, current, source, parent);

    return 0;
}
