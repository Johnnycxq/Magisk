/* daemon.h - Utility functions for daemon-client communication
 */

#ifndef _DAEMON_H_
#define _DAEMON_H_

#include <pthread.h>
#include <sys/un.h>
#include <sys/socket.h>

extern int setup_done;
extern int seperate_vendor;

// Commands require connecting to daemon
enum {
	DO_NOTHING = 0,
	SUPERUSER,
	CHECK_VERSION,
	CHECK_VERSION_CODE,
	POST_FS_DATA,
	LATE_START,
	BOOT_COMPLETE,
	LAUNCH_MAGISKHIDE,
	STOP_MAGISKHIDE,
	ADD_HIDELIST,
	RM_HIDELIST,
	LS_HIDELIST,
	HIDE_CONNECT,
	HANDSHAKE
};

// Return codes for daemon
enum {
	DAEMON_ERROR = -1,
	DAEMON_SUCCESS = 0,
	ROOT_REQUIRED,
	LOGCAT_DISABLED,
	HIDE_IS_ENABLED,
	HIDE_NOT_ENABLED,
	HIDE_ITEM_EXIST,
	HIDE_ITEM_NOT_EXIST,
};

typedef enum {
	MAIN_DAEMON,
	LOG_DAEMON
} daemon_t;

// daemon.c

void main_daemon();
int connect_daemon();
int connect_daemon2(daemon_t d, int *sockfd);

// log_monitor.c

void log_daemon();
int check_and_start_logger();

// socket.c

socklen_t setup_sockaddr(struct sockaddr_un *sun, daemon_t d);
int create_rand_socket(struct sockaddr_un *sun);
int socket_accept(int sockfd, int timeout);
int recv_fd(int sockfd);
void send_fd(int sockfd, int fd);
int read_int(int fd);
int read_int_be(int fd);
void write_int(int fd, int val);
void write_int_be(int fd, int val);
char *read_string(int fd);
char *read_string_be(int fd);
void write_string(int fd, const char *val);
void write_string_be(int fd, const char *val);
void write_key_value(int fd, const char *key, const char *val);
void write_key_token(int fd, const char *key, int tok);

/***************
 * Boot Stages *
 ***************/

void startup();
void post_fs_data(int client);
void late_start(int client);
void boot_complete(int client);

/**************
 * MagiskHide *
 **************/

void launch_magiskhide(int client);
void stop_magiskhide(int client);
void add_hide_list(int client);
void rm_hide_list(int client);
void ls_hide_list(int client);

/*************
 * Superuser *
 *************/

void su_daemon_handler(int client, struct ucred *credential);

#endif
