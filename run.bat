@echo off

if "%1"=="clean" (
    del /f /q benchmark.exe results\plot_*.png 2>nul
    echo Projet nettoye.
    exit /b 0
)

if not exist results mkdir results

gcc -Wall -Wextra -O2 -Iinclude -o benchmark.exe src\*.c
if errorlevel 1 (
    echo Erreur lors de la compilation !
    exit /b 1
)
echo Compilation reussie.

set CMD=%1
if "%CMD%"=="" set CMD=demo

if "%CMD%"=="demo" (
    benchmark.exe --demo %2 %3
) else if "%CMD%"=="test" (
    benchmark.exe --test %2
) else if "%CMD%"=="full" (
    benchmark.exe --full %2 %3
    call :plot %2
) else (
    benchmark.exe %CMD% %2 %3
    call :plot %CMD%
)
exit /b 0

:plot
where gnuplot >nul 2>&1
if errorlevel 1 exit /b 0
if not exist plot.gp exit /b 0

set TYPE=%1
if "%TYPE%"=="" set TYPE=all
if "%TYPE%"=="reverse" set TYPE=reverse_sorted
if "%TYPE%"=="nearly" set TYPE=nearly_sorted
if "%TYPE%"=="duplicates" set TYPE=many_duplicates

if "%TYPE%"=="all" (
    echo Generation de tous les graphes...
    for %%t in (random sorted reverse_sorted nearly_sorted many_duplicates) do (
        gnuplot -e "type='%%t'" plot.gp
    )
) else (
    echo Generation du graphe pour %TYPE%...
    gnuplot -e "type='%TYPE%'" plot.gp
)
echo Graphes enregistres dans results/
exit /b 0
