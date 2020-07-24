#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

/*
* Enter a binary tree and find the depth of the tree. The nodes (including roots and leaf nodes)
* passing through from the root node to the leaf node in turn form a path of the tree, and
* the length of the longest path is the depth of the tree.
* 输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。
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
 
class Solution_by_recursion {
public:
    int TreeDepth(TreeNode* pRoot, int height) {
        if(!pRoot) return height;
        if(pRoot) ++height;
        return TreeDepth(pRoot->left, height) >= TreeDepth(pRoot->right, height) ?
            TreeDepth(pRoot->left, height) : TreeDepth(pRoot->right, height);
    }
    int TreeDepth(TreeNode* pRoot)
    {
        if(!pRoot) return 0;
        int height = 0;
        return TreeDepth(pRoot, height);
    }
};

/*
* 分治法
* 链接：https://www.nowcoder.com/questionTerminal/435fb86331474282a3499955f0a41e8b?answerType=1&f=discussion
* 来源：牛客网

* 函数是求二叉树的最大深度，我们不必管函数具体是怎么实现的。
* 所以最终结果为 max( 头结点左子树的最大深度, 头结点右子树的最大深度)+1

* 求TreeDepth(TreeNode* pRoot)->int
* 先求 TreeDepth(pRoot->left) ->lval
* 再求TreeDepth(pRoot->right) ->rval
* return max(lval, rval) + 1
*/
class Solution_by_recursion_v2 {
public:
    int TreeDepth(TreeNode* pRoot)
    {
        if (!pRoot) return 0;
        int lval = TreeDepth(pRoot->left);
        int rval = TreeDepth(pRoot->right);
        return std::max(lval, rval) + 1;
    }
};

class Solution_by_aux_queue {
public:
    int TreeDepth(TreeNode* pRoot)
    {
        if(!pRoot) return 0;
        int height = 1;
        int max = 0;
        std::queue<TreeNode*> qt;
        std::queue<int> qh;
        qt.push(pRoot);
        qh.push(height);
        while(!qt.empty()) {
            pRoot = qt.front();
            height = qh.front();
            if(height > max) max = height;
            if(pRoot->left) {
                qt.push(pRoot->left);
                qh.push(height+1);
            }
            if(pRoot->right) {
                qt.push(pRoot->right);
                qh.push(height+1);
            }
            qt.pop();
            qh.pop();
        }
        return max;
    }
};

class Solution_by_iteration {
public:
    int TreeDepth(TreeNode* pRoot)
    {
        if (!pRoot) return 0;
        //when push child tree, remember the size of father node
        //each time, pop all father node, push all child nodes.
        std::queue<TreeNode*> qt;
        int size = 1;
        int height = 1;
        qt.push(pRoot);
        while(!qt.empty()) {
            size = qt.size();
            //pop and push
            while(size--) {
                pRoot = qt.front();
                qt.pop();
                if(pRoot->left) qt.push(pRoot->left);
                if(pRoot->right) qt.push(pRoot->right);
            }
            //if empty, break
            if(qt.empty()) break;
            //height++
            height++;
        }
        return height;
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
    int height = 0;
    Solution_by_recursion sl;
    //Solution_by_aux_queue sl;
    //Solution_by_iteration sl;
    std::vector<int> vt;
    std::cout<<"bt1 : "<<"\n";
    travIn(bt1, visit);
    std::cout<<"\n";
    height = sl.TreeDepth(bt1);
    std::cout<<"bt1 height : "<<height<<"\n";
 
    std::cout<<"bt2 : "<<"\n";
    travIn(bt2, visit);
    std::cout<<"\n";
    height = sl.TreeDepth(bt2);
    std::cout<<"bt2 height : "<<height<<"\n";

    std::cout<<"bt3 : "<<"\n";
    travIn(bt3, visit);
    std::cout<<"\n";
    height = sl.TreeDepth(bt3);
    std::cout<<"bt3 height : "<<height<<"\n";
 
    deleteBT(bt1);
    deleteBT(bt2);
    deleteBT(bt3);
    return 0;
}
