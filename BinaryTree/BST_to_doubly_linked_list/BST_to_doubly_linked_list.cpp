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
* Enter a binary search tree and convert the binary search tree into a sorted doubly linked list.
* It is required that no new nodes can be created, and only the point of the node pointer in the tree can be adjusted.

* 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。
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
* 中序遍历的性质是，节点从左到右，而搜索二叉树从左到右非降。
* 中序遍历后即是有序的数据。
* 如何转换成双向链表？将每次遍历的节点与前一节点建立起联系即可。
* 联系包括前向与后向联系。
*/
//Time complexity: O(n)
//Space complexity: O(1)
class Solution_by_iteration {
public:
    TreeNode* InOrder(TreeNode* root) {
        std::stack<TreeNode*> st;
        TreeNode* lastnode = nullptr;
        TreeNode* newroot = nullptr;
        while(true) {
            while(root) {
                st.push(root);
                root = root->left;
            }
            if(st.empty()) break;
            root = st.top();
            st.pop();
            //visit
            root->left = lastnode;
            if(lastnode) lastnode->right = root;
            else newroot = root;
            lastnode = root;
            //turn to right tree
            root = root->right;
        }
        return newroot;
    }
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        //check
        if(!pRootOfTree) return nullptr;
        TreeNode* lastnode = InOrder(pRootOfTree);
        return lastnode;
    }
};

//TODO，递归解法
/*
链接：https://www.nowcoder.com/questionTerminal/947f6eb80d944a84850b0538bf0ec3a5?answerType=1&f=discussion
来源：牛客网

private TreeNode treeNode = null ;
public void Convert(TreeNode pRootOfTree) {

       if (pRootOfTree == null){
            return null ;
        }else {
            Convert(pRootOfTree.left);
            pRootOfTree.left = treeNode ; //左节点指向小节点
            if (treeNode!=null){
                treeNode.right = pRootOfTree ;//右节点指向大节点
            }
            treeNode = pRootOfTree ; // 记录上一个遍历到的节点
            Convert(pRootOfTree.right);

        }
    }
*/

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
    TreeNode* root = new TreeNode(5);
    TreeNode* two = root->left = new TreeNode(2);
    TreeNode* seven = root->right = new TreeNode(7);
    two->left = new TreeNode(1);
    two->right = new TreeNode(3);
    seven->left = new TreeNode(6);
    seven->right = new TreeNode(8);
    return root;
}

TreeNode* contructBT2() {
    TreeNode* root = new TreeNode(8);
    root->left = new TreeNode(5);
    root->right = new TreeNode(9);
    return root;
}

TreeNode* contructBT3() {
    TreeNode* root = new TreeNode(2);
    root->right = new TreeNode(4);
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

    Solution_by_iteration sl;
    TreeNode* linkedlist = nullptr;
    std::cout<<"bt1 : "<<"\n";
    travIn(bt1, visit);
    std::cout<<"\n";
    linkedlist = sl.Convert(bt1);
    std::cout<<"bt1 Convert : \n";
    while(linkedlist) {std::cout<<"["<<linkedlist->val<<"] "; linkedlist = linkedlist->right;}
    std::cout<<"\n";
    linkedlist = sl.Convert(bt2);
    std::cout<<"bt2 Convert : \n";
    while(linkedlist) {std::cout<<"["<<linkedlist->val<<"] "; linkedlist = linkedlist->right;}
    std::cout<<"\n";
    linkedlist = sl.Convert(bt3);
    std::cout<<"bt3 Convert : \n";
    while(linkedlist) {std::cout<<"["<<linkedlist->val<<"] "; linkedlist = linkedlist->right;}
    std::cout<<"\n";
 
    deleteBT(bt1);
    deleteBT(bt2);
    deleteBT(bt3);
    return 0;
}
