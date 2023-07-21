// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// char **sort_bubble(char **str)
// {
//     char **res = (char **)malloc(sizeof(char *) * (5 + 1)); // 마지막에 NULL 포인터를 위해 추가 공간 할당
//     if (!res)
//     {
//         perror("Memory allocation error!");
//         exit(1);
//     }

//     // 입력된 문자열 포인터 배열을 결과 배열에 복사합니다.
//     int i = 0;
//     while (str[i])
//     {
//         printf("while loop start!\n");
//         printf("str[i] : %s\n", str[i]);
//         res[i] = strdup(str[i]);
//         if (!res[i])
//         {
//             perror("Memory allocation error!");
//             exit(1);
//         }
//         ++i;
//     }
//     res[i] = NULL; 

//     int sorted = 0; 
//     while (!sorted)
//     {
//         sorted = 1;
//         i = 0;
//         while (res[i + 1]) 
//         {
//             if (strcmp(res[i], res[i + 1]) > 0)
//             {
//                 char *tmp = res[i];
//                 res[i] = res[i + 1];
//                 res[i + 1] = tmp;
//                 sorted = 0;
//             }
//             ++i;
//         }
//     }

//     return res;
// }

// int main()
// {
//     char **str;
//     char **res;
//     int i = 0;


//     str[0] = "abc";
//     str[1] = "bbc";
//     str[2] = "cba";
//     str[3] = "aabcd";
//     str[4] = "sdfb";
//     str[5] = NULL;
//     res = sort_bubble(str);
    
//     while (res[i])
//     {
//         printf("%s\n", res[i]);
//         ++i;
//     }
//     return (0);
// }