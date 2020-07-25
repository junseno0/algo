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
* Please implement two functions to serialize and deserialize the binary tree respectively

* The serialization of a binary tree refers to saving a binary tree as a string in a certain format
* according to the result of a certain traversal method, so that the binary tree established in the memory
* can be persisted. Serialization can be modified based on the binary tree traversal method of pre-order,
* middle-order, post-order, and layer order. The result of serialization is a string. When serializing,
* an empty node (#) is represented by a certain symbol. Indicates the end of a node value (value!).
* The deserialization of the binary tree refers to reconstructing the binary tree according to the serialized
* string result str obtained in a certain traversal sequence.

* 请实现两个函数，分别用来序列化和反序列化二叉树
* 二叉树的序列化是指：把一棵二叉树按照某种遍历方式的结果以某种格式保存为字符串，
* 从而使得内存中建立起来的二叉树可以持久保存。序列化可以基于先序、中序、后序、层序的二叉树遍历方式来进行修改，
* 序列化的结果是一个字符串，序列化时通过 某种符号表示空节点（#），以 ！ 表示一个结点值的结束（value!）。
* 二叉树的反序列化是指：根据某种遍历顺序得到的序列化字符串结果str，重构二叉树。
* 例如，我们可以把一个只有根节点为1的二叉树序列化为"1,"，然后通过自己的函数来解析回这个二叉树
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

//这题目刚开始想错了，妄想着把空节点的空左右节点也记录下来，其实没必要。 
//我们把每一层的节点与其对应的左右子节点保存起来，总是先上层节点再下层节点且1:2的关系
//在反序列化中，每取出一个节点，总会把其左右子节点推送到队列中，也形成
//先上层节点再下层节点且1:2的关系，与字符串一一对应
//另外搞不定的是，字符串的操作不熟悉，导致复杂的想法，如果熟悉STL string，且string与char
//的转换，加上atoi的trick，就容易操作字符串
class Solution {
public:
    char* Serialize(TreeNode *root) {    
        std::string ret = "";
        char *chr;
        if(!root) return chr;
        std::queue<TreeNode*> qt;
        qt.push(root);
        while(!qt.empty()) {
            root = qt.front();
            qt.pop();
            if(root) {
                ret += std::to_string(root->val);
                ret += ",";
            } else {
                ret += "#,";
                continue;
            }
            qt.push(root->left);
            qt.push(root->right);
        }
        chr = new char[ret.length() + 1];
        strcpy(chr, ret.c_str());
        return chr;
    }
    TreeNode* Deserialize(char *str) {
        if(!str) return nullptr;
        std::string s(str);
        if(s.size() == 0) return nullptr;
        TreeNode* root = new TreeNode(atoi(s.c_str()));
        s = s.substr(s.find_first_of(',') + 1);
        std::queue<TreeNode*> qt;
        qt.push(root);
        int size = 1;
        while(!s.empty() && !qt.empty()) {
            size = qt.size();
            while(size--) {
                TreeNode* node = qt.front();
                qt.pop();
                if(s[0] != '#') {
                    node->left = new TreeNode(atoi(s.c_str()));
                    qt.push(node->left);
                } else {
                    node->left = nullptr;
                }
                s = s.substr(s.find_first_of(',') + 1);
                if(s[0] != '#') {
                    node->right = new TreeNode(atoi(s.c_str()));
                    qt.push(node->right);
                } else {
                    node->right = nullptr;
                }
                s = s.substr(s.find_first_of(',') + 1);
            }
        }
        return root;
    }
};

/*
//链接：https://www.nowcoder.com/questionTerminal/cf7e25aa97c04cc1a68c8f040e71fb84?answerType=1&f=discussion
//来源：牛客网
//这代码采用递归的方式，清晰简单，而且，在字符串的操作也十分简单，值得学习
class Solution {
public:
    string s;
    int j=0;
    void Srtial(TreeNode *root)
    {
        if(root==NULL)
        {
            s+="#!";
            return ;
        }
        s+=to_string(root->val);
        s+="!";
        Srtial(root->left);
        Srtial(root->right);
    }
    char* Serialize(TreeNode *root) {    
        Srtial(root);
        return (char *)s.data();
    }
    TreeNode* Deserialize(char *str) {
        s=str;
        return Deserial();
    }
    TreeNode* Deserial()
    {
        if(s.size()==0)
            return NULL;
        if(s[j]=='!') {
            j++;
            if(j>=s.size())
                return NULL;    
        }
        if(s[j]=='#'){
            j++;
            return NULL;
        }
        int num=0;
        while(s[j]>='0' && s[j]<='9'){
        num=num*10+s[j++]-'0';}
        TreeNode *root=new TreeNode(num);
        root->left=Deserial();
        root->right=Deserial();
        return root;
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
    char* chr;
    TreeNode* ret;
    std::cout<<"bt1 : "<<"\n";
    travIn(bt1, visit);
    std::cout<<"\n";
    chr = sl.Serialize(bt1);
    ret = sl.Deserialize(chr);
    std::cout<<"deserialized bt1 : "<<"\n";
    travIn(ret, visit);
    std::cout<<"\n";
 
    deleteBT(bt1);
    deleteBT(bt2);
    deleteBT(bt3);
    return 0;
}
