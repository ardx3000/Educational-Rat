# Set paths
$serverPath = "..\bin\server.exe"
$clientPath = "..\bin\client.exe"

if (!(Test-Path $serverPath)) {
    Write-Host "Error: No .exe found at: $serverPath"
    exit 1
}

if (!(Test-Path $clientPath)) {
    Write-Host "Error: No .exe found at: $clientPath"
    exit 1
}


Write-Host "Starting server..."
Start-Process -FilePath "cmd.exe" -ArgumentList "/c start cmd /k `"$serverPath`"" -NoNewWindow

# Wait for the server to be ready
Start-Sleep -Seconds 3


Write-Host "Starting client..."
Start-Process -FilePath "cmd.exe" -ArgumentList "/c start cmd /k `"$clientPath`"" -NoNewWindow
