There are philos >= 1 sitting around a round table. In the middle of the table there is a plate of spaghetti.
they can do three actions (in this order)
- eat
- sleep 
- think
There are forks = philos, and each philo has to eat with two forks (one on the right and one on the left)
The program quits if one of the philos dies.
Rules
- none shoud starve to death
- no talking
- none knows the status of another philo
- no dying
- there can be philo >= 1
- philo[1] sits next to philo[n + 1], while philo[>1] sits next to philo[n + 1] and philo[n - 1]
Argv
- number of philos that is the same as forks
- time in milliseconds in which a philo would die (in other words, if time between meals is > than time to die, philo dies)
- time in milliseconds that a philo has to eat
- time in milliseconds that a philo has to sleep
- optional : times philo has to eat before dying
Print
on the screen the following messages need to be showed without "cutting" each other
- time stamp in ms for philo taking fork
- time stamp in ms for philo eating
- time stamp in ms for philo sleeping
- time stamp in ms for philo thinking
- time stamp in ms for philo who has died - time of death cannot be dealeyd more than 10 ms after the actual death
Keywords
DATA RACES: losing data
THREADS: each philo is a thread
MUTEX: protect fork to be continusly created
Functions I can use
- memset
- printf, write
- malloc, free
- usleep, gettimeofday, 
- pthread_create,pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock

What i can:
create a program, paramteres, varibles and converting functions (from string to number)
maybe sit one philo at the table -> create a thraed

functions pthread
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
it returns 0 if it is a success;
thread is type pthread_t;
attr we can set to NULL - customize
start routine is function pointer that will be performed when calling a thread
arg is data structure passed in the function
function type
pthrad_join: makes the programm keep running till the thread is not done. 
