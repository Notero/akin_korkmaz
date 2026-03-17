
#define GENRE_H

#include <stdio.h>


int genres() {
    const char* genres[] = {
        "Drama", "Comedy", "Science Fiction", "Fantasy", "Mystery",
        "Thriller", "Horror", "Romance", "Action", "Adventure", "Documentary",
        "Animation", "Family", "Reality TV"
    };

    int numGenres = sizeof(genres) / sizeof(genres[0]);

    printf("List of TV Series Genres:\n");
    for (int i = 0; i < numGenres; i++) {
        printf("%d. %s\n", i + 1, genres[i]);
    }

    return 0;
}
