# Microshell 42 exam4

This project implements a minimal Unix shell emulator in C that supports:

    command execution with execve
    pipelines (|)
    command sequencing (;)
    the cd built-in command with basic error handling

## Features

    Execute external programs using execve
    Support for | (piping) between commands
    Support for ; (sequential execution)
    Built-in cd command
    Error output to stderr using write(2, ...)
    Minimal memory usage, no dynamic memory allocation

## Source Overview

    int std_in; // Backup of original stdin
    void printt_err(char *str); // Custom error message printer to stderr
    void ft_exec(char **argv, int limit, char **envp); // Core function to execute a command or pipe
    int main(int argc, char **argv, char **envp); // Argument parser and command dispatcher

Good luck. Don't panic. feel free to visit me at school.
