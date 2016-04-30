#ifndef ANZLIZ
#define ANALIZ
#define PATH_MAX 261

typedef struct passwd_record {
	char user[32]; // man useradd
	char passwd[256];
	int uid, gid;
	char gecos[256];
	char home[PATH_MAX];
	char shell[PATH_MAX];
} pwdrecs[1024];

char *skip_spaces(char *suf);
void open_file();
void analiz(char *str);
int sspn_time(char *s);

#endif
