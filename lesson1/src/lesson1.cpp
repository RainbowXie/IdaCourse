#include <cstdio>
#include <cstring>
#include <string.h>

const char* key = "cm9vdA==";
#define BASE64_PAD '='
#define BASE64DE_FIRST '+'
#define BASE64DE_LAST 'z'

/* BASE 64 encode table */
static const char base64en[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/',
};

unsigned int
base64_encode(const unsigned char *in, unsigned int inlen, char *out)
{
	int s;
	unsigned int i;
	unsigned int j;
	unsigned char c;
	unsigned char l;

	s = 0;
	l = 0;
	for (i = j = 0; i < inlen; i++) {
		c = in[i];

		switch (s) {
		case 0:
			s = 1;
			out[j++] = base64en[(c >> 2) & 0x3F];
			break;
		case 1:
			s = 2;
			out[j++] = base64en[((l & 0x3) << 4) | ((c >> 4) & 0xF)];
			break;
		case 2:
			s = 0;
			out[j++] = base64en[((l & 0xF) << 2) | ((c >> 6) & 0x3)];
			out[j++] = base64en[c & 0x3F];
			break;
		}
		l = c;
	}

	switch (s) {
	case 1:
		out[j++] = base64en[(l & 0x3) << 4];
		out[j++] = BASE64_PAD;
		out[j++] = BASE64_PAD;
		break;
	case 2:
		out[j++] = base64en[(l & 0xF) << 2];
		out[j++] = BASE64_PAD;
		break;
	}

	out[j] = 0;

	return j;
}

int algorithm3(char* str1, int str1_len, char* str2, int str2_len)
{
    for ( int i = 0; i < str1_len; ++i )
    {
        str1[i] ^= str2[i % str2_len];
    }
    return str1_len;
}

bool check_field(char* field)
{
    bool ret = false;
    char symbol[5] = {'@', '|', ';', '+', '-'};

    int i1 = strlen(field);
    if (i1 <= 0x64)
    {
        for (int j = 0; j < i1; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                char c = symbol[k];
                if (c == field[j])
                {
                    ret = false;
                    return ret;
                }
            }
        }
        ret = true;
    }
    else 
    {
        ret = false;
    }

    return ret;
}

char* base64(char* org, char* outbuff, int shifted)
{
    return nullptr;
}

bool check_register(char* username, char* password )
{
    char username_encoded[0x200] = {0};
    bool ret = false;

    if ( username && password )
    {
        if (check_field(username) && check_field(password)) 
        {
            base64_encode((const unsigned char*)username, strlen(username), username_encoded);            
            if (!strcmp(username_encoded, key))
            {
                int i1 = strlen(username);
                int i2 = strlen(password);
                algorithm3(password, i2, username, i1);
                ret = strncmp(password, " __", i1);
                if (!ret)
                {
                    ret = true;
                }
            }
        }
    }
    else 
    {
        ret = false;
    }

    return ret;
}

__attribute__ ((visibility("hidden"))) int main()
{
    char username[100] = {0};
    char password[100] = {0};
    
    printf("Find username and password\n");
    printf("username:");
    scanf("%s", username);
    printf("password:");
    scanf("%s", password);
    if (check_register(username, password))
        printf("success!\n");
    else
        printf("user name or password is invalid.\n");
    getchar();
    getchar();
}