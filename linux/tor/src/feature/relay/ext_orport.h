/* Copyright (c) 2001 Matej Pfajfar.
 * Copyright (c) 2001-2004, Roger Dingledine.
 * Copyright (c) 2004-2006, Roger Dingledine, Nick Mathewson.
 * Copyright (c) 2007-2019, The Tor Project, Inc. */
/* See LICENSE for licensing information */

#ifndef EXT_ORPORT_H
#define EXT_ORPORT_H

/** States of the Extended ORPort protocol. Be careful before changing
 *  the numbers: they matter. */
#define EXT_OR_CONN_STATE_MIN_ 1
/** Extended ORPort authentication is waiting for the authentication
 *  type selected by the client. */
#define EXT_OR_CONN_STATE_AUTH_WAIT_AUTH_TYPE 1
/** Extended ORPort authentication is waiting for the client nonce. */
#define EXT_OR_CONN_STATE_AUTH_WAIT_CLIENT_NONCE 2
/** Extended ORPort authentication is waiting for the client hash. */
#define EXT_OR_CONN_STATE_AUTH_WAIT_CLIENT_HASH 3
#define EXT_OR_CONN_STATE_AUTH_MAX 3
/** Authentication finished and the Extended ORPort is now accepting
 *  traffic. */
#define EXT_OR_CONN_STATE_OPEN 4
/** Extended ORPort is flushing its last messages and preparing to
 *  start accepting OR connections. */
#define EXT_OR_CONN_STATE_FLUSHING 5
#define EXT_OR_CONN_STATE_MAX_ 5

int connection_ext_or_start_auth(or_connection_t *or_conn);

ext_or_cmd_t *ext_or_cmd_new(uint16_t len);

#define ext_or_cmd_free(cmd)                            \
  FREE_AND_NULL(ext_or_cmd_t, ext_or_cmd_free_, (cmd))

void ext_or_cmd_free_(ext_or_cmd_t *cmd);
void connection_or_set_ext_or_identifier(or_connection_t *conn);
void connection_or_remove_from_ext_or_id_map(or_connection_t *conn);
void connection_or_clear_ext_or_id_map(void);
or_connection_t *connection_or_get_by_ext_or_id(const char *id);

int connection_ext_or_finished_flushing(or_connection_t *conn);
int connection_ext_or_process_inbuf(or_connection_t *or_conn);

int init_ext_or_cookie_authentication(int is_enabled);
char *get_ext_or_auth_cookie_file_name(void);
void ext_orport_free_all(void);

#ifdef EXT_ORPORT_PRIVATE
STATIC int connection_write_ext_or_command(connection_t *conn,
                                           uint16_t command,
                                           const char *body,
                                           size_t bodylen);
STATIC int handle_client_auth_nonce(const char *client_nonce,
                         size_t client_nonce_len,
                         char **client_hash_out,
                         char **reply_out, size_t *reply_len_out);
#ifdef TOR_UNIT_TESTS
extern uint8_t *ext_or_auth_cookie;
extern int ext_or_auth_cookie_is_set;
#endif
#endif /* defined(EXT_ORPORT_PRIVATE) */

#endif /* !defined(EXT_ORPORT_H) */
