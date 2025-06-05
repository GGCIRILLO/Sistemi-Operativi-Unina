#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "prodcons.h"

void inizializza(MonitorPC *m)
{

    printf("Inizializzazione monitor\n");

    /* TBD: Inizializzazione */
    m->num_liberi = DIM;
    m->num_occupati_tipo1 = 0;
    m->num_occupati_tipo2 = 0;
    for (int i = 0; i < DIM; i++)
    {
        m->stato[i] = LIBERO;
    }
    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->cv_libero, NULL);
    pthread_cond_init(&m->cv_occupato1, NULL);
    pthread_cond_init(&m->cv_occupato2, NULL);

    printf("Monitor inizializzato!\n");
}

void rimuovi(MonitorPC *m)
{

    printf("Rimozione monitor\n");

    /* TBD: Rimozione */
    pthread_mutex_destroy(&m->mutex);
    pthread_cond_destroy(&m->cv_libero);
    pthread_cond_destroy(&m->cv_occupato1);
    pthread_cond_destroy(&m->cv_occupato2);
}

void produci_tipo_1(MonitorPC *m, int valore)
{

    int index = 0;
    int my_id = syscall(SYS_gettid);

    /* TBD: Sincronizzazione, e selezione dell'indice su cui produrre */
    pthread_mutex_lock(&m->mutex);
    while (m->num_liberi == 0)
    {
        pthread_cond_wait(&m->cv_libero, &m->mutex);
    }

    while (index < DIM && m->stato[index] != LIBERO)
        index++;

    m->stato[index] = INUSO;
    m->num_liberi--;

    pthread_mutex_unlock(&m->mutex);

    // printf("[%d]Produttore1: Uscito da monitor\n",my_id);

    // printf("[%d]Produzione di tipo 1 in corso (valore=%d, index=%d)\n", my_id, valore, index);

    printf("[%d]Produzione di tipo 1 (valore=%d, index=%d)\n", my_id, valore, index);

    pthread_mutex_lock(&m->mutex);
    m->vettore[index] = valore;
    m->stato[index] = OCCUPATO1;
    m->num_occupati_tipo1++;
    pthread_cond_signal(&m->cv_occupato1);
    pthread_mutex_unlock(&m->mutex);

    // printf("[%d]Uscito da monitor\n",my_id);
}

void produci_tipo_2(MonitorPC *m, int valore)
{

    int index = 0;
    int my_id = syscall(SYS_gettid);

    /* TBD: Sincronizzazione, e selezione dell'indice su cui produrre */
    pthread_mutex_lock(&m->mutex);
    while (m->num_liberi == 0)
    {
        pthread_cond_wait(&m->cv_libero, &m->mutex);
    }
    while (index < DIM && m->stato[index] != LIBERO)
        index++;
    m->stato[index] = INUSO;
    m->num_liberi--;
    pthread_mutex_unlock(&m->mutex);

    // printf("[%d]Produttore2: Uscito da monitor\n",my_id);

    printf("[%d]Produzione di tipo 2 in corso (valore=%d, index=%d)\n", my_id, valore, index);

    pthread_mutex_lock(&m->mutex);
    m->vettore[index] = valore;
    m->stato[index] = OCCUPATO2;
    m->num_occupati_tipo2++;
    pthread_cond_signal(&m->cv_occupato2);
    pthread_mutex_unlock(&m->mutex);

    // printf("[%d]Uscito da monitor\n",my_id);
}

void consuma_tipo_1(MonitorPC *m, int *valore)
{

    int index = 0;
    int my_id = syscall(SYS_gettid);

    /* TBD: Sincronizzazione, e selezione dell'indice su cui consumare */
    pthread_mutex_lock(&m->mutex);
    while (m->num_occupati_tipo1 == 0)
    {
        pthread_cond_wait(&m->cv_occupato1, &m->mutex);
    }
    while (index < DIM && m->stato[index] != OCCUPATO1)
        index++;
    m->stato[index] = INUSO;
    m->num_occupati_tipo1--;
    pthread_mutex_unlock(&m->mutex);

    // printf("[%d]Consumatore1: Uscito da monitor\n",my_id);

    printf("[%d]Consumazione di tipo 1 (valore=%d, index=%d)\n", my_id, *valore, index);

    pthread_mutex_lock(&m->mutex);
    *valore = m->vettore[index];
    m->stato[index] = LIBERO;
    m->num_liberi++;
    pthread_cond_signal(&m->cv_libero);
    pthread_mutex_unlock(&m->mutex);

    // printf("[%d]Uscito da monitor\n",my_id);
}

void consuma_tipo_2(MonitorPC *m, int *valore)
{

    int index = 0;
    int my_id = syscall(SYS_gettid);

    /* TBD: Sincronizzazione, e selezione dell'indice su cui consumare */
    pthread_mutex_lock(&m->mutex);
    while (m->num_occupati_tipo2 == 0)
    {
        pthread_cond_wait(&m->cv_occupato2, &m->mutex);
    }
    while (index < DIM && m->stato[index] != OCCUPATO2)
        index++;
    m->stato[index] = INUSO;
    m->num_occupati_tipo2--;
    pthread_mutex_unlock(&m->mutex);

    // printf("[%d]Consumatore2: Uscito da monitor\n",my_id);

    printf("[%d]Consumazione di tipo 2 (valore=%d, index=%d)\n", my_id, *valore, index);

    pthread_mutex_lock(&m->mutex);
    *valore = m->vettore[index];
    m->stato[index] = LIBERO;
    m->num_liberi++;
    pthread_cond_signal(&m->cv_libero);
    pthread_mutex_unlock(&m->mutex);

    // printf("[%d]Uscito da monitor\n",my_id);
}
