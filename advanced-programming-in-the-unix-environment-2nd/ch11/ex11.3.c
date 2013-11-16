/*
 * \file ex11.3.c
 * \brief worker thread use conditional variable
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-11-16
 */
/* $Id$ */

#include "apue.h"
#include <stdlib.h>
#include <pthread.h>

#define WORKER_NUM 3
#define JOB_NUM 300

enum job_cmd {
	JOB_CMD_RUN,
	JOB_CMD_END
};

struct job {
	struct job *j_next;
	struct job *j_prev;
	pthread_t   j_id;   /* tells which thread handles this job */
	enum job_cmd j_cmd;
};

struct queue {
	struct job      *q_head;
	struct job      *q_tail;
	pthread_rwlock_t q_lock;
};

struct thr_cond {
	pthread_t tid;
	pthread_cond_t cond;
	pthread_mutex_t mutex;
};

static struct queue job_queue;

/*
 * Initialize a queue.
 */
int queue_init (struct queue *qp)
{
	int err;

	qp->q_head = NULL;
	qp->q_tail = NULL;
	err = pthread_rwlock_init(&qp->q_lock, NULL);
	if (err != 0)
		return(err);

	/* ... continue initialization ... */

	return(0);
}

/*
 * Insert a job at the head of the queue.
 */
void job_insert(struct queue *qp, struct job *jp)
{
	pthread_rwlock_wrlock(&qp->q_lock);
	jp->j_next = qp->q_head;
	jp->j_prev = NULL;
	if (qp->q_head != NULL)
		qp->q_head->j_prev = jp;
	else
		qp->q_tail = jp;	/* list was empty */
	qp->q_head = jp;
	pthread_rwlock_unlock(&qp->q_lock);
}

/*
 * Append a job on the tail of the queue.
 */
void job_append(struct queue *qp, struct job *jp)
{
	pthread_rwlock_wrlock(&qp->q_lock);
	jp->j_next = NULL;
	jp->j_prev = qp->q_tail;
	if (qp->q_tail != NULL)
		qp->q_tail->j_next = jp;
	else
		qp->q_head = jp;	/* list was empty */
	qp->q_tail = jp;
	pthread_rwlock_unlock(&qp->q_lock);
}

/*
 * Remove the given job from a queue.
 */
void job_remove(struct queue *qp, struct job *jp)
{
	pthread_rwlock_wrlock(&qp->q_lock);
	if (jp == qp->q_head) {
		qp->q_head = jp->j_next;
		if (qp->q_tail == jp)
			qp->q_tail = NULL;
	} else if (jp == qp->q_tail) {
		qp->q_tail = jp->j_prev;
		if (qp->q_head == jp)
			qp->q_head = NULL;
	} else {
		jp->j_prev->j_next = jp->j_next;
		jp->j_next->j_prev = jp->j_prev;
	}
	pthread_rwlock_unlock(&qp->q_lock);
}

/*
 * Find a job for the given thread ID.
 */
struct job* job_find(struct queue *qp, pthread_t id)
{
	struct job *jp = NULL;

	if (pthread_rwlock_rdlock(&qp->q_lock) != 0)
		return(NULL);

	for (jp = qp->q_head; jp != NULL; jp = jp->j_next)
		if (pthread_equal(jp->j_id, id))
			break;

	pthread_rwlock_unlock(&qp->q_lock);
	return(jp);
}

void* thr_fn (void *arg)
{
	struct job *jp = NULL;
	pthread_t id = pthread_self ();
	struct thr_cond *cond = (struct thr_cond *)arg;
	int end = 0;

	while (!end) {
		/* get the job */
		pthread_mutex_lock (&(cond->mutex));
		while (!(jp = job_find (&job_queue, id))) {
			pthread_cond_wait (&(cond->cond), &(cond->mutex));
		}
		pthread_mutex_unlock (&(cond->mutex));
		switch (jp->j_cmd) {
			case JOB_CMD_RUN:
				printf ("received JOB_CMD_RUN\n");
				break;
			case JOB_CMD_END:
				printf ("received JOB_CMD_END\n");
				end = 1;
				break;
			default:
				printf ("received unknown cmd : %d\n", jp->j_cmd);
				break;
		}
		job_remove (&job_queue, jp);
		free (jp);
	}
	pthread_exit ((void *)0);
}

int main (int argc, char *argv[])
{
	struct thr_cond thr_cond_array[WORKER_NUM], *tc;
	struct job *jp = NULL;
	int i = 0, err = 0;

	/* Init queue */
	err = queue_init (&job_queue);
	if (err) {
		err_quit ("can't init queue, err = %s\n", strerror (err));
	}

	/* Create worker thread */
	for (i = 0; i < WORKER_NUM; i++) {
		err = pthread_mutex_init (&(thr_cond_array[i].mutex), NULL);
		if (err) {
			err_quit ("can't init mutex, err = %s\n", strerror (err));
		}
		err = pthread_cond_init (&(thr_cond_array[i].cond), NULL);
		if (err) {
			err_quit ("can't init cond, err = %s\n", strerror (err));
		}
		err = pthread_create (&(thr_cond_array[i].tid), NULL, thr_fn,
				&(thr_cond_array[i]));
		if (err) {
			err_quit ("can't create thread, err = %s\n", strerror (err));
		}
	}

	/* add job to queue */
	for (i = 0; i < JOB_NUM; i++) {
		tc = &(thr_cond_array[i % WORKER_NUM]);
		jp = (struct job *)malloc (sizeof (struct job));
		jp->j_id = tc->tid;
		jp->j_cmd = JOB_CMD_RUN;
		job_append (&job_queue, jp);
		pthread_cond_signal (&tc->cond);
	}

	/* notify the worker to end */
	for (i = 0; i < WORKER_NUM; i++) {
		tc = &thr_cond_array[i % WORKER_NUM];
		jp = (struct job *)malloc (sizeof (struct job));
		jp->j_id = tc->tid;
		jp->j_cmd = JOB_CMD_END;
		job_append (&job_queue, jp);
		pthread_cond_signal (&tc->cond);
	}

	/* waiting the worker exit */
	for (i = 0; i < WORKER_NUM; i++) {
		pthread_join (thr_cond_array[i].tid, NULL);
	}
	exit (0);
}
