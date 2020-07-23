#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

/*
* Enter two binary trees A and B to determine whether B is a substructure of A.
(Ps: We agree that the empty tree is not a substructure of any tree)
* 输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）
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
链接：https://www.nowcoder.com/questionTerminal/6e196c44c7004d15b1610b9afca8bd88?answerType=1&f=discussion
来源：牛客网

1.首先需要判断A,B的根节点是否一样。
2.如果不一样，判断A的左孩子和B的根节点是否一样，同理可判断A的右孩子和B的根节点是否一样。依次找下去
如果上述情况都不满足则说明不包含
1.如果找到了A中有值和B中的根节点相同，则比较左右子树是否相同。
2.如果B为空了，则说明包含
3.如果A为空了，则说明不包含

Refer to details below.
https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof/solution/mian-shi-ti-26-shu-de-zi-jie-gou-xian-xu-bian-li-p/
*/

class Solution {
public:
    bool dfs(TreeNode* pRoot1, TreeNode* pRoot2) {
        if(pRoot1 == nullptr && pRoot2 != nullptr) return false;
        if(pRoot2 == nullptr) return true;
        return (pRoot1->val == pRoot2->val) &&
            dfs(pRoot1->left, pRoot2->left) && dfs(pRoot1->right, pRoot2->right);
    }
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        //check
        if(!pRoot1 || !pRoot2) return false;
        //if pRoot2 same with pRoot1, then true
        //otherwise, check if pRoot2 same with pRoot1 left child tree and right child tree
        return dfs(pRoot1, pRoot2) || HasSubtree(pRoot1->left, pRoot2) ||
            HasSubtree(pRoot1->right, pRoot2);
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
    TreeNode* bt2 = contructBT2();
    TreeNode* bt3 = contructBT3();
    Solution sl;
    bool flag = sl.HasSubtree(bt1, bt2);
    if(flag) std::cout<<"bt1 has the subtree of bt2."<<"\n";//yes
    flag = sl.HasSubtree(bt1, bt3);
    if(flag) std::cout<<"bt1 has the subtree of bt3."<<"\n";//no
    deleteBT(bt1);
    deleteBT(bt2);
    deleteBT(bt3);
    return 0;
}
