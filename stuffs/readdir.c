#include <stdio.h>
#include <dirent.h>

int main() {
    char path[1024];
    scanf("%s", path);

    DIR *d = opendir(path);
    if (!d) return 1;

    struct dirent *e;
    while ((e = readdir(d))) {
        if (e->d_name[0] == '.') continue; // bỏ . và ..
        printf("%s\n", e->d_name);
    }

    closedir(d);
    return 0;
}

