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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/V3-03-HMCSPI-Async.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/V3-03-HMCSPI-Async.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../COMMON/BLI/BLI.c ../COMMON/BLI/BLIInit.c ../COMMON/BLI/BLILocal.c ../COMMON/BLI/BLIMorse.c ../COMMON/HMCSPI/HMCSPI_Async.c ../COMMON/HMCSPI/HMCSPI_Init.c ../COMMON/HMCSPI/HMCSPI_ISR.c ../COMMON/HMCSPI/HMCSPI_Local.c ../COMMON/HMCSPI/NMCSPI_Sync.c ../COMMON/Init/Init.c ../COMMON/SDL/SDL_API.c ../COMMON/SDL/SDL_Init.c ../COMMON/SDL/SDL_ISR.c ../COMMON/SDL/SDL_Local.c ../COMMON/TMR/TMR.c ../COMMON/TMR/TMRInit.c ../COMMON/TMR/TMRLocal.c ../COMMON/TMR/TMR_ISR.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/151698742/BLI.o ${OBJECTDIR}/_ext/151698742/BLIInit.o ${OBJECTDIR}/_ext/151698742/BLILocal.o ${OBJECTDIR}/_ext/151698742/BLIMorse.o ${OBJECTDIR}/_ext/779025533/HMCSPI_Async.o ${OBJECTDIR}/_ext/779025533/HMCSPI_Init.o ${OBJECTDIR}/_ext/779025533/HMCSPI_ISR.o ${OBJECTDIR}/_ext/779025533/HMCSPI_Local.o ${OBJECTDIR}/_ext/779025533/NMCSPI_Sync.o ${OBJECTDIR}/_ext/407451387/Init.o ${OBJECTDIR}/_ext/151682650/SDL_API.o ${OBJECTDIR}/_ext/151682650/SDL_Init.o ${OBJECTDIR}/_ext/151682650/SDL_ISR.o ${OBJECTDIR}/_ext/151682650/SDL_Local.o ${OBJECTDIR}/_ext/151681404/TMR.o ${OBJECTDIR}/_ext/151681404/TMRInit.o ${OBJECTDIR}/_ext/151681404/TMRLocal.o ${OBJECTDIR}/_ext/151681404/TMR_ISR.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/151698742/BLI.o.d ${OBJECTDIR}/_ext/151698742/BLIInit.o.d ${OBJECTDIR}/_ext/151698742/BLILocal.o.d ${OBJECTDIR}/_ext/151698742/BLIMorse.o.d ${OBJECTDIR}/_ext/779025533/HMCSPI_Async.o.d ${OBJECTDIR}/_ext/779025533/HMCSPI_Init.o.d ${OBJECTDIR}/_ext/779025533/HMCSPI_ISR.o.d ${OBJECTDIR}/_ext/779025533/HMCSPI_Local.o.d ${OBJECTDIR}/_ext/779025533/NMCSPI_Sync.o.d ${OBJECTDIR}/_ext/407451387/Init.o.d ${OBJECTDIR}/_ext/151682650/SDL_API.o.d ${OBJECTDIR}/_ext/151682650/SDL_Init.o.d ${OBJECTDIR}/_ext/151682650/SDL_ISR.o.d ${OBJECTDIR}/_ext/151682650/SDL_Local.o.d ${OBJECTDIR}/_ext/151681404/TMR.o.d ${OBJECTDIR}/_ext/151681404/TMRInit.o.d ${OBJECTDIR}/_ext/151681404/TMRLocal.o.d ${OBJECTDIR}/_ext/151681404/TMR_ISR.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/151698742/BLI.o ${OBJECTDIR}/_ext/151698742/BLIInit.o ${OBJECTDIR}/_ext/151698742/BLILocal.o ${OBJECTDIR}/_ext/151698742/BLIMorse.o ${OBJECTDIR}/_ext/779025533/HMCSPI_Async.o ${OBJECTDIR}/_ext/779025533/HMCSPI_Init.o ${OBJECTDIR}/_ext/779025533/HMCSPI_ISR.o ${OBJECTDIR}/_ext/779025533/HMCSPI_Local.o ${OBJECTDIR}/_ext/779025533/NMCSPI_Sync.o ${OBJECTDIR}/_ext/407451387/Init.o ${OBJECTDIR}/_ext/151682650/SDL_API.o ${OBJECTDIR}/_ext/151682650/SDL_Init.o ${OBJECTDIR}/_ext/151682650/SDL_ISR.o ${OBJECTDIR}/_ext/151682650/SDL_Local.o ${OBJECTDIR}/_ext/151681404/TMR.o ${OBJECTDIR}/_ext/151681404/TMRInit.o ${OBJECTDIR}/_ext/151681404/TMRLocal.o ${OBJECTDIR}/_ext/151681404/TMR_ISR.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=../COMMON/BLI/BLI.c ../COMMON/BLI/BLIInit.c ../COMMON/BLI/BLILocal.c ../COMMON/BLI/BLIMorse.c ../COMMON/HMCSPI/HMCSPI_Async.c ../COMMON/HMCSPI/HMCSPI_Init.c ../COMMON/HMCSPI/HMCSPI_ISR.c ../COMMON/HMCSPI/HMCSPI_Local.c ../COMMON/HMCSPI/NMCSPI_Sync.c ../COMMON/Init/Init.c ../COMMON/SDL/SDL_API.c ../COMMON/SDL/SDL_Init.c ../COMMON/SDL/SDL_ISR.c ../COMMON/SDL/SDL_Local.c ../COMMON/TMR/TMR.c ../COMMON/TMR/TMRInit.c ../COMMON/TMR/TMRLocal.c ../COMMON/TMR/TMR_ISR.c main.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/V3-03-HMCSPI-Async.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24EP512GP806
MP_LINKER_FILE_OPTION=,--script=p24EP512GP806.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/151698742/BLI.o: ../COMMON/BLI/BLI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151698742 
	@${RM} ${OBJECTDIR}/_ext/151698742/BLI.o.d 
	@${RM} ${OBJECTDIR}/_ext/151698742/BLI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/BLI/BLI.c  -o ${OBJECTDIR}/_ext/151698742/BLI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151698742/BLI.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151698742/BLI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151698742/BLIInit.o: ../COMMON/BLI/BLIInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151698742 
	@${RM} ${OBJECTDIR}/_ext/151698742/BLIInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/151698742/BLIInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/BLI/BLIInit.c  -o ${OBJECTDIR}/_ext/151698742/BLIInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151698742/BLIInit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151698742/BLIInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151698742/BLILocal.o: ../COMMON/BLI/BLILocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151698742 
	@${RM} ${OBJECTDIR}/_ext/151698742/BLILocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/151698742/BLILocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/BLI/BLILocal.c  -o ${OBJECTDIR}/_ext/151698742/BLILocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151698742/BLILocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151698742/BLILocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151698742/BLIMorse.o: ../COMMON/BLI/BLIMorse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151698742 
	@${RM} ${OBJECTDIR}/_ext/151698742/BLIMorse.o.d 
	@${RM} ${OBJECTDIR}/_ext/151698742/BLIMorse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/BLI/BLIMorse.c  -o ${OBJECTDIR}/_ext/151698742/BLIMorse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151698742/BLIMorse.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151698742/BLIMorse.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/779025533/HMCSPI_Async.o: ../COMMON/HMCSPI/HMCSPI_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/779025533 
	@${RM} ${OBJECTDIR}/_ext/779025533/HMCSPI_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/779025533/HMCSPI_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/HMCSPI/HMCSPI_Async.c  -o ${OBJECTDIR}/_ext/779025533/HMCSPI_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/779025533/HMCSPI_Async.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/779025533/HMCSPI_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/779025533/HMCSPI_Init.o: ../COMMON/HMCSPI/HMCSPI_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/779025533 
	@${RM} ${OBJECTDIR}/_ext/779025533/HMCSPI_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/779025533/HMCSPI_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/HMCSPI/HMCSPI_Init.c  -o ${OBJECTDIR}/_ext/779025533/HMCSPI_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/779025533/HMCSPI_Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/779025533/HMCSPI_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/779025533/HMCSPI_ISR.o: ../COMMON/HMCSPI/HMCSPI_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/779025533 
	@${RM} ${OBJECTDIR}/_ext/779025533/HMCSPI_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/779025533/HMCSPI_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/HMCSPI/HMCSPI_ISR.c  -o ${OBJECTDIR}/_ext/779025533/HMCSPI_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/779025533/HMCSPI_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/779025533/HMCSPI_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/779025533/HMCSPI_Local.o: ../COMMON/HMCSPI/HMCSPI_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/779025533 
	@${RM} ${OBJECTDIR}/_ext/779025533/HMCSPI_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/779025533/HMCSPI_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/HMCSPI/HMCSPI_Local.c  -o ${OBJECTDIR}/_ext/779025533/HMCSPI_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/779025533/HMCSPI_Local.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/779025533/HMCSPI_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/779025533/NMCSPI_Sync.o: ../COMMON/HMCSPI/NMCSPI_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/779025533 
	@${RM} ${OBJECTDIR}/_ext/779025533/NMCSPI_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/779025533/NMCSPI_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/HMCSPI/NMCSPI_Sync.c  -o ${OBJECTDIR}/_ext/779025533/NMCSPI_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/779025533/NMCSPI_Sync.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/779025533/NMCSPI_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/407451387/Init.o: ../COMMON/Init/Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/407451387 
	@${RM} ${OBJECTDIR}/_ext/407451387/Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/407451387/Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/Init/Init.c  -o ${OBJECTDIR}/_ext/407451387/Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/407451387/Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/407451387/Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151682650/SDL_API.o: ../COMMON/SDL/SDL_API.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151682650 
	@${RM} ${OBJECTDIR}/_ext/151682650/SDL_API.o.d 
	@${RM} ${OBJECTDIR}/_ext/151682650/SDL_API.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/SDL/SDL_API.c  -o ${OBJECTDIR}/_ext/151682650/SDL_API.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151682650/SDL_API.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151682650/SDL_API.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151682650/SDL_Init.o: ../COMMON/SDL/SDL_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151682650 
	@${RM} ${OBJECTDIR}/_ext/151682650/SDL_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/151682650/SDL_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/SDL/SDL_Init.c  -o ${OBJECTDIR}/_ext/151682650/SDL_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151682650/SDL_Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151682650/SDL_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151682650/SDL_ISR.o: ../COMMON/SDL/SDL_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151682650 
	@${RM} ${OBJECTDIR}/_ext/151682650/SDL_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/151682650/SDL_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/SDL/SDL_ISR.c  -o ${OBJECTDIR}/_ext/151682650/SDL_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151682650/SDL_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151682650/SDL_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151682650/SDL_Local.o: ../COMMON/SDL/SDL_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151682650 
	@${RM} ${OBJECTDIR}/_ext/151682650/SDL_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/151682650/SDL_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/SDL/SDL_Local.c  -o ${OBJECTDIR}/_ext/151682650/SDL_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151682650/SDL_Local.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151682650/SDL_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151681404/TMR.o: ../COMMON/TMR/TMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151681404 
	@${RM} ${OBJECTDIR}/_ext/151681404/TMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/151681404/TMR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/TMR/TMR.c  -o ${OBJECTDIR}/_ext/151681404/TMR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151681404/TMR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151681404/TMR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151681404/TMRInit.o: ../COMMON/TMR/TMRInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151681404 
	@${RM} ${OBJECTDIR}/_ext/151681404/TMRInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/151681404/TMRInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/TMR/TMRInit.c  -o ${OBJECTDIR}/_ext/151681404/TMRInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151681404/TMRInit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151681404/TMRInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151681404/TMRLocal.o: ../COMMON/TMR/TMRLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151681404 
	@${RM} ${OBJECTDIR}/_ext/151681404/TMRLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/151681404/TMRLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/TMR/TMRLocal.c  -o ${OBJECTDIR}/_ext/151681404/TMRLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151681404/TMRLocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151681404/TMRLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151681404/TMR_ISR.o: ../COMMON/TMR/TMR_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151681404 
	@${RM} ${OBJECTDIR}/_ext/151681404/TMR_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/151681404/TMR_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/TMR/TMR_ISR.c  -o ${OBJECTDIR}/_ext/151681404/TMR_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151681404/TMR_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151681404/TMR_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/151698742/BLI.o: ../COMMON/BLI/BLI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151698742 
	@${RM} ${OBJECTDIR}/_ext/151698742/BLI.o.d 
	@${RM} ${OBJECTDIR}/_ext/151698742/BLI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/BLI/BLI.c  -o ${OBJECTDIR}/_ext/151698742/BLI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151698742/BLI.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151698742/BLI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151698742/BLIInit.o: ../COMMON/BLI/BLIInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151698742 
	@${RM} ${OBJECTDIR}/_ext/151698742/BLIInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/151698742/BLIInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/BLI/BLIInit.c  -o ${OBJECTDIR}/_ext/151698742/BLIInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151698742/BLIInit.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151698742/BLIInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151698742/BLILocal.o: ../COMMON/BLI/BLILocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151698742 
	@${RM} ${OBJECTDIR}/_ext/151698742/BLILocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/151698742/BLILocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/BLI/BLILocal.c  -o ${OBJECTDIR}/_ext/151698742/BLILocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151698742/BLILocal.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151698742/BLILocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151698742/BLIMorse.o: ../COMMON/BLI/BLIMorse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151698742 
	@${RM} ${OBJECTDIR}/_ext/151698742/BLIMorse.o.d 
	@${RM} ${OBJECTDIR}/_ext/151698742/BLIMorse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/BLI/BLIMorse.c  -o ${OBJECTDIR}/_ext/151698742/BLIMorse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151698742/BLIMorse.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151698742/BLIMorse.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/779025533/HMCSPI_Async.o: ../COMMON/HMCSPI/HMCSPI_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/779025533 
	@${RM} ${OBJECTDIR}/_ext/779025533/HMCSPI_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/779025533/HMCSPI_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/HMCSPI/HMCSPI_Async.c  -o ${OBJECTDIR}/_ext/779025533/HMCSPI_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/779025533/HMCSPI_Async.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/779025533/HMCSPI_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/779025533/HMCSPI_Init.o: ../COMMON/HMCSPI/HMCSPI_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/779025533 
	@${RM} ${OBJECTDIR}/_ext/779025533/HMCSPI_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/779025533/HMCSPI_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/HMCSPI/HMCSPI_Init.c  -o ${OBJECTDIR}/_ext/779025533/HMCSPI_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/779025533/HMCSPI_Init.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/779025533/HMCSPI_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/779025533/HMCSPI_ISR.o: ../COMMON/HMCSPI/HMCSPI_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/779025533 
	@${RM} ${OBJECTDIR}/_ext/779025533/HMCSPI_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/779025533/HMCSPI_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/HMCSPI/HMCSPI_ISR.c  -o ${OBJECTDIR}/_ext/779025533/HMCSPI_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/779025533/HMCSPI_ISR.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/779025533/HMCSPI_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/779025533/HMCSPI_Local.o: ../COMMON/HMCSPI/HMCSPI_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/779025533 
	@${RM} ${OBJECTDIR}/_ext/779025533/HMCSPI_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/779025533/HMCSPI_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/HMCSPI/HMCSPI_Local.c  -o ${OBJECTDIR}/_ext/779025533/HMCSPI_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/779025533/HMCSPI_Local.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/779025533/HMCSPI_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/779025533/NMCSPI_Sync.o: ../COMMON/HMCSPI/NMCSPI_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/779025533 
	@${RM} ${OBJECTDIR}/_ext/779025533/NMCSPI_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/779025533/NMCSPI_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/HMCSPI/NMCSPI_Sync.c  -o ${OBJECTDIR}/_ext/779025533/NMCSPI_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/779025533/NMCSPI_Sync.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/779025533/NMCSPI_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/407451387/Init.o: ../COMMON/Init/Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/407451387 
	@${RM} ${OBJECTDIR}/_ext/407451387/Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/407451387/Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/Init/Init.c  -o ${OBJECTDIR}/_ext/407451387/Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/407451387/Init.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/407451387/Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151682650/SDL_API.o: ../COMMON/SDL/SDL_API.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151682650 
	@${RM} ${OBJECTDIR}/_ext/151682650/SDL_API.o.d 
	@${RM} ${OBJECTDIR}/_ext/151682650/SDL_API.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/SDL/SDL_API.c  -o ${OBJECTDIR}/_ext/151682650/SDL_API.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151682650/SDL_API.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151682650/SDL_API.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151682650/SDL_Init.o: ../COMMON/SDL/SDL_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151682650 
	@${RM} ${OBJECTDIR}/_ext/151682650/SDL_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/151682650/SDL_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/SDL/SDL_Init.c  -o ${OBJECTDIR}/_ext/151682650/SDL_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151682650/SDL_Init.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151682650/SDL_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151682650/SDL_ISR.o: ../COMMON/SDL/SDL_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151682650 
	@${RM} ${OBJECTDIR}/_ext/151682650/SDL_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/151682650/SDL_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/SDL/SDL_ISR.c  -o ${OBJECTDIR}/_ext/151682650/SDL_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151682650/SDL_ISR.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151682650/SDL_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151682650/SDL_Local.o: ../COMMON/SDL/SDL_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151682650 
	@${RM} ${OBJECTDIR}/_ext/151682650/SDL_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/151682650/SDL_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/SDL/SDL_Local.c  -o ${OBJECTDIR}/_ext/151682650/SDL_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151682650/SDL_Local.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151682650/SDL_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151681404/TMR.o: ../COMMON/TMR/TMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151681404 
	@${RM} ${OBJECTDIR}/_ext/151681404/TMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/151681404/TMR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/TMR/TMR.c  -o ${OBJECTDIR}/_ext/151681404/TMR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151681404/TMR.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151681404/TMR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151681404/TMRInit.o: ../COMMON/TMR/TMRInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151681404 
	@${RM} ${OBJECTDIR}/_ext/151681404/TMRInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/151681404/TMRInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/TMR/TMRInit.c  -o ${OBJECTDIR}/_ext/151681404/TMRInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151681404/TMRInit.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151681404/TMRInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151681404/TMRLocal.o: ../COMMON/TMR/TMRLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151681404 
	@${RM} ${OBJECTDIR}/_ext/151681404/TMRLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/151681404/TMRLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/TMR/TMRLocal.c  -o ${OBJECTDIR}/_ext/151681404/TMRLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151681404/TMRLocal.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151681404/TMRLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/151681404/TMR_ISR.o: ../COMMON/TMR/TMR_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/151681404 
	@${RM} ${OBJECTDIR}/_ext/151681404/TMR_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/151681404/TMR_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../COMMON/TMR/TMR_ISR.c  -o ${OBJECTDIR}/_ext/151681404/TMR_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/151681404/TMR_ISR.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/151681404/TMR_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../Common" -msmart-io=1 -Wall -msfr-warn=off
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
dist/${CND_CONF}/${IMAGE_TYPE}/V3-03-HMCSPI-Async.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/V3-03-HMCSPI-Async.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/V3-03-HMCSPI-Async.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/V3-03-HMCSPI-Async.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/V3-03-HMCSPI-Async.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
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
