#include "File_code/include/add_operations.h"

int main(){
    const char *source[]={
        "testcase (1)/testcase/2.hamlet.txt",
        "testcase (1)/testcase/1.MIT-license.txt",
        "testcase (1)/testcase/3.USTC-logo.bmp"
    };
    const char *target[]={"hamlet.hfm","license.hfm","logo.hfm"};
    const char *restored[]={"hamlet_restored.txt","license_restored.txt","logo_restored.bmp"};

    for(int i=0;i<3;i++){
        printf("\nSource: %s\n",source[i]);
        if(!CompressFile(source[i],target[i])||
           !DecompressFile(target[i],restored[i])){
            printf("failed\n");
            return 1;
        }

        FILE *in=fopen(source[i],"rb");
        FILE *out=fopen(restored[i],"rb");
        FILE *fp=fopen(target[i],"rb");
        if(!in||!out||!fp){
            if(in) fclose(in);
            if(out) fclose(out);
            if(fp) fclose(fp);
            return 1;
        }
        bool success=true;
        int ch;
        int decoded;
        uint64_t size=0;
        uint64_t compressedSize=0;
        do{
            ch=fgetc(in);
            decoded=fgetc(out);
            if(ch!=decoded){
                success=false;
                break;
            }
            if(ch!=EOF){
                size++;
            }
        }while(ch!=EOF);
        if(ferror(in)||ferror(out)){
            success=false;
        }
        while(fgetc(fp)!=EOF){
            compressedSize++;
        }
        if(ferror(fp)){
            success=false;
        }
        fclose(in);
        fclose(out);
        fclose(fp);

        if(!success){
            printf("Restored file differs from source.\n");
            return 1;
        }
        printf("Original: %llu bytes\n",(unsigned long long)size);
        printf("Compressed: %llu bytes\n",(unsigned long long)compressedSize);
        if(size!=0){
            printf("Compressed/original: %.2f%%\n",100.0*(double)compressedSize/(double)size);
        }
        printf("Restored file matches source.\n");
    }
    return 0;
}
