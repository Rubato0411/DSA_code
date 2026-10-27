#include "../../include/operations.h"

bool Encoding(HuffmanTree HT,unsigned int n,char *charset,
              const char *source,const char *target);

bool Decoding(HuffmanTree HT,unsigned int n,char *charset,
              const char *source,const char *target);

bool Printing(const char *source,const char *target);

bool TreePrinting(HuffmanTree HT,unsigned int n,char *charset,const char *target);

void HuffmanSystem(void);

bool Initialization(HuffmanTree *HT,unsigned int *n,char **charset,const char *source);

bool CompressFile(const char *source,const char *target);
bool DecompressFile(const char *source,const char *target);
