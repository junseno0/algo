#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

/*
* Please implement a function to print the binary tree in a zigzag pattern, that is,
* the first line is printed from left to right, the second layer is printed from right to left,
* the third line is printed from left to right, and the other lines are printed from left to right. And so on.
* 请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。
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
* 此题跟“按层打印二叉树”，仅有一点区别，“按层打印二叉树”是每层都按照从左到右打印二叉树。
* 而此题是，按照奇数层，从左到右打印，偶数层，从右到左打印。
* 区分奇数层与偶数层，每一层都用vector存放，偶数层打印时先翻转即可。
* 另外，还可以用辅助栈，用双端队列。
*/
//Time complexity: O(N^2)
//Space complexity: O(1)
class Solution {
public:
    std::vector<std::vector<int> > Print(TreeNode* pRoot) {
        //CHECK
        std::vector<std::vector<int>> vtt;
        if(!pRoot) return vtt;
        std::vector<int> vt;
        //InOrder
        //use queue and size and store data each level
        std::queue<TreeNode*> qt;
        qt.push(pRoot);
        int size = 1;
        while(!qt.empty()) {
            size = qt.size();
            vt.clear();
            while(size--) {
                //pop and push
                //save data of one level
                pRoot = qt.front();
                qt.pop();
                vt.push_back(pRoot->val);
                if(pRoot->left) qt.push(pRoot->left);
                if(pRoot->right) qt.push(pRoot->right);
            }
            if(vtt.size() & 1) std::reverse(vt.begin(), vt.end());
            vtt.push_back(vt);
        }
        return vtt;
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
    std::vector<std::vector<int>> vtt;
    std::cout<<"bt1 : "<<"\n";
    travIn(bt1, visit);
    std::cout<<"\n";
    vtt = sl.Print(bt1);
    for(auto itt : vtt) {
        for (auto it : itt) {
            std::cout<<" "<<it<<" ";
        }
        std::cout<<"\n";
    }
 
    deleteBT(bt1);
    deleteBT(bt2);
    deleteBT(bt3);
    return 0;
}
