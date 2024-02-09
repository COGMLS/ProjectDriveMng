<###################### Auxiliary System Tools for Windows ######################
 # Project: PC Backup Tools
 # --------------------------------------------------------
 # Author: Matheus L. Silvati
 # ------------------------------------
 # Version: 1.0.0
 # ------------------------------------
 # PowerShell Minimum Version: 7.0
 # --------------------------------------------------------
 # OBS: N/A
################################################################################>

# Requires -Version 7.0

<#
.SYNOPSIS
    Script used to manage the backup routines for Project Drive.
.DESCRIPTION
    
.NOTES
    This script uses default resources available in .NET 7.0 and superior and PowerShell 7.0.
.LINK
    No additional help is available. Use the 'help' internal command to access the script commands.
.EXAMPLE
    Backup.ps1 -Destintion "H:\Backups"
    Make a backup of ProjectDrive to H:\Backups folder. A additional folder will be created inside destination directory.
.EXAMPLE
    Backup.ps1 -Destintion "H:\Backups" -Test
    Make a backup test of ProjectDrive to H:\Backups folder. A log will be generated on same location of destination directory
#>

Param
(
    # Destination
    [Parameter(Mandatory = $false, Position = 0)]
    [string]
    $Destination,

    # Only test
    [Parameter(Mandatory = $false, Position = 1)]
    [switch]
    $Test
)

function BackupWithRobocopy
{
    Param
    (
        [string]$InputDir,
        [string]$OutputBase,
        [System.Collections.Generic.List[string]]$Files = [System.Collections.Generic.List[string]]::new(),
        [System.Collections.Generic.List[string]]$ExcludeDirs = [System.Collections.Generic.List[string]]::new(),
        [System.Collections.Generic.List[string]]$ExcludeFiles = [System.Collections.Generic.List[string]]::new(),
        [string]$LogOutput = "",
        [switch]$UseCompression,
        [switch]$TestOperation,
        [switch]$ShowOnConsole
    )

    [System.Collections.Generic.List[string]]$ArgList = [System.Collections.Generic.List[string]]::new();

    [string]$TempInput = ""

    if (-not $InputDir.StartsWith('`"'))
    {
        $TempInput += "`""
    }

    $TempInput += $InputDir

    if (-not $InputDir.EndsWith('`"'))
    {
        $TempInput += "`""
    }

    $ArgList.Add($TempInput)

    [string]$TempOutput = [System.IO.Path]::Combine($OutputBase, "ProjectDriveBackup_$(Get-Date -UFormat "%Y-%m-%d %H-%M-%S")")
    
    [System.IO.DirectoryInfo]$DirInfo = [System.IO.DirectoryInfo]::new($TempOutput)

    if (-not $DirInfo.Exists)
    {
        $DirInfo.Create()
    }

    if (-not $TempOutput.StartsWith('`"'))
    {
        $TempOutput = "`"" + $TempOutput
    }

    if (-not $TempOutput.EndsWith('`"'))
    {
        $TempOutput = $TempOutput + "`""
    }

    $ArgList.Add($TempOutput)
    
    if ($Files.Count -eq 0)
    {
        $ArgList.Add("`"*.*`"")
    }
    else
    {
        for ($i = 0; $i -lt $Files.Count; $i++)
        {
            [string]$TempFiles = ""
            $TempFiles += " "

            if (-not $Files[$i].StartsWith('`"'))
            {
                $TempFiles += "`""
            }

            $TempFiles += $Files[$i]

            if (-not $Files[$i].EndsWith('`"'))
            {
                $TempFiles += "`""
            }

            $ArgList.Add($TempFiles)
        }
    }

    if ($ExcludeDirs.Count -gt 0)
    {
        $ArgList.Add("-XD")

        for ($i = 0; $i -lt $ExcludeDirs.Count; $i++)
        {
            $TempExcludeDir = ""

            if (-not $ExcludeDirs[$i].StartsWith('`"'))
            {
                $TempExcludeDir += "`""
            }

            $TempExcludeDir += $ExcludeDirs[$i]

            if (-not $ExcludeDirs[$i].EndsWith('`"'))
            {
                $TempExcludeDir += "`""
            }

            $ArgList.Add($TempExcludeDir)
        }
    }

    if ($ExcludeFiles.Count -gt 0)
    {
        $ArgList.Add("-XF")

        for ($i = 0; $i -lt $ExcludeFiles.Count; $i++)
        {
            $TempExcludeFile = ""

            if (-not $ExcludeFiles[$i].StartsWith('`"'))
            {
                $TempExcludeFile += "`""
            }

            $TempExcludeFile += $ExcludeFiles[$i]

            if (-not $ExcludeFiles[$i].EndsWith('`"'))
            {
                $TempExcludeFile += "`""
            }

            $ArgList.Add($TempExcludeFile)
        }
    }

    $ArgList.Add("-E")
    $ArgList.Add("-Z")
    $ArgList.Add("-X")
    $ArgList.Add("-V")

    if ($TestOperation)
    {
        $ArgList.Add("-L")
    }

    if ($UseCompression)
    {
        $ArgList.Add("-COMPRESS")
    }

    $ArgList.Add("-ETA")

    if ($ShowOnConsole)
    {
        $ArgList.Add("-TEE")
    }
    $ArgList.Add("-UNICODE")

    if ($LogOutput.Length -ne 0 -and (Test-Path -Path $LogOutput -ErrorAction SilentlyContinue))
    {
        [string]$LogName = "$($DirInfo.Name).log"
        [string]$LogPath = [System.IO.Path]::Combine($LogOutput, "Logs", $LogName)

        [string]$LogDir = [System.IO.Path]::Combine($LogOutput, "Logs")

        [System.IO.DirectoryInfo]$LogDirInfo = [System.IO.DirectoryInfo]::new($LogDir)

        if (-not $LogDirInfo.Exists)
        {
            $LogDirInfo.Create()
        }

        $TempLogPath = "-UNILOG:"

        if (-not $LogPath.StartsWith('`"'))
        {
            $LogPath = "`"" + $LogPath
        }

        if (-not $LogPath.EndsWith('`"'))
        {
            $LogPath = $LogPath + "`""
        }

        $TempLogPath += $LogPath

        $ArgList.Add($TempLogPath)
    }

    [string]$ArgListStr = ""

    for ($i = 0; $i -lt $ArgList.Count; $i++)
    {
        if ($i -ne 0)
        {
            $ArgListStr += " "
        }

        $ArgListStr += $ArgList[$i]
    }

    Start-Process -FilePath "Robocopy" -ArgumentList $ArgListStr -Wait -NoNewWindow

    return $DirInfo
}

function WriteConsoleLine
{
    [int]$maxWidth = [System.Console]::BufferWidth
    [int]$i = 0

    while ($i -lt $maxWidth)
    {
        Write-Host -Object '-' -NoNewline
        $i++
    }
}

$ProjectDrivePath = Get-ItemPropertyValue -Path "HKCU:\Environment" -Name "ProjectDrive"

$ExcludeDirectories = @(
    "`$RECYCLE.BIN"
    "System Volume Information"
)

$HelpCommand = @(
    "Commands Avaialble:",
    "Help - Show the commands available",
    "Info - Show details about the backup"
    "Backup - Make the backup",
    "NetBackup - Use network compression transfer during the backup operation"
    "Check - Verify the backup size",
    "Compress - Compress the backup directory"
    "SetDestination - Define a new destination to backup (Will override parameter's data)"
    "Exit - Exit the script"
)

[string]$UserEntry = ""
[bool]$WaitForCommand = $true
[System.IO.DirectoryInfo]$RefDirBackup = $null

while ($WaitForCommand)
{
    if ($Test)
    {
        Write-Host -Object "[TEST]" -ForegroundColor Red -NoNewline
    }

    $UserEntry = Read-Host -Prompt "Enter with a command >"

    switch ($UserEntry)
    {
        "Help"
        {
            WriteConsoleLine
            
            foreach ($h in $HelpCommand)
            {
                Write-Host -Object $h
            }
            
            WriteConsoleLine
            
            break
        }

        "Info"
        {
            WriteConsoleLine

            Write-Host -Object "Backup Path: " -NoNewline
            Write-Host -Object $ProjectDrivePath -ForegroundColor DarkYellow
            Write-Host -Object "Status: " -NoNewline

            [System.IO.DirectoryInfo]$Info = [System.IO.DirectoryInfo]::new($ProjectDrivePath)

            if ($Info.Exists)
            {
                if ($Info.Attributes -bor [System.IO.FileAttributes]::Directory)
                {
                    Write-Host -Object "Ready to backup" -ForegroundColor Green
                }
                else
                {
                    Write-Host -Object "Path do not point to a directory" -ForegroundColor Yellow
                }
            }
            else
            {
                Write-Host -Object "Path don't exist" -ForegroundColor Red
            }

            Write-Host -Object "Destination Path: " -NoNewline
            Write-Host -Object $Destination -ForegroundColor DarkYellow
            Write-Host -Object "Status: " -NoNewline

            if ($Destination)
            {
                [System.IO.DirectoryInfo]$Dest = [System.IO.DirectoryInfo]::new($Destination)

                if ($Dest.Exists)
                {
                    if ($Dest.Attributes -bor [System.IO.FileAttributes]::Directory)
                    {
                        Write-Host -Object "Ready" -ForegroundColor Green
                    }
                    else
                    {
                        Write-Host -Object "Path do not point to a directory" -ForegroundColor Yellow
                    }
                }
                else
                {
                    Write-Host -Object "Path don't exist" -ForegroundColor Red
                }
            }
            else
            {
                Write-Host -Object "Not defined" -ForegroundColor Red
            }

            WriteConsoleLine

            break
        }

        "Backup"
        {
            if ((Test-Path -Path $ProjectDrivePath -ErrorAction SilentlyContinue) -and (Test-Path -Path $Destination -ErrorAction SilentlyContinue))
            {
                $RefDirBackup = BackupWithRobocopy -InputDir $ProjectDrivePath -OutputBase $Destination -ExcludeDirs $ExcludeDirectories -LogOutput $Destination -ShowOnConsole -TestOperation:$Test
            }
            else
            {
                Write-Warning -Message "Backup and/or Destination path are not ready to be used. Use 'info' command for more information."
                $RefDirBackup = $null
            }
            break
        }

        "NetBackup"
        {
            if ((Test-Path -Path $ProjectDrivePath -ErrorAction SilentlyContinue) -and (Test-Path -Path $Destination -ErrorAction SilentlyContinue))
            {
                $RefDirBackup = BackupWithRobocopy -InputDir $ProjectDrivePath -OutputBase $Destination -ExcludeDirs $ExcludeDirectories -LogOutput $Destination -ShowOnConsole -UseCompression -TestOperation:$Test
            }
            else
            {
                Write-Warning -Message "Backup and/or Destination path are not ready to be used. Use 'info' command for more information."
                $RefDirBackup = $null
            }
            break
        }

        "Check"
        {
            $ProjectDriveContent = Get-ChildItem -Path $ProjectDrivePath -Exclude $ExcludeDirectories -Recurse -Force

            [double]$BackupSize = ($ProjectDriveContent | Measure-Object -Property Length -AllStats).Sum

            [string]$Unit = "B"

            if ($BackupSize -lt 1KB)
            {
                [string]$Unit = "B"
            }
            if ($BackupSize -gt 1KB -and $BackupSize -lt 1MB)
            {
                $BackupSize /= 1KB
                $Unit = "KB"
            }
            elseif ($BackupSize -gt 1MB -and $BackupSize -lt 1GB)
            {
                $BackupSize /= 1MB
                $Unit = "MB"
            }
            elseif ($BackupSize -gt 1GB -and $BackupSize -lt 1TB)
            {
                $BackupSize /= 1GB
                $Unit = "GB"
            }
            else
            {
                $BackupSize /= 1TB
                $Unit = "TB"
            }

            WriteConsoleLine

            Write-Host -Object "Backup Size: " -NoNewline
            Write-Host -Object "$([System.Math]::Round($BackupSize, 2)) $Unit" -ForegroundColor Cyan

            WriteConsoleLine

            break
        }

        "Compress"
        {
            if ($null -eq $RefDirBackup)
            {
                Write-Warning -Message "No backup directory was created!"
            }
            else
            {
                $RefDirBackup.Refresh()
                [string]$PathIn = $RefDirBackup.FullName
                [string]$PathOutput = "$($RefDirBackup.FullName).zip"
                [System.IO.Compression.ZipFile]::CreateFromDirectory($PathIn, $PathOutput, [System.IO.Compression.CompressionLevel]::SmallestSize, $true)
            }

            break
        }

        "SetDestination"
        {
            [string]$tmpDestination = Read-Host -Prompt "Set new destination (Empty entry cancel)"

            if ($tmpDestination.Length -gt 0)
            {
                $Destination = $tmpDestination
            }
            
            break
        }

        "Exit"
        {
            $WaitForCommand = $false
            break
        }

        Default
        {
            Write-Host -Object "Command not recognized!" -ForegroundColor Red
            break
        }
    }

    $UserEntry = ""
}

