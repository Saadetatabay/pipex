#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Benim programım başladı!\n");

    // "ls -l" komutunu çalıştır
    execlp("ping","ping","-c","3","google.com",NULL);
    //execlp("ls", "ls", "-l", NULL);

    // Buraya GELEMEZ çünkü exec başarılı olursa geri dönmez
    printf("Bunu asla göremezsin!\n");

    return 0;
}
