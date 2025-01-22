#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

struct Database {
    unsigned int max_data;
    unsigned int max_rows;
    struct Address **rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void die(struct Connection *conn,const char *message);
void Address_print(struct Address *addr);
void Database_load(struct Connection *conn);
struct Connection *Database_open(const char *filename, char mode);
void Database_close(struct Connection *conn);
void Database_write(struct Connection *conn);
void Database_create(struct Connection *conn, unsigned int max_data, unsigned int max_rows);
void Database_set(struct Connection *conn, int id, const char *name, const char *email);
void Database_get(struct Connection *conn, int id);
void Database_delete(struct Connection *conn, int id);
void Database_list(struct Connection *conn);
void Database_find(struct Connection *conn, const char *name);



void die(struct Connection *conn,const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("Error: %s\n", message);
    }
    Database_close(conn);
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    int i = 0;
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) die(conn,"Failed to load database.");
    conn->db->rows = malloc(sizeof(struct Address *) * conn->db->max_rows);
    if(conn->db->rows == NULL) die(conn,"Failed to malloc rows database.");
    // for(i = 0; i < conn->db->max_rows; i++) {
    //     conn->db->rows[i] = malloc(sizeof(struct Address *));
    //     if(conn->db->rows[i] == NULL) die(conn," conn->db->rows[i] Memory error");
    // }

    if(conn->db->rows == NULL) die(conn,"Memory error");

    for(i = 0; i < conn->db->max_rows; i++) {
        struct Address *addr = malloc(sizeof(struct Address));
        if(addr == NULL) die(conn,"Memory error");
        addr->name = malloc(conn->db->max_data);
        if(addr->name == NULL) die(conn," addr->name Memory error");
        addr->email = malloc(conn->db->max_data);
        if(addr->email == NULL) die(conn," addr->email Memory error");

        rc = fread((void *)&addr->id, sizeof(addr->id), 1, conn->file);
        if(rc != 1) die(conn,"Failed to load addr->id.");
        rc = fread((void *)&addr->set, sizeof(addr->set), 1, conn->file);
        if(rc != 1) die(conn,"Failed to load addr->set.");
        rc = fread((void *)addr->name, conn->db->max_data, 1, conn->file);
        if(rc != 1) die(conn,"Failed to load addr->name.");
        rc = fread((void *)addr->email, conn->db->max_data, 1, conn->file);
        if(rc != 1) die(conn,"Failed to load addr->email.");

        conn->db->rows[i] = addr;
    }
}

struct Connection *Database_open(const char *filename, char mode)
{
    char error_message[25] = "Memory error";
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(conn == NULL) {
        memcpy(error_message, "Memory error", 25);
        goto fail1;
    }
    conn->db = malloc(sizeof(struct Database));
    if(conn->db == NULL) {
        memcpy(error_message, "Memory error", 25);
        goto fail1;
    }
    if(mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if(conn->file) {
            Database_load(conn);
        }
    }

    if(conn->file == NULL) {
        memcpy(error_message, "Failed to open the file", 25);
        goto fail1;
    }
    return conn;

fail1:
    die(conn,error_message);
    //die will exit the program
    return NULL;
}


void Database_close(struct Connection *conn)
{
    if(conn != NULL) {
        if(conn->file != NULL) fclose(conn->file);

        if(conn->db != NULL) {
            if(conn->db->rows != NULL) {
                for(int i = 0; i < conn->db->max_rows; i++) {
                    struct Address *addr = conn->db->rows[i];
                    if(addr != NULL) {
                        if(addr->name != NULL) free(addr->name);
                        if(addr->email != NULL) free(addr->email);
                        free(addr);
                    }
                }
            }
            free(conn->db->rows);
            free(conn->db);
        }
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    char error_message[25] = "Memory error";
    int i = 0;
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) {
        memcpy(error_message, "Failed to write database", 25);
        goto fail1;
    }

    for(i = 0; i < conn->db->max_rows; i++) {
        struct Address *addr = conn->db->rows[i];

        rc = fwrite((void *)&addr->id, sizeof(addr->id), 1, conn->file);
        if(rc != 1) {
            memcpy(error_message, "Failed to write id address", 25);
            goto fail1;
        }
        rc = fwrite((void *)&addr->set, sizeof(addr->set), 1, conn->file);
        if(rc != 1) {
            memcpy(error_message, "Failed to write set address", 25);
            goto fail1;
        }
        rc = fwrite(addr->name, conn->db->max_data, 1, conn->file);
        if(rc != 1) {
            memcpy(error_message, "Failed to write name address", 25);
            goto fail1;
        }
        rc = fwrite(addr->email, conn->db->max_data, 1, conn->file);
        if(rc != 1) {
            memcpy(error_message, "Failed to write email address", 25);
            goto fail1;
        }
    }

    rc = fflush(conn->file);
    if(rc == -1) {
        memcpy(error_message, "Cannot flush database", 25);
        goto fail1;
    }
    return;

fail1:
    die(conn,error_message);
}

void Database_create(struct Connection *conn, unsigned int max_data, unsigned int max_rows)
{
    int i = 0;
    conn->db->max_data = max_data;
    conn->db->max_rows = max_rows;
    conn->db->rows = malloc(sizeof(struct Address *) * max_rows);
    if(conn->db->rows == NULL) die(conn,"conn->db->rows Memory error");

    for(i = 0; i < max_rows; i++) {
        struct Address *tmp = malloc(sizeof(struct Address));
        if(tmp == NULL) die(conn,"tmp Memory error");
        tmp->name = malloc(max_data);
        memset(tmp->name, 0, max_data);
        if(tmp->name == NULL) die(conn,"tmp->name Memory error");
        tmp->email = malloc(max_data);
        memset(tmp->email, 0, max_data);
        if(tmp->email == NULL) die(conn,"tmp->email Memory error");
        tmp->id = i;
        tmp->set = 0;
        conn->db->rows[i] = tmp;
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = conn->db->rows[id];
    if(addr->set) die(conn,"Already set, delete it first");

    addr->set = 1;
    char *res = strncpy(addr->name, name, conn->db->max_data);
    if(!res) die(conn,"Name copy failed");

    res = strncpy(addr->email, email, conn->db->max_data);
    if(!res) die(conn,"Email copy failed");
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = conn->db->rows[id];

    if(addr->set) {
        Address_print(addr);
    } else {
        die(conn,"ID is not set");
    }
}

void Database_delete(struct Connection *conn, int id)
{
    struct Address *addr = conn->db->rows[id];
    addr->set = 0;
}

void Database_find(struct Connection *conn, const char *name)
{
    int i = 0;
    for(i = 0; i < conn->db->max_rows; i++) {
        struct Address *addr = conn->db->rows[i];
        if(addr->set && strcmp(addr->name, name) == 0) {
            Address_print(addr);
            return;
        }
    }
    printf("Not found name:\"%s\"\n",name);
}

void Databale_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for(i = 0; i < conn->db->max_rows; i++) {
        struct Address *cur = db->rows[i];

        if(cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc < 3) die(NULL,"USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    if(action != 'c') {
        printf("load file \"%s\" ok, max_data=%d, max_rows=%d\n",filename,conn->db->max_data,conn->db->max_rows);
    }

    int id = 0;
    unsigned int max_data = 0;
    unsigned int max_rows = 0;
    if(argc > 3) id = atoi(argv[3]);
    if(action != 'c' && id >= conn->db->max_rows) die(conn,"There's not that many records.");

    switch(action) {
        case 'c':
            if(argc != 5) die(conn,"Need id, name, email to set");
            max_data = atoi(argv[3]);
            max_rows = atoi(argv[4]);
            Database_create(conn, max_data, max_rows);
            Database_write(conn);
            break;
        case 'g':
            if(argc != 4) die(conn,"Need an id to get");
            Database_get(conn, id);
            break;

        case 's':
            if(argc != 6) die(conn,"Need id, name, email to set");
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if(argc != 4) die(conn,"Need id to delete");
            Database_delete(conn, id);
            Database_write(conn);
            break;
        case 'f':
            //such as build/ex17_1 db.dat f cai
            if(argc != 4) die(conn,"Need name to find");
            Database_find(conn, argv[3]);
            Database_write(conn);
            break;

        case 'l':
            Databale_list(conn);
            break;

        default:
            die(conn,"Invalid action, only: c=create, g=get, s=set, d=del, l=list");

    }


    Database_close(conn);

    return 0;
}