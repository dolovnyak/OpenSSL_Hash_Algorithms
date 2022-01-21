#include "defenitions.h"

void print_empty_arg_usage() {
    printf("usage: ft_ssl command [flags] [file/string]\n");
}

void print_command_usage(const char *command) {
    printf("ft_ssl: Error: \'%s\' is an invalid command\n", command);
    printf("\n%s", basic_usage);
}

void print_flag_usage(const char *flag) {
    printf("ft_ssl: Error: \'%s\' invalid flag\n", flag);
    printf("\n%s", basic_usage);
}

void print_few_argument_usage() {
    printf("Only one argument [file/string] allowed\n");
    printf("\n%s", basic_usage);
}

void print_s_without_arg_usage() {
    printf("option \'-s\' requires an argument\n");
}

void init_structs(t_preprocessed_data *preprocessed_data, t_ssl_data *ssl_data) {
    preprocessed_data->argument_string = NULL;
    bzero(preprocessed_data->flags, sizeof(preprocessed_data->flags));

    ssl_data->input_ssl_data = NULL;
    bzero(ssl_data->flags, sizeof(ssl_data->flags));
}

bool input_preprocessing(int argc, char **argv,
                         t_preprocessed_data *preprocessed_data, t_ssl_algorithm *ssl_algorithm) {
    if (argc == 1) {
        print_empty_arg_usage();
        return false;
    }

    if (strcmp(argv[1], "md5") == 0) {
        ssl_algorithm->preprocessing_ssl_data = basic_data_preprocessing;
        ssl_algorithm->hash_data = md5_algorithm;
    }
    else if (strcmp(argv[1], "sha256") == 0) {
        ssl_algorithm->preprocessing_ssl_data = basic_data_preprocessing;
        ssl_algorithm->hash_data = sha256_algorithm;
    }
    else {
        print_command_usage(argv[1]);
        return false;
    }

    int i;
    for (i = 2; i < argc; ++i) {
        if (strcmp(argv[i], "-p") == 0) {
            preprocessed_data->flags[k_p_flag] = true;
        }
        else if (strcmp(argv[i], "-q") == 0) {
            preprocessed_data->flags[k_q_flag] = true;
        }
        else if (strcmp(argv[i], "-r") == 0) {
            preprocessed_data->flags[k_r_flag] = true;
        }
        else if (strcmp(argv[i], "-s") == 0) {
            preprocessed_data->flags[k_s_flag] = true;
        }
        else if (strlen(argv[i]) == 0 || argv[i][0] == '-') {
            print_flag_usage(argv[i]);
            return false;
        }
        else {
            break;
        }
    }

    if (i + 1 < argc) {
        print_few_argument_usage();
        return false;
    }
    if (i < argc) {
        preprocessed_data->argument_string = strdup(argv[i]);
    }
    return true;
}

bool input_processing(t_preprocessed_data preprocessed_data, t_ssl_data *ssl_data) {
    memcpy(ssl_data->flags, preprocessed_data.flags, k_flags_number);
    int fd;

    /// not empty data
    if (preprocessed_data.argument_string != NULL) {
        if (preprocessed_data.flags[k_s_flag]) {
            /// processing from string
            ssl_data->input_ssl_data = preprocessed_data.argument_string;
            preprocessed_data.argument_string = NULL;
        }
        else {
            /// processing from file
            fd = open(preprocessed_data.argument_string, O_RDONLY);
            if (fd < 0) {
                perror(preprocessed_data.argument_string);
                return false;
            }
            if (!read_file(fd, &ssl_data->input_ssl_data, &ssl_data->input_ssl_data_size)) {
                perror(preprocessed_data.argument_string);
            }
        }
        return true;
    }

    /// empty data
    if (preprocessed_data.flags[k_s_flag]) {
        print_s_without_arg_usage();
        return false;
    }

    /// processing from stdin
    if (!read_file(0, &ssl_data->input_ssl_data, &ssl_data->input_ssl_data_size)) {
        perror(preprocessed_data.argument_string);
    }
    return true;
}

int main(int argc, char **argv) {
    t_preprocessed_data preprocessed_data;
    t_ssl_data ssl_data;
    t_ssl_algorithm ssl_algorithm;

    init_structs(&preprocessed_data, &ssl_data);

    if (!input_preprocessing(argc, argv, &preprocessed_data, &ssl_algorithm)) {
        exit(0);
    }
    if (!input_processing(preprocessed_data, &ssl_data)) {
        exit(0);
    }

//    ssl_algorithm.preprocessing_ssl_data(&ssl_data);
//    printf("%s\n", ssl_algorithm.hash_data(&ssl_data));
    exit(0);
}
