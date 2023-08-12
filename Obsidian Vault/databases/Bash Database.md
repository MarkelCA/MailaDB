This is the simplest example of a database. Made in bash as a key-value store.
# Script
File: `bdb`
```bash
#!/usr/bin/env bash


set() {
    echo "$1;$2" >> ./database
}

get() {
    grep "^$1;" ./database | sed -e "s/^$1;//" | tail -n 1
}

$@

```

# Database
File: `database`
```
foo;bar
fizz;buzz
fizz;bazz

```
