#include <unistd.h>
#include <fcntl.h>
int OpenChatFellow(void);

int main(void) {
	int fellow_desc, r;
	char chr_fellow, chr_own;
	int file_flags;
	fellow_desc = OpenChatFellow();
	file_flags = fcntl(fellow_desc, F_GETFL);
	file_flags = file_flags | O_NONBLOCK;
	fcntl(fellow_desc, F_SETFL, file_flags);
	
	file_flags = fcntl(0, F_GETFL);
	file_flags = file_flags | O_NONBLOCK;
	fcntl(0, F_SETFL, file_flags);
	
	r = read(fellow_desc,&chr_fellow, 1);
	
	while(r!=0) {
		if (r > 0) 
			write(1, &chr_fellow, 1);
		
		r = read(0, &chr_own, 1);
		if (r > 0) 
			write(1, &chr_own, 1);
		
		r = read(fellow_desc,&chr_fellow, 1); 
	}
	return 0;

}