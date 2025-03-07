/*
 * Copyright (c) 2025, oldteam. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdnoreturn.h>

const char	*exec=NULL;
const char	*prfx=NULL, *ptfx;
char		input[2048]={0};
int		oflag;
int		bflag;
int		Oflag;
int		dflag;
int		n;

void inline noreturn static usage(void)
{
	fprintf(stdout,"Usage %s <nickname> [flags]\n",exec);
	fprintf(stdout,"  -o		display how one sequence\n");
	fprintf(stdout,"  -p <txt>	set prefix, ex: 0x\n");
	fprintf(stdout,"  -b		display seq in binary\n");
	fprintf(stdout,"  -d		display seq in decimal\n");
	fprintf(stdout,"  -P <txt>	set postfix, ex: h\n");
	fprintf(stdout,"  -O		display seq in octal\n");
	fprintf(stdout,"  -h		display this \"help\" menu\n");
	exit(0);
}

static inline void binprint(size_t size, void *ptr)
{
    u_char *b=(u_char*)ptr;
    u_char byte;
    int i,j;
    
    for (i=size-1;i>=0;i--) {
        for (j=7;j>=0;j--) {
            byte=(b[i]>>j)&1;
            printf("%u", byte);
        }
    }
}

int main(int argc, char **argv)
{
	/* getopt */
	if ((exec=*argv)&&argc<=1)
		usage();
	for (;--argc;) {
		if (**(++argv)=='-'&&isalpha(*++(*argv))) {
			switch(**argv) {
			case 'p':
				if (!*(argv+1)) usage();
				prfx=*(argv+1);
				argv++,argc--;	/* skip param */
				break;
			case 'P':
				if (!*(argv+1)) usage();
				ptfx=*(argv+1);
				argv++,argc--;
				break;
			case 'o': oflag++; break;
			case 'O': Oflag++; break;
			case 'b': bflag++; break;
			case 'd': dflag++; break;
			case 'h': usage();
			}
			continue;
		}
		memcpy(input,*argv,strlen(*argv));
	}
	if (oflag)
		printf("%s", (prfx)?prfx:"");

	for (n=0;n<strlen(input);n++) {
		if (!oflag)
			printf("%s", (prfx)?prfx:"");

		if (bflag)
			binprint(1, &input[n]);
		else if (Oflag)
			printf("%o", input[n]);
		else if (dflag)
			printf("%d", input[n]);
		else
			printf("%02x", input[n]);

		if (!oflag) {
			printf("%s", (ptfx)?ptfx:"");
			putchar(' ');
		}
	}
	if (oflag)
		printf("%s", (ptfx)?ptfx:"");

	putchar(0x0a);
	return 0;
}
