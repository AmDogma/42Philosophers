# Philosophers

##  Описание

* [Задача об обедающих философах ВИКИПЕДИЯ](https://ru.wikipedia.org/wiki/Задача_об_обедающих_философах)

Данный проект помогает освоить управление потоками и процессами, а также способам избегать дедлоки

## Запуск программы 

В папке Philo программа выполнена на потоках threads с контролем через mutex. 
В папке philo_bonus эта же задача но на процессах через fork() с контролем через семафоры.

Зайдите в папку, откройте терминал и напишите "make" (Makefile) в командной строке. 
Далее исполните команду:
./philo number_philosopher time_to_die time_to_eat time_to_sleep each_must_eat(not required)
Или просто введите ./philo 20 440 200 200 200 

## Информация

* [Parallel Computing](https://computing.llnl.gov/tutorials/parallel_comp/)
* [POSIX Threads](https://computing.llnl.gov/tutorials/pthreads/) ([pthread routines](https://computing.llnl.gov/tutorials/pthreads/#AppendixA))
* [Working example](https://timmurphy.org/2010/05/04/pthreads-in-c-a-minimal-working-example/)
* [French tutorial](https://franckh.developpez.com/tutoriels/posix/pthreads/)
* [Semaphores in C](http://greenteapress.com/thinkos/html/thinkos012.html)
* [Semaphores example in French](http://jean-luc.massat.perso.luminy.univ-amu.fr/ens/docs/thread-sem.html)
* [fork() example](https://timmurphy.org/2014/04/26/using-fork-in-cc-a-minimum-working-example/)
* [fork() multiple childs](https://stackoverflow.com/questions/876605/multiple-child-process)
* [Semaphore when programs end](https://stackoverflow.com/questions/9537068/sem-close-vs-sem-unlink-when-process-terminates)