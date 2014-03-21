#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/30-Directories.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/30-Directories.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../00-Shared/BLI/BLI.c ../00-Shared/BLI/BLIInit.c ../00-Shared/BLI/BLILocal.c ../00-Shared/BLI/BLIMorse.c ../00-Shared/FSIO/FS_DirControl.c ../00-Shared/FSIO/FS_FileControl.c ../00-Shared/FSIO/FS_IO.c ../00-Shared/FSIO/FS_Management.c ../00-Shared/FSIO/FS_System.c ../00-Shared/FSIO/SDFS_DataCacheMgmt.c ../00-Shared/FSIO/SDFS_DirectoryMgmt.c ../00-Shared/FSIO/SDFS_FATMgmt.c ../00-Shared/FSIO/SDFS_FileMgmt.c ../00-Shared/FSIO/SDFS_Globals.c ../00-Shared/FSIO/SDFS_Name8r3Mgmt.c ../00-Shared/FSIO/SDFS_VolumeMgmt.c ../00-Shared/Init/Init.c ../00-Shared/LOG/Log.c ../00-Shared/LOG/LogLocal.c ../00-Shared/SDSPI/SD-SPI-Local.c ../00-Shared/SDSPI/SD-SPI.c ../00-Shared/TMR/TMR.c ../00-Shared/TMR/TMRInit.c ../00-Shared/TMR/TMRLocal.c ../00-Shared/TMR/TMR_ISR.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/2016097133/BLI.o ${OBJECTDIR}/_ext/2016097133/BLIInit.o ${OBJECTDIR}/_ext/2016097133/BLILocal.o ${OBJECTDIR}/_ext/2016097133/BLIMorse.o ${OBJECTDIR}/_ext/1925624287/FS_DirControl.o ${OBJECTDIR}/_ext/1925624287/FS_FileControl.o ${OBJECTDIR}/_ext/1925624287/FS_IO.o ${OBJECTDIR}/_ext/1925624287/FS_Management.o ${OBJECTDIR}/_ext/1925624287/FS_System.o ${OBJECTDIR}/_ext/1925624287/SDFS_DataCacheMgmt.o ${OBJECTDIR}/_ext/1925624287/SDFS_DirectoryMgmt.o ${OBJECTDIR}/_ext/1925624287/SDFS_FATMgmt.o ${OBJECTDIR}/_ext/1925624287/SDFS_FileMgmt.o ${OBJECTDIR}/_ext/1925624287/SDFS_Globals.o ${OBJECTDIR}/_ext/1925624287/SDFS_Name8r3Mgmt.o ${OBJECTDIR}/_ext/1925624287/SDFS_VolumeMgmt.o ${OBJECTDIR}/_ext/1925740636/Init.o ${OBJECTDIR}/_ext/2016087432/Log.o ${OBJECTDIR}/_ext/2016087432/LogLocal.o ${OBJECTDIR}/_ext/423620625/SD-SPI-Local.o ${OBJECTDIR}/_ext/423620625/SD-SPI.o ${OBJECTDIR}/_ext/2016079795/TMR.o ${OBJECTDIR}/_ext/2016079795/TMRInit.o ${OBJECTDIR}/_ext/2016079795/TMRLocal.o ${OBJECTDIR}/_ext/2016079795/TMR_ISR.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/2016097133/BLI.o.d ${OBJECTDIR}/_ext/2016097133/BLIInit.o.d ${OBJECTDIR}/_ext/2016097133/BLILocal.o.d ${OBJECTDIR}/_ext/2016097133/BLIMorse.o.d ${OBJECTDIR}/_ext/1925624287/FS_DirControl.o.d ${OBJECTDIR}/_ext/1925624287/FS_FileControl.o.d ${OBJECTDIR}/_ext/1925624287/FS_IO.o.d ${OBJECTDIR}/_ext/1925624287/FS_Management.o.d ${OBJECTDIR}/_ext/1925624287/FS_System.o.d ${OBJECTDIR}/_ext/1925624287/SDFS_DataCacheMgmt.o.d ${OBJECTDIR}/_ext/1925624287/SDFS_DirectoryMgmt.o.d ${OBJECTDIR}/_ext/1925624287/SDFS_FATMgmt.o.d ${OBJECTDIR}/_ext/1925624287/SDFS_FileMgmt.o.d ${OBJECTDIR}/_ext/1925624287/SDFS_Globals.o.d ${OBJECTDIR}/_ext/1925624287/SDFS_Name8r3Mgmt.o.d ${OBJECTDIR}/_ext/1925624287/SDFS_VolumeMgmt.o.d ${OBJECTDIR}/_ext/1925740636/Init.o.d ${OBJECTDIR}/_ext/2016087432/Log.o.d ${OBJECTDIR}/_ext/2016087432/LogLocal.o.d ${OBJECTDIR}/_ext/423620625/SD-SPI-Local.o.d ${OBJECTDIR}/_ext/423620625/SD-SPI.o.d ${OBJECTDIR}/_ext/2016079795/TMR.o.d ${OBJECTDIR}/_ext/2016079795/TMRInit.o.d ${OBJECTDIR}/_ext/2016079795/TMRLocal.o.d ${OBJECTDIR}/_ext/2016079795/TMR_ISR.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/2016097133/BLI.o ${OBJECTDIR}/_ext/2016097133/BLIInit.o ${OBJECTDIR}/_ext/2016097133/BLILocal.o ${OBJECTDIR}/_ext/2016097133/BLIMorse.o ${OBJECTDIR}/_ext/1925624287/FS_DirControl.o ${OBJECTDIR}/_ext/1925624287/FS_FileControl.o ${OBJECTDIR}/_ext/1925624287/FS_IO.o ${OBJECTDIR}/_ext/1925624287/FS_Management.o ${OBJECTDIR}/_ext/1925624287/FS_System.o ${OBJECTDIR}/_ext/1925624287/SDFS_DataCacheMgmt.o ${OBJECTDIR}/_ext/1925624287/SDFS_DirectoryMgmt.o ${OBJECTDIR}/_ext/1925624287/SDFS_FATMgmt.o ${OBJECTDIR}/_ext/1925624287/SDFS_FileMgmt.o ${OBJECTDIR}/_ext/1925624287/SDFS_Globals.o ${OBJECTDIR}/_ext/1925624287/SDFS_Name8r3Mgmt.o ${OBJECTDIR}/_ext/1925624287/SDFS_VolumeMgmt.o ${OBJECTDIR}/_ext/1925740636/Init.o ${OBJECTDIR}/_ext/2016087432/Log.o ${OBJECTDIR}/_ext/2016087432/LogLocal.o ${OBJECTDIR}/_ext/423620625/SD-SPI-Local.o ${OBJECTDIR}/_ext/423620625/SD-SPI.o ${OBJECTDIR}/_ext/2016079795/TMR.o ${OBJECTDIR}/_ext/2016079795/TMRInit.o ${OBJECTDIR}/_ext/2016079795/TMRLocal.o ${OBJECTDIR}/_ext/2016079795/TMR_ISR.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=../00-Shared/BLI/BLI.c ../00-Shared/BLI/BLIInit.c ../00-Shared/BLI/BLILocal.c ../00-Shared/BLI/BLIMorse.c ../00-Shared/FSIO/FS_DirControl.c ../00-Shared/FSIO/FS_FileControl.c ../00-Shared/FSIO/FS_IO.c ../00-Shared/FSIO/FS_Management.c ../00-Shared/FSIO/FS_System.c ../00-Shared/FSIO/SDFS_DataCacheMgmt.c ../00-Shared/FSIO/SDFS_DirectoryMgmt.c ../00-Shared/FSIO/SDFS_FATMgmt.c ../00-Shared/FSIO/SDFS_FileMgmt.c ../00-Shared/FSIO/SDFS_Globals.c ../00-Shared/FSIO/SDFS_Name8r3Mgmt.c ../00-Shared/FSIO/SDFS_VolumeMgmt.c ../00-Shared/Init/Init.c ../00-Shared/LOG/Log.c ../00-Shared/LOG/LogLocal.c ../00-Shared/SDSPI/SD-SPI-Local.c ../00-Shared/SDSPI/SD-SPI.c ../00-Shared/TMR/TMR.c ../00-Shared/TMR/TMRInit.c ../00-Shared/TMR/TMRLocal.c ../00-Shared/TMR/TMR_ISR.c main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/30-Directories.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24HJ128GP202
MP_LINKER_FILE_OPTION=,--script=p24HJ128GP202.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/2016097133/BLI.o: ../00-Shared/BLI/BLI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016097133 
	@${RM} ${OBJECTDIR}/_ext/2016097133/BLI.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016097133/BLI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/BLI/BLI.c  -o ${OBJECTDIR}/_ext/2016097133/BLI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016097133/BLI.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016097133/BLI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016097133/BLIInit.o: ../00-Shared/BLI/BLIInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016097133 
	@${RM} ${OBJECTDIR}/_ext/2016097133/BLIInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016097133/BLIInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/BLI/BLIInit.c  -o ${OBJECTDIR}/_ext/2016097133/BLIInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016097133/BLIInit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016097133/BLIInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016097133/BLILocal.o: ../00-Shared/BLI/BLILocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016097133 
	@${RM} ${OBJECTDIR}/_ext/2016097133/BLILocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016097133/BLILocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/BLI/BLILocal.c  -o ${OBJECTDIR}/_ext/2016097133/BLILocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016097133/BLILocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016097133/BLILocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016097133/BLIMorse.o: ../00-Shared/BLI/BLIMorse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016097133 
	@${RM} ${OBJECTDIR}/_ext/2016097133/BLIMorse.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016097133/BLIMorse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/BLI/BLIMorse.c  -o ${OBJECTDIR}/_ext/2016097133/BLIMorse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016097133/BLIMorse.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016097133/BLIMorse.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/FS_DirControl.o: ../00-Shared/FSIO/FS_DirControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_DirControl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_DirControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/FS_DirControl.c  -o ${OBJECTDIR}/_ext/1925624287/FS_DirControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/FS_DirControl.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/FS_DirControl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/FS_FileControl.o: ../00-Shared/FSIO/FS_FileControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_FileControl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_FileControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/FS_FileControl.c  -o ${OBJECTDIR}/_ext/1925624287/FS_FileControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/FS_FileControl.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/FS_FileControl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/FS_IO.o: ../00-Shared/FSIO/FS_IO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_IO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_IO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/FS_IO.c  -o ${OBJECTDIR}/_ext/1925624287/FS_IO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/FS_IO.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/FS_IO.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/FS_Management.o: ../00-Shared/FSIO/FS_Management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_Management.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_Management.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/FS_Management.c  -o ${OBJECTDIR}/_ext/1925624287/FS_Management.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/FS_Management.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/FS_Management.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/FS_System.o: ../00-Shared/FSIO/FS_System.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_System.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_System.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/FS_System.c  -o ${OBJECTDIR}/_ext/1925624287/FS_System.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/FS_System.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/FS_System.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/SDFS_DataCacheMgmt.o: ../00-Shared/FSIO/SDFS_DataCacheMgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_DataCacheMgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_DataCacheMgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/SDFS_DataCacheMgmt.c  -o ${OBJECTDIR}/_ext/1925624287/SDFS_DataCacheMgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/SDFS_DataCacheMgmt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/SDFS_DataCacheMgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/SDFS_DirectoryMgmt.o: ../00-Shared/FSIO/SDFS_DirectoryMgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_DirectoryMgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_DirectoryMgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/SDFS_DirectoryMgmt.c  -o ${OBJECTDIR}/_ext/1925624287/SDFS_DirectoryMgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/SDFS_DirectoryMgmt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/SDFS_DirectoryMgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/SDFS_FATMgmt.o: ../00-Shared/FSIO/SDFS_FATMgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_FATMgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_FATMgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/SDFS_FATMgmt.c  -o ${OBJECTDIR}/_ext/1925624287/SDFS_FATMgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/SDFS_FATMgmt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/SDFS_FATMgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/SDFS_FileMgmt.o: ../00-Shared/FSIO/SDFS_FileMgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_FileMgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_FileMgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/SDFS_FileMgmt.c  -o ${OBJECTDIR}/_ext/1925624287/SDFS_FileMgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/SDFS_FileMgmt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/SDFS_FileMgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/SDFS_Globals.o: ../00-Shared/FSIO/SDFS_Globals.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_Globals.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_Globals.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/SDFS_Globals.c  -o ${OBJECTDIR}/_ext/1925624287/SDFS_Globals.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/SDFS_Globals.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/SDFS_Globals.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/SDFS_Name8r3Mgmt.o: ../00-Shared/FSIO/SDFS_Name8r3Mgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_Name8r3Mgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_Name8r3Mgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/SDFS_Name8r3Mgmt.c  -o ${OBJECTDIR}/_ext/1925624287/SDFS_Name8r3Mgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/SDFS_Name8r3Mgmt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/SDFS_Name8r3Mgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/SDFS_VolumeMgmt.o: ../00-Shared/FSIO/SDFS_VolumeMgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_VolumeMgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_VolumeMgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/SDFS_VolumeMgmt.c  -o ${OBJECTDIR}/_ext/1925624287/SDFS_VolumeMgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/SDFS_VolumeMgmt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/SDFS_VolumeMgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925740636/Init.o: ../00-Shared/Init/Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925740636 
	@${RM} ${OBJECTDIR}/_ext/1925740636/Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925740636/Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/Init/Init.c  -o ${OBJECTDIR}/_ext/1925740636/Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925740636/Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925740636/Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016087432/Log.o: ../00-Shared/LOG/Log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016087432 
	@${RM} ${OBJECTDIR}/_ext/2016087432/Log.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016087432/Log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/LOG/Log.c  -o ${OBJECTDIR}/_ext/2016087432/Log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016087432/Log.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016087432/Log.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016087432/LogLocal.o: ../00-Shared/LOG/LogLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016087432 
	@${RM} ${OBJECTDIR}/_ext/2016087432/LogLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016087432/LogLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/LOG/LogLocal.c  -o ${OBJECTDIR}/_ext/2016087432/LogLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016087432/LogLocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016087432/LogLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/423620625/SD-SPI-Local.o: ../00-Shared/SDSPI/SD-SPI-Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/423620625 
	@${RM} ${OBJECTDIR}/_ext/423620625/SD-SPI-Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/423620625/SD-SPI-Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/SDSPI/SD-SPI-Local.c  -o ${OBJECTDIR}/_ext/423620625/SD-SPI-Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/423620625/SD-SPI-Local.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/423620625/SD-SPI-Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/423620625/SD-SPI.o: ../00-Shared/SDSPI/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/423620625 
	@${RM} ${OBJECTDIR}/_ext/423620625/SD-SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/423620625/SD-SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/SDSPI/SD-SPI.c  -o ${OBJECTDIR}/_ext/423620625/SD-SPI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/423620625/SD-SPI.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/423620625/SD-SPI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016079795/TMR.o: ../00-Shared/TMR/TMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016079795 
	@${RM} ${OBJECTDIR}/_ext/2016079795/TMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016079795/TMR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/TMR/TMR.c  -o ${OBJECTDIR}/_ext/2016079795/TMR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016079795/TMR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016079795/TMR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016079795/TMRInit.o: ../00-Shared/TMR/TMRInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016079795 
	@${RM} ${OBJECTDIR}/_ext/2016079795/TMRInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016079795/TMRInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/TMR/TMRInit.c  -o ${OBJECTDIR}/_ext/2016079795/TMRInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016079795/TMRInit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016079795/TMRInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016079795/TMRLocal.o: ../00-Shared/TMR/TMRLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016079795 
	@${RM} ${OBJECTDIR}/_ext/2016079795/TMRLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016079795/TMRLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/TMR/TMRLocal.c  -o ${OBJECTDIR}/_ext/2016079795/TMRLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016079795/TMRLocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016079795/TMRLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016079795/TMR_ISR.o: ../00-Shared/TMR/TMR_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016079795 
	@${RM} ${OBJECTDIR}/_ext/2016079795/TMR_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016079795/TMR_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/TMR/TMR_ISR.c  -o ${OBJECTDIR}/_ext/2016079795/TMR_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016079795/TMR_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016079795/TMR_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/2016097133/BLI.o: ../00-Shared/BLI/BLI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016097133 
	@${RM} ${OBJECTDIR}/_ext/2016097133/BLI.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016097133/BLI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/BLI/BLI.c  -o ${OBJECTDIR}/_ext/2016097133/BLI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016097133/BLI.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016097133/BLI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016097133/BLIInit.o: ../00-Shared/BLI/BLIInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016097133 
	@${RM} ${OBJECTDIR}/_ext/2016097133/BLIInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016097133/BLIInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/BLI/BLIInit.c  -o ${OBJECTDIR}/_ext/2016097133/BLIInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016097133/BLIInit.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016097133/BLIInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016097133/BLILocal.o: ../00-Shared/BLI/BLILocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016097133 
	@${RM} ${OBJECTDIR}/_ext/2016097133/BLILocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016097133/BLILocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/BLI/BLILocal.c  -o ${OBJECTDIR}/_ext/2016097133/BLILocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016097133/BLILocal.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016097133/BLILocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016097133/BLIMorse.o: ../00-Shared/BLI/BLIMorse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016097133 
	@${RM} ${OBJECTDIR}/_ext/2016097133/BLIMorse.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016097133/BLIMorse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/BLI/BLIMorse.c  -o ${OBJECTDIR}/_ext/2016097133/BLIMorse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016097133/BLIMorse.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016097133/BLIMorse.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/FS_DirControl.o: ../00-Shared/FSIO/FS_DirControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_DirControl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_DirControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/FS_DirControl.c  -o ${OBJECTDIR}/_ext/1925624287/FS_DirControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/FS_DirControl.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/FS_DirControl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/FS_FileControl.o: ../00-Shared/FSIO/FS_FileControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_FileControl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_FileControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/FS_FileControl.c  -o ${OBJECTDIR}/_ext/1925624287/FS_FileControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/FS_FileControl.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/FS_FileControl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/FS_IO.o: ../00-Shared/FSIO/FS_IO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_IO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_IO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/FS_IO.c  -o ${OBJECTDIR}/_ext/1925624287/FS_IO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/FS_IO.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/FS_IO.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/FS_Management.o: ../00-Shared/FSIO/FS_Management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_Management.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_Management.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/FS_Management.c  -o ${OBJECTDIR}/_ext/1925624287/FS_Management.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/FS_Management.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/FS_Management.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/FS_System.o: ../00-Shared/FSIO/FS_System.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_System.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/FS_System.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/FS_System.c  -o ${OBJECTDIR}/_ext/1925624287/FS_System.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/FS_System.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/FS_System.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/SDFS_DataCacheMgmt.o: ../00-Shared/FSIO/SDFS_DataCacheMgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_DataCacheMgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_DataCacheMgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/SDFS_DataCacheMgmt.c  -o ${OBJECTDIR}/_ext/1925624287/SDFS_DataCacheMgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/SDFS_DataCacheMgmt.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/SDFS_DataCacheMgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/SDFS_DirectoryMgmt.o: ../00-Shared/FSIO/SDFS_DirectoryMgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_DirectoryMgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_DirectoryMgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/SDFS_DirectoryMgmt.c  -o ${OBJECTDIR}/_ext/1925624287/SDFS_DirectoryMgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/SDFS_DirectoryMgmt.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/SDFS_DirectoryMgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/SDFS_FATMgmt.o: ../00-Shared/FSIO/SDFS_FATMgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_FATMgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_FATMgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/SDFS_FATMgmt.c  -o ${OBJECTDIR}/_ext/1925624287/SDFS_FATMgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/SDFS_FATMgmt.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/SDFS_FATMgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/SDFS_FileMgmt.o: ../00-Shared/FSIO/SDFS_FileMgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_FileMgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_FileMgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/SDFS_FileMgmt.c  -o ${OBJECTDIR}/_ext/1925624287/SDFS_FileMgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/SDFS_FileMgmt.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/SDFS_FileMgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/SDFS_Globals.o: ../00-Shared/FSIO/SDFS_Globals.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_Globals.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_Globals.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/SDFS_Globals.c  -o ${OBJECTDIR}/_ext/1925624287/SDFS_Globals.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/SDFS_Globals.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/SDFS_Globals.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/SDFS_Name8r3Mgmt.o: ../00-Shared/FSIO/SDFS_Name8r3Mgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_Name8r3Mgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_Name8r3Mgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/SDFS_Name8r3Mgmt.c  -o ${OBJECTDIR}/_ext/1925624287/SDFS_Name8r3Mgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/SDFS_Name8r3Mgmt.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/SDFS_Name8r3Mgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925624287/SDFS_VolumeMgmt.o: ../00-Shared/FSIO/SDFS_VolumeMgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925624287 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_VolumeMgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925624287/SDFS_VolumeMgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/FSIO/SDFS_VolumeMgmt.c  -o ${OBJECTDIR}/_ext/1925624287/SDFS_VolumeMgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925624287/SDFS_VolumeMgmt.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925624287/SDFS_VolumeMgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1925740636/Init.o: ../00-Shared/Init/Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1925740636 
	@${RM} ${OBJECTDIR}/_ext/1925740636/Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1925740636/Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/Init/Init.c  -o ${OBJECTDIR}/_ext/1925740636/Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1925740636/Init.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1925740636/Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016087432/Log.o: ../00-Shared/LOG/Log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016087432 
	@${RM} ${OBJECTDIR}/_ext/2016087432/Log.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016087432/Log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/LOG/Log.c  -o ${OBJECTDIR}/_ext/2016087432/Log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016087432/Log.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016087432/Log.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016087432/LogLocal.o: ../00-Shared/LOG/LogLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016087432 
	@${RM} ${OBJECTDIR}/_ext/2016087432/LogLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016087432/LogLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/LOG/LogLocal.c  -o ${OBJECTDIR}/_ext/2016087432/LogLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016087432/LogLocal.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016087432/LogLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/423620625/SD-SPI-Local.o: ../00-Shared/SDSPI/SD-SPI-Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/423620625 
	@${RM} ${OBJECTDIR}/_ext/423620625/SD-SPI-Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/423620625/SD-SPI-Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/SDSPI/SD-SPI-Local.c  -o ${OBJECTDIR}/_ext/423620625/SD-SPI-Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/423620625/SD-SPI-Local.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/423620625/SD-SPI-Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/423620625/SD-SPI.o: ../00-Shared/SDSPI/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/423620625 
	@${RM} ${OBJECTDIR}/_ext/423620625/SD-SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/423620625/SD-SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/SDSPI/SD-SPI.c  -o ${OBJECTDIR}/_ext/423620625/SD-SPI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/423620625/SD-SPI.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/423620625/SD-SPI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016079795/TMR.o: ../00-Shared/TMR/TMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016079795 
	@${RM} ${OBJECTDIR}/_ext/2016079795/TMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016079795/TMR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/TMR/TMR.c  -o ${OBJECTDIR}/_ext/2016079795/TMR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016079795/TMR.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016079795/TMR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016079795/TMRInit.o: ../00-Shared/TMR/TMRInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016079795 
	@${RM} ${OBJECTDIR}/_ext/2016079795/TMRInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016079795/TMRInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/TMR/TMRInit.c  -o ${OBJECTDIR}/_ext/2016079795/TMRInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016079795/TMRInit.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016079795/TMRInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016079795/TMRLocal.o: ../00-Shared/TMR/TMRLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016079795 
	@${RM} ${OBJECTDIR}/_ext/2016079795/TMRLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016079795/TMRLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/TMR/TMRLocal.c  -o ${OBJECTDIR}/_ext/2016079795/TMRLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016079795/TMRLocal.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016079795/TMRLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2016079795/TMR_ISR.o: ../00-Shared/TMR/TMR_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2016079795 
	@${RM} ${OBJECTDIR}/_ext/2016079795/TMR_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/2016079795/TMR_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Shared/TMR/TMR_ISR.c  -o ${OBJECTDIR}/_ext/2016079795/TMR_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2016079795/TMR_ISR.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2016079795/TMR_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -D__PIC24H__ -fast-math -O0 -I"../00-Shared" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/30-Directories.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/30-Directories.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -D__PIC24H__ -fast-math  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/30-Directories.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/30-Directories.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -D__PIC24H__ -fast-math -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/30-Directories.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
