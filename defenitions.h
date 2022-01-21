#ifndef DEFENITIONS_H
#define DEFENITIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/fcntl.h>



#define BUFFER_SIZE 128

static const char *basic_usage = "Commands:\n"
                                 "md5\n"
                                 "sha256\n"
                                 "\n"
                                 "Flags:\n"
                                 "-p -q -r -s\n";

static const int k_flags_number = 4;

enum e_flag {
    k_p_flag = 0,
    k_q_flag,
    k_r_flag,
    k_s_flag
};

typedef struct  s_preprocessed_data {
    char        *argument_string;
    bool        flags[k_flags_number];
}               t_preprocessed_data;

typedef struct  s_ssl_data {
    char        *input_ssl_data;
    size_t      input_ssl_data_size;
    bool        flags[k_flags_number];
}               t_ssl_data;

typedef struct  s_ssl {
    void        (*preprocessing_ssl_data)(t_ssl_data *ssl_data);
    char        *(*hash_data)(const t_ssl_data *ssl_data);
}               t_ssl_algorithm;


void basic_data_preprocessing(t_ssl_data *ssl_data);
char *sha256_algorithm(const t_ssl_data *ssl_data);
char *md5_algorithm(const t_ssl_data *ssl_data);
bool read_file(int fd, char **str, size_t *f_size);

#endif // DEFENITIONS_H
