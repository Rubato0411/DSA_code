#include "../include/add_operations.h"

static char* ReadFile(const char* src){
    FILE *fp=fopen(src,"rb");
    if(fp==NULL){
        return NULL;
    }
    size_t len=0;
    size_t capacity=1024;
    char* str=(char*)malloc(capacity);
    if(!str){
        fclose(fp);
        return NULL;
    }
    int ch;
    while((ch=fgetc(fp))!=EOF){
        if(ch=='\0'){
            free(str);
            fclose(fp);
            return NULL;
        }
        if(len==capacity-1){
            if(capacity>(size_t)-1/2){
                free(str);
                fclose(fp);
                return NULL;
            }
            size_t size=capacity*2;
            char *temp=(char*)realloc(str,size);
            if(!temp){
                free(str);
                fclose(fp);
                return NULL;
            }
            str=temp;
            capacity=size;
        }
        str[len++]=(char)ch;
    }
    if(ferror(fp)){
        free(str);
        fclose(fp);
        return NULL;
    }
    str[len]='\0';
    fclose(fp);
    return str;
}

static bool WriteFile(const char* target,const char* str){
    if(!str){
        return false;
    }
    FILE *fp=fopen(target,"wb");
    if(fp==NULL){
        return false;
    }
    size_t len=strlen(str);
    bool success=fwrite(str,1,len,fp)==len;
    if(fclose(fp)!=0){
        success=false;
    }
    return success;
}

bool Encoding(HuffmanTree HT,unsigned int n,char *charset,
              const char *source,const char *target){
    if(!HT||!charset||n<2||n>(unsigned int)INT_MAX||strcmp(source,target)==0){
        return false;
    }
    char* str=ReadFile(source);
    if(!str){
        return false;
    }
    HuffmanCode HC=NULL;
    CreateHuffmanCode(HT,&HC,n);
    char* encoded_str=Encode(HC,str,n,charset);
    free(str);
    destroyHuffmanCode(&HC,n);
    bool success=WriteFile(target,encoded_str);
    free(encoded_str);
    return success;
}

bool Decoding(HuffmanTree HT,unsigned int n,char *charset,
              const char *source,const char *target){
    if(!HT||!charset||n<2||n>(unsigned int)INT_MAX||strcmp(source,target)==0){
        return false;
    }
    char* str=ReadFile(source);
    if(!str){
        return false;
    }
    char* decoded_str=Decode(HT,str,n,charset);
    free(str);
    bool success=WriteFile(target,decoded_str);
    free(decoded_str);
    return success;
}

bool Printing(const char *source,const char *target){
    if(!source||!target){
        return false;
    }
    int cnt=0;
    FILE *fp=fopen(source,"rb");
    if(!fp){
        return false;
    }
    FILE *fp_out=fopen(target,"w");
    if(!fp_out){    
        fclose(fp);
        return false;
    }
    int ch;
    while((ch=fgetc(fp))!=EOF){
        putchar(ch);
        fputc(ch,fp_out);
        cnt++;
        if(cnt==50){
            putchar('\n');
            fputc('\n',fp_out);
            cnt=0;
        }
    }
    if(cnt!=0){
        putchar('\n');
        fputc('\n',fp_out);
    }
    fclose(fp);
    fclose(fp_out);
    return true;
}

static void PrintNode(FILE *fp,HuffmanTree HT,unsigned int n,char *charset,unsigned int cur,int depth,char branch){
    if(cur==0){
        return;
    }
    for(int i=0;i<depth;i++){
        fputs("    ",fp);
    }
    fprintf(fp,"%c: ",branch);
    if(cur<=n){
        unsigned char ch=(unsigned char)charset[cur-1];
        if(ch==' '){
            fputs("[SPACE]",fp);
        }else if(ch=='\n'){
            fputs("[LF]",fp);
        }else if(ch=='\r'){
            fputs("[CR]",fp);
        }else if(ch=='\t'){
            fputs("[TAB]",fp);
        }else if(ch>=33&&ch<=126){
            fprintf(fp,"'%c'",ch);
        }else{
            fprintf(fp,"[%u]",(unsigned int)ch);
        }
        fprintf(fp," (%u)\n",HT[cur].weight);
    }else{
        fprintf(fp,"* (%u)\n",HT[cur].weight);
    }
    PrintNode(fp,HT,n,charset,HT[cur].lchild,depth+1,'L');
    PrintNode(fp,HT,n,charset,HT[cur].rchild,depth+1,'R');
}

bool TreePrinting(HuffmanTree HT,unsigned int n,char *charset,const char *target){
    if(!HT||!charset||!target||n<2){
        return false;
    }
    FILE *fp=fopen(target,"w");
    if(!fp){
        return false;
    }
    PrintNode(stdout,HT,n,charset,2*n-1,0,'T');
    PrintNode(fp,HT,n,charset,2*n-1,0,'T');
    fclose(fp);
    return true;
}

void HuffmanSystem(void){
    HuffmanTree HT=NULL;
    char *charset=NULL;
    unsigned int n=0;
    char command;
    bool success;
    while(true){
        printf("\nI: Initialization\n");
        printf("E: Encoding\n");
        printf("D: Decoding\n");
        printf("P: Print code\n");
        printf("T: Print tree\n");
        printf("Q: Quit\n");
        printf("Command: ");
        if(scanf(" %c",&command)!=1){
            break;
        }
        if(command>='a'&&command<='z'){
            command=(char)(command-'a'+'A');
        }
        if(command=='Q'){
            break;
        }
        if(command=='I'){
            success=Initialization(&HT,&n,&charset,"hfmTree");
        }else if(command=='P'){
            success=Printing("CodeFile","CodePrin");
        }else if(command=='E'||command=='D'||command=='T'){
            if(!HT){
                FILE *fp=fopen("hfmTree","rb");
                if(!fp){
                    printf("Initialize first.\n");
                    continue;
                }
                fscanf(fp,"%u",&n);
                fgetc(fp);
                charset=(char*)malloc(n+1);
                HT=(HuffmanTree)calloc(2*n,sizeof(HNode));
                if(!charset||!HT){
                    free(charset);
                    charset=NULL;
                    destroyHuffmanTree(&HT);
                    fclose(fp);
                    break;
                }
                for(unsigned int i=0;i<n;i++){
                    charset[i]=(char)fgetc(fp);
                    fgetc(fp);
                }
                charset[n]='\0';
                for(unsigned int i=1;i<=2*n-1;i++){
                    fscanf(fp,"%u %u %u %u",&HT[i].weight,
                           &HT[i].parent,&HT[i].lchild,&HT[i].rchild);
                }
                fclose(fp);
            }
            if(command=='E'){
                success=Encoding(HT,n,charset,"ToBeTran","CodeFile");
            }else if(command=='D'){
                success=Decoding(HT,n,charset,"CodeFile","TextFile");
            }else{
                success=TreePrinting(HT,n,charset,"TreePrint");
            }
        }else{
            printf("Invalid command.\n");
            continue;
        }
        printf("%s\n",success?"Success.":"failed.");
    }
    destroyHuffmanTree(&HT);
    free(charset);
}

bool Initialization(HuffmanTree *HT,unsigned int *n,char **charset,const char *source){
    unsigned int cnt=0;
    unsigned int w[256];
    int end;

    printf("Enter charset size : ");
    scanf("%u",&cnt);
    while((end=getchar())!='\n'&&end!=EOF);
    char *str=(char*)malloc(cnt+1);
    if(!str){
        return false;
    }
    printf("Enter one character and its weight per line.\n");
    for(unsigned int i=0;i<cnt;i++){
        printf("Character %u: ",i+1);
        scanf("%c %u",&str[i],&w[i]);
        while((end=getchar())!='\n'&&end!=EOF);
    }
    str[cnt]='\0';

    destroyHuffmanTree(HT);
    free(*charset);
    *n=cnt;
    *charset=str;
    CreateHuffmanTree(HT,w,*n);
    if(!*HT){
        return false;
    }
    FILE *fp=fopen(source,"wb");
    if(!fp){
        return false;
    }
    bool success=fprintf(fp,"%u\n",cnt)>0;
    for(unsigned int i=0;i<cnt&&success;i++){
        success=fprintf(fp,"%c\n",str[i])>0;
    }
    for(unsigned int i=1;i<=2*cnt-1&&success;i++){
        success=fprintf(fp,"%u %u %u %u\n",(*HT)[i].weight,
                        (*HT)[i].parent,(*HT)[i].lchild,(*HT)[i].rchild)>0;
    }
    if(fclose(fp)!=0){
        success=false;
    }
    return success;
}

bool CompressFile(const char *source,const char *target){
    if(strcmp(source,target)==0){
        return false;
    }
    FILE *in=fopen(source,"rb");
    if(!in){
        return false;
    }
    FILE *out=NULL;
    HuffmanTree HT=NULL;
    HuffmanCode HC=NULL;
    unsigned int frequency[256]={0};
    unsigned int w[256];
    int index[256]={0};
    unsigned int n=0;
    int weightBytes=2;
    uint64_t fileSize=0;
    bool success=false;
    int ch;
    while((ch=fgetc(in))!=EOF){
        if(fileSize>=UINT_MAX||fileSize>=UINT32_MAX){
            goto finish;
        }
        frequency[(unsigned char)ch]++;
        fileSize++;
    }
    if(ferror(in)){
        goto finish;
    }
    for(int i=0;i<256;i++){
        if(frequency[i]!=0){
            if(frequency[i]>UINT16_MAX){
                weightBytes=4;
            }
            w[n]=frequency[i];
            index[i]=(int)++n;
        }
    }
    if(n>1){
        CreateHuffmanTree(&HT,w,n);
        if(!HT){
            goto finish;
        }
        CreateHuffmanCode(HT,&HC,n);
        if(!HC){
            goto finish;
        }
    }

    out=fopen(target,"wb");
    if(!out){
        goto finish;
    }
    if(fwrite(weightBytes==2?"HFM2":"HFM1",1,4,out)!=4){
        goto finish;
    }
    for(int i=0;i<8;i++){
        if(fputc((int)((fileSize>>(8*i))&255),out)==EOF){
            goto finish;
        }
    }
    for(int i=0;i<2;i++){
        if(fputc((int)((n>>(8*i))&255),out)==EOF){
            goto finish;
        }
    }
    for(int i=0;i<256;i++){
        if(frequency[i]!=0){
            if(fputc(i,out)==EOF){
                goto finish;
            }
            for(int j=0;j<weightBytes;j++){
                if(fputc((int)(((uint32_t)frequency[i]>>(8*j))&255),out)==EOF){
                    goto finish;
                }
            }
        }
    }
    if(n<2){
        success=true;
        goto finish;
    }
    //写入文件头，文件长度，字节频度等信息
    rewind(in);
    unsigned char byte=0;
    int count=0;
    while((ch=fgetc(in))!=EOF){
        char *p=HC[index[(unsigned char)ch]];
        while(*p){
            byte=(unsigned char)((byte<<1)|(*p-'0'));
            count++;
            if(count==8){
                if(fputc(byte,out)==EOF){
                    goto finish;
                }
                byte=0;
                count=0;
            }
            p++;
        }
    }
    if(count!=0){
        byte=(unsigned char)(byte<<(8-count));
        if(fputc(byte,out)==EOF){
            goto finish;
        }
    }
    success=!ferror(in);

finish:
    fclose(in);
    if(out&&fclose(out)!=0){
        success=false;
    }
    destroyHuffmanCode(&HC,n);
    destroyHuffmanTree(&HT);
    return success;
}



bool DecompressFile(const char *source,const char *target){
    if(strcmp(source,target)==0){
        return false;
    }
    FILE *in=fopen(source,"rb");
    if(!in){
        return false;
    }
    FILE *out=NULL;
    HuffmanTree HT=NULL;
    char charset[256];
    unsigned int frequency[256]={0};
    unsigned int w[256];
    unsigned int n=0;
    uint64_t fileSize=0;
    uint64_t total=0;
    bool success=false;
    char magic[4];
    int weightBytes;
    int ch;

    if(fread(magic,1,4,in)!=4){
        goto finish;
    }
    if(memcmp(magic,"HFM2",4)==0){
        weightBytes=2;
    }else if(memcmp(magic,"HFM1",4)==0){
        weightBytes=4;
    }else{
        goto finish;
    }
    for(int i=0;i<8;i++){
        if((ch=fgetc(in))==EOF){
            goto finish;
        }
        fileSize|=(uint64_t)(unsigned char)ch<<(8*i);
    }
    for(int i=0;i<2;i++){
        if((ch=fgetc(in))==EOF){
            goto finish;
        }
        n|=(unsigned int)(unsigned char)ch<<(8*i);
    }
    if(n>256||fileSize>UINT_MAX||fileSize>UINT32_MAX){
        goto finish;
    }
    for(unsigned int i=0;i<n;i++){
        int symbol=fgetc(in);
        uint32_t weight=0;
        if(symbol==EOF||frequency[symbol]!=0){
            goto finish;
        }
        for(int j=0;j<weightBytes;j++){
            if((ch=fgetc(in))==EOF){
                goto finish;
            }
            weight|=(uint32_t)(unsigned char)ch<<(8*j);
        }
        if(weight==0||weight>UINT_MAX){
            goto finish;
        }
        frequency[symbol]=(unsigned int)weight;
        total+=weight;
    }
    if(total!=fileSize){
        goto finish;
    }
    unsigned int cnt=0;
    for(int i=0;i<256;i++){
        if(frequency[i]!=0){
            charset[cnt]=(char)(unsigned char)i;
            w[cnt++]=frequency[i];
        }
    }
    if(n>1){
        CreateHuffmanTree(&HT,w,n);
        if(!HT){
            goto finish;
        }
    }
    out=fopen(target,"wb");
    if(!out){
        goto finish;
    }
    if(n==0){
        success=true;
        goto finish;
    }
    if(n==1){
        for(uint64_t i=0;i<fileSize;i++){
            if(fputc((unsigned char)charset[0],out)==EOF){
                goto finish;
            }
        }
        success=true;
        goto finish;
    }

    unsigned int root=2*n-1;
    unsigned int p=root;
    uint64_t written=0;
    while(written<fileSize&&(ch=fgetc(in))!=EOF){
        for(int i=7;i>=0&&written<fileSize;i--){
            p=((ch>>i)&1)?HT[p].rchild:HT[p].lchild;
            if(HT[p].lchild==0&&HT[p].rchild==0){
                if(fputc((unsigned char)charset[p-1],out)==EOF){
                    goto finish;
                }
                written++;
                p=root;
            }
        }
    }
    success=written==fileSize&&!ferror(in);

finish:
    fclose(in);
    if(out&&fclose(out)!=0){
        success=false;
    }
    destroyHuffmanTree(&HT);
    return success;
}
