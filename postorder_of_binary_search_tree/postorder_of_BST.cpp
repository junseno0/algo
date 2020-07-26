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
* Enter an integer array to determine whether the array is the result of a post-order traversal of a binary search tree.
* If yes, output Yes, otherwise output No. Assume that any two numbers in the input array are different from each other.

* 输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。
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

//Time complexity: O(nlogn)
//Space complexity: O(n)
class Solution_by_recursion {
public:
    bool _verifySequence(std::vector<int> &sequence, int left, int right) {
        if(left >= right) return true;
        int anchor = sequence[right];
        //find the pos
        //if second part all > anchor?
        //no, return false
        int pos = right;//最后一个元素是不用比较的，故i < right
        for(int i = left; i < right; i++) {
            if(sequence[i] > anchor) pos = i;
            if(pos != right && sequence[i] < anchor) return false;
        }
        //_verifySequence [left, pos-1] &&  [pos, right-1]
        return _verifySequence(sequence, left, pos-1) && _verifySequence(sequence, pos, right-1);
    }
    bool VerifySquenceOfBST(std::vector<int> sequence) {
        //CHECK
        if(sequence.size() == 0) return false;
        //last as anchor, find ths pos, ahead all < anchor
        //check if second part all > anchor, if not, return false
        //if yes, recurse the first part and second part
        return _verifySequence(sequence, 0, sequence.size() - 1);
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
    //TreeNode* bt1 = contructBT1();
    //TreeNode* bt2 = contructBT2();
    //TreeNode* bt3 = contructBT3();
    std::vector<int> vt1 = {4, 8, 6, 12, 16, 14, 10};
    std::vector<int> vt2 = {};
    std::vector<int> vt3 = {4, 6, 8};
    Solution_by_recursion sl;
    bool flag = false;

    flag = sl.VerifySquenceOfBST(vt1);
    std::cout<<"vt1 VerifySquenceOfBST : "<<flag<<"\n";
    flag = sl.VerifySquenceOfBST(vt2);
    std::cout<<"vt2 VerifySquenceOfBST : "<<flag<<"\n";
    flag = sl.VerifySquenceOfBST(vt3);
    std::cout<<"vt3 VerifySquenceOfBST : "<<flag<<"\n";
 
    //deleteBT(bt1);
    //deleteBT(bt2);
    //deleteBT(bt3);
    return 0;
}
