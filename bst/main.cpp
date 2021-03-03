#include <vector>
#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BST.h"
using namespace std;

// selection sort first
// in-place sort means we don't make an extra copy of the entire data structure
// at most we swap elements (generally what it means)
/*
 *  Selection sort "find min sort"
 *  scan the list/vector/array/whatever
 *  start current = 0 for:
 *      find the min from current to end
 *      swap it to the current position
 *      advance current position + 1
 */

typedef vector<int> (*sorting_function) (vector<int> &);

void selection_sort(vector<int> & my_vector)
{
    // how do we analyze an algorithm for its runtime?
    // count the number of times each loop runs,
    // count lines of code that aren't loops/function calls as O(1)
    // this runs n times.
    // sum_ current = 1 to n of O(n - current)
    for (unsigned int current = 0; current < my_vector.size(); current++)
    {
        unsigned int min_position = current;
        // for loop runs n = my_vector.size() n - current times.
        // (n - current)(O(1)) = O(n - current)
        for(unsigned int find_min = current; find_min < my_vector.size(); find_min++)
        {
            // innermost piece of code
            // what is its runtime?
            // memory access takes constant time, if statement is constant time
            // assignment is constant time.
            // O(1) constant time.
            if (my_vector[find_min] < my_vector[min_position])
            {
                min_position = find_min;
            }
        }
        // swap
        // swap(my_vector[current], my_vector[min_position]);
        // really really don't care about the exact implementation details.
        int temp_element = my_vector[current];
        my_vector[current] = my_vector[min_position];
        my_vector[min_position] = temp_element;
    }
}

vector<int> quick_sort(vector<int> & my_list)
{
    if (my_list.size() > 1)
    {
        vector<int> less_bucket;
        vector<int> greater_bucket;
        vector<int> equal_bucket;

        // my_list[0] is the pivot element.
        for (unsigned int i = 0; i < my_list.size(); i++)
        {
            if(my_list[i] < my_list[0])
            {
                less_bucket.push_back(my_list[i]);
            }
            else if (my_list[i] > my_list[0])
            {
                greater_bucket.push_back(my_list[i]);
            } else{
                //it's equal so stick that in the equal bucket.
                equal_bucket.push_back(my_list[i]);
            }
        }

        // sort the less and greater buckets
        less_bucket = quick_sort(less_bucket);
        greater_bucket = quick_sort(greater_bucket);
        // assumes it's all been sorted
        // merge all of this back together
        vector<int> new_list;
        for (int x : less_bucket)
        {
            new_list.push_back(x);
        }
        for (int x : equal_bucket)
        {
            new_list.push_back(x);
        }
        for (int x : greater_bucket)
        {
            new_list.push_back(x);
        }
        return new_list;
    }
    else
    {
        // just one element or zero is sorted already.
        return my_list;
    }
}

/*
 * This is not merge_sort this is just the merge part
 *
 */
vector<int> merge(vector<int>& first_list, vector<int> & second_list)
{
    vector<int> result_list;
    unsigned int first_index = 0;
    unsigned int second_index = 0;
    while(first_index < first_list.size() && second_index < second_list.size())
    {
        // add the first_list[first_index] to our resulting list
        if(first_list[first_index] < second_list[second_index])
        {
            result_list.push_back(first_list[first_index]);
            first_index++;
        } else{
            result_list.push_back(second_list[second_index]);
            second_index++;
        }
    }
    // one of the lists is going to be "used up"
    // only one will ever run <-- better english
    // it's ok, the other one won't enter because the indices are already past the length
    for(unsigned int i = first_index; i < first_list.size(); i++)
    {
        result_list.push_back(first_list[i]);
    }

    for(unsigned int j = second_index; j < second_list.size(); j++)
    {
        result_list.push_back(second_list[j]);
    }

    return result_list;
}


vector<int> merge_sort(vector<int>& list_to_sort)
{
    if (list_to_sort.size() <= 1)
    {
        // a list of size 0 is "sorted" and a list of size 1 is sorted
        return list_to_sort;
    }
    // first_list = list_to_sort[0: len(list_to_sort)//2]
    // first_list = list_to_sort[len(list_to_sort)//2: len(list_to_sort)]
    vector<int> first_list;
    vector<int> second_list;
    for(unsigned int i = 0; i < list_to_sort.size() / 2; i++)
    {
        first_list.push_back(list_to_sort[i]);
    }
    for(unsigned int j = list_to_sort.size() / 2; j < list_to_sort.size(); j++)
    {
        second_list.push_back(list_to_sort[j]);
    }
    first_list = merge_sort(first_list);
    second_list = merge_sort(second_list);

    /// here, merging is actually putting things in order
    /// in quick sort, merging is just sticking first_list + second_list
    return merge(first_list, second_list);
}



void test_selection_sort(int n)
{
    vector<int> new_vector;
    for (int i = 0; i < n; i++)
        new_vector.push_back(rand() % 1000);
    clock_t start, end;
    start = clock();
    selection_sort(new_vector);
    end = clock();
    cout << "The amount of time it took to sort " << n << " elements was: " << end - start << endl;
}

void test_quick_sort(int n)
{
    vector<int> new_vector;
    for (int i = 0; i < n; i++)
        new_vector.push_back(rand() % 1000);
    clock_t start, end;
    start = clock();
    quick_sort(new_vector);
    end = clock();
    cout << "The amount of time it took to sort " << n << " elements was: " << end - start << endl;
}


/*
 * insertion sort = pull back sort
 */
vector<int> insertion_sort(vector<int> & list_to_sort)
{
    for (unsigned int i = 1; i < list_to_sort.size(); i++)
    {
        unsigned int current = i;
        while(current > 0 && list_to_sort[current] < list_to_sort[current - 1])
        {
            swap(list_to_sort[current], list_to_sort[current - 1]);
            // pulling back part
            current--;
        }
    }
    return list_to_sort;
}

void test_sort(int n, sorting_function sf)
{
    vector<int> new_vector;
    for (int i = 0; i < n; i++)
        new_vector.push_back(rand() % 1000);
    clock_t start, end;
    start = clock();
    sf(new_vector);
    end = clock();
    cout << "The amount of time it took to sort " << n << " elements was: " << end - start << endl;
}

void bst_driver();

int main() {
    bst_driver();
    return 0;
}
void bst_driver()
{
    BST bst;
    string s;
    cout << "Enter command: ";
    cin >> s;
    int x;

    while(s != "quit")
    {
        if(s == "insert")
        {
            cin >> x;
            bst.insert(x);
        }
        else if (s == "find")
        {
            cin >> x;
            if(bst.find(x))
            {
                cout << "We found " << x << endl;
            } else{
                cout << "We did not find " << x << endl;
            }
        }
        else if (s == "display")
        {
            bst.display();
        }
        else if (s == "display-with-leaves")
        {
            bst.display(true);
        }
        bst.display();
        cout << "Enter command: ";
        cin >> s;
    }
}
