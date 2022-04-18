#include "header.h"

jstruct job_generation(char *j_commands, int job_id)
{
    jstruct genjob;
    genjob.job_id = job_id;
    genjob.exit_status = -1;
    genjob.j_commands = copyInputString(j_commands, -1);
    genjob.start_time = genjob.stop_time = NULL;
    genjob.j_status = "waiting";
    sprintf(genjob.fdout, "%d.out", genjob.job_id);
    sprintf(genjob.fderr, "%d.err", genjob.job_id);
    return genjob;
}

queue *queue_init(int k)
{
    queue *q = malloc(sizeof(queue));
    q->buffer = malloc(sizeof(jstruct *) * k);
    q->size = k;
    q->end = 0;
    q->start = 0;
    q->count = 0;

    return q;
}

int queue_insert(queue *q, jstruct *jobp_Pointer)
{
    if ((q == NULL) || (q->count == q->size))
        return -1;

    q->buffer[q->end % q->size] = jobp_Pointer;
    q->end = (q->end + 1) % q->size;
    q->count++;

    return q->count;
}

jstruct *queue_delete(queue *q)
{
    if ((q == NULL) || (q->count == 0))
        return (jstruct *)-1;

    jstruct *genjob = q->buffer[q->start];
    q->start = (q->start + 1) % q->size;
    q->count--;

    return genjob;
}

void queue_destroy(queue *q)
{
    free(q->buffer);
    free(q);
}

