/*
** EPITECH PROJECT, 2020
** main.h
** File description:
** main
*/

#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <zconf.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <stdbool.h>
#include <netdb.h>
#include <limits.h>
#include <fcntl.h>

#define CRLF "\r\n\0"
#define IP "127.0.0.1"
#define CLIENT_NUMBER 1024
#define BUFFER_SIZE 1024

#undef EXIT_FAILURE
#define EXIT_FAILURE 84

void str_to_upper(char * line);
bool starts_with(const char * pre, const char * str);
bool ends_with(char * base, char * str);
int is_numeric(const char * s);
bool dir_exists(const char * path);
bool dir_permissions(const char * path);

int help(int ac, char ** av);
void help_message(void);
void print_raw_str(char * line);

void remove_first_chars(char * line, int times);

typedef enum ftp_actions_t
{
    USER,
    PASS,
    CWD,
    CDUP,
    QUIT,
    DELE,
    PWD,
    PASV,
    PORT,
    HELP,
    NOOP,
    RETR,
    STOR,
    LIST,
    NO_ORDER,
    ERROR
} ftp_actions_t;

typedef struct ftp_order_t
{
    int order;
    char ** parameters;
} ftp_order_t;
void identify_ftp_command(ftp_order_t * ftp_order, char * line);

typedef struct user_t
{
    char * user;
    char * passwd;
} user_t;

typedef struct client_t
{
    char * path;
    int fd;
    struct sockaddr_in socket;
    struct client_t * next;
    user_t login;
    bool logged;
    uint16_t pasv_port;
    bool pasv_set;
    uint16_t port_port;
    bool port_set;
    int fd_mod;
    char * ip;
    char * ip_b;
} client_t;
client_t * new_client(char * path, int fd, struct sockaddr_in socet, char * ip);

typedef struct network_t
{
    uint16_t port;
    char * path;
    int local_fd;
    int distant_fd;
    int addr_len;
    struct sockaddr_in local_sock;
    struct sockaddr_in distant_sock;
    client_t * client;
    fd_set readfds;
    int max_sd;
    struct protoent * pr_e;
    char * ip;
} network_t;
void add_client(network_t * w, client_t * new);
int accept_new_client(network_t * w);
int manage_client(int fd);
void read_client(int distandFd);
void remove_client(network_t * w, client_t * client);

char * ls(network_t * w);

int network(network_t * w);

int ftp_loop(network_t * w);

char ** split(char * line, const char * delimiter);
void free_2darray(void ** array);

typedef struct message_t
{
    int error_code;
    char * msg;
    int argc;
} message_t;

int my_send(int fd, int id, char *arg);
int my_send_custom(int fd, int id, char * format);
void launch_command(client_t * client, ftp_order_t * ftp_order);

#define USER_NUMBER 1
#define SEND_FTP(code, arg) my_send(w->fd, code, arg)
#define SEND_FTP_C(code, format) my_send_custom(w->fd, code, format)

void ftp_user(client_t * w, ftp_order_t * ftp_order);
void ftp_pass(client_t * w, ftp_order_t * ftp_order);
void ftp_cwd(client_t * w, ftp_order_t * ftp_order);
void ftp_cdup(client_t * w, ftp_order_t * ftp_order);
void ftp_quit(client_t * w, ftp_order_t * ftp_order);
void ftp_dele(client_t * w, ftp_order_t * ftp_order);
void ftp_pwd(client_t * w, ftp_order_t * ftp_order);
void ftp_pasv(client_t * w, ftp_order_t * ftp_order);
void ftp_port(client_t * w, ftp_order_t * ftp_order);
void ftp_help(client_t * w, ftp_order_t * ftp_order);
void ftp_noop(client_t * w, ftp_order_t * ftp_order);
void ftp_retr(client_t * w, ftp_order_t * ftp_order);
void ftp_stor(client_t * w, ftp_order_t * ftp_order);
void ftp_list(client_t * w, ftp_order_t * ftp_order);

int read_sockets(network_t * w);
char * multi_tok(char *input, const char *delimiter);

int open_pasv_port(client_t * w);
void close_pasv_port(client_t * client);

char * assemble_path_file(client_t * w, ftp_order_t * ftp_order);

void download_file(FILE * file, int fd_new, client_t * w);
void upload_file(int file, int fd_new, client_t * w);

void destroy_network(network_t * w);
int ftp_loopy_loop(network_t * w, bool pass);

typedef struct fork_pair_t
{
    int pid;
    client_t * client;
} fork_pair_t;

int my_fork(int order, client_t * w);

#define MY_FORK(client) my_fork(0, client)
#define MY_FORK_DELETE_ALL() my_fork(1, NULL)
#define MY_FORK_DELETE_CLIENT(client) my_fork(2, client)

void signal_remover(int sig);
void signal_int_handler(int sig);
void signal_usr1_handler(int sig);

int bsignals(int mode);

#define BLOCK_SIGNALS bsignals(0)
#define UNBLOCK_SIGNALS bsignals(1)

void signal_handler(int sig);
void signal_handler2(int sig);

#endif // MAIN_H