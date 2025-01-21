#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_size 256

int freq[max_size];
struct leafNode* tree[max_size];
int last = 0;
int compressedSize = 0;

struct leafNode{
	char letter;
	int freq;
	
	struct leafNode *left, *right;

};

void calcFreq(char txt[]){
	int i = 0;
	
	for(i = 0; i <= max_size; i++){
		freq[i] = 0;
	}
	
	for(i = 0; txt[i] != '\0'; ++i){
		if(txt[i] != '\n'){
			freq[(int) txt[i]]++;
		}		
	}
}

struct leafNode* newNode(char data, int freq) {
	
    struct leafNode* node = (struct leafNode*)malloc(sizeof(struct leafNode));
    
    node->letter = data;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void createTree(char txt[]) {
    int capacity = strlen(txt);

    while (last < capacity && txt[last] != '\0') {
        struct leafNode* node = newNode(txt[last], freq[(int)txt[last]]);
        int i = 0;

        for (i = 0; i < last; i++) {
            if (node->freq < tree[i]->freq) {
                int j;
                for (j = last; j > i; j--) {
                    tree[j] = tree[j - 1];
                }
                tree[i] = node;
                break;
            }
        }

        if (i == last) {
            tree[last] = node;
        }

        last++;
    }

    int i;
    for (i = 0; i < last; i++) {
        printf("letter %c: %d\n", tree[i]->letter, tree[i]->freq);
    }
}

void createHuffmanTree() {
    while (last > 1) {
        int sum = tree[0]->freq + tree[1]->freq;
        struct leafNode* node = newNode(' ', sum);
        node->left = tree[0];
        node->right = tree[1];

        memmove(&tree[0], &tree[2], (last - 2) * sizeof(struct leafNode*));
        last -= 2;

        int i = 0;
        for (i = 0; i < last; i++) {
            if (node->freq < tree[i]->freq) {
                memmove(&tree[i + 1], &tree[i], (last - i) * sizeof(struct leafNode*));
                break;
            }
        }
        tree[i] = node;
        last++;
    }

    printf("\nHuffman Tree created successfully.\n");
}

void printCodes(struct leafNode* root, char* code, int top) {
    if (root == NULL) {
        return;
    }

    if (root->left == NULL && root->right == NULL) {
        printf("Character: %c, Code: %s\n", root->letter, code);
        compressedSize += root->freq * top;
        return;
    }

    code[top] = '0';
    code[top + 1] = '\0';
    printCodes(root->left, code, top + 1);

    code[top] = '1';
    code[top + 1] = '\0';
    printCodes(root->right, code, top + 1);
}

void generateAndPrintHuffmanCodes() {
    char code[max_size];
    code[0] = '\0';
    printCodes(tree[0], code, 0);
}

int main(void){
	
	char text[max_size];
	
	printf("Enter the text to be compressed:\n");
	fgets(text, sizeof(text), stdin);
	
	printf("You entered: %s\n", text);
	printf("Compressing...\n");
	
	int i;
	
	for(i = 0; text[i] != '\0'; ++i){
		if(text[i] == '\n'){
			text[i] = '\0';
		}		
	}
	
	calcFreq(text);
	
	int count = 0;
	for(i = 0; i <= max_size; i++){
		if(freq[i] != 0){
			count++;
		}
	}
	
	char uniq[count];
	int j = 0;
	
	for(i = 0; i <= max_size; i++){
		if(freq[i] != 0){
			uniq[j] = (char) i;
			j++;
		}
	}
	
	for(j = 0; j <= max_size; j++){
		tree[j] == NULL;
	}
	
	createTree(uniq);
	createHuffmanTree();
	generateAndPrintHuffmanCodes();	
	
	printf("\n\nOriginal text size: %d bits\n", strlen(text) * 8);
	printf("Compressed text size: %d bits\n", compressedSize);
}
