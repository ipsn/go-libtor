/*
 * List of tokens common to V3 authority certificates and V3 consensuses.
 */
  T1("dir-key-certificate-version", K_DIR_KEY_CERTIFICATE_VERSION,
                                                     GE(1),       NO_OBJ ),
  T1("dir-identity-key", K_DIR_IDENTITY_KEY,         NO_ARGS,     NEED_KEY ),
  T1("dir-key-published",K_DIR_KEY_PUBLISHED,        CONCAT_ARGS, NO_OBJ),
  T1("dir-key-expires",  K_DIR_KEY_EXPIRES,          CONCAT_ARGS, NO_OBJ),
  T1("dir-signing-key",  K_DIR_SIGNING_KEY,          NO_ARGS,     NEED_KEY ),
  T1("dir-key-crosscert", K_DIR_KEY_CROSSCERT,       NO_ARGS,     NEED_OBJ ),
  T1("dir-key-certification", K_DIR_KEY_CERTIFICATION,
                                                     NO_ARGS,     NEED_OBJ),
  T01("dir-address",     K_DIR_ADDRESS,              GE(1),       NO_OBJ),
