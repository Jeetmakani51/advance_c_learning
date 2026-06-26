#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    struct Node *left;
    struct Node *right;
    char word[64];
}Node;

Node *insert(Node *root, char *word){
    if(root == NULL){
        Node *new_node = malloc(sizeof(Node));
        strcpy(new_node -> word, word);
        new_node -> left = NULL;
        new_node -> right = NULL;
        return new_node;
    }else if(strcmp(word, root -> word) < 0){
        root -> left = insert(root -> left, word);
    }else if(strcmp(word, root -> word) > 0){
        root -> right = insert(root -> right , word);
    }
    return root;
}

void print_all(Node *root){
    if(root == NULL) return;
    print_all(root -> left);
    printf("%s\n",root -> word);
    print_all(root -> right);
}

int search(Node *root, char *word){
    if(root == NULL){
        return 0;
    }
    else if(strcmp(word, root -> word) < 0){
        return search(root -> left, word);
    }else if(strcmp(word, root -> word) > 0){
        return search(root -> right, word);
    }else{
        return 1;
    }
}
void autocomplete(Node *root, char *prefix){
    if(root == NULL){
        return;
    }
    autocomplete(root -> left,prefix);
    autocomplete(root -> right,prefix);
    if(strncmp(root -> word, prefix, strlen(prefix)) == 0){
        printf("%s\n",root -> word);
    }
}

void cleanup(Node *root){
    if(root == NULL){
        return;
    }
    cleanup(root -> left);
    cleanup(root -> right);
    free(root);
}

int main(){
    Node *root = NULL;
    root = insert(root, "apple");
    root = insert(root, "application");
    root = insert(root, "appetite");
    root = insert(root, "mango");
    root = insert(root, "banana");
    root = insert(root, "blueberry");
    root = insert(root, "avacado");
    root = insert(root, "orange");

    print_all(root);

    printf("mango found : %d\n",search(root, "mango"));
    printf("blackberry found : %d\n",search(root, "blackberry"));

    autocomplete(root, "ap");
    cleanup(root);

    return 0;

}