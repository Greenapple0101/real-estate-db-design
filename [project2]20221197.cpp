#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mysql.h"
#include <string.h>

#pragma comment(lib, "libmysql.lib")

const char* host = "127.0.0.1";
const char* user = "root";
const char* pw = "asdf";
const char* db = "project";

void execute_query(MYSQL* connection, const char* query) {
    if (mysql_query(connection, query)) {
        printf("Query execution failed: %s\n", mysql_error(connection));
        return;
    }

    MYSQL_RES* result = mysql_store_result(connection);
    if (result == NULL) {
        printf("Could not retrieve result set\n");
        return;
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    MYSQL_FIELD* fields = mysql_fetch_fields(result);

    // Print column names
    for (int i = 0; i < num_fields; i++) {
        printf("%s\t", fields[i].name);
    }
    printf("\n");

    // Print rows
    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s\t", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(result);
}

int main(void) {
    MYSQL* connection = NULL;
    MYSQL conn;
    if (mysql_init(&conn) == NULL) {
        printf("mysql_init() error!");
        return 1;
    }

    connection = mysql_real_connect(&conn, host, user, pw, db, 3306, NULL, 0);
    if (connection == NULL) {
        printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
        return 1;
    }
    else {
        printf("Connection Succeed\n");

        char query[1000];
        int i, j, k;

        while (1) {
            printf("------- SELECT QUERY TYPES -------\n\n");
            printf("\t1. TYPE 1\n");
            printf("\t2. TYPE 2\n");
            printf("\t3. TYPE 3\n");
            printf("\t4. TYPE 4\n");
            printf("\t5. TYPE 5\n");
            printf("\t6. TYPE 6\n");
            printf("\t7. TYPE 7\n");
            printf("\t0. QUIT\n");
            printf("\nSelect Query type: ");
            scanf("%d", &i);
            getchar(); // 입력 버퍼 비우기
            printf("\n");

            if (i == 0) {
                break;
            }

            switch (i) {
            case 1:
                printf("\n-- TYPE 1: Find address of homes for sale in the district 'Mapo'.\n");
                sprintf(query, "SELECT a.street, a.city, a.district FROM Property p JOIN Address a ON p.address_id = a.address_id WHERE a.district = 'Mapo';");
                execute_query(connection, query);

                while (1) {
                    printf("\n------- Subtypes in TYPE I -------\n\n");
                    printf("\t1. TYPE I-1\n");
                    printf("If you want to quit, input 0, please press enter after input number\n");
                    printf("Select subtype: ");
                    scanf("%d", &j);
                    getchar(); // 입력 버퍼 비우기
                    printf("\n");

                    if (j == 0) {
                        break;
                    }

                    switch (j) {
                    case 1:
                        printf("\n-- TYPE 1-1: Then find the costing between ￦1,000,000,000 and ￦1,500,000,000.\n");
                        sprintf(query, "SELECT a.street, a.city, a.district, p.property_price FROM Property p JOIN Address a ON p.address_id = a.address_id WHERE a.district = 'Mapo' AND p.property_price BETWEEN 1000000000 AND 1500000000;");
                        execute_query(connection, query);
                        printf("\n");
                        break;
                    default:
                        printf("wrong selection\n\n");
                        break;
                    }
                }
                break;

            case 2:
                printf("\n-- TYPE 2: Find the address of homes for sale in the 8th school district.\n");
                sprintf(query, "SELECT a.street, a.city, a.district FROM Property p JOIN Address a ON p.address_id = a.address_id WHERE p.school_district = '8th';");
                execute_query(connection, query);

                while (1) {
                    printf("\n------- Subtypes in TYPE II -------\n\n");
                    printf("\t1. TYPE II-1\n");
                    printf("If you want to quit, input 0, please press enter after input number\n");
                    printf("Select subtype: ");
                    scanf("%d", &j);
                    getchar(); // 입력 버퍼 비우기
                    printf("\n");

                    if (j == 0) {
                        break;
                    }

                    switch (j) {
                    case 1:
                        printf("\n-- TYPE 2-1: Then find properties with 4 or more bedrooms and 2 bathrooms.\n");
                        sprintf(query, "SELECT a.street, a.city, a.district, p.property_bedroom, p.property_bathroom FROM Property p JOIN Address a ON p.address_id = a.address_id WHERE p.school_district = '8th' AND p.property_bedroom >= 4 AND p.property_bathroom >= 2;");
                        execute_query(connection, query);
                        printf("\n");
                        break;
                    default:
                        printf("wrong selection\n\n");
                        break;
                    }
                }
                break;

            case 3:
                printf("\n-- TYPE 3: Find the name of the agent who has sold the most properties in the year 2022 by total won value.\n");
                sprintf(query, "SELECT a.agent_name, SUM(s.sale_price) AS total_value FROM Agent a JOIN Sale s ON a.agent_id = s.agent_id WHERE YEAR(s.sale_date) = 2022 GROUP BY a.agent_name ORDER BY total_value DESC LIMIT 1;");
                execute_query(connection, query);

                while (1) {
                    printf("\n------- Subtypes in TYPE III -------\n\n");
                    printf("\t1. TYPE III-1\n");
                    printf("\t2. TYPE III-2\n");
                    printf("If you want to quit, input 0, please press enter after input number\n");
                    printf("Select subtype: ");
                    scanf("%d", &j);
                    getchar(); // 입력 버퍼 비우기
                    printf("\n");

                    if (j == 0) {
                        break;
                    }

                    switch (j) {
                    case 1:
                        printf("** Find the top k agents in the year 2023 by total won value **\n");
                        printf("Enter value for k: ");
                        scanf("%d", &k);
                        getchar(); // 입력 버퍼 비우기
                        sprintf(query, "SELECT a.agent_name, SUM(s.sale_price) AS total_value FROM Agent a JOIN Sale s ON a.agent_id = s.agent_id WHERE YEAR(s.sale_date) = 2023 GROUP BY a.agent_name ORDER BY total_value DESC LIMIT %d;", k);
                        execute_query(connection, query);
                        printf("\n");
                        break;
                    case 2:
                        printf("** Find the bottom 10%% agents in the year 2021 by total won value **\n");
                        sprintf(query, "SELECT agent_name, total_value FROM (SELECT a.agent_name, SUM(s.sale_price) AS total_value, PERCENT_RANK() OVER (ORDER BY SUM(s.sale_price)) AS `rank` FROM Agent a JOIN Sale s ON a.agent_id = s.agent_id WHERE YEAR(s.sale_date) = 2021 GROUP BY a.agent_name) ranked_agents WHERE `rank` <= 0.1;");
                        execute_query(connection, query);
                        printf("\n");
                        break;
                    default:
                        printf("wrong selection\n\n");
                        break;
                    }
                }
                break;


            case 4:
                printf("\n-- TYPE 4: Compute the average selling price of properties sold in 2022, and the average time the property was on the market for each agent.\n");
                sprintf(query, "SELECT a.agent_name, AVG(s.sale_price) AS avg_selling_price_2022, AVG(DATEDIFF(s.sale_date, p.list_date)) AS avg_time_on_market_2022 FROM agent a JOIN sale s ON a.agent_id = s.agent_id JOIN property p ON s.property_id = p.property_id WHERE YEAR(s.sale_date) = 2022 GROUP BY a.agent_name;");
                execute_query(connection, query);

                while (1) {
                    printf("\n------- Subtypes in TYPE IV -------\n\n");
                    printf("\t1. TYPE IV-1\n");
                    printf("\t2. TYPE IV-2\n");
                    printf("If you want to quit, input 0, please press enter after input number\n");
                    printf("Select subtype: ");
                    scanf("%d", &j);
                    getchar(); // 입력 버퍼 비우기
                    printf("\n");

                    if (j == 0) {
                        break;
                    }

                    switch (j) {
                    case 1:
                        printf("** Compute the maximum selling price of properties sold in 2023 for each agent **\n");
                        sprintf(query, "SELECT a.agent_name, MAX(s.sale_price) AS max_selling_price_2023 FROM agent a JOIN sale s ON a.agent_id = s.agent_id WHERE YEAR(s.sale_date) = 2023 GROUP BY a.agent_name;");
                        execute_query(connection, query);
                        printf("\n");
                        break;
                    case 2:
                        printf("** Compute the longest time the property was on the market for each agent **\n");
                        sprintf(query, "SELECT a.agent_name, MAX(DATEDIFF(s.sale_date, p.list_date)) AS longest_time_on_market FROM agent a JOIN sale s ON a.agent_id = s.agent_id JOIN property p ON s.property_id = p.property_id GROUP BY a.agent_name;");
                        execute_query(connection, query);
                        printf("\n");
                        break;
                    default:
                        printf("wrong selection\n\n");
                        break;
                    }
                }
                break;


            case 5:
                while (1) {
                    printf("\n-- TYPE 5: Show photos of the most expensive studio, one-bedroom, multi-bedroom apartment(s), and detached house(s).\n");
                    sprintf(query, "SELECT pr.type, ph.description FROM Property pr JOIN Photo ph ON pr.property_id = ph.property_id WHERE pr.property_price = (SELECT MAX(property_price) FROM Property WHERE type = 'studio') OR pr.property_price = (SELECT MAX(property_price) FROM Property WHERE type = 'one-bedroom') OR pr.property_price = (SELECT MAX(property_price) FROM Property WHERE type = 'multi-bedroom') OR pr.property_price = (SELECT MAX(property_price) FROM Property WHERE type = 'detached house');");
                    execute_query(connection, query);
                    printf("\n");

                    // Ask the user if they want to perform another query of the same type
                    printf("If you want to quit, input 0, please press enter after input number\n");
                    int exit_choice;
                    scanf("%d", &exit_choice);
                    getchar(); // 입력 버퍼 비우기
                    if (exit_choice == 0) {
                        break;
                    }
                }
                break;

            default:
                printf("wrong selection\n");
                break;


            case 6:
                printf("\n-- TYPE 6: Record the sale of a property that had been listed as being available.\n");
                printf("Enter property ID: ");
                int property_id;
                scanf("%d", &property_id);
                getchar(); // 입력 버퍼 비우기

                printf("Enter sale price: ");
                double sale_price;
                scanf("%lf", &sale_price);
                getchar(); // 입력 버퍼 비우기

                printf("Enter buyer ID: ");
                int buyer_id;
                scanf("%d", &buyer_id);
                getchar(); // 입력 버퍼 비우기

                printf("Enter selling agent ID: ");
                int selling_agent_id;
                scanf("%d", &selling_agent_id);
                getchar(); // 입력 버퍼 비우기

                printf("Enter buyer agent ID (or 0 if none): ");
                int buyer_agent_id;
                scanf("%d", &buyer_agent_id);
                getchar(); // 입력 버퍼 비우기

                printf("Enter sale date (YYYY-MM-DD): ");
                char sale_date[11];
                scanf("%s", sale_date);
                getchar(); // 입력 버퍼 비우기

                // Update property status
                sprintf(query, "UPDATE Property SET status = 'sold' WHERE property_id = %d;", property_id);
                if (mysql_query(connection, query)) {
                    printf("Query execution failed: %s\n", mysql_error(connection));
                    break;
                }

                // Insert into sales
                if (buyer_agent_id == 0) {
                    sprintf(query, "INSERT INTO Sale (property_id, buyer_id, seller_id, agent_id, sale_price, sale_date) VALUES (%d, %d, %d, %d, %.2f, '%s');",
                        property_id, buyer_id, selling_agent_id, selling_agent_id, sale_price, sale_date);
                }
                else {
                    sprintf(query, "INSERT INTO Sale (property_id, buyer_id, seller_id, agent_id, sale_price, sale_date) VALUES (%d, %d, %d, %d, %.2f, '%s');",
                        property_id, buyer_id, selling_agent_id, buyer_agent_id, sale_price, sale_date);
                }

                if (mysql_query(connection, query)) {
                    printf("Query execution failed: %s\n", mysql_error(connection));
                    break;
                }
                else {
                    printf("Sale recorded successfully\n");
                }
                printf("\n");
                break;




            case 7:
                printf("\n-- TYPE 7: Add a new agent to the database.\n");
                printf("Enter agent name: ");
                char name[100];
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                printf("Enter agent contact: ");
                char contact[100];
                fgets(contact, sizeof(contact), stdin);
                contact[strcspn(contact, "\n")] = '\0';

                // Insert into agents
                sprintf(query, "INSERT INTO Agent (agent_name, agent_contact) VALUES ('%s', '%s');", name, contact);
                if (mysql_query(connection, query)) {
                    printf("Query execution failed: %s\n", mysql_error(connection));
                }
                else {
                    printf("Agent added successfully\n");
                }
                break;





            }
        }
    }

    mysql_close(connection);
    return 0;
}
