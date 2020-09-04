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
* Enter a binary tree to determine whether the binary tree is a balanced binary tree.
* Here, we only need to consider its balance, not whether it is a sorted binary tree

* 输入一棵二叉树，判断该二叉树是否是平衡二叉树。
* 在这里，我们只需要考虑其平衡性，不需要考虑其是不是排序二叉树
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

/*
链接：https://www.nowcoder.com/questionTerminal/8b3b95850edb4115918ecebdf1b4d222?answerType=1&f=discussion
来源：牛客网

判断一个数是否为平衡二叉树。平衡二叉树是左子树的高度与右子树的高度差的绝对值小于等于1，同样左子树是平衡二叉树，右子树为平衡二叉树。

根据定义，如果我们能够求出以每个结点为根的树的高度，然后再根据左右子树高度差绝对值小于等于1，,就可以判断以每个结点为根的树是否满足定义.
*/
//Time complexity: O(n)
//Space complexity: O(n)
class Solution_by_recursion {
public:
    int depth(TreeNode* root) {
        if(!root) return 0;
        return std::max(depth(root->left), depth(root->right)) + 1;
    }
    bool judge(TreeNode* root) {
        if(!root) return true;
        //visit root. preOrder visit.
        return (abs(depth(root->left) - depth(root->right)) <= 1)
            && judge(root->left) && judge(root->right);
    }
    bool IsBalanced_Solution(TreeNode* pRoot) {
        //check
        if(pRoot == nullptr) return true;
        return judge(pRoot);
    }
};

//优化解法，在求高度的同时，判断，采用剪枝。
//利用后序遍历：左子树、右子树、根节点,可以先递归到叶子节点，然后在回溯的过程中来判断是否满足条件。
class Solution {
public:
    int depth(TreeNode *root) {
        if (!root) return 0;
        int ldep = depth(root->left);
        if (ldep == -1) return -1;
        int rdep = depth(root->right);
        if (rdep == -1) return -1;
        int sub = abs(ldep - rdep);
        if (sub > 1) return -1;
        return std::max(ldep, rdep) + 1;
    }
    bool IsBalanced_Solution(TreeNode* root) {
        return depth(root) != -1;
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
    root->right->right = new TreeNode(7);
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

    Solution_by_recursion sl;
    bool flag = false;
    std::cout<<"bt1 : "<<"\n";
    travIn(bt1, visit);
    std::cout<<"\n";
    flag = sl.IsBalanced_Solution(bt1);
    std::cout<<"bt1 IsBalanced_Solution : "<<flag<<"\n";
    flag = sl.IsBalanced_Solution(bt2);
    std::cout<<"bt2 IsBalanced_Solution : "<<flag<<"\n";
    flag = sl.IsBalanced_Solution(bt3);
    std::cout<<"bt3 IsBalanced_Solution : "<<flag<<"\n";
 
    deleteBT(bt1);
    deleteBT(bt2);
    deleteBT(bt3);
    return 0;
}
