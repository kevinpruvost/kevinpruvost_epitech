/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *identify_msg(char type, char app_domain, short int msg)
{
    char *str = NULL;
    char nutrition[3][2][15] = {{{"Eat"}, {"Defecate"}}, {{"Hungry"}, \
            {"Thirsty"}}, {{"Indigestion"}, {"Starving"}}};
    char entert[3][3][15] = {{{"Ball"}, {"Bite"}, {""}}, {{"NeedAffection"}, \
            {"Wanna play"}, {"Hug"}}, {{"Bored"}, {""}, {""}}};
    char educ[3][2][15] = {{{"TeachCoding"}, {"BeAwesome"}}, \
            {{"FeelStupid"}, {""}}, {{"BrainDamage"}, {""}}};

    (type == 4) ? (--type) : (0);
    (app_domain == 1) ? (str = nutrition[type-1][msg-1]) : (0);
    (app_domain == 2) ? (str = entert[type-1][msg-1]) : (0);
    (app_domain == 4) ? (str = educ[type-1][msg-1]) : (0);
    printf("%s", str);
    return (str);
}

void print_message(char type, char app_domain, short int msg, const char *cnt)
{
    const char types[5][15] = {\
        {""}, {"Notification"}, {"Request"}, {""}, {"Error"}\
    };
    const char domains[5][15] = {\
        {""}, {"Nutrition"}, {"Entertainment"}, {""}, {"Education"}\
    };

    printf("%s %s ", types[type], domains[app_domain]);
    identify_msg(type, app_domain, msg);
    if (cnt == NULL)
        printf("\n");
    else
        printf(" %s\n", cnt);
}

int prettyprint_message(uint32_t header, const char *content)
{
    char message_type = header >> 4 * 6;
    char app_domain = header >> 4 * 4;
    short int message = (header & 1) ? (1) : (0);

    (header & 2) ? (message = 2) : (0);
    (app_domain & 1) ? (app_domain = 1) : (0);
    (app_domain & 2) ? (app_domain = 2) : (0);
    (app_domain & 4) ? (app_domain = 4) : (0);
    if (message_type == 0 || app_domain == 0 || message == 0) {
        printf("Invalid message.\n");
        return (1);
    }
    print_message(message_type, app_domain, message, content);
    return (0);
}