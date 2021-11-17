// Q25 - In the drawing to the left, which is the best types of pointers to use
/*
    C
    unique_ptr to the root, unique_ptr to nodes. No destination overlap
*/

// Q26 - In the drawing to the left, which is the best types of pointers to use
/*
    A
    unique_ptr to the root, shared_ptr to nodes. Destination overlap
*/

// Q27 - In the drawing to the left, which is the best types of pointers to use
/*
    A
    unique_ptr to the root, weak_ptr back up the tree, shared_ptr to nodes. Destination overlap with backtrace
*/