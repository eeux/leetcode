// Source : https://leetcode.com/problems/merge-two-binary-trees
// Author : xjliang
// Date   : 2020-12-05

/***************************************************************************************************** 
 *
 * Given two binary trees and imagine that when you put one of them to cover the other, some nodes of 
 * the two trees are overlapped while the others are not.
 * 
 * You need to merge them into a new binary tree. The merge rule is that if two nodes overlap, then 
 * sum node values up as the new value of the merged node. Otherwise, the NOT null node will be used 
 * as the node of new tree.
 * 
 * Example 1:
 * 
 * Input: 
 * 	Tree 1                     Tree 2                  
 *           1                         2                             
 *          / \                       / \                            
 *         3   2                     1   3                        
 *        /                           \   \                      
 *       5                             4   7                  
 * Output: 
 * Merged tree:
 * 	     3
 * 	    / \
 * 	   4   5
 * 	  / \   \ 
 * 	 5   4   7
 * 
 * Note: The merging process must start from the root nodes of both trees.
 ******************************************************************************************************/

#include <cassert> // assert
#include <iostream>
#include <vector>

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


TreeNode* CreateNode(std::vector<TreeNode*>& node_pool, int val) {
  TreeNode* node = new TreeNode(val);
  node_pool.push_back(node);
  return node;
}

TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2, std::vector<TreeNode*>& node_pool) {
  if (t1 != nullptr && t2 != nullptr) {
    TreeNode* root = CreateNode(node_pool, t1->val + t2->val);
    root->left = mergeTrees(t1->left, t2->left, node_pool);
    root->right = mergeTrees(t1->right, t2->right, node_pool);
    return root;
  }
  return t1 ? t1 : t2;
}

int main(int argc, char const *argv[])
{
  // resource holder
  std::vector<TreeNode*> node_pool;
  
  // init
  TreeNode* root1 = CreateNode(node_pool, 1);
  TreeNode* left2 = CreateNode(node_pool, 2);
  TreeNode* left3 = CreateNode(node_pool, 3);
  TreeNode* left5 = CreateNode(node_pool, 5);
  root1->left = left3;
  root1->right = left2;
  left3->left = left5;
  TreeNode* root2 = CreateNode(node_pool, 2);
  TreeNode* right1 = CreateNode(node_pool, 1);
  TreeNode* right3 = CreateNode(node_pool, 3);
  TreeNode* right4 = CreateNode(node_pool, 4);
  TreeNode* right7 = CreateNode(node_pool, 7);
  root2->left = right1;
  root2->right = right3;
  right1->right = right4;
  right3->right = right7;
  
  // process
  TreeNode* result = mergeTrees(root1, root2, node_pool);
  
  // check result
  assert(result->val == 3);
  assert(result->left->val == 4);
  assert(result->left->left->val == 5);
  assert(result->left->right->val == 4);
  assert(result->right->val == 5);
  assert(result->right->right->val == 7);
  
  // clean up
  for (TreeNode* p : node_pool) {
    if (p) {
      delete p;
      p = nullptr;
    }
  }
  node_pool.clear();
  std::cout << "success." << std::endl;
  
  return 0;
}
