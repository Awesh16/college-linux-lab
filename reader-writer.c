
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex;
pthread_mutex_t mutex;

int read_count = 0;
int shared_data = 0;

void *reader(void *arg)
{
    int id = *(int *)arg;

    pthread_mutex_lock(&mutex);

    read_count++;

    if (read_count == 1)
        sem_wait(&rw_mutex);

    pthread_mutex_unlock(&mutex);

    printf("Reader %d is reading data: %d\n", id, shared_data);
    sleep(1);

    pthread_mutex_lock(&mutex);

    read_count--;

    if (read_count == 0)
        sem_post(&rw_mutex);

    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *writer(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&rw_mutex);

    shared_data += 10;

    printf("Writer %d is writing data: %d\n", id, shared_data);
    sleep(1);

    sem_post(&rw_mutex);

    return NULL;
}

int main()
{
    int R, W;

    printf("Enter number of readers: ");
    scanf("%d", &R);

    printf("Enter number of writers: ");
    scanf("%d", &W);

    if (R < 0 || W < 0 || (R == 0 && W == 0))
    {
        printf("Invalid input!\n");
        return 1;
    }

    pthread_t *readers = malloc(R * sizeof(pthread_t));
    pthread_t *writers = malloc(W * sizeof(pthread_t));

    int *reader_id = malloc(R * sizeof(int));
    int *writer_id = malloc(W * sizeof(int));

    if ((R > 0 && (readers == NULL || reader_id == NULL)) ||
        (W > 0 && (writers == NULL || writer_id == NULL)))
    {
        printf("Memory allocation failed!\n");
        free(readers);
        free(writers);
        free(reader_id);
        free(writer_id);
        return 1;
    }

    pthread_mutex_init(&mutex, NULL);
    sem_init(&rw_mutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < R; i++)
    {
        reader_id[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_id[i]);
    }

    // Create writer threads
    for (int i = 0; i < W; i++)
    {
        writer_id[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_id[i]);
    }

    // Wait for all readers
    for (int i = 0; i < R; i++)
        pthread_join(readers[i], NULL);

    // Wait for all writers
    for (int i = 0; i < W; i++)
        pthread_join(writers[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&rw_mutex);

    free(readers);
    free(writers);
    free(reader_id);
    free(writer_id);

    return 0;
}
