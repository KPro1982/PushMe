echo off
cd /D "%~dp0"
cd ../UIHelper
Powershell.exe -executionpolicy remotesigned -File  CreateUIFromLayout.ps1
