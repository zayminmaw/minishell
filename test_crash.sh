#!/bin/bash
echo "(echo A) | echo B" | ./minishell 2>&1
echo "Exit code: $?"
