#include<stdio.h>
char chess[8][8]={{'0','0','0','0','0','0','0','0'},
                  {'0','0','0','0','0','0','0','0'},
                  {'0','0','0','0','0','0','0','0'},
                  {'0','0','0','2','1','0','0','0'},
                  {'0','0','0','1','2','0','0','0'},
                  {'0','0','0','0','0','0','0','0'},
                  {'0','0','0','0','0','0','0','0'},
                  {'0','0','0','0','0','0','0','0'}};
char next[8][8];
int check(short y,short x,short xt,short yt,char input){
    int c=0;
    int n=0;
    for (int i = x+xt,j=y+yt; i >-1 && j >-1 && j<8 && i<8; i+=xt,j+=yt){
        n++;
        if(chess[j][i]==input)  return 0;
        if(chess[j][i]!=input&&chess[j][i]!='0')    c=1;
        if(chess[j][i]=='0'){
            if(c==1){
                return n;
            }
            return 0;
        }
    }return 0;
}
void dnext(char input,short j,short i){
    if(input=='1'){
        if(next[j][i]!='2'){
            next[j][i]='1';
        }else{
            next[j][i]='3';
        }
        }else{
            if(next[j][i]!='1'){
                next[j][i]='2';
            }else{
                next[j][i]='3';
            }
    }
}
void printInput(char input){
    int d=0;
    input=(input=='1') ?'1':'2';
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if(next[i][j]==input||next[i][j]=='3'){
                if(d==1)    printf(",");
                else    d=1;
                printf("(%d,%d)",i,j);
            }
        }
    }
    printf("\n");
}
short filp(short y,short x,short xt,short yt,char color,int isFilp){
    int k=0,n=0;
    chess[y][x]=color;
    char anoColor=(color-48)^3+48;
    for (int i = x+xt,j=y+yt;i >-1 && j >-1 && j<8 && i<8; i+=xt,j+=yt){
        if(chess[j][i]==color){
            k=1;
            break;
        }
    }
    
    for (int i = x+xt,j=y+yt;i >-1 && j >-1 && j<8 && i<8; i+=xt,j+=yt){
        if(k){
            if(chess[j][i]==anoColor){
                n++;
                if(isFilp)  chess[j][i]=color;                
            }else break;
        }
    }
    if(!isFilp) chess[y][x]='0';
    return n;
}
short checkColor(char color){
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(next[i][j]==color||next[i][j]=='3')  return 1;
    return 0;
}
int main(){
    short col=1;
    while(1){
        printf("\n   ");
        for (int i = 0; i < 8; i++)
            printf("%d ",i);
        printf("\n--+");
        for (int i = 0; i < 8; i++)
            printf("--");
        printf("\n");
        for (int i = 0; i < 8; i++){
            printf("%d |",i);
            for (int j = 0; j < 8; ){
                next[i][j]='0';
                printf("%c ",chess[i][j]);
                j++;
            }
            printf("\n");
        }
        
        for (int k = 0; k < 8; k++){
            for (int m = 0; m < 8; m++){
                if(chess[k][m]=='0') continue;
                int tFilp=0;
                for (short i = -1; i < 2; i++){
                    for (short j = -1; j < 2; j++){                    
                        int temp=check(k,m,i,j,chess[k][m]);
                        if(temp)    dnext(chess[k][m],k+temp*j,m+temp*i);                        
                    }
                }
            }
        }
        if(!(checkColor('1')||checkColor('2'))) break;
        if(col==1){
            col=2;
            if(!checkColor('1')){
                printf("黑子無法下");
                continue;
            }
            printInput('1');
            int x,y;
            char haha;
            printf("input ");
            scanf("%1d%c%1d",&x,&haha,&y);
            if (next[x][y]!='1'&&next[x][y]!='3'){
                printf("這裡不能下!");
                col=1;
                continue;
            }
            for (short i = -1; i < 2; i++)
                for (short j = -1; j < 2; j++)
                    filp(x,y,i,j,'1',1);            
        }else{
            col=1;
            if(!checkColor('2')){
                printf("白子無法下");
                continue;
            }
            
            short maxF=0,maxX=0,maxY=0;
            for (short k = 0; k < 8; k++){
                for (short m = 0; m < 8; m++){
                    if(next[k][m]=='2'||next[k][m]=='3'){
                        short n=0;
                        for (short i = -1; i < 2; i++)
                            for (short j = -1; j < 2; j++)
                                n+=filp(k,m,i,j,'2',0);    
                        if(n>maxF){
                            maxF=n;
                            maxX=k;
                            maxY=m;
                        }
                    }
                }
            }
            for (short i = -1; i < 2; i++)
                for (short j = -1; j < 2; j++)
                    filp(maxX,maxY,i,j,'2',1);        
        }
        
    }
    char w=0,b=0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(chess[i][j]=='1') b++;
            if(chess[i][j]=='2') w++;
        }
    }
    printf("黑子:%d 白子:%d\n",b,w);
    (b>w)?printf("黑勝"):printf("白勝");
}
