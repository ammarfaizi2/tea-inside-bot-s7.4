
#include <my_pcre.h>

void my_pcre_res_destroy(pcre_res *result)
{
    for (int i = 0; i < result->count; ++i) {
        free(result->r[i]);
    }
    free(result->r);
}

pcre2_code *my_pcre_compile(const unsigned char *pattern)
{
    int err_number;
    pcre2_code *re;
    PCRE2_SIZE err_offset;
    re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, 0, &err_number, &err_offset, NULL);
    if (re == NULL) {
        PCRE2_UCHAR8 buffer[256];
        pcre2_get_error_message(err_number, buffer, sizeof(buffer));
        printf("PCRE2 compilation failed at offset %d: %s\n", (int)err_offset, buffer);
    }
    return re;
}

int my_pcre_find(pcre2_code *re, const unsigned char *subject, pcre_res* result)
{
    size_t subject_length;
    PCRE2_SIZE *ovector;
    pcre2_match_data *match_data = NULL;
    int rc;

    subject_length = strlen((char *)subject);
    match_data = pcre2_match_data_create_from_pattern(re, NULL);
    rc = pcre2_match(re, subject, subject_length, 0, 0, match_data, NULL);

    if ((rc < 0) || (result == NULL)) {
        switch (rc) {
            case PCRE2_ERROR_NOMATCH:
                rc = 0;
                break;
            default:
                break;
        }
        goto ret;
    }

    result->r = (char **)malloc(sizeof(char *) * (rc + 1));
    ovector = pcre2_get_ovector_pointer(match_data);

    for (int i = 0; i < rc; i++) {
        PCRE2_SPTR substr_start = subject + ovector[2*i];
        size_t substr_length = ovector[2*i+1] - ovector[2*i];
        result->r[i] = (char *)malloc(sizeof(char) * (substr_length + 1));
        memcpy(result->r[i], substr_start, substr_length);
    }

ret:
    if (re != NULL) {
        pcre2_match_data_free(match_data);
    }
    if (re != NULL) {
        pcre2_code_free(re);
    }
    if (result != NULL) {
        result->count = rc;
    }
    return rc;
}
