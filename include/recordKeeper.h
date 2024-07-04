#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#ifndef RECORDKEEPER_H
#define RECORDKEEPER_H

typedef struct Entry
{
    const char *key;
    int value;
} Entry;

typedef struct RecordKeeper
{
    const char *dir;
    const char *filename;
    Entry entries[3];
    size_t size;
} RecordKeeper;

void writeSettings(RecordKeeper *keeper)
{
    FILE *f = fopen(TextFormat("%s\\%s", keeper->dir, keeper->filename), "w");
    for (size_t i = 0; i < keeper->size; i++)
    {
        Entry entry = keeper->entries[i];
        fprintf(f, "%s:%d\n", entry.key, entry.value);
    }
    fclose(f);
}

void readSettings(RecordKeeper *keeper)
{
    struct stat stats;
    if (stat(keeper->dir, &stats) != 0 || !S_ISDIR(stats.st_mode))
    { // Directory does not exist
        mkdir(keeper->dir);
        writeSettings(keeper);
        return;
    }

    FILE *f = fopen(TextFormat("%s\\%s", keeper->dir, keeper->filename), "r");
    if (f != NULL)
    {

        // read from file 255 bytes at a time
        int size = 0;
        char *content = (char *)malloc(0xff);
        strcpy(content, "");
        char *c2 = (char *)malloc(0xff);
        while (fread(c2, 1, 0xff, f) != 0)
        {
            size += 0xff;
            content = (char *)realloc(content, size);
            strcat(content, c2);
        }
        free(c2);
        const char *delim2 = ":\n";
        for (int i = 0; i < keeper->size; i++)
        {
            Entry* entry = &(keeper->entries[i]);
            char *token;
            
            if (i == 0)
            {
                token = strtok(content, delim2);
            }
            else
            {
                token = strtok(NULL, delim2);
            }

            if (token == NULL || strcmp(token, entry->key) != 0)
            {
                // printf("%s does not match entry %s, override immediately;", token, entry->key);
                // token does not match entry key, override immediately;
                writeSettings(keeper);
                return;
            }
            token = strtok((char *)NULL, delim2);
            if (token == NULL)
            {
                // token is null, override immediately;
                // printf("token is null, override immediately;");
                writeSettings(keeper);
                return;
            }
            puts(token);
            int value = atoi(token);
            if (0 > value || 100 < value)
            {
                // printf("value does not fit setting critera, override immediately;");
                // value does not fit setting critera, override immediately;
                writeSettings(keeper);
                return;
            }
            entry->value = value;
        }
        free(content);
        fclose(f);
    }
    else
    {
        writeSettings(keeper);
    }
}

// creates a new settign manager with the given setting name
RecordKeeper newSettingManager(const char *filename)
{
    const char *dir = "settings";
    RecordKeeper keeper = (RecordKeeper){dir, filename, {{"Volume", 100}, {"Narration", 100}, {"YapVolume", 100}}, 3};
    readSettings(&keeper);
    return keeper;
}

// get the value of the given key, returns NULL if keeper does not have the entry
int getRecordValue(RecordKeeper *keeper, const char *key)
{
    for (size_t i = 0; i < keeper->size; i++)
    {
        Entry entry = keeper->entries[i];
        if (strcmp(entry.key, key) == 0)
        {
            return entry.value;
        }
    }
    return (int)NULL;
}

// set the value of the given key to the given value, returns NULL if keeper does not have the entry
int setRecordValue(RecordKeeper *keeper, const char *key, int val)
{
    for (size_t i = 0; i < keeper->size; i++)
    {
        Entry *entry = &(keeper->entries[i]);
        if (strcmp(entry->key, key) == 0)
        {
            entry->value = val;
        }
    }
    writeSettings(keeper);
    return (int)NULL;
}

#endif // RECORDKEEPER_H
