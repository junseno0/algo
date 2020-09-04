#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

 //Definition for binary tree
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {z}
};
 
/*
链接：https://www.nowcoder.com/questionTerminal/9023a0c988684a53960365b889ceaf5e?answerType=1&f=discussion
来源：牛客网

根据中序遍历的规则，当结点存在右子树的时候，中序遍历的下一个结点为右子树的最左节点。
但是当节点不存在右子树的时候，中序遍历的下一个结点必定为该节点的父辈节点。但是究竟是哪一辈呢？
根据中序遍历特性，左父结点一定已经被中序遍历访问过，所以下一个结点一定是在父节点路径上的第一个右父节点。
*/

class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        //check
        if(pNode == nullptr) return nullptr;
        TreeLinkNode* targetnode = nullptr;
        //if has right child
        if(pNode->right) {
            targetnode = pNode->right;
            while(targetnode->left) targetnode = targetnode->left;
        } else {
            targetnode = pNode;
            while(targetnode->next && targetnode->next->right == targetnode) targetnode = targetnode->next;
            targetnode = targetnode->next;
        }
        //if not have right child
        return targetnode;
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

int main() {
    //TODO
    return 0;
}
