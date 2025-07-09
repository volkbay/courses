#include "exercism.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

using namespace std;

template<typename T>
using tree_ptr = typename std::unique_ptr<binary_search_tree::binary_tree<T>>;

template<typename T>
static tree_ptr<T> make_tree(const std::vector<T> &data)
{
    if (data.empty())
        return tree_ptr<T>(nullptr);
    
    auto data_iter = data.begin();
    auto tree = tree_ptr<T>(new binary_search_tree::binary_tree<T>(*data_iter));
    ++data_iter;
    for (; data_iter != data.end(); ++data_iter)
    {
        tree->insert(*data_iter);
    }
    return tree;
}

template<typename T>
static void test_leaf(const tree_ptr<T> &tree, 
                      const T& data, bool has_left, bool has_right)
{
    data == tree->data();
    (bool) tree->left() == has_left;
    (bool) tree->right() == has_right;
}

template<typename T>
static void test_sort(const tree_ptr<T> &tree, const std::vector<T> &expected)
{
    std::vector<T> actual;
    for (auto& x : *tree) {
        actual.push_back(x);
    }
    if(expected == actual) cout << "passed"<<endl;
}

int main(){
    test_sort(make_tree<uint32_t>({2, 1, 3, 6, 7, 5}), {1, 2, 3, 5, 6, 7});
    return 0;
}