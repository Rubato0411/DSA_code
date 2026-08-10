#include"common.h"

void CreateHuffmanTree(HuffmanTree *HT,unsigned int *w,unsigned int n);
void CreateHuffmanCode(HuffmanTree HT,HuffmanCode *HC,unsigned int n);
char* Encode(HuffmanCode HC,char *str,int n,char* charset);
char* Decode(HuffmanTree HT,char *str,int n,char* charset);
void destroyHuffmanTree(HuffmanTree *HT);
void destroyHuffmanCode(HuffmanCode *HC,unsigned int n);