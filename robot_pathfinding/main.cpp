#include <iostream>
#include <queue>
#include <set>
#include <vector>

const int ROW{4};
const int COL{4};

int main()
{
    std::pair<int, int> source{0, 0};
    std::pair<int, int> end{2, 2};

    std::vector<std::vector<int>> grid(ROW, std::vector<int>(COL));
    // QUEUE
    std::queue<std::pair<int, int>> queue;
    queue.push(source);
    // VISITED
    std::set<std::pair<int, int>> visited;
    visited.insert(source);
    // PARENT
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> parent;
    parent.push_back({source, source});

    std::vector<std::pair<int, int>> directions{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!queue.empty())
    {
        std::pair current = queue.front();
        queue.pop();

        if (current == end)
        {
            std::cout << "Found the end!" << std::endl;
            break;
        }
        int NewX{current.first};
        int NewY{current.second};
        for (const auto &dir : directions)
        {
            NewX += dir.first;
            NewY += dir.second;
            std::pair NewNode{NewX, NewY};
            if (NewX <= ROW && NewX >= 0 && NewY <= COL && NewY >= 0 &&
                visited.find(NewNode) == visited.end())
            {
                if (NewNode == end)
                {
                    std::cout << NewX << ',' << NewY << std::endl;
                    std::cout << "AAAA" << std::endl;
                    break;
                }
                queue.push(NewNode);
                visited.insert(NewNode);
                parent.push_back({current, NewNode});
                std::cout << NewX << ',' << NewY << std::endl;
            }
        }
    }
    return 0;
}
