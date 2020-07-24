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
 
class Solution_by_recursion {
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

class Solution_by_iteration_v1 {
public:
    bool isSymmetrical(TreeNode* pRoot)
    {
        if(!pRoot) return true;
        std::queue<TreeNode*> qt;
        qt.push(pRoot->left);
        qt.push(pRoot->right);
        TreeNode* first = nullptr;
        TreeNode* second = nullptr;
        if(!pRoot->left && !pRoot->right) return true;
        while(!qt.empty()) {
            //push sequence, if valid
            //left tree left, right tree right, same
            //left tree right, right tree left, same
            //break case
            //pop and compare
            //if two element not equal
            //check if two at least
            first = qt.front();
            qt.pop();
            second = qt.front();
            qt.pop();
            //check val equal
            if(first && second && first->val != second->val) return false;
            //if one of nullptr, false, we have ensure one not nullptr at least.
            //在这里，我们的判断不等条件与推送到队列的判断条件耦合了，显示繁琐
            //我们在判断都集中在一处，如果两个指针都为空，我们就进行下一轮的弹出与判断
            //如果其中一个为空，则明显不等，返回失败
            //同时，保证了在推送队列时，first, second都是非空的节点，就不需要再加判断条件了
            //同时，如果一开始的左右节点都为空，再一下轮就队列为空了，避免了循环前的一次判断
            //代码见Solution_by_iteration_v2
            if(!(first && second)) return false;
 
            if(first->left || second->right) {
                qt.push(first->left);
                qt.push(second->right);
            }
            if(first->right || second->left) {
                qt.push(first->right);
                qt.push(second->left);
            }
        }
        return true;
    }
};

class Solution_by_iteration_v2 {
public:
    bool isSymmetrical(TreeNode* pRoot)
    {
        if(!pRoot) return true;
        std::queue<TreeNode*> qt;
        qt.push(pRoot->left);
        qt.push(pRoot->right);
        TreeNode* first = nullptr;
        TreeNode* second = nullptr;
        while(!qt.empty()) {
            first = qt.front();
            qt.pop();
            second = qt.front();
            qt.pop();
            //check val equal
            if(!first && !second) continue;
            if((!first || !second) || (first->val != second->val)) return false;
            {
                qt.push(first->left);
                qt.push(second->right);
            }
            {
                qt.push(first->right);
                qt.push(second->left);
            }
        }
        return true;
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
    //Solution_by_recursion sl;
    //Solution_by_iteration_v1 sl;
    Solution_by_iteration_v2 sl;
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
