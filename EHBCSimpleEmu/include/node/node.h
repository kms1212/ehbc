#ifndef __NODE_NODE_H__
#define __NODE_NODE_H__



struct node {
    char id[16];

    union {
        
    };

    size_t child_cnt;
    struct node* child[];
};

#endif  // __NODE_NODE_H__
