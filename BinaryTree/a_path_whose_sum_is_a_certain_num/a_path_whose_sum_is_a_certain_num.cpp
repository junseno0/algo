#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
* Input the root node of a binary tree and an integer, and print out all the paths where the sum
* of the node values ​​in the binary tree is the input integer in lexicographic order. The path is defined
* as a path from the root node of the tree and going down to the nodes passed by the leaf nodes.

* 输入一颗二叉树的根节点和一个整数，按字典序打印出二叉树中结点值的和为输入整数的所有路径。
* 路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。
*/

 //Definition for binary tree
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};

class Solution {
public:
    std::vector<std::vector<int>> ret;
    std::vector<std::vector<int>> _findPath(TreeNode* root, int number, std::vector<int> path,
                                           std::vector<std::vector<int>>& ret, int total) {
        path.push_back(root->val);
        if(root->left == nullptr && root->right == nullptr &&
              (total + root->val == number)) {
            ret.push_back(path);
            return ret;
        }
        total += root->val;
        if(root->left) _findPath(root->left, number, path, ret, total);
        if(root->right) _findPath(root->right, number, path, ret, total);
        return ret;
    }
    std::vector<std::vector<int> > FindPath(TreeNode* root,int expectNumber) {
        //check
        int total = 0;
        if(!root) return ret;
        std::vector<int> path;
        _findPath(root, expectNumber, path, ret, total);
        return ret;
    }
};

void visit(TreeNode* x) {
    std::cout<<" ["<<x->val<<"] ";
}

template<typename VST>
void travIn(TreeNode* treevertex, VST& visit) {
    // WAVE
    //to left bottom
    //to top
    //to right WAVE again
    TreeNode* root = treevertex;
    std::stack<TreeNode*> st;
    //st.push(root);
    while(true){
        while(root) {
            st.push(root);
            root = root->left;
        }
        if(st.empty()) break;
        root = st.top();
        visit(root);
        st.pop();
        root = root->right;
    }
}

TreeNode* contructBT1() {
    TreeNode* root = new TreeNode(8);
    TreeNode* six = root->left = new TreeNode(6);
    TreeNode* ten = root->right = new TreeNode(10);
    six->left = new TreeNode(5);
    six->right = new TreeNode(7);
    ten->left = new TreeNode(9);
    ten->right = new TreeNode(11);
    return root;
}

TreeNode* contructBT2() {
    TreeNode* root = new TreeNode(2);
    root->right = new TreeNode(5);
    return root;
}

TreeNode* contructBT3() {
    TreeNode* root = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left = new TreeNode(3);
    return root;
}

void preorder(TreeNode* root, std::vector<TreeNode*> &vt) {
    std::stack<TreeNode*> st;
    if(root == nullptr) return;
    //preorder traverse
    //visist st.top();
    st.push(root);
    while(!st.empty()) {
        root = st.top();
        vt.push_back(root);
        st.pop();
        if(root->right) {
            st.push(root->right);
        }
        if(root->left) {
            st.push(root->left);
        }
    }
}

void deleteBT(TreeNode* root) {
    std::vector<TreeNode*> vt;
    std::stack<TreeNode*> st;
    preorder(root, vt);
    while(vt.size()) {
        TreeNode* tmp = vt.front();
        vt.erase(vt.begin());
        delete tmp;
    }
}

int main() {
    TreeNode* bt1 = contructBT1();
    TreeNode* bt2 = contructBT2();
    TreeNode* bt3 = contructBT3();

    Solution sl;
    std::vector<std::vector<int>> ret;
    std::cout<<"bt1 : "<<"\n";
    travIn(bt1, visit);
    std::cout<<"\n";
    ret = sl.FindPath(bt1, 19);
    std::cout<<"bt1 path whose sun is 19: \n";
    for(auto itt : ret) {
        for(auto it : itt) std::cout<<"[ "<<it<<"] ";
        std::cout<<"\n";
    }
 
    deleteBT(bt1);
    deleteBT(bt2);
    deleteBT(bt3);
    return 0;
}
