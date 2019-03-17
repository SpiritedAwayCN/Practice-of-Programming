#include<cstdio>
#include<cstring>

char calc_char(char text, char key){
    //printf("%c %c ",text,key);
    bool low = false;
    if(text>='a' && text<='z') {text += 'A'-'a' ; low = true;}
    if(key>='a' && key<='z') key += 'A'-'a';
    if(text-key<0)text+=26;
    text = ((text-key)%26) + 'A';
    //printf("%c %c\n",text,key);
    if(low) text += 'a'-'A';
    return text;
}

int main(){
    char key_s[105];
    char text_s[1005];
    gets(key_s);
    gets(text_s);
    //printf("%c\n\n\n",text_s[3]);
    int len = strlen(text_s),len_k = strlen(key_s);
    for(int i=0;i<len;i++){
        putchar(calc_char(text_s[i],key_s[i%len_k]));
    }
    return 0;
}
