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
* Given a binary search tree, please find the k-th smallest node in it. For example, in (5,3,7,2,4,6,8), 
* the value of the third small node is 4 in order of node value.

* 给定一棵二叉搜索树，请找出其中的第k小的结点。例如，（5，3，7，2，4，6，8）中，按结点数值大小顺序第三小结点的值为4。
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
* 链接：https://www.nowcoder.com/questionTerminal/ef068f602dde4d28aab2b210e859150a?answerType=1&f=discussion
* 来源：牛客网
* 采用递归的方式，不断递归深入根节点的左孩子，直到碰到空节点为止，然后回溯输出当前节点。
* 再以同样的方式递归遍历其右孩子。在此期间，每访问一个节点，我们都对k进行减一操作，直到k为0，说明该节点即为第k个节点。
* 
* 这个递归要注意的点是，如何获取目标节点。当递归结束时，可能K仍未递减为0，或者是负数。
* 这个第K个结点的位置，根据K的取值不同，会存在不同情况，在树中，不在树中。
*/
class Solution_by_recursion {
public:
    TreeNode* targetnode;
    int m;
    TreeNode* _kthnode(TreeNode* root) {
        //if m has been <=0, we needn't to visit other node any more.
        if(root == nullptr || m <= 0) return nullptr;
        _kthnode(root->left);
        //visit node
        m--;
        if(m == 0) targetnode = root;
        _kthnode(root->right);
        return nullptr;
    }
    TreeNode* KthNode(TreeNode* pRoot, int k)
    {
        if(k <= 0 || pRoot == nullptr) return nullptr;
        m = k;
        _kthnode(pRoot);
        //maybe after visiting all nodes, m still >　0.
        //That means k greater than the size of binary tree.
        if(m > 0) return nullptr;
        return targetnode;
    }
};

class Solution_by_iteration {
public:
    TreeNode* KthNode(TreeNode* pRoot, int k)
    {
        if(k <= 0) return nullptr;
        std::stack<TreeNode*> st;
        //go along left tree until bottom
        //pop and vist
        //turn to right tree
        //that is InOrder traverse
        //remember to break out.
        while(true) {
            while(pRoot) {
                st.push(pRoot);
                pRoot = pRoot->left;
            }
            if(st.empty()) break;
            pRoot = st.top();
            if(--k == 0) break;
            st.pop();
            pRoot = pRoot->right;
        }
        if(k == 0) return pRoot;
        else return nullptr;
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

    //Solution_by_iteration sl;
    Solution_by_recursion sl;
    TreeNode* targetnode = nullptr;
    std::cout<<"bt1 : "<<"\n";
    travIn(bt1, visit);
    std::cout<<"\n";
    targetnode = sl.KthNode(bt1, 0);
    std::cout<<"bt1 KthNode of 0: "<<targetnode<<"\n";
    targetnode = sl.KthNode(bt1, 3);
    std::cout<<"bt1 KthNode of 3:"<<targetnode<<"\n";
    targetnode = sl.KthNode(bt1, 12);
    std::cout<<"bt1 KthNode of 12: "<<targetnode<<"\n";

    deleteBT(bt1);
    deleteBT(bt2);
    deleteBT(bt3);
    return 0;
}
