#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

typedef struct SaveManager
{
    const char *filename;
    int levels[GAMEUPGRADES_ID_MAX];
} SaveManager;

// level(char)
SaveManager newSaveManager(const char *filename)
{
    SaveManager manager = {filename};
    FILE *file = fopen(TextFormat("saves\\%s", filename), "r");
    if (file == NULL)
    {
        for (size_t i = 0; i < GAMEUPGRADES_ID_MAX; i++)
        {
            manager.levels[i] = (int)(i == 0);
        }
    }

    for (size_t i = 0; i < GAMEUPGRADES_ID_MAX; i++)
    {
        char level = getc(file);

        if (level == EOF)
        {
            level = (int)i == 0;
        }
        manager.levels[i] = level;
    }
    
    fclose(file);
    return manager;
}

void saveLevels(SaveManager *manager,char levels[GAMEUPGRADES_ID_MAX])
{
    struct stat stats;
    if (stat("saves", &stats) != 0 || !S_ISDIR(stats.st_mode))
    { // Directory does not exist
        mkdir("saves");
    }
    FILE *file = fopen(TextFormat("saves\\%s", manager->filename), "w");
    for (size_t i = 0; i < GAMEUPGRADES_ID_MAX; i++)
    {
        putc(levels[i], file);
        manager->levels[i] = levels[i];
    }
    fclose(file);
}

int loadLevelFromSave(SaveManager *manager, int ID){
    return manager->levels[ID];
}

bool isSaveNew(SaveManager *manager){
    bool result = true;
    for (size_t i = 0; i < GAMEUPGRADES_ID_MAX; i++)
    {
        result = result & (manager->levels[i] == ((int)i==0));
        if (!result)
        {
            break;
        }
    }
    return result;
}

void resetSave(SaveManager *manager){
    char levels[2];
    for (size_t i = 0; i < GAMEUPGRADES_ID_MAX; i++)
    {
        levels[i] = (char)(int)(i==0);
    }
    saveLevels(manager,levels);
}

#endif SAVEMANAGER_H