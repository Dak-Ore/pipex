# Pipex

## Description

**Pipex** est un projet de l'école 42 qui consiste à reproduire le fonctionnement du pipeline (`|`) dans le shell Unix. Le programme doit exécuter une série de commandes en utilisant des redirections et des tubes pour transmettre les données entre elles.

Ce projet est une excellente opportunité pour explorer les concepts fondamentaux de l'environnement Unix, tels que les appels système (`pipe`, `fork`, `execve`, etc.) et la manipulation des fichiers.

## Fonctionnalités

- Reproduit le comportement suivant dans le terminal :
  ```bash
  < file1 cmd1 | cmd2 > file2
