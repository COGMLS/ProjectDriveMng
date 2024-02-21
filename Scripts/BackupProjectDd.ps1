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

        [string]$ProjectDbBackupName = "$($ProjectDbFileInfo.BaseName)_BACKUP-$($ProjectDbFileInfo.LastWriteTime.ToString("yyyy-MM-dd HH-mm-ss"))$($ProjectDbFileInfo.Extension)"

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

if ($Backup)
{
    MakeProjectDriveDbBackup
}
elseif (-not $Backup -and $ListOnlyBackups)
{
    ListProjectDriveDb -OnlyBackups
}
else
{
    ListProjectDriveDb
}