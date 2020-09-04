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
 
/*
链接：https://www.nowcoder.com/questionTerminal/8a19cbe657394eeaac2f6ea9b0f6fcf6?answerType=1&f=discussion
来源：牛客网

根据中序遍历和前序遍历可以确定二叉树，具体过程为：

根据前序序列第一个结点确定根结点
根据根结点在中序序列中的位置分割出左右两个子序列
对左子树和右子树分别递归使用同样的方法继续分解
例如：
前序序列{1,2,4,7,3,5,6,8} = pre
中序序列{4,7,2,1,5,3,8,6} = in

根据当前前序序列的第一个结点确定根结点，为 1
找到 1 在中序遍历序列中的位置，为 in[3]
切割左右子树，则 in[3] 前面的为左子树， in[3] 后面的为右子树
则切割后的左子树前序序列为：{2,4,7}，切割后的左子树中序序列为：{4,7,2}；切割后的右子树前序序列为：{3,5,6,8}，切割后的右子树中序序列为：{5,3,8,6}
对子树分别使用同样的方法分解
*/

 //This solutions new a lot of vector in stack.
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
        // You really should draw a graph to clearly determine the left and right position.
        if(!leftnull) leftvin.assign(vin.begin(), it);
        if(!rightnull) rightvin.assign (it+1, vin.end());
        if(!leftnull) leftpre.assign(pre.begin()+1, pre.begin()+1+leftvin.size());
        if(!rightnull) rightpre.assign(pre.begin()+1+leftvin.size(), pre.end());
        if(!leftnull) root->left = reConstructBinaryTree(leftpre, leftvin);
        if(!rightnull)  root->right = reConstructBinaryTree(rightpre, rightvin);
        return root;
    }
};

// This solution uses mid to set the section position. Save a lot of time compared with v1.
class Solution_by_own_recursion_v2 {
public:
    TreeNode* reConstructBinaryTree(std::vector<int> pre, std::vector<int> vin) {
        if(pre.size() == 0 || vin.size() == 0) return nullptr;
        TreeNode *root = new TreeNode(pre.front());
        if(pre.size() == 1) return root;
        bool leftnull = false;
        bool rightnull = false;
        std::vector<int>::iterator mid = std::find(vin.begin(), vin.end(), pre.front());
        std::vector<int> leftvin, rightvin, leftpre, rightpre;
        // You really should draw a graph to clearly determine the left and right position.
        int leftsize = mid - vin.begin();
        leftpre.assign(pre.begin()+1, pre.begin()+leftsize+1);
        rightpre.assign(pre.begin()+leftsize+1, pre.end());
        leftvin.assign(vin.begin(), mid);
        rightvin.assign(mid+1, vin.end());
        root->left = reConstructBinaryTree(leftpre, leftvin);
        root->right = reConstructBinaryTree(rightpre, rightvin);
        return root;
    }
};

class Solution_by_section_recursion {
public:
    TreeNode *reBuildBinaryTree(std::vector<int> pre, std::vector<int> vin,
                               int preleft, int preright, int vinleft, int vinright) {
        if(preleft > preright) return nullptr;
        TreeNode *root = new TreeNode(pre[preleft]);
        if(preleft == preright) return root;
        //find pos as mid
        int mid = - 1;
        for(int i = vinleft; i <= vinright; i++) {
            if(vin[i] == pre[preleft]) {
                mid = i;
                break;
            }
        }
        int rootleftsize = mid - vinleft;
        int rootrightsize = vinright - mid;
        //for root left,  pre: [preleft+1 --> prelfet+rootleftsize], vin: [vinleft-->vinleft+rootleftsize-1]
        //for root right, pre: [preleft+rootleftsize+1, preright], vin: [vinleft+rootleftsize+1, vinright]
        root->left = reBuildBinaryTree(pre, vin, preleft+1, preleft+rootleftsize,
                                      vinleft, vinleft+rootleftsize-1);
        root->right = reBuildBinaryTree(pre, vin, preleft+rootleftsize+1, preright,
                                       vinleft+rootleftsize+1, vinright);
        return root;
    }
    TreeNode* reConstructBinaryTree(std::vector<int> pre, std::vector<int> vin) {
        return reBuildBinaryTree(pre, vin, 0, pre.size()-1, 0, pre.size()-1);
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
    std::cout<<"Solution_by_own_recursion. reConstructBinaryTree: "<<"\n";
    travIn(tr, visit);
    std::cout<<"\n";
    pre = {1, 2, 3, 4, 5, 6, 7};
    vin = {3, 2, 4, 1, 6, 5, 7};
    tr = sr.reConstructBinaryTree(pre, vin);
    std::cout<<"Solution_by_own_recursion. reConstructBinaryTree: "<<"\n";
    travIn(tr, visit);
    std::cout<<"\n";

    tr = nullptr;

    Solution_by_own_recursion_v2 sr2;
     pre = {1, 2, 4, 3, 5, 6};
    vin = {4, 2, 1, 5, 3, 6};
    tr = sr2.reConstructBinaryTree(pre, vin);
    std::cout<<"Solution_by_own_recursion_v2. reConstructBinaryTree: "<<"\n";
    travIn(tr, visit);
    std::cout<<"\n";
    pre = {1, 2, 3, 4, 5, 6, 7};
    vin = {3, 2, 4, 1, 6, 5, 7};
    tr = sr.reConstructBinaryTree(pre, vin);
    std::cout<<"Solution_by_own_recursion_v2. reConstructBinaryTree: "<<"\n";
    travIn(tr, visit);
    std::cout<<"\n";

    tr = nullptr;

    Solution_by_section_recursion ss;
    pre = {1, 2, 4, 3, 5, 6};
    vin = {4, 2, 1, 5, 3, 6};
    std::cout<<"Solution_by_section_recursion. reConstructBinaryTree: "<<"\n";
    tr = ss.reConstructBinaryTree(pre, vin);
    travIn(tr, visit);
    std::cout<<"\n";
    pre = {1, 2, 3, 4, 5, 6, 7};
    vin = {3, 2, 4, 1, 6, 5, 7};
    std::cout<<"Solution_by_section_recursion. reConstructBinaryTree: "<<"\n";
    tr = ss.reConstructBinaryTree(pre, vin);
    travIn(tr, visit);
    std::cout<<"\n";

    std::vector<int> vt;
    vt.push_back(3);
    std::vector<int> vt2;
    vt2.assign(vt.begin(), vt.begin());
    return 0;
}
