#include <stdio.h>
#include <string.h>

#define m_size 5000

int is_present(char c, char *str) {
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == c) {
			return 1;
		}
	}
	return 0;
}

void str_diff(char *str1, char *str2) {
    char first[] = "";
    char second[] = "";

    for (int i = 0; i < 128; i++) {
    	char ch[] = {(char)i};
        int is_in_first = is_present((char)i, str1);
        int is_in_second = is_present((char)i, str2);
        if (is_in_first && !is_in_second) {
        	strcat(first, ch);
        	// first += (char)i;
        }
        if (is_in_second && !is_in_first) {
        	strcat(second, ch);
        	// second += (char)i;
        }
    }

    char res[m_size] = " ";
    strcat(res, first);
    strcat(res, "\n");
    strcat(res, second);

    memset(str1, 0, m_size);
    strcpy(str1, res);
}

