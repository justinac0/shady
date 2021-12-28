#include "s_internal.h"

char* s_internal_read_file(const char* file_path) {
    /* Open file stream as read-only */
    FILE* f = fopen(file_path, "r");
	if (f == NULL) return NULL;

    /* Jump to the end of the file */
    fseek(f, 0, SEEK_END);

    /* Get the number of ascii characters in file */
    size_t length = ftell(f);

    /* Set file stream to start */
    rewind(f);

    /* Allocate space for file contents */
    char* contents = (char*) calloc(length, sizeof (char));
    if (contents == NULL) return NULL;

    /* Read file to 'contents' */
    if (fread(contents, sizeof (char), length, f) == 0) return NULL;

    fclose(f);

    return contents;
}

#if !defined(_WIN32)
extern DirShaderInfo s_internal_dir_file_names(const char* file_path) {
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    DirShaderInfo dir_info;
    dir_info.fragment_path = (char*) calloc(MAX_PATH_LENGTH, sizeof (char));
    dir_info.vertex_path   = (char*) calloc(MAX_PATH_LENGTH, sizeof (char));

    if (!(dir = opendir(file_path))) {
        perror("opendir() error");
    } else {
        while ((entry = readdir(dir))) {
            /* TODO: this is dirty and probably dumb; but it does the job :) */
            char* path = (char*) calloc(MAX_PATH_LENGTH, sizeof (char));

            strncat(path, file_path, strlen(file_path));
            strncat(path, "/", 1);
            strncat(path, entry->d_name, strlen(entry->d_name));

            if (entry->d_name[0] == 'f')
                memcpy(dir_info.fragment_path, path, MAX_PATH_LENGTH);

            if (entry->d_name[0] == 'v')
                memcpy(dir_info.vertex_path, path, MAX_PATH_LENGTH);

            free(path);
        }

        closedir(dir);
    }

    return dir_info;
}
#endif