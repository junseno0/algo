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

class Solution {
public:
    std::vector<TreeNode*> InOrder(TreeNode* root, TreeNode* p, TreeNode* q) {
        std::stack<TreeNode*> st;
        std::vector<TreeNode*> vt;
        bool stored = false;
        bool end = false;
        while(true) {
            while(root) {
                //go along left and push
                st.push(root);
                root = root->left;
            }
        //check and break
        if(st.empty()) break;
        root = st.top();
        //visit and pop top
        if(stored == true && (root == p || root == q)) {
            stored = false;
            end = true;
            vt.push_back(root);
        }
        if(end == false && stored == false && (root == p || root == q)) {
            stored = true;
        }
        if(stored == true) {
            vt.push_back(root);
        }
        st.pop();
        //turn to right
        root = root->right;
        }
        return vt;
    }
    std::vector<TreeNode*> LayerOrder(TreeNode* root) {
        std::queue<TreeNode*> qt;
        std::vector<TreeNode*> vt;
        qt.push(root);
        int size = 1;
        while(!qt.empty()) {
            //get size
            size = qt.size();
            //until size == 0
            //pop front
            //push left and right
            while(size--) {
                root = qt.front();
                qt.pop();
                vt.push_back(root);
                if(root->left) qt.push(root->left);
                if(root->right) qt.push(root->right);
            }
            
        }
        return vt;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //CHECK
        if(!root) return nullptr;
        std::vector<TreeNode*> vt;
        std::vector<TreeNode*> layervt;
        //InOrder traverse and store nodes
        vt = InOrder(root, p, q);

        //Layer Order and store all nodes
        layervt = LayerOrder(root);

        //compare node with all nodes in vector
        //if found, return
        for(int i = 0; i < layervt.size(); i++) {
            for(int j = 0; j < vt.size(); j++) {
                if(layervt[i] == vt[j]) return layervt[i];
            }
        }

        //return
        return nullptr;
    }
};

/*
(递归) O(n)O(n)

当我们用递归去做这个题时不要被题目误导，应该要明确一点
这个函数的功能有三个：给定两个节点 pp 和 qq

如果 pp 和 qq 都存在，则返回它们的公共祖先；
如果只存在一个，则返回存在的一个；
如果 pp 和 qq 都不存在，则返回NULL
本题说给定的两个节点都存在，那自然还是能用上面的函数来解决

具体思路：
（1） 如果当前结点 rootroot 等于 NULL，则直接返回 NULL
（2） 如果 rootroot 等于 pp 或者 qq ，那这棵树一定返回 pp 或者 qq
（3） 然后递归左右子树，因为是递归，使用函数后可认为左右子树已经算出结果，用 leftleft 和 rightright 表示
（4） 此时若leftleft为空，那最终结果只要看 rightright；若 rightright 为空，那最终结果只要看 leftleft
（5） 如果 leftleft 和 rightright 都非空，因为只给了 pp 和 qq 两个结点，都非空，说明一边一个，因此 rootroot 是他们的最近公共祖先
（6） 如果 leftleft 和 rightright 都为空，则返回空（其实已经包含在前面的情况中了）

时间复杂度是 O(n)O(n)：每个结点最多遍历一次或用主定理，空间复杂度是 O(n)O(n)：需要系统栈空间

作者：Wilson79
链接：https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/solution/c-jing-dian-di-gui-si-lu-fei-chang-hao-li-jie-shi-/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
/*
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == NULL)
            return NULL;
        if(root == p || root == q) 
            return root;
            
        TreeNode* left =  lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
       
        if(left == NULL)
            return right;//为什么返回右节点而不是父节点或者是标记值，这个可以想一想
        if(right == NULL)
            return left;      
        if(left && right) // p和q在两侧
            return root;
        
        return NULL; // 必须有返回值
    }
};
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
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
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
    Solution sl;
    TreeNode* targetnode = nullptr;
    std::cout<<"bt1 : "<<"\n";
    travIn(bt1, visit);
    std::cout<<"\n";
    targetnode = sl.lowestCommonAncestor(bt1, bt1->right->left, bt1->right->right);

    deleteBT(bt1);
    deleteBT(bt2);
    deleteBT(bt3);
    return 0;
}
