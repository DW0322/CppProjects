#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

const int ROW{10};
const int COL{10};
bool found{false};

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

    bool blocked{false};
    while (!queue.empty() && !(found && blocked))
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
                else
                {
                    std::cout << "No end could be found. The way is blocked." << std::endl;
                    break;
                }
            }
        }
    }
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
    printGrid(ROW, COL);
    // PATH: START & END
    std::pair<int, int> source{9, 3};
    std::pair<int, int> end{4, 8};
    // GRID (GRAPH DS)
    std::vector<std::vector<int>> grid(ROW, std::vector<int>(COL));
    //  QUEUE
    std::queue<std::pair<int, int>> queue;
    queue.push(source);
    // VISITED
    std::set<std::pair<int, int>> visited;
    visited.insert(source);
    // PARENT
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> parent;
    parent.push_back({source, source});
    // DIRECTIONS
    std::vector<std::pair<int, int>> directions{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // BSF START
    BSF(source, end, queue, directions, visited, parent, grid);

    // PATH
    std::vector<std::pair<int, int>> path;
    std::pair<int, int> current{end};
    if (found)
        pathReconstruction(path, current, source, parent);

    return 0;
}
