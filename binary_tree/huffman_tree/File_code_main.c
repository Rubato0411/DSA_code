#include "File_code/include/add_operations.h"
#ifdef _WIN32
#include<windows.h>
#endif

int main(){
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    const char *source[]={
        "testcase (1)/testcase/2.hamlet.txt",
        "testcase (1)/testcase/1.MIT-license.txt",
        "testcase (1)/testcase/3.USTC-logo.bmp",
        "testcase (1)/testcase/4.USTC-logo.png",
        "testcase (1)/testcase/5.data-structure.pdf",
        "testcase (1)/testcase/6.MV.mp4"
    };
    const char *compressed[]={"hamlet.hfm","license.hfm","logo.hfm",
                              "logo_png.hfm","data_structure.hfm","MV.hfm"};
    const char *restored[]={"hamlet_restored.txt","license_restored.txt","logo_restored.bmp",
                            "logo_restored.png","data_structure_restored.pdf","MV_restored.mp4"};
    char line[1024];
    char input[1024];
    char output[1024];
    int command;
    int choice;

    while(true){
        printf("\n1. 压缩文件\n2. 解压文件\n0. 退出\n请选择操作：");
        if(!fgets(line,sizeof(line),stdin)){
            break;
        }
        if(sscanf(line,"%d",&command)!=1){
            continue;
        }
        if(command==0){
            break;
        }
        if(command!=1&&command!=2){
            continue;
        }
        printf("\n1. 哈姆雷特\n2. MIT许可证\n3. BMP图片\n4. PNG图片\n");
        printf("5. PDF文档\n6. 视频\n7. 自定义路径\n0. 返回\n请选择文件：");
        if(!fgets(line,sizeof(line),stdin)){
            break;
        }
        if(sscanf(line,"%d",&choice)!=1||choice<0||choice>7){
            continue;
        }
        if(choice==0){
            continue;
        }
        if(choice==7){
            printf("请输入源文件路径（不加引号）：");
            if(!fgets(input,sizeof(input),stdin)){
                break;
            }
            input[strcspn(input,"\r\n")]='\0';
        }else{
            strcpy(input,command==1?source[choice-1]:compressed[choice-1]);
        }
        printf("源文件：%s\n",input);
        if(choice!=7){
            printf("请输入输出路径（直接回车使用 %s）：",
                   command==1?compressed[choice-1]:restored[choice-1]);
        }else{
            printf("请输入输出文件路径（不加引号）：");
        }
        if(!fgets(output,sizeof(output),stdin)){
            break;
        }
        output[strcspn(output,"\r\n")]='\0';
        if(output[0]=='\0'){
            if(choice==7){
                continue;
            }
            strcpy(output,command==1?compressed[choice-1]:restored[choice-1]);
        }

        bool success=command==1?CompressFile(input,output):DecompressFile(input,output);
        if(!success){
            printf("操作失败，请检查文件路径和输入文件。\n");
            continue;
        }
        printf("输出文件：%s\n",output);

        const char *paths[]={input,output};
        uint64_t size[2]={0,0};
        bool counted=true;
        for(int i=0;i<2;i++){
            FILE *fp=fopen(paths[i],"rb");
            if(!fp){
                counted=false;
                break;
            }
            while(fgetc(fp)!=EOF){
                size[i]++;
            }
            if(ferror(fp)){
                counted=false;
            }
            fclose(fp);
        }
        if(counted){
            printf("源文件大小：%llu 字节，输出文件大小：%llu 字节\n",
                   (unsigned long long)size[0],(unsigned long long)size[1]);
            if(command==1&&size[0]!=0){
                printf("占比：%.2f%%\n",100.0*(double)size[1]/(double)size[0]);
            }
        }
    }
    return 0;
}
