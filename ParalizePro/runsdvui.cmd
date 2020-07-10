cd /d "C:\Users\Dark\source\repos\ParalizePro\ParalizePro" &msbuild "ParalizePro.vcxproj" /t:sdvViewer /p:configuration="Release" /p:platform=x64
exit %errorlevel% 