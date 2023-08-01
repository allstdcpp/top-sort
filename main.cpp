#include <iostream>
#include <vector>

class directed_graph {
public:
    explicit directed_graph(int vertices);
    directed_graph(directed_graph const&) = default;
    directed_graph& operator=(directed_graph const&) = default;
    directed_graph(directed_graph&&) = default;
    directed_graph& operator=(directed_graph&&) = default;
    void add_edge(int v, int w);
    std::vector<int> const& neighbors(int v) const noexcept;
    size_t edge_size(int v) const noexcept;
    size_t size() const noexcept;
    bool empty() const noexcept;
    ~directed_graph() = default;

private:
    std::vector<std::vector<int>> data_;
};

directed_graph::directed_graph(int vertices) {
    data_.resize(vertices);
}

void directed_graph::add_edge(int v, int w) {
    data_[v].push_back(w);
}

std::vector<int> const& directed_graph::neighbors(int v) const noexcept {
    return data_[v];
}

size_t directed_graph::edge_size(int v) const noexcept {
    return data_[v].size();
}

size_t directed_graph::size() const noexcept {
    return data_.size();
}

bool directed_graph::empty() const noexcept {
    return data_.empty();
}

class top_sort {
public:
    top_sort(directed_graph const& g)
        : g_ {g} {

        ordering_.resize(g.size());
        visited_.resize(g.size());

        for(size_t i = 0; i < g.size(); ++i) {
            if(!visited_[i]) { dfs(static_cast<int>(i)); }
        }
    }

    std::vector<int> const& ordering() const noexcept {
        return ordering_;
    }

private:
    void dfs(int v) {
        visited_[v] = true;

        auto const& neighbors = g_.neighbors(v);

        for(auto n : neighbors) {
            if(!visited_[n]) { dfs(n); }
        }

        ordering_[--position_] = v;
    }

    directed_graph const& g_;
    std::vector<int> ordering_;
    std::vector<int> visited_;
    int position_ {static_cast<int>(g_.size())};
};

int main(int argc, char** argv) {

    directed_graph g {5};
    g.add_edge(0, 3);
    g.add_edge(0, 2);
    g.add_edge(2, 3);
    g.add_edge(4, 0);
    g.add_edge(4, 2);
    g.add_edge(1, 4);
    g.add_edge(1, 2);

    top_sort s {g};
    auto const& ordering = s.ordering();

    for(auto const& o : ordering) { std::cout << o << " "; }

    std::cout << std::endl;
    return EXIT_SUCCESS;
}
