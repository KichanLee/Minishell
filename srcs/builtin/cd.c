#include "../incs/minishell.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void change_directory(const char *directory) {
    if (chdir(directory) != 0) {
        perror("cd");
    }
}

int main() {
    char *input = NULL;
    size_t input_size = 0;

    while (1) {
        printf("Enter directory: ");
        ssize_t input_length = getline(&input, &input_size, stdin);

        if (input_length == -1) {
            perror("getline");
            break;
        }

        // 개행 문자 제거
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        } else if (strncmp(input, "cd ", 3) == 0) {
            // "cd "로 시작하는 명령어만 처리
            const char *directory = input + 3;

            pid_t child_pid = fork();
            if (child_pid == -1) {
                perror("fork");
                break;
            } else if (child_pid == 0) {
                // 자식 프로세스에서 디렉토리 변경
                change_directory(directory);
                break;
            } else {
                // 부모 프로세스에서 자식 프로세스가 종료될 때까지 대기
                waitpid(child_pid, NULL, 0);
                char cwd[1024];
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                    printf("Current directory: %s\n", cwd);
                } else {
                    perror("getcwd");
                }
            }
        } else {
            printf("Unknown command.\n");
        }
    }

    free(input);
    return 0;
}
