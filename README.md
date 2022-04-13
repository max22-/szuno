# Szuno

A toy language written in C89.
TL;DR : prefix notation, like lisp, but without the parentheses because we use a fixed number of arguments for the functions.

## Goals
The goals this little language are :
- to have fun !
- to be as small as possible, and limited
- to be embeddable on resource limited microcontrollers, as a library
- to be a fast prototyping tool : make a motor turn in less than 5 minutes, do some bit banging, etc
- to be terse
- to be able to edit little scripts, save and load them from the serial port
- and why not making some music with it ? because it is inspired by the Monome [Teletype](https://monome.org/docs/teletype/)

## Non goals
- to be fast
- to have lots of fancy features


## Hello, world !
Strings are not supported yet ^^. But we can do some calculations :

```
> print * 2 + 1 3
8
```

## Under the hood

I have read some stuff recently about PEG parsers : [Packrat Parsing from Scratch](https://blog.bruce-hill.com/packrat-parsing-from-scratch) and watched this video : [Writing a PEG Parser for fun and Profit](https://youtu.be/7MuQQQWVzU4?t=991) by Guido van Rossum. I didn't know how they worked internally before, and it is quite easy to understand and to implement. Guido van Rossum explains it very well in his talk.

So the parsing is done by a handmade (naive) peg parser. Evaluation is done at the same time. Is it a good idea ? I don't know ! I am exploring things.

## LICENSE

MIT
