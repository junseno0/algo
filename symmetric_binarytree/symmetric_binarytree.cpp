#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

/*
* Please implement a function to determine whether a binary tree is symmetric.
* Note that if a binary tree is the same as the mirror image of this binary tree, define it as symmetric.
* 请实现一个函数，用来判断一棵二叉树是不是对称的。注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。
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
    bool compare(TreeNode* p1, TreeNode* p2) {
        if(p1 == nullptr && p2 == nullptr) return true;
        if(!p1 || !p2 || (p1->val != p2->val)) return false;
        return compare(p1->left, p2->right) && compare(p1->right, p2->left);
    }
    bool isSymmetrical(TreeNode* pRoot)
    {
        //check
        if(!pRoot) return true;
        return compare(pRoot->left, pRoot->right);
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
    TreeNode* root = new TreeNode(1);
    TreeNode* two = root->left = new TreeNode(2);
    TreeNode* three = root->right = new TreeNode(2);
    two->left = new TreeNode(4);
    three->right = new TreeNode(4);
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
    bool flag = false;
    Solution sl;
    std::vector<int> vt;
    std::cout<<"bt1 : "<<"\n";
    travIn(bt1, visit);
    std::cout<<"\n";
    flag = sl.isSymmetrical(bt1);
    std::cout<<"bt1 isSymmetrical : "<<flag<<"\n";
    for(auto it : vt) std::cout<<"[ "<<it<<" ]";
    std::cout<<"\n";
 
    std::cout<<"bt2 : "<<"\n";
    travIn(bt2, visit);
    std::cout<<"\n";
    flag = sl.isSymmetrical(bt2);
    std::cout<<"bt2 isSymmetrical : "<<flag<<"\n";
    for(auto it : vt) std::cout<<"[ "<<it<<" ]";
    std::cout<<"\n";

    std::cout<<"bt3 : "<<"\n";
    travIn(bt3, visit);
    std::cout<<"\n";
    flag = sl.isSymmetrical(bt3);
    std::cout<<"bt3 isSymmetrical : "<<flag<<"\n";
    for(auto it : vt) std::cout<<"[ "<<it<<" ]";
    std::cout<<"\n";
 
    deleteBT(bt1);
    deleteBT(bt2);
    deleteBT(bt3);
    return 0;
}
