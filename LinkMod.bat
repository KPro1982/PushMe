@echo off

cd /D "%~dp0"

IF exist "P:\PushMe\" (
	echo Removing existing link P:\PushMe
	rmdir "P:\PushMe\"
)

echo mklink /J "P:\PushMe\" "%~dp0"
mklink /J "P:\PushMe\" "%~dp0"

echo Done
