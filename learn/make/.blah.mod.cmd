savedcmd_/home/teiwiet/Main/code/learn/make/blah.mod := printf '%s\n'   blah.o | awk '!x[$$0]++ { print("/home/teiwiet/Main/code/learn/make/"$$0) }' > /home/teiwiet/Main/code/learn/make/blah.mod
