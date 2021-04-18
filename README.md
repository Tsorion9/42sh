# What is 42sh
[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)
[![forthebadge](http://forthebadge.com/images/badges/built-with-love.svg)](http://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/ages-18.svg)](https://forthebadge.com)

42sh is a bash-styled shell project completely written from scratch in C with very limited access to libraries and tools.

# The learning goals of the project:
- Learn a lot more about the inner workings of the UNIX system.
- Learn about the different type of shell implementations.
- Learn what a lexer is and how to write it.
- Learn what a parser is and how to write it.
- Learn how to write nice and clean code.
- Learn how process execution work.
- Learn some porsix features.
- To create a stable and complete UNIX shell.

# Functionality
1. Error monitoring without using `errno`.
2. Prompt display.
3. Complete management of input.
4. (Multiline) line edition.
5. Redirection with the following operators:
   * `>`
   * `>>`
   * `<`
   * `<<`
   * `>&`
   * `<&`
6. Control operators:
   * `|`
   * `||`
   * `&&`
   * `;`
   * `&`
7. Quoting managment `"`, `'`, and `\` or inhibitors.
8. Basic parameter expansion and additional parameter formats:
   *  Word expansion performs by [POSIX](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_06)
   *  `~`
   *  `${parameter:-word}`
   *  `${parameter:=word}`
   *  `${parameter:?word}`
   *  `${parameter:+word}`
   *  `${#parameter}`
   *  `${parameter%}`
   *  `${parameter%%}`
   *  `${parameter#}`
   *  `${parameter##}`
9. Command history:
   *  `!!`
   *  `!word`
   *  `!number`
   *  `!-number`
   *  Saving to a file so that it can be used over several sessions
   *  Built-in fc (all POSIX options)
   *  Incremental search in the history with CTRL-R
10. Autocomplete.
11. Builtins:
    *  `echo`
    *  `cd`
    *  `env`
    *  `export`
    *  `setenv`
    *  `unsetenv`
    *  `exit`
    *  `type`
12. Pattern matching (globing): `*`, `?`, `[]`, `!` and the caracters intervals with `\` (backslash).
13. Control or command substitution: `$()`.
14. Alias management via built-ins `alias` and `unalias`.
15. A hash table and built-in `hash` to interact with it.
16. Monitoring of intern shell variables.
17. Job control monitoring, with buitl-ins `jobs`, `fg`, `bg` and the `&` operator.
# Installing and running 42sh
Install:
```
git clone https://github.com/Tsorion9/42sh.git
make && make clean
```

Run:
```
./42sh
```
# Authors
[Volkov Ilya](https://github.com/volkov7),
[Alex Buyanov](https://github.com/SoliddSnake),
[Golovizin Anton](https://github.com/ag95v2),
[Artur Tsorionov](https://github.com/Tsorion9)
