#!/bin/bash
if [ "$#" -gt 0 ]
    then
        cd src
        echo 'Compilando...'
        gcc main.c -o app-file
        echo 'Compilado!'

        if [ $1 == "@" ]
        then
            echo 'Executando "./exemplos.data"...'
            ./app-file ./exemplos.data
        else
            echo 'Executando "'$1'"...'
            ./app-file $1
        fi
    else
        echo '##################################################'
        echo '##  Strange Compressor:                         ##'
        echo '##  Use para arquivo novo:   | app.sh <arquivo> ##'
        echo '##  Use para arquivo padrão: | app.sh "@"       ##'
        echo '##################################################'
fi
