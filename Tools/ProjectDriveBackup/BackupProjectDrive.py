#################################################
# Archive Script for Project Drive:
# ----------------------------------------------
# This Python script is developed for Linux systems
# at first place. The support for Windows OS will
# included in the future.
#
#################################################

import os
import sys
import tarfile
import time
import io
import math

# Version info:
__ScriptVersionNumber__ = {
        "Major"     :   0,
        "Minor"     :   8,
        "Revision"  :   0
    }

# Debug Script mode:
DEBUG_SCRIPT = False

# Control Variables:
bDebugScript = DEBUG_SCRIPT
bExperimentalMode = False
bForceProjectDrivePath = False
bForceBackupDestination = False
bForceLogDestination = False
bIsHelpCli = False

# Help command line:
helpCmd = ["-help","-h","-?"]

# Help CLI info:
help_cli = [
    "--force-projectdrive-path\n\t\tForce to use an specific path for Project Drive\n\t\tThis parameter is useful when the PROJECTDRIVE is not set on user environment",
    "--force-backup-destination\n\t\tForce to use an specific path to save the backup file",
    "--force-log-destination\n\t\tForce to use an specific path to save the log files\n\t\tThe default location is the system temporary directory"
]

# Help Console:
help_console = [
    "Commands available for Project Drive Manager:",
    " help\t\tShow the commands available",
    " backup ProjectDrive\tStart a complete backup from Project Drive with TAR file backup and compression",
    " print ProjectDrive\tPrint the paths that will be added into the backup of Project Drive",
    "status\t\tGet the path status before start any backup",
    "status reset\t\tReset custom paths used in command line to default values",
    " exit\t\tClose the script console"
]

# Help arrays index:
help_arrays = [help_cli, help_console]

# Check for Debug parameter:
if not bDebugScript:
    for arg in sys.argv:
        if arg.lower() == "--debugscript" or arg.lower() == "-debug":
            bDebugScript = True
            pass
        if arg.lower() == "--experimental":
            bExperimentalMode = True
            pass
        if arg.lower() == helpCmd[0] or arg.lower() == helpCmd[1] or arg.lower() == helpCmd[2]:
            bIsHelpCli = True
            pass
        pass
    pass

# Script Constants:

USER_PATH=os.getenv("HOME")
USER_NAME=os.getenv("USER")

DEFAULT_PROJECT_DRIVE_PATH = os.getenv("PROJECTDRIVE")
DEFAULT_BACKUP_DESTINATION_PATH = f"/media/{USER_NAME}/Backup Drive/ProjectDrive"
DEFAULT_LOG_DESTINATION_PATH = f"/tmp"

# Script Global Variables:

ProjectDrivePath=DEFAULT_PROJECT_DRIVE_PATH
BackupBaseDestination=DEFAULT_BACKUP_DESTINATION_PATH
LogDestinationPath=DEFAULT_LOG_DESTINATION_PATH

ProjectDriveExcludeFiles=[]

ProjectDriveExcludeDirs=[
    "$RECYCLE.BIN",
    "System Volume Information"
]
ProjectDriveExcludePattern=[
    ".Trash-*"
]

# Script Methods:

# Script Presentation:
def PrintScriptPresentation(addLine: bool = False) -> None:
    global bExperimentalMode
    presentation = f"Project Drive Backup Script - {__ScriptVersionNumber__['Major']}.{__ScriptVersionNumber__['Minor']}.{__ScriptVersionNumber__['Revision']}"
    if bExperimentalMode:
        presentation += " | EXPERIMENTAL MODE"
        pass
    print(presentation)
    if addLine:
        terminal_columns = os.get_terminal_size().columns
        line = ""
        i = 0
        while i < terminal_columns:
            line += '-'
            i = i + 1
            pass
        print(line)
        pass
    pass

# Print the help command, based on help array index
def PrintHelp(printHelpArr: int) -> None:
    global help_arrays
    if printHelpArr < 0 or printHelpArr >= len(help_arrays):
        print(f"[ERROR]::PrintHelp method received an unrecognizable help array! | Argument value: {printHelpArr}")
        pass
    if printHelpArr == 0:
        PrintScriptPresentation(True)
        i = 0
        iMax = len(helpCmd)
        help_str = ""
        while i < iMax:
            if i + 1 < iMax:
                help_str += f"{helpCmd[i]} "
                pass
            else:
                help_str += f"{helpCmd[i]}"
                pass
            pass
        help_str += "\tPrint the help information"
        print(help_str)
        pass
    i = 0
    iMax = len(help_arrays[printHelpArr])
    while i < iMax:
        print(help_arrays[printHelpArr][i])
        i = i + 1
        pass
    pass

# Get the Date Time information as a string, using ISO 8601 format
# NOTE: If exportTimeZone is true but not exportTime, the time will be exported
# NOTE: timeStrCompatibleWithFs: Export the time string compatible with filesystems, using dash instead of two dots
def getTimeStr(exportTime: bool, exportTimeZone: bool, timeStrCompatibleWithFs: bool) -> str:
    timeStr = ""

    if not exportTime and exportTimeZone:
        exportTime = True
        pass

    lTime = time.localtime()
    # Time String for Year-Month-Day:
    month = f"{lTime.tm_mon}"
    day = f"{lTime.tm_mday}"

    if lTime.tm_mon < 10:
        month = f"0{month}"
        pass
    if lTime.tm_mday < 10:
        day = f"0{day}"
        pass

    if timeStrCompatibleWithFs:
        timeStr = f"{lTime.tm_year}-{month}-{day}"
        pass
    else:
        timeStr = f"{lTime.tm_year}/{month}/{day}"
        pass

    # Complete Date Time info for YYYY-MM-dd_HH-mm-ssT<TimeZone>:
    hour = f"{lTime.tm_hour}"
    minute = f"{lTime.tm_min}"
    second = f"{lTime.tm_sec}"

    if lTime.tm_hour < 10:
        hour = f"0{lTime.tm_hour}"
        pass
    if lTime.tm_min < 10:
        minute = f"0{lTime.tm_min}"
        pass
    if lTime.tm_sec < 10:
        second = f"0{lTime.tm_sec}"
        pass

    if exportTime:
        if timeStrCompatibleWithFs:
            timeStr = f"{timeStr}_{hour}-{minute}-{second}"
            pass
        else:
            timeStr = f"{timeStr} {hour}:{minute}:{second}"
            pass
        pass

    if exportTimeZone:
        if timeStrCompatibleWithFs:
            timeStr = f"{timeStr}T{lTime.tm_zone}"
            pass
        else:
            timeStr = f"{timeStr} T {lTime.tm_zone}"
            pass
        pass

    return timeStr

# Write the entries in the log object:
def writeLogEntry(title: str, msg: list[str], logFile: io.TextIOWrapper) -> None:
    if logFile.writable():
        logFile.seek(0, io.SEEK_END)

        if len(msg) <= 1:
            if len(msg) == 1:
                logEntry = f"{title}::{msg[0]}\n"
                pass
            else:
                logEntry = f"{title}\n"
                pass
            pass
        else:
            logEntry = f"{title}:\n"
            for i in msg:
                logEntry = logEntry + f"\t{i}\n"
                pass
            pass
        pass

        if logEntry != "":
            logFile.writelines(logEntry)
            pass
    pass

# Get the Path list, filtering the files, directories and path patterns:
def getPathList() -> list:
    pathList = []

    listDir = os.listdir(ProjectDrivePath)

    for i in listDir:
        bIsExcludeDir = False

        # Verify if the current path is part of the Exclude Directory List:
        for j in ProjectDriveExcludeDirs:
            if i == j:
                bIsExcludeDir = True;
                break
            pass

        bAdd2List = False

        if not bIsExcludeDir:
            # Test the path for directories and files. Other filesystem object should be excluded from the backup list:
            p = ProjectDrivePath + "/" + i
            if os.path.isdir(p):
                bAdd2List = True
                pass

            if os.path.isfile(p):
                bAdd2List = True
                pass

            # Verify if the item is part of the pattern exclusion list:
            for j in ProjectDriveExcludePattern:
                if j.startswith('*') and j.endswith('*'):
                    j = j.removesuffix('*')
                    j = j.removeprefix('*')
                    if p.__contains__(j):
                        bAdd2List = False
                        break
                    pass
                
                if j.endswith('*') and not j.startswith('*'):
                    j = j.removesuffix('*')
                    if i.startswith(j):
                        bAdd2List = False
                        break
                    pass
                
                if j.startswith('*') and not j.endswith('*'):
                    j = j.removeprefix('*')
                    if i.endswith(j):
                        bAdd2List = False
                        break
                    pass
                pass

        # If the item passed, add it into the backup path list:
        if bAdd2List:
            pathList.append(p)
            pass

    return pathList

# Get the complete path list, with more options to filter the files, directories and path patterns:
def getPathList2(path: str, excludeDirs = list[str], excludeFiles = list[str], excludePattern = list[str], bListDir = True, bListFiles = True) -> list[str]:
    if not os.path.exists(path):
        return list[str]
    
    pathList = []

    listDir = os.listdir(path)

    for i in listDir:
        bIsExcludeDir = False
        bIsExcludeFile = False

        for j in excludeDirs:
            if i == j:
                bIsExcludeDir = True
                break
            pass

        for j in excludeFiles:
            if i == j:
                bIsExcludeFile = True
                break
            pass

        bAdd2List = False

        if not bIsExcludeDir and not bIsExcludeFile:
            p = path + "/" + i
            if os.path.isdir(p):
                bAdd2List = True
                pass

            if os.path.isfile(p):
                bAdd2List = True
                pass

            for j in excludePattern:
                if j.startswith('*') and j.endswith('*'):
                    j = j.removesuffix('*')
                    j = j.removeprefix('*')
                    if p.__contains__(j):
                        bAdd2List = False
                        break
                    pass
                
                if j.endswith('*') and not j.startswith('*'):
                    j = j.removesuffix('*')
                    if i.startswith(j):
                        bAdd2List = False
                        break
                    pass
                
                if j.startswith('*') and not j.endswith('*'):
                    j = j.removeprefix('*')
                    if i.endswith(j):
                        bAdd2List = False
                        break
                    pass
                pass

        if bAdd2List:
            if os.path.isfile(p) and bListFiles:
                pathList.append(p)
                pass
            if os.path.isdir(p) and bListDir:
                pathList.append(p)
                pass
            pass

    return pathList

# Create an tar file to make the backup:
def mkTarFile(basepath: str, backup_fileName: str, compress: bool, backupDateTime: str = "") -> (tarfile.TarFile | int):
    backup_dateTime = backupDateTime
    if backup_dateTime == "":
        backup_dateTime = getTimeStr(True, False, True)
        pass
    backup_extension = ".tar"

    if compress:
        backup_extension = ".tar.gz"
        pass

    backup_fullname = f"{backup_fileName}_{backup_dateTime}{backup_extension}"
    backup_path = f"{basepath}/{backup_fullname}"

    try:
        tar = tarfile.open(backup_path, "x:gz", None, tarfile.GNU_FORMAT)
        return tar
    except:
        print(f"Fail to create the tar file: {sys.exception()}")
        return 1

# Add a new path into the backup file
# This method return 0 if a file was add and 1 when it is a directory. In case of exception, will return -1. If the path does not exists, will return -2
def add2TarFile(tarObj: tarfile.TarFile, workPath: str, path2Add: str, includeWorkPath: bool) -> int:
    current_working_dir = os.getcwd()
    originalPath2Add = path2Add
    try:
        if os.path.exists(path2Add):
            if path2Add.startswith(workPath):
                path2Add = path2Add.removeprefix(workPath)
                if path2Add.startswith("/"):
                    if includeWorkPath:
                        wdn = os.path.basename(workPath)
                        path2Add = f"{wdn}{path2Add}"
                        pass
                    else:
                        path2Add = path2Add.removeprefix("/")
                        pass
                    pass
                pass
            pass
        else:
            return -2
        
        if includeWorkPath:
            #workDirName = os.path.basename(workPath)
            #workPath = workPath.removesuffix(f"/{workDirName}")
            workPath = os.path.dirname(workPath)
            pass

        os.chdir(workPath)
        tarObj.add(path2Add)
        os.chdir(current_working_dir)

        if os.path.isdir(originalPath2Add):
            return 1
        
        return 0
    except:
        os.chdir(current_working_dir) # Restore to original current working directory if fails
        print(f"Fail to add path: {path2Add} into tar file")
        print(f"Exception: {sys.exception()}")
        return -1

# Show a progress bar
def progressBar(totalPaths, actualPathsProcessed) -> None:
    consoleLength = os.get_terminal_size().columns
    barStart = f"Status:["
    barEnd = f"] "
    p = actualPathsProcessed / totalPaths * 100
    p = math.floor(p)
    
    if p < 10:
        barEnd = f"{barEnd}  {p}/100"
        pass
    elif p >= 10 and p < 100:
        barEnd = f"{barEnd} {p}/100"
        pass
    else:
        barEnd = f"{barEnd}{p}/100"
        pass

    bar = ""

    consoleLengthRemain = consoleLength - (len(barStart) + len(barEnd)) - 50
    barDrawing = consoleLengthRemain * p / 100

    i = 0
    while i < consoleLengthRemain:
        if i <= barDrawing:
            bar = bar + '█'
            pass
        else:
            bar = bar + '.'
            pass
        i = i + 1
        pass

    bar = barStart + bar + barEnd

    if p < 100:
        print(bar, end='\r', flush=True, file=sys.stdout)
        pass
    else:
        print(bar, end='\n', flush=True, file=sys.stdout)
        pass
    pass

# Make a TAR Backup
# ---------Params------------
# backupListPaths: List of paths to make the backup
# workingDirPath: Base working directory for the backup
# backupBasePath: Base location for the backup file
# backupFileName: Name for the TAR file that will receive the backup date and time in it's name
# baseBackupLogPath: Path to save the backup log. The log file will include the base backup file name and the backup date and time in it's name
# compressBackupFile: If True, will compress the file with .tar.gz extension
# includeLogInBackupFile: If True will add the log file inside the base of the backup file and remove from the system temp folder
def makeTarBackup(backupListPaths: list[str], workingDirPath: str, backupBasePath: str, backupBaseFileName: str, baseBackupLogPath: str, compressBackupFile: bool, includeLogInBackupFile: bool) -> int:
    backup_date_time = getTimeStr(True, False, True)
    backupLogPath = f"{baseBackupLogPath}/{backupBaseFileName}_{backup_date_time}.log"

    backupLog = open(backupLogPath, 'wt', encoding="utf-8")
    backupLogBasePath = os.path.dirname(backupLogPath)

    # Prepare the TAR backup file:
    tarFileName = backupBaseFileName
    tarFileBasePath = backupBasePath
    tarCompletePath = f"{tarFileBasePath}/{tarFileName}"
    
    if os.path.exists(tarCompletePath):
        os.remove(tarCompletePath)
        pass

    tarObj = mkTarFile(tarFileBasePath, tarFileName, compressBackupFile, backup_date_time)

    # Add the base information about the backup file into the log:
    writeLogEntry("Tar backup file", [tarCompletePath], backupLog)
    writeLogEntry("Backup created", [getTimeStr(True, True, False)], backupLog)
    writeLogEntry("---------------------------------------", [], backupLog)
    writeLogEntry("Paths to backup", backupListPaths, backupLog)
    writeLogEntry("---------------------------------------", [], backupLog)

    # Get the original working directory
    cwd = os.getcwd()

    # Prepare the backup counters:
    totalPaths = len(backupListPaths)
    actualPathsProcessed = 0

    backupOfDirs = 0
    backupOfFiles = 0
    backupFails = 0

    progressBar(totalPaths, actualPathsProcessed)

    backupArr = []

    # Backup the paths:
    for i in backupListPaths:
        b = i
        i = f"{os.path.basename(workingDirPath)}/{os.path.basename(b)}"
        status = add2TarFile(tarObj, workingDirPath, b, True)
        backupArr.append(f"{b} backup as TAR path: {i} | Status: {status}")
        if status == 0:
            backupOfFiles += 1
            pass
        elif status == 1:
            backupOfDirs += 1
            pass
        else:
            backupFails += 1
            pass
        actualPathsProcessed = actualPathsProcessed + 1
        progressBar(totalPaths, actualPathsProcessed)
        pass

    # Print the backup resume and close it:
    writeLogEntry("Succeed backup paths", backupArr, backupLog)
    writeLogEntry("---------------------------------------", [], backupLog)
    backupResume = [
        f"Total of paths to backup: {totalPaths}",
        f"Total of Directories: {backupOfDirs}",
        f"Total of Files: {backupOfFiles}",
        f"Total of Fails: {backupFails}"
    ]
    writeLogEntry("Backup Resume", backupResume, backupLog)
    writeLogEntry("---------------------------------------", [], backupLog)

    completeTime = getTimeStr(True, True, False)

    writeLogEntry(f"Backup completed in time: {completeTime}", [], backupLog)
    backupLog.close()

    # Add the log file:
    if includeLogInBackupFile:
        os.chdir(backupLogBasePath)
        logName = backupLogPath.removeprefix(backupLogBasePath)
        if logName.startswith('/'):
            logName = logName.removeprefix('/')
            pass
        add2TarFile(tarObj, backupLogBasePath, logName, False)
        pass

    # Close the backup file:
    tarObj.close()

    # Restore the original working directory:
    os.chdir(cwd)

    # Remove the backup log is included into the backup file:
    backupLog.close()

    if includeLogInBackupFile:
        if os.path.exists(backupLogPath):
            os.remove(backupLogPath)
            pass
        pass

    # Return zero if no error in the function was found:
    return 0

# Print the paths to backup:
def printBackupList(backupList: list[str]) -> None:
    for i in backupList:
        print(f"Path: {i}")
        pass
    pass

# Get or Update the global variables status and check for availability to make the script's functions:
def scriptStatus(printStatus: bool, resetPaths: bool) -> None:
    global BackupBaseDestination
    global ProjectDrivePath
    global LogDestinationPath

    # Control Variables:

    ProjectDrivePathStatus = "Does not exist"
    BackupBaseDestinationStatus = "Does not exist"
    LogDestinationPathStatus = "Does not exist"
    
    # Check for all paths:

    testProjectDrivePath = ""
    testBackupBaseDestination = ""
    testLogDestination = ""

    if resetPaths:
        BackupBaseDestination = DEFAULT_BACKUP_DESTINATION_PATH
        ProjectDrivePath = DEFAULT_PROJECT_DRIVE_PATH
        LogDestinationPath = DEFAULT_LOG_DESTINATION_PATH
        pass

    if bForceProjectDrivePath:
        testProjectDrivePath = ProjectDrivePath
        pass
    else:
        #testProjectDrivePath = DEFAULT_PROJECT_DRIVE_PATH
        testProjectDrivePath = ProjectDrivePath
        pass

    if bForceBackupDestination:
        testBackupBaseDestination = BackupBaseDestination
        pass
    else:
        #testBackupBaseDestination = DEFAULT_BACKUP_DESTINATION_PATH
        testBackupBaseDestination = BackupBaseDestination
        pass

    if bForceLogDestination:
        testLogDestination = LogDestinationPath
        pass
    else:
        #testLogDestination = DEFAULT_LOG_DESTINATION_PATH
        testLogDestination = LogDestinationPath
        pass

    if os.path.exists(testProjectDrivePath):
        ProjectDrivePathStatus = "Not a directory"
        if os.path.isdir(testProjectDrivePath):
            ProjectDrivePathStatus = "Ready"
            pass
        pass

    if os.path.exists(testBackupBaseDestination):
        BackupBaseDestinationStatus = "Not a directory"
        if os.path.isdir(testBackupBaseDestination):
            BackupBaseDestinationStatus = "Ready"
            pass
        pass

    if os.path.exists(testLogDestination):
        LogDestinationPathStatus = "Not a directory"
        if os.path.isdir(testLogDestination):
            LogDestinationPathStatus = "Ready"
            pass
        pass

    if printStatus:
        print("Project Drive Manager Script Status:")
        print("--------------------------------------------------------")
        print(f"Project Drive Path: {testProjectDrivePath}")
        print(f"\tStatus: {ProjectDrivePathStatus}")
        print(f"Backup base path: {testBackupBaseDestination}")
        print(f"\tStatus: {BackupBaseDestinationStatus}")
        print(f"Log destination path: {testLogDestination}")
        print(f"\tStatus: {LogDestinationPathStatus}")
        print("")
        pass
    pass

# Check the command line:
def chkCmdLine() -> None:
    global ProjectDrivePath
    global BackupBaseDestination
    global LogDestinationPath

    chkProjectDrivePath = 0
    chkBackupBasePath = 0
    chkLogBasePath = 0

    for arg in sys.argv:
        if chkProjectDrivePath == 1:
            if not arg.startswith('-'):
                chkProjectDrivePath = 2
                ProjectDrivePath = arg
                pass
            else:
                chkProjectDrivePath = -1
                pass
            pass
        if chkBackupBasePath == 1:
            if not arg.startswith('-'):
                chkBackupBasePath = 2
                BackupBaseDestination = arg
                pass
            else:
                chkBackupBasePath = -1
                pass
            pass
        if chkLogBasePath == 1:
            if not arg.startswith('-'):
                chkLogBasePath = 2
                LogDestinationPath = arg
                pass
            else:
                chkLogBasePath = -1
                pass
            pass

        if arg.lower() == "--force-projectdrive-path" and chkProjectDrivePath == 0:
            chkProjectDrivePath = 1
            pass
        if arg.lower() == "--force-backup-destination" and chkBackupBasePath == 0:
            chkBackupBasePath = 1
            pass
        if arg.lower() == "--force-log-destination" and chkLogBasePath == 0:
            chkLogBasePath = 1
            pass
        pass
    pass

# ---------------------------------------------------------
# Script Start Here:
# ---------------------------------------------------------

# Make a full command line check:
chkCmdLine()

if bIsHelpCli:
    PrintHelp(0)
    exit(0)

PrintScriptPresentation(True)

while (True):
    command = input(">")

    # Make the console more permissive, allowing any type of writing:
    command = command.lower()

    if command == "exit":
        break
    if command == "help":
        PrintHelp(1)
        pass
    elif command == "print projectdrive":
        myDirList = getPathList2(ProjectDrivePath, ProjectDriveExcludeDirs, ProjectDriveExcludeFiles, ProjectDriveExcludePattern, True, True)
        printBackupList(myDirList)
        pass
    elif command == "backup projectdrive":
        tarFileName = f"ProjectDriveBackup"
        tarFileBasePath = BackupBaseDestination
        myDirList = getPathList2(ProjectDrivePath, ProjectDriveExcludeDirs, ProjectDriveExcludeFiles, ProjectDriveExcludePattern, True, True)
        makeTarBackup(myDirList, ProjectDrivePath, tarFileBasePath, tarFileName, LogDestinationPath, True, True)
        pass
    elif command == "status":
        scriptStatus(True, False)
        pass
    elif command == "status reset":
        scriptStatus(False, True)
        pass
    else:
        print(f"Command not recognized! Type 'help' to see more information.")
        pass
    pass

exit(0)