//
// Created by Inarchus on 2/26/2021.
//

#ifndef BIGO_BST_H
#define BIGO_BST_H

struct tree_node
{
    tree_node(int new_data)
    // p_right, p_left = nullptr you're going to end up with some trouble.
        : p_left(nullptr), p_right(nullptr), p_parent(nullptr), data(new_data)
    {}

    ~tree_node()
    {
        delete p_left;
        delete p_right;
    }

    tree_node * p_left, *p_right;
    tree_node * p_parent;
    int data; // really this can be anything as long as it's "comparable" <, == operator
    // a < b and b < c then a < c otherwise you end up with real issues.  '
    // partial order on the set of data elements / full order on it really.
    // like a linked list node, except instead of having one pointer m_next
    // p_left, p_right <-- make the tree because now you have two directions to go in.
};

class BST {
    public:
        BST();
        BST(const BST & other_bst);
        BST & operator = (const BST & other_bst);
        ~BST();

        void insert(int data);
        bool find(int data);
        //
        void display(bool verbose_leaves=false);
        // later today or next week
        void remove(int data);
    private:
        

        tree_node * find_node(int data);
        tree_node * get_successor(tree_node * p_current);
        tree_node * find_node_rec(int data, tree_node * p_current);
        void remove_node(tree_node * delete_node);
        tree_node * copy_subtree(tree_node * p_current);
        void display_subtree(tree_node * p_current, bool verbose_leaves=false, int depth = 0);
        // a linked list has a "head" <-- old fashioned magnetic tape readers/ also its the top
        tree_node * m_root;
};


#endif //BIGO_BST_H
