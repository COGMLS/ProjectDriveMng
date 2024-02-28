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
.EXAMPLE
    BackupProjectDb.ps1 -Restore
    Restore the ProjectDatabase file, using the newest backup file.
.EXAMPLE
    BackupProjectDb.ps1 -Restore -Backup
    Make a backup of the actual database file before restore it with the newest ProjectDatabase's backup file.
.EXAMPLE
    BackupProjectDb.ps1 -Restore -DateTime "2024-02-21 16-14-50"
    Restore the ProjectDatabase file, using the date and time reference backup last write time information.
    NOTE: The date and time format accepted are: "YYYY-MM-DD hh-mm-ss" and "YYYY-MM-DD hh:mm:ss"
.EXAMPLE
    BackupProjectDb.ps1 -Backup -Restore -DateTime "2024-02-21 16-14-50"
    Make a backup of the actual database file and restore the ProjectDatabase file, using the date and time reference backup last write time information. 
    NOTE: The date and time format accepted are: "YYYY-MM-DD hh-mm-ss" and "YYYY-MM-DD hh:mm:ss"
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
    # NOTE: The date and time format accepted are: "YYYY-MM-DD hh-mm-ss" and "YYYY-MM-DD hh:mm:ss"
    [Parameter(Mandatory = $false, Position = 1)]
    [string]
    $DateTime,

    # List only backup. This option does not have effect if Backup parameter is send.
    [Parameter(Mandatory = $false, Position = 0)]
    [switch]
    $ListOnlyBackups
)

# Global variables: (DO NOT CHANGE THEM!)
[string]$ProjectDbBaseName = "ProjectsDatabase"
[string]$ProjectDbExtension = ".accdb"
[string]$ProjectDbFileName = "$($ProjectDbBaseName)$($ProjectDbExtension)"
[string]$ManagementFolder = "Gerenciamento"
[string]$BackupDirName = "Backup"
[string]$BackupSigniture = "_BACKUP-"
[string]$DateTimeStringConverter = "yyyy-MM-dd HH-mm-ss"
[string]$RegexDateTime_Date = "\[0-9]\[0-9]\[0-9]\[0-9]-\[0-9]\[0-9]-\[0-9]\[0-9]"
[string]$RegexDateTime_Time = "T\[0-9]:\[0-9]:\[0-9]"

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

    if ($ProjectDbFileInfo.Directory.Exists)
    {
        if ($ProjectDbFileInfo.Exists -and -not $OnlyBackups)
        {
            $ProjectDbList.Add($ProjectDbFileInfo)
        }
    
        if ($BackupDirInfo.Exists)
        {
            [System.IO.FileInfo[]]$BackupFilesArr = $BackupDirInfo.GetFiles("$ProjectDbBaseName*", [System.IO.SearchOption]::TopDirectoryOnly)

            if ($BackupFilesArr.Length -gt 0)
            {
                $BackupFilesArr = $BackupFilesArr | Sort-Object -Property LastWriteTime -Descending

                foreach ($BackupFile in $BackupFilesArr)
                {
                    $ProjectDbList.Add($BackupFile)
                }
            }
        }
        
        $ProjectDbList | Format-Table -AutoSize
    }
    else
    {
        Write-Host -Object "The directory $($ProjectDbFileInfo.Directory.FullName) doesn't exist!"
    }
}

function RestoreProjectDriveDbBackup
{
    [bool]$UseMostRecentBackup = $true
    [System.DateTime]$BackupDt = [System.DateTime]::MinValue

    if ($DateTime.Length -gt 0)
    {
        try
        {
            [string[]]$DtStr = $DateTime.Split(' ', 2)

            if ($DtStr.Count -eq 2)
            {
                if ($DtStr[1].Contains('-'))
                {
                    $DtStr[1] = $DtStr[1].Replace('-',':')
                }

                [string]$DateTimeConverted = $DtStr[0] + "T" + $DtStr[1]

                $BackupDt = [System.DateTime]::Parse($DateTimeConverted)
                $UseMostRecentBackup = $false
            }
        }
        catch
        {
            throw [System.Exception]::new("Fail to convert the value $($DateTime) to System.DateTime data.")
        }
    }
    
    [string]$BackupDirPath = [System.IO.Path]::Combine($env:ProjectDrive, $ManagementFolder, $BackupDirName)
    [System.IO.DirectoryInfo]$BackupDirInfo = [System.IO.DirectoryInfo]::new($BackupDirPath)

    [System.IO.FileInfo]$OriginalProjectDriveDbFileInfo = [System.IO.FileInfo]::new([System.IO.Path]::Combine($env:ProjectDrive, $ManagementFolder, $ProjectDbFileName))

    if ($BackupDirInfo.Exists)
    {
        [System.IO.FileInfo[]]$BackupFiles = $BackupDirInfo.GetFiles("$($ProjectDbBaseName)$($BackupSigniture)*", [System.IO.SearchOption]::TopDirectoryOnly)
        
        if ($BackupFiles.Length -gt 0)
        {
            [System.IO.FileInfo]$Backup2Restore = $null

            # Restore the most recent backup.
            if ($UseMostRecentBackup)
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
                        Write-Error -Message "Fail to copy file"
                    }

                    [System.IO.FileInfo]$CopiedFile = [System.IO.FileInfo]::new($OriginalProjectDriveDbFileInfo.FullName)

                    if ($CopiedFile.LastWriteTime -eq $Backup2Restore.LastWriteTime)
                    {
                        if ($CopiedFile.IsReadOnly)
                        {
                            $CopiedFile.Attributes = $CopiedFile.Attributes -= [System.IO.FileAttributes]::ReadOnly
                        }

                        Write-Host -Object "DataBase $($Backup2Restore.Name) from $($Backup2Restore.LastWriteTime.ToString($DateTimeStringConverter)) was restored with success!" -ForegroundColor Green
                    }
                    else
                    {
                        Write-Host -Object "The backup dataBase file $($Backup2Restore.Name) wasn't restored!"
                        
                        Write-Host -Object "Backup to restore:"
                        $Backup2Restore

                        Write-Host -Object "`nActual file:"
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
        RestoreProjectDriveDbBackup
    }
}
elseif ($Restore)
{
    RestoreProjectDriveDbBackup
}
elseif (-not $Backup -and -not $Restore -and $ListOnlyBackups)
{
    ListProjectDriveDb -OnlyBackups
}
else
{
    ListProjectDriveDb
}