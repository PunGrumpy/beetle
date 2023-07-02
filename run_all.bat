@echo off
for /r scripts %%G in (output/*.exe) do (
    start "" "%%G"
)
exit
