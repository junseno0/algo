#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

/*
* Print out each node of the binary tree from top to bottom, and print the nodes at the same level from left to right.
* 从上往下打印出二叉树的每个节点，同层节点从左至右打印。
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
    std::vector<int> PrintFromTopToBottom(TreeNode* root) {
        std::vector<int> vt;
        if(!root) return vt;
        std::queue<TreeNode*> qt;
        qt.push(root);
        while(!qt.empty()) {
            root = qt.front();
            vt.push_back(root->val);
            qt.pop();
            if(root->left) qt.push(root->left);
            if(root->right) qt.push(root->right);
        }
        return vt;
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
    TreeNode* bt1 = contructBT1();
    TreeNode* bt2 = contructBT2();
    TreeNode* bt3 = contructBT3();
    Solution sl;
    std::vector<int> vt;
    std::cout<<"bt1 : "<<"\n";
    travIn(bt1, visit);
    std::cout<<"\n";
    vt = sl.PrintFromTopToBottom(bt1);
    std::cout<<"bt1 PrintFromTopToBottom : "<<"\n";
    for(auto it : vt) std::cout<<"[ "<<it<<" ]";
    std::cout<<"\n";
 
    std::cout<<"bt2 : "<<"\n";
    travIn(bt2, visit);
    std::cout<<"\n";
    vt = sl.PrintFromTopToBottom(bt2);
    std::cout<<"bt2 PrintFromTopToBottom : "<<"\n";
    for(auto it : vt) std::cout<<"[ "<<it<<" ]";
    std::cout<<"\n";

 
    deleteBT(bt1);
    deleteBT(bt2);
    deleteBT(bt3);
    return 0;
}
