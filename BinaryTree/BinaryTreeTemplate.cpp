#include <iostream>
#include <string>
#include <vector>
#include <stack>

template <typename T> struct BinNode {
    T data;
    BinNode<T>* parent;
    BinNode<T>* left;
    BinNode<T>* right;
    int height;
    BinNode() : parent(nullptr), left(nullptr), right(nullptr), height(0) {}
    BinNode(T e, BinNode<T>* p = nullptr, BinNode<T>* left = nullptr, BinNode<T>* right = nullptr, int height = 0)
    : data(e), parent(p), left(left), right(right),height(height){}
    //ops
    //int size();
    BinNode<T>* insertAsLeft(T const&);
    BinNode<T>* insertAsRight(T const&);
    //BinNode<T>* succ();
    template <typename VST> void travPre(VST&);
    template <typename VST> void travIn(VST&);
    template <typename VST> void travPost(VST&);
};

template <typename T> BinNode<T>* BinNode<T>::insertAsLeft(T const &e) {
    return left = new BinNode<T>(e, this);
}

template <typename T> BinNode<T>* BinNode<T>::insertAsRight(T const &e) {
    return right = new BinNode<T>(e, this);
}

template <typename T> void visit(BinNode<T>* x) {
    std::cout<<" ["<<x->data<<"] ";
}

//lambda expression. auto visit = [](BinNode<T>* x){std::cout<<" ["<<x->data<<"] ";}

//function object
template <typename T> struct Visit {
    virtual void operator()(BinNode<T>* x) const {/*std::cout<<" ["<<x->data<<"] ";*/}
};

template <typename T>  template<typename VST>
void BinNode<T>::travPre(VST& visit) {
    BinNode<T>* root = this;
    //preorder
    //visit order: root --> left --> right
    //push stack order: visit root , stack right --> left
    std::stack<BinNode<T>*> st;
    st.push(root);
    while(true) {
        if(st.empty()) break;
        root = st.top();
        visit(root);
        st.pop();

        if(root->right)
            st.push(root->right);
        if(root->left)
            st.push(root->left);
    }
}

template <typename T>  template<typename VST>
void BinNode<T>::travPost(VST& visit) {
    BinNode<T>* root = this;
    //preorder
    //visit order: root --> left --> right
    //push stack order: visit root , stack right --> left
    std::stack<BinNode<T>*> st;
    std::stack<BinNode<T>*> st_visit;
    st.push(root);
    while(true) {
        if(st.empty()) break;
        root = st.top();
        st_visit.push(root);
        st.pop();

        if(root->left)
            st.push(root->left);
        if(root->right)
            st.push(root->right);
    }
    while(!st_visit.empty()) {
        visit(st_visit.top());
        st_visit.pop();
    }
}

template <typename T>  template<typename VST>
void BinNode<T>::travIn(VST& visit) {
    // WAVE
    //to left bottom
    //to top
    //to right WAVE again
    BinNode<T>* root = this;
    std::stack<BinNode<T>*> st;
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
template <typename T> class BinTree{
protected:
    int _size;
    BinNode<T>* _root;
public:
    BinTree():_size(0), _root(nullptr) {}
    ~BinTree(){}
    int size() {return _size;}
    bool empty(){return !_root;}
    BinNode<T>* root() const {return _root;}
    BinNode<T>* insertAsRoot(T const& e);
    BinNode<T>* insertAsLeft(BinNode<T>* x, T const& e);
    BinNode<T>* insertAsRight(BinNode<T>* x, T const& e);
    BinNode<T>* attachAsLeft(BinNode<T>* x, BinTree<T>* lc);
    BinNode<T>* attachAsRight(BinNode<T>* x, BinTree<T>* rc);
    template <typename VST> void travPre(VST& visit) {if(_root) _root->travPre(visit);}
    template <typename VST> void travIn(VST& visit) {if(_root) _root->travIn(visit);}
    template <typename VST> void travPost(VST& visit) {if(_root) _root->travPost(visit);}
};

template <typename T>
BinNode<T>* BinTree<T>::insertAsRoot(T const& e) {
    _size = 1;
    _root = new BinNode<T>(e);
    return _root;
}

template <typename T>
BinNode<T>* BinTree<T>::insertAsLeft(BinNode<T>* x, T const& e) {
    _size++;
    x->left = new BinNode<T>(e);
    x->left->parent = x;
    return x->left;
}

template <typename T>
BinNode<T>* BinTree<T>::insertAsRight(BinNode<T>* x, T const& e) {
    _size++;
    x->right = new BinNode<T>(e);
    x->right->parent = x;
    return x->right;
}

template <typename T>
BinNode<T>* BinTree<T>::attachAsLeft(BinNode<T>* x, BinTree<T>* lc) {
    _size += lc.size();
    x->left = lc.root();
    x->left->parent = x;
    //lc = nullptr;
    return x;
}

template <typename T>
BinNode<T>* BinTree<T>::attachAsRight(BinNode<T>* x, BinTree<T>* rc) {
    _size += rc.size();
    x->left = rc.root();
    x->left->parent = x;
    //rc->_root = nullptr;
    //rc->_size = 0;
    //rc = nullptr;
    return x;
}


int main() {
    BinTree<std::string> bt;
    /*
    BinNode<std::string>* Huawei = nullptr;
    std::string str = "i";
    Huawei = bt.insertAsRoot(str);
    BinNode<std::string>* xm = bt.insertAsLeft(Huawei, "XiaoMi");
    BinNode<std::string>* op = bt.insertAsRight(Huawei, "Oppo");
    BinNode<std::string>* yj = bt.insertAsLeft(xm, "YiJia");
    BinNode<std::string>* vv = bt.insertAsRight(op, "Vivo");
    BinTree<std::string> bt_foreign;
    std::string applestr = "Apple";
    BinNode<std::string>* apple = bt_foreign.insertAsRoot(applestr);
    bt_foreign.insertAsLeft(apple, "Google");
    bt_foreign.insertAsRight(apple, "Nokia");
    bt.attachAsRight(vv, bt_foreign);
    */
    std::string str = "i";
    BinNode<std::string>* root = bt.insertAsRoot(str);
    BinNode<std::string>* d = bt.insertAsLeft(root, "d");
    BinNode<std::string>* l = bt.insertAsRight(root, "l");

    BinNode<std::string>* c = bt.insertAsLeft(d, "c");
    BinNode<std::string>* h = bt.insertAsRight(d, "h");

    BinNode<std::string>* a = bt.insertAsLeft(c, "a");
    BinNode<std::string>* b = bt.insertAsRight(a, "b");

    BinNode<std::string>* f = bt.insertAsLeft(h, "f");
    BinNode<std::string>* e = bt.insertAsLeft(f, "e");
    BinNode<std::string>* g = bt.insertAsRight(f, "g");

    BinNode<std::string>* k = bt.insertAsLeft(l, "k");
    BinNode<std::string>* n = bt.insertAsRight(l, "n");

    BinNode<std::string>* j = bt.insertAsLeft(k, "j");

    BinNode<std::string>* m = bt.insertAsLeft(n, "m");
    BinNode<std::string>* p = bt.insertAsRight(n, "p");
    BinNode<std::string>* o = bt.insertAsLeft(p, "o");

    //auto visit = [](BinNode<T>* x){std::cout<<" ["<<x->data<<"] ";}
    //bt.travPre(Visit<std::string>());
    bt.travPre(visit<std::string>);
    std::cout<<"\n";
    bt.travPost(visit<std::string>);
    std::cout<<"\n";
    bt.travIn(visit<std::string>);
    return 0;
}
