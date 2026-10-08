# Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$root = Split-Path -Parent $PSScriptRoot
$buildDir = Join-Path $root "build"

if (-not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

cmake -S $root -B $buildDir -G "Visual Studio 17 2022"
cmake --build $buildDir --config Release

Write-Host "Build finished. Binary is in: $buildDir\\bin\\Release"
