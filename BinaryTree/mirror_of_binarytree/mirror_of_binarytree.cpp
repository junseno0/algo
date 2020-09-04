#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

/*
* Operate the given binary tree and transform it into a mirror image of the source binary tree.
* 操作给定的二叉树，将其变换为源二叉树的镜像
* Mirror definition of binary tree: source binary tree 
    	    8
    	   / \
    	  6 10
    	 / \ / \
    	5 7 9 11
    	Mirror Binary Tree
    	    8
    	   / \
    	  10 6
    	 / \ / \
    	11 9 7 5
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
* 实质是先序/后序遍历的做法，可采用迭代版本。递归版本太简单了。
*/

class Solution {
public:
    void Mirror(TreeNode *pRoot) {
        if(!pRoot) return;
        std::stack<TreeNode*> st;
        st.push(pRoot);
        while(!st.empty()) {
            TreeNode* top = st.top();
            std::swap(top->left, top->right);
            st.pop();
            if(top->right)
                st.push(top->right);
            if(top->left)
                st.push(top->left);
        }
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
    TreeNode* three = root->right = new TreeNode(3);
    TreeNode* four = two->left = new TreeNode(4);
    TreeNode* five = two->right = new TreeNode(5);
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
    //TODO
    TreeNode* bt1 = contructBT1();
    //TreeNode* bt2 = contructBT2();
    //TreeNode* bt3 = contructBT3();
    Solution sl;
    std::cout<<"bt1 : "<<"\n";
    travIn(bt1, visit);
    std::cout<<"\n";
    sl.Mirror(bt1);
    std::cout<<"bt1 Mirror : "<<"\n";
    travIn(bt1, visit);
    std::cout<<"\n";
    deleteBT(bt1);
    //deleteBT(bt2);
    //deleteBT(bt3);
    return 0;
}
