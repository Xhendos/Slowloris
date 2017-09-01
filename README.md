# Slowloris

## Table of Contents
1. [Overview](#section-features)
2. [Dependencies](#section-dependencties)
3. [Usage](#section-usages)

## [Overview](id:section-features)

Slowloris is using the weaknesses in the way Apache webserver was build. To overflow the maximal amount of open connections a server can handle, we overflow this number. As a result the webserver is unavailable to provide its services to other users. This causes a Denial of Service.

## [Dependencies](id:section-dependencies)

This slowloris program was developed and compiled using a GNU/Linux machine. It uses the standard C libaries and additional POSIX libraries. To provide the best performances I have chosen to develop it in a way to support multi threading. The 
[POSIX threads](https://en.wikipedia.org/wiki/POSIX_Threads) are used because the way it is programmed is very clean and it is portable. No Windows users will be able to use this program.

## [Usage](id:section-usages)

Compile and link using the GNU Compiler Collection
```
gcc -Wall slowloris.c -o program -lpthread
```

```
./program [IP to DOS] [Port number] [number of threads]
```
This program is not tested on port 443 (HTTPS) and will not probably work, because no encryption is set up.
In future update I might use openssl to solve this issue.

