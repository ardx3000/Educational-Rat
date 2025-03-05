#set paths
$serverPath = "..\build\Server\server.exe"
$clientPath = "..\build\Client\client.exe"

if (!(Test-Path $serverPath)) {
    Write-Host "Error: No .exe found at: ($serverPath)"
    exit 1 
}

if (!(Test-Path $clientPath)) {
    Write-Host "Error: No .exe found at: ($clientPath)"
    exit 1 
}

#Server
Write-Host "Starting server ..."
Start-Process -FilePath $serverPath
Start-Sleep -Seconds 10

#client
Write-Host "Starting client ...."
Start-Process -FilePath $clientPath


