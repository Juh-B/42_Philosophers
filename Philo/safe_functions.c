#include "philo.h"

void  *safe_malloc(size_t bytes)
{
  void  *ret;

  ret = mallloc(bytes);
  if (!ret)
    error_exit("Error with the Malloc");
  return (ret);
}

static void handle_mutex_error(int status, t_opcode opcode)
{
  if (status == 0)
    return ;
  if (EINVAL == status && (LOOK == opcode || UNLOCK == opcode || DESTROY == opcode))
    error_exit("The value specified by mutex is invalid.");
  else if (EINVAL == status && INIT == opcode)
    error_exit("The value specified by att is invalid.");
  else if (EDEADLK == status)
    error_exit("A deadlock would occur if the thread blocked waitinf for mutex.");
  else if (EPERM == status)
    error_exit("The current thread doesn't hold a lock on mutex.");
  else if (ENOMEM == status)
    error_exit("Mutex is locked.");
}

void  safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
  if (LOCK == opcode)
    handle_mutex_error(pthread_mutex_lock(mutex), opcode);
  else if (UNLOCK == opcode)
    handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
  else if (INIT == opcode)
    handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
  else if (DESTROY == opcode)
    handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
  else
    error_exit("Wrong opcode for mutex handle.");
}

static void handle_thread_error(int status, t_opcode opcode)
{
  if (status == 0)
    return ;
  if (EAGAIN == status)
    error_exit("No resources to create another thread.");
  else if (EPERM == status)
    error_exit("The caller doesn't have appropriate permission.");
  else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
    error_exit("The value specified by thread is not joinble.");
  else if (ESRCH == status)
    error_exit("No thread could be found corresponding to that "
      "specified by the given thread ID, thread.");
  else if (EDEADLK == status)
    error_exit("A deadlock was detected or "
      "the value of thered specifies the calling thread.");
}

void  safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
       t_opcode opcode)
{
  if (CREATE == opcode)
    handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
  else if (JOIN == opcode)
    handle_thread_error(pthread_join(*thread, NULL), opcode);
  else if (DETACH == opcode)
    handle_thread_error(pthread_detach(*thread), opcode);
  else
    error_exit("Wrong opcode for thread handle: Use <CREATE> <JOIN> <DETACH>");
}
