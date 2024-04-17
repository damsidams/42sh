/*
** EPITECH PROJECT, 2024
** gpt
** File description:
** all function related to gpt feature
*/

#include <stdio.h>
#include <curl/curl.h>
#include "minishell1.h"
#include "my.h"
#include "cJSON.h"
#include <string.h>

static char *json_builder(char *msg)
{
    char *res = NULL;
    char *temp = NULL;
    char *start_json = "{\"model\": \"gpt-3.5-turbo\", \"messages\": [{\"role\": \"user\", \"content\": \"";
    char *end_json = "\"}]}";

    if (msg != NULL)
        temp = my_strcat(start_json, msg);
    else
        temp = my_strcat(start_json, "Hello World");
    res = my_strcat(temp, end_json);
    return res;
}

static size_t callback(char *content, size_t size, size_t nmemb, void *userdata)
{
    size_t total_size = size * nmemb;
    strncat((char *)userdata, content, total_size);
    return total_size;
}

static int parse_json(char *API_respons)
{
    cJSON *root = cJSON_Parse(API_respons);
    cJSON *choices = NULL;
    cJSON *choice = NULL;
    cJSON *message = NULL;
    cJSON *content = NULL;

    if (root == NULL) {
        printf("[ERROR] Unable to parse Json:\n%s\n", (char *)cJSON_GetErrorPtr);
        return ERROR_EXIT;
    }
    choices = cJSON_GetObjectItem(root, "choices");
    if (choices == NULL) {
        printf("[ERROR] Unable to get choices object in Json:\n%s\n", (char *)cJSON_GetErrorPtr);
        return ERROR_EXIT;
    }
    choice = cJSON_GetArrayItem(choices, 0);
    if (choice == NULL) {
        printf("[ERROR] Unable to get choice object in Json:\n%s\n", (char *)cJSON_GetErrorPtr);
        return ERROR_EXIT;
    }
    message = cJSON_GetObjectItem(choice, "message");
    if (message == NULL) {
        printf("[ERROR] Unable to get message object in Json:\n%s\n", (char *)cJSON_GetErrorPtr);
        return ERROR_EXIT;
    }
    content = cJSON_GetObjectItem(message, "content");
    if (message == NULL) {
        printf("[ERROR] Unable to get content object in Json:\n%s\n", (char *)cJSON_GetErrorPtr);
        return ERROR_EXIT;
    }
    printf("%s\n", content->valuestring);
    return SUCCESS_EXIT;
}

void gpt(char **args, shell_info *my_shell)
{
    CURL *curl = curl_easy_init();
    CURLcode res;
    struct curl_slist *header = NULL;
    char *json = NULL;
    char API_respons[JSON_BUFFER_LENGHT] = "\0";
    char *command = args[1];

    if (command == NULL) {
        fprintf(stderr, "[ERROR] No Command Provided\n");
        my_shell->exit_status = ERROR_EXIT;
        return;
    }
    if (curl == NULL) {
        fprintf(stderr, "[ERROR] Unnable to Initialize Curl\n");
        my_shell->exit_status = ERROR_EXIT;
        return;
    }
    json = json_builder(command);
    header = curl_slist_append(header, "Content-Type: application/json");
    header = curl_slist_append(header, "Authorization: Bearer " API_KEY);
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, API_respons);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "[ERROR] Unable to Perform the Request %s\n", curl_easy_strerror(res));
        my_shell->exit_status = ERROR_EXIT;
        return;
    }
    parse_json(API_respons);
    curl_slist_free_all(header);
    curl_easy_cleanup(curl);
    my_shell->exit_status = SUCCESS_EXIT;
    return;
}