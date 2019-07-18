#include "../inc/ft_ssl.h"

void   main(int argc, char **argv)
{
	int c;
	FILE *fd;

    if (argc < 2) {
        printf("usage: %s 'string'\n", argv[0]);
        return;
    }
	argv++;
    argc--;
	if(argc > 0 && strcmp(argv[0],"-d") == 0){
		debug++;
		argv++;
        argc--;
	}

	if(argc > 0 && strcmp(argv[0],"-x") == 0){
		hex++;
		argv++;
        argc--;
	}

	if(argc == 0)
		sum(stdin,0);
	else for(c = 0; c < argc; c++){
		fd = fopen(argv[c],"r");
		if(fd==NULL){
			fprintf(stderr, "md5sum: can't open %s\n", argv[c]);
			continue;
		}
		sum(fd, argv[c]);
		fclose(fd);
	}
}
