#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

 //Definition for binary tree
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 
 //TODO. This solutions new a lot of vector in stack.
 //You can use recursion function with left and right para to avoid new vector.
class Solution_by_own_recursion {
public:
    TreeNode* reConstructBinaryTree(std::vector<int> pre, std::vector<int> vin) {
        if(pre.size() == 0 || vin.size() == 0) return nullptr;
        TreeNode *root = new TreeNode(pre.front());
        if(pre.size() == 1) return root;
        bool leftnull = false;
        bool rightnull = false;
        std::vector<int>::iterator it = std::find(vin.begin(), vin.end(), pre.front());
        if(it == vin.end()) return root; //impossible
        if(it == vin.begin()) leftnull = true;
        if(it == vin.end() - 1) rightnull = true; 
        std::vector<int> leftvin, rightvin, leftpre, rightpre;
        if(!leftnull) leftvin.assign(vin.begin(), it);
        if(!rightnull) rightvin.assign (it+1, vin.end());
        if(!leftnull) leftpre.assign(pre.begin()+1, pre.begin()+1+leftvin.size());
        if(!rightnull) rightpre.assign(pre.begin()+1+leftvin.size(), pre.end());
        if(!leftnull) root->left = reConstructBinaryTree(leftpre, leftvin);
        if(!rightnull)  root->right = reConstructBinaryTree(rightpre, rightvin);
        return root;
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
    std::vector<int> pre = {1, 2, 4, 3, 5, 6};
    std::vector<int> vin = {4, 2, 1, 5, 3, 6};
    Solution_by_own_recursion sr;
    TreeNode* tr = sr.reConstructBinaryTree(pre, vin);
    travIn(tr, visit);
    std::cout<<"\n";
    pre = {1, 2, 3, 4, 5, 6, 7};
    vin = {3, 2, 4, 1, 6, 5, 7};
    tr = sr.reConstructBinaryTree(pre, vin);
    travIn(tr, visit);
    std::cout<<"\n";
    return 0;
}
