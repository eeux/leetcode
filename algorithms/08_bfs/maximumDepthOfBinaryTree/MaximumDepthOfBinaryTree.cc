// Source : https://leetcode.com/problems/maximum-depth-of-binary-tree
// Author : xjliang
// Date   : 2020-12-05

/***************************************************************************************************** 
 *
 * Given the root of a binary tree, return its maximum depth.
 * 
 * A binary tree's maximum depth is the number of nodes along the longest path from the root node down 
 * to the farthest leaf node.
 * 
 * Example 1:
 * 
 * Input: root = [3,9,20,null,null,15,7]
 * Output: 3
 * 
 * Example 2:
 * 
 * Input: root = [1,null,2]
 * Output: 2
 * 
 * Example 3:
 * 
 * Input: root = []
 * Output: 0
 * 
 * Example 4:
 * 
 * Input: root = [0]
 * Output: 1
 * 
 * Constraints:
 * 
 * 	The number of nodes in the tree is in the range [0, 104].
 * 	-100 <= Node.val <= 100
 ******************************************************************************************************/

#include <cassert> // assert
#include <iostream>
#include <algorithm> // max
#include <vector>
#include <queue>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// DFS
int maxDepth(const TreeNode* root) {
  if (root == nullptr) {
    return 0;
  }
  return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
}

// BFS
int maxDepthBFS(const TreeNode* root) {
  if (root == nullptr) {
    return 0;
  }
  
  int max_depth = 0;
  std::queue<const TreeNode*> que;
  que.push(root);
  while (!que.empty()) {
    int size = que.size();
    while (size > 0)
    {
      const TreeNode* node = que.front();
      que.pop();
      
      if (node->left) {
        que.push(node->left);
      }
      if (node->right) {
        que.push(node->right);
      }
      size--;
    }
    max_depth++;
  }
  return max_depth;
}

TreeNode* CreateNode(std::vector<TreeNode*>& node_pool, int val) {
  TreeNode* node = new TreeNode(val);
  node_pool.push_back(node);
  return node;
}

int Solution(const TreeNode* root) {
  //return maxDepth(root);
  return maxDepthBFS(root);
}

void RunAllTests() {
  // resource holder
  std::vector<TreeNode*> node_pool;
  
  TreeNode* root1 = CreateNode(node_pool, 3);
  TreeNode* left9 = CreateNode(node_pool, 9);
  TreeNode* left20 = CreateNode(node_pool, 20);
  TreeNode* left15 = CreateNode(node_pool, 15);
  TreeNode* left7 = CreateNode(node_pool, 7);
  root1->left = left9;
  root1->right = left20;
  left20->left = left15;
  left20->right = left7;
  assert(Solution(root1) == 3);
  std::cout << "case1 success." << std::endl;
  
  TreeNode* root2 = CreateNode(node_pool, 2);
  TreeNode* right2 = CreateNode(node_pool, 2);
  root2->left = nullptr;
  root2->right = right2;
  assert(Solution(root2) == 2);
  std::cout << "case2 success." << std::endl;
  
  TreeNode* root3 = CreateNode(node_pool, 0);
  assert(Solution(root3) == 1);
  std::cout << "case3 success." << std::endl;
  
  // clean up
  for (TreeNode* p : node_pool) {
    if (p) {
      delete p;
      p = nullptr;
    }
  }
  node_pool.clear();
}

int main(int argc, char const *argv[])
{
  RunAllTests();
  std::cout << "done." << std::endl;
  return 0;
}
