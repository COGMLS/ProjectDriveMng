<################################################################################
 # Project: Backup Project Drive DataBase
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
    Script used make backup routines for ProjectDatabase.accdb
.DESCRIPTION

.NOTES
    This script uses default resources available in .NET 7.0 and superior and PowerShell 7.0.
.LINK
    No additional help is available. Use the 'help' internal command to access the script commands.
.EXAMPLE
    BackupProjectDb.ps1 -Backup
    Make a backup of ProjectDatabase file. The backup folder will be created inside destination directory is doesn't exist.
.EXAMPLE
    BackupProjectDb.ps1
    List all ProjectDatabase files available, including the file in use.
.EXAMPLE
    BackupProjectDb.ps1 -ListOnlyBackups
    List only the ProjectDatabase backup files available.
#>

Param
(
    # Make the backup. Otherwise, show the backups available.
    [Parameter(Mandatory = $false, Position = 0)]
    [switch]
    $Backup,

    # Restore a backup file. This parameter can be used with Backup, to set a backup before restore the file.
    [Parameter(Mandatory = $false, Position = 0)]
    [switch]
    $Restore,

    # Specify the date and time backup to restore. This parameter only have effect when Restore is used.
    [Parameter(Mandatory = $false, Position = 1)]
    [System.DateTime]
    $DateTime,

    # List only backup. This option does not have effect if Backup parameter is send.
    [Parameter(Mandatory = $false, Position = 0)]
    [switch]
    $ListOnlyBackups
)

[string]$ProjectDbBaseName = "ProjectsDatabase"
[string]$ProjectDbExtension = ".accdb"
[string]$ProjectDbFileName = "$($ProjectDbBaseName)$($ProjectDbExtension)"
[string]$ManagementFolder = "Gerenciamento"
[string]$BackupDirName = "Backup"
[string]$BackupSigniture = "_BACKUP-"
[string]$DateTimeStringConverter = "yyyy-MM-dd HH-mm-ss"

function MakeProjectDriveDbBackup
{
    [System.IO.FileInfo]$ProjectDbFileInfo = [System.IO.FileInfo]::new([System.IO.Path]::Combine($env:ProjectDrive, $ManagementFolder, $ProjectDbFileName))

    if ($ProjectDbFileInfo.Exists)
    {
        [System.IO.DirectoryInfo]$BackupDirInfo = [System.IO.DirectoryInfo]::new([System.IO.Path]::Combine($env:ProjectDrive, $ManagementFolder, $BackupDirName))

        if (-not $BackupDirInfo.Exists)
        {
            $BackupDirInfo.Create()
        }

        [string]$ProjectDbBackupName = "$($ProjectDbFileInfo.BaseName)$($BackupSigniture)$($ProjectDbFileInfo.LastWriteTime.ToString($DateTimeStringConverter))$($ProjectDbFileInfo.Extension)"

        [string]$ProjectDbBackupPath = [System.IO.Path]::Combine($BackupDirInfo.FullName, $ProjectDbBackupName)

        try
        {
            Copy-Item -Path $ProjectDbFileInfo -Destination $ProjectDbBackupPath -Verbose -Force -Confirm
            
            [System.IO.FileInfo]$ProjectDbBackupInfo = [System.IO.FileInfo]::new($ProjectDbBackupPath)
            
            if ($ProjectDbBackupInfo.Exists)
            {
                try
                {
                    $ProjectDbBackupInfo.Attributes += [System.IO.FileAttributes]::ReadOnly
                }
                catch
                {
                    Write-Error -Message "Fail to set backup as Readonly"
                }
            }
            else
            {
                Write-Error -Message "The backup file doesn't appear on $($BackupDirName) folder"
            }
        }
        catch
        {
            Write-Error -Message "Fail in create the backup"
        }
    }
    else
    {
        Write-Error -Message "File $($ProjectDbFileInfo) does not exist!"
    }
}

function ListProjectDriveDb
{
    Param
    (
        [switch]$OnlyBackups
    )

    [System.Collections.Generic.List[System.IO.FileInfo]]$ProjectDbList = [System.Collections.Generic.List[System.IO.FileInfo]]::new()

    [System.IO.FileInfo]$ProjectDbFileInfo = [System.IO.FileInfo]::new([System.IO.Path]::Combine($env:ProjectDrive, $ManagementFolder, $ProjectDbFileName))
    [System.IO.DirectoryInfo]$BackupDirInfo = [System.IO.DirectoryInfo]::new([System.IO.Path]::Combine($env:ProjectDrive, $ManagementFolder, $BackupDirName))

    if ($ProjectDbFileInfo.Exists -and -not $OnlyBackups)
    {
        $ProjectDbList.Add($ProjectDbFileInfo)
    }

    if ($BackupDirInfo.Exists)
    {
        foreach ($BackupFile in $BackupDirInfo.EnumerateFiles("$ProjectDbBaseName*", [System.IO.SearchOption]::TopDirectoryOnly))
        {
            $ProjectDbList.Add($BackupFile)
        }
    }

    $ProjectDbList | Format-Table -AutoSize
}

function RestoreProjectDriveDbBackup
{
    Param
    (
        [System.DateTime]$BackupDt = $null
    )
    
    [string]$BackupDirPath = [System.IO.Path]::Combine($env:ProjectDrive, $ManagementFolder, $BackupDirName)
    [System.IO.DirectoryInfo]$BackupDirInfo = [System.IO.DirectoryInfo]::new($BackupDirPath)

    [System.IO.FileInfo]$OriginalProjectDriveDbFileInfo = [System.IO.FileInfo]::new([System.IO.Path]::Combine($env:ProjectDrive, $ManagementFolder, $ProjectDbFileName))

    if ($BackupDirInfo.Exists)
    {
        [System.IO.FileInfo[]]$BackupFiles = $BackupDirInfo.GetFiles("$($ProjectDbBaseName)$($BackupSigniture)", [System.IO.SearchOption]::TopDirectoryOnly)
        
        if ($BackupFiles.Length -gt 0)
        {
            [System.IO.FileInfo]$Backup2Restore = $null

            # Restore the most recent backup.
            if ($null -eq $BackupDt)
            {
                $BackupFiles = $BackupFiles | Sort-Object -Property LastWriteTime -Descending

                $Backup2Restore = $BackupFiles[0]
            }
            else
            {
                [string]$Dt2Str = $BackupDt.ToString($DateTimeStringConverter)
                [string]$ProjectDriveDbNameSearch = "$($ProjectDbBaseName)$($BackupSigniture)$($Dt2Str)$($ProjectDbExtension)"

                for ($i = 0; $i -lt $BackupFiles.Length; $i++)
                {
                    if ($BackupFiles[$i].Name -eq $ProjectDriveDbNameSearch)
                    {
                        $Backup2Restore = $BackupFiles[$i]
                        break
                    }
                }
            }

            if ($null -ne $Backup2Restore)
            {
                if ($Backup2Restore.Exists)
                {
                    try
                    {
                        Copy-Item -Path $Backup2Restore -Destination $OriginalProjectDriveDbFileInfo.FullName -Verbose -Force -Confirm
                    }
                    catch
                    {
                        
                    }

                    [System.IO.FileInfo]$CopiedFile = [System.IO.FileInfo]::new($OriginalProjectDriveDbFileInfo.FullName)

                    if ($CopiedFile.LastWriteTime -eq $Backup2Restore.LastWriteTime)
                    {
                        Write-Host -Object "DataBase $($Backup2Restore.Name) from $($Backup2Restore.LastWriteTime.ToString($DateTimeStringConverter)) was restored with success!" -ForegroundColor Green
                    }
                    else
                    {
                        Write-Host -Object "Fail in retore the DataBase file $($Backup2Restore.Name)!"
                        Write-Host -Object "Backup to restore:"
                        $Backup2Restore
                        Write-Host -Object "Actual file:"
                        $OriginalProjectDriveDbFileInfo
                    }
                }
                else
                {
                    Write-Host -Object "The backup file $($Backup2Restore.Name) doesn't exist!"
                }
            }
            else
            {
                Write-Host -Object "Fail to find the backup $($ProjectDriveDbNameSearch)"
            }
        }
        else
        {
            Write-Host -Object "There is no backup file available to make the restore operation!"
        }
    }
    else
    {
        Write-Host -Object "The backup folder doesn't exist!"
    }
}

if ($Backup)
{
    MakeProjectDriveDbBackup

    if ($Restore)
    {
        if ($null -eq $DateTime)
        {
            RestoreProjectDriveDbBackup
        }
        else
        {
            RestoreProjectDriveDbBackup -BackupDt $DateTime
        }
    }
}
elseif ($Restore)
{
    if ($null -eq $DateTime)
    {
        RestoreProjectDriveDbBackup
    }
    else
    {
        RestoreProjectDriveDbBackup -BackupDt $DateTime
    }
}
elseif (-not $Backup -and -not $Restore -and $ListOnlyBackups)
{
    ListProjectDriveDb -OnlyBackups
}
else
{
    ListProjectDriveDb
}