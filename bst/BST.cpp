//
// Created by Inarchus on 2/26/2021.
//

#include "BST.h"
#include <iostream>
using namespace std;

/*
 * Comparable data <, ==, >, >=, <=, != need to work
 * If they don't work, then it's impossible to tell if two things are in various orders
 *
 */

BST::BST()
    : m_root(nullptr)
{

}

BST::BST(const BST & other_bst)
{
    // our m_root <-- other_bst.m-root but copied
    m_root = copy_subtree(other_bst.m_root);
}

tree_node * BST::copy_subtree(tree_node * p_current)
{
    /*
     * Has to be recursive because unlike find/insert/ we only go down one path
     * to make a copy you must go down all possible paths.
     * recursive or you make your own stack.
     */
    if(p_current)
    {
        tree_node * p_new = new tree_node(p_current->data);
        p_new->p_left = copy_subtree(p_current->p_left);
        p_new->p_right = copy_subtree(p_current->p_right);
        return p_new;
    }
    return nullptr;
}

BST & BST::operator = (const BST & other_bst)
{
    return *this;
}

BST::~BST()
{
    delete m_root;
}

bool BST::find(int data)
{
    // alternative way to code find up.
    //return find_node_rec(data, m_root) != nullptr;

    tree_node * p_current = m_root;
    while(p_current != nullptr)
    {
        // if data is less than the current node's data, we go down and to the left
        // if the data is greater than or equal to the current node's data then we go down
        // and to the right

        if(data < p_current->data)
        {
            p_current = p_current->p_left;
        }
        else if (data > p_current->data)
        {
            p_current = p_current->p_right;
        }
        else
        {
            // there's only one option left, trichotomy <-- less than greater than or EQUAL to...
            return true;
        }
    }
    return false;
}


tree_node * BST::find_node(int data)
{
    return find_node_rec(data, m_root);
}

tree_node * BST::find_node_rec(int data, tree_node * p_current)
{
    // p_current != nullptr
    if (!p_current)
    {
        // we've gone through the tree haven't found the thing
        return nullptr;
    }
    else
    {
        if (data == p_current->data)
        {
            return p_current;
        }
        else if (data < p_current->data)
        {
            return find_node_rec(data, p_current->p_left);
        }
        else
        {
            // not equal, not less than, means greater than.
            return find_node_rec(data, p_current->p_right);
        }
    }
}

tree_node * BST::get_successor(tree_node * p_current)
{
    if(p_current)
    {
        // go right once
        // auto is the lazy way of saying to C++ "you know what type it is"
        auto successor = p_current->p_right;
        // a bit more modern
        if (!successor)
        {
            return nullptr;
        }
        // at this point there is a successor node (there's one node on the right).
        while(successor->p_left)
        {
            successor = successor->p_left;
        }
        return successor;
    }

    return nullptr;
}

void BST::insert(int data)
{
    // a lot like find...
    // except at the end we stick the data into the tree.
    tree_node * p_current = m_root;
    tree_node * parent = nullptr;

    // m_root == nullptr
    if (!m_root)
    {
        m_root = new tree_node(data);
        return;
    }

    while(p_current != nullptr)
    {
        // if data is less than the current node's data, we go down and to the left
        // if the data is greater than or equal to the current node's data then we go down
        // and to the right

        if(data < p_current->data)
        {
            parent = p_current;
            p_current = p_current->p_left;
        }
        else if (data >= p_current->data)
        {
            parent = p_current;
            p_current = p_current->p_right;
        }
    }

    if (data < parent->data)
    {
        parent->p_left = new tree_node(data);
        parent->p_left->p_parent = parent;
    }
    else
    {
        parent->p_right = new tree_node(data);
        parent->p_right->p_parent = parent;
    }
}

void BST::display(bool verbose_leaves)
{
    display_subtree(m_root, verbose_leaves, 0);
}

void BST::remove(int data)
{
    tree_node * del_node = find_node(data);
    remove_node(del_node);
}


void BST::remove_node(tree_node * del_node)
{
    if (!del_node)
    {
        // tried to remove something not in the tree.
        return;
    }
    // a few ways to resolve this issue...
    tree_node * parent = del_node->p_parent;

    tree_node * successor = get_successor(del_node);
    if (!successor)
    {
        // need the parent of the node itself.  think about it
        if (del_node->p_left)
        {
            // || del_node->p_right impossible since it has no successor.
            if(del_node == m_root)
            {
                m_root = del_node->p_left;
            }
            else if(del_node == del_node->p_parent->p_left)
            {
                del_node->p_parent->p_left = del_node->p_left;
            } else{
                del_node->p_parent->p_right = del_node->p_left;
            }
        }
        delete del_node;
        if(parent && parent->p_left == del_node)
        {
            parent->p_left = nullptr;
        }
        else if (parent)
        {
            parent->p_right = nullptr;
        }
    }
    // we find the node, the successor exists
    del_node->data = successor->data;
    // successor->p_left || impossible
    if(successor->p_right)
    {
        // more to do it's not a leaf
        remove_node(successor);
    }
    else
    {
        // multiple pointer arrows like this yield segfaults very easily.
        // successor->p_parent is null and then we try to access p_left
        if(successor == successor->p_parent->p_left)
        {
            successor->p_parent->p_left = nullptr;
        }
        else
        {
            successor->p_parent->p_right = nullptr;
        }
        delete successor;
        // tell successor's parent to forget about it.
    }
}

void BST::display_subtree(tree_node * p_current, bool verbose_leaves, int depth)
{
    if(p_current)
    {
        display_subtree(p_current->p_left, verbose_leaves, depth + 1);
        for(int i = 0; i < depth; i++)
        {
            cout << "     ";
        }
        cout << p_current->data << endl;
        display_subtree(p_current->p_right,  verbose_leaves, depth + 1);
    } else{
        if (verbose_leaves)
        {
            for(int i = 0; i < depth; i++)
            {
                cout << "     ";
            }
            cout << "null-leaf" << endl;
        }
    }
}