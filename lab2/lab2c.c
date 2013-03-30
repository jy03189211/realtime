#include<unistd.h>
int OpenChatFellow(void);
int main(void){
	int fellow_desc,r;
	char chr_fellow,chr_own;
	fellow_desc=OpenChatFellow();
	r=read(fellow_desc,&chr_fellow,1);
	while(r>0){
		write(1,&chr_fellow,1);
		read(0,&chr_own,1);
		write(1,&chr_own,1);
		r=read(fellow_desc,&chr_fellow,1);
	}
}