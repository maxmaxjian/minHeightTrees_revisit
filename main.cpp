#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>

class solution {
  public:
    std::vector<int> findMHTrees(int n, const std::vector<std::pair<int,int>>& edges) {
        std::vector<int> heights;
        std::vector<int> visited(n);
        for (int i = 0; i < n; i++) {
            auto cpy = visited;
            cpy[i] = 1;
            heights.push_back(getHeight(i, edges, cpy));
        }
        auto it = std::min_element(heights.begin(), heights.end());

        std::vector<int> result;
        for (int i = 0; i < heights.size(); i++)
            if (heights[i] == *it)
                result.push_back(i);

        std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        return result;
    }

  private:
    int getHeight(int n, const std::vector<std::pair<int,int>> & edges, const std::vector<int> & visited) {
        int hgt;
        std::vector<int> next = getNext(n, edges, visited);
        if (next.empty())
            hgt = 1;
        else {
            std::vector<int> cands;
            for (auto nx : next) {
                auto cpy = visited;
                cpy[nx] = 1;
                cands.push_back(1+getHeight(nx, edges, cpy));
            }
            hgt = *std::max_element(cands.begin(), cands.end());
        }
        return hgt;
    }

    std::vector<int> getNext(int n, const std::vector<std::pair<int,int>> & edges, const std::vector<int> & visited) {
        std::vector<int> next;
        for (auto it = edges.begin(); it != edges.end(); ++it) {
            if (it->first == n && visited[it->second] == 0)
                next.push_back(it->second);
            else if (it->second == n && visited[it->first] == 0)
                next.push_back(it->first);
        }
        return next;
    }
};

int main() {
    // std::vector<std::pair<int,int>> edges{
    //     std::make_pair(1,0),
    //         std::make_pair(1,2),
    //         std::make_pair(1,3)
    //         };
    // int n = 4;

    std::vector<std::pair<int,int>> edges{
        std::make_pair(0,3),
            std::make_pair(1,3),
            std::make_pair(2,3),
            std::make_pair(4,3),
            std::make_pair(5,4)
    };
    int n = 6;

    solution soln;
    auto roots = soln.findMHTrees(n, edges);
}
