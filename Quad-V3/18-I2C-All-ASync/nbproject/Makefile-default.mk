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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/18-I2C-All-ASync.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/18-I2C-All-ASync.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c ../00-COMMON/BLI/BLI.c ../00-COMMON/BLI/BLIInit.c ../00-COMMON/BLI/BLILocal.c ../00-COMMON/BLI/BLIMorse.c ../00-COMMON/I2C/I2C_Async.c ../00-COMMON/I2C/I2C_Init.c ../00-COMMON/I2C/I2C_ISR.c ../00-COMMON/I2C/I2C_Local.c ../00-COMMON/I2C/I2C_Sync.c ../00-COMMON/I2C/I2C_SyncRead.c ../00-COMMON/I2C/I2C_SyncWrite.c ../00-COMMON/Init/Init.c ../00-COMMON/MPL/MPL_Async.c ../00-COMMON/MPL/MPL_Init.c ../00-COMMON/MPL/MPL_ISR.c ../00-COMMON/MPL/MPL_Local.c ../00-COMMON/MPL/MPL_Mgmt.c ../00-COMMON/MPL/MPL_Sync.c ../00-COMMON/MPU/MPU_Async.c ../00-COMMON/MPU/MPU_Init.c ../00-COMMON/MPU/MPU_ISR.c ../00-COMMON/MPU/MPU_Local.c ../00-COMMON/MPU/MPU_Mgmt.c ../00-COMMON/MPU/MPU_Reset.c ../00-COMMON/MPU/MPU_Sync.c ../00-COMMON/SDL/SDL_API.c ../00-COMMON/SDL/SDL_Init.c ../00-COMMON/SDL/SDL_ISR.c ../00-COMMON/SDL/SDL_Local.c ../00-COMMON/TMR/TMR.c ../00-COMMON/TMR/TMRInit.c ../00-COMMON/TMR/TMRLocal.c ../00-COMMON/TMR/TMR_ISR.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/_ext/554684679/BLI.o ${OBJECTDIR}/_ext/554684679/BLIInit.o ${OBJECTDIR}/_ext/554684679/BLILocal.o ${OBJECTDIR}/_ext/554684679/BLIMorse.o ${OBJECTDIR}/_ext/554678764/I2C_Async.o ${OBJECTDIR}/_ext/554678764/I2C_Init.o ${OBJECTDIR}/_ext/554678764/I2C_ISR.o ${OBJECTDIR}/_ext/554678764/I2C_Local.o ${OBJECTDIR}/_ext/554678764/I2C_Sync.o ${OBJECTDIR}/_ext/554678764/I2C_SyncRead.o ${OBJECTDIR}/_ext/554678764/I2C_SyncWrite.o ${OBJECTDIR}/_ext/15113546/Init.o ${OBJECTDIR}/_ext/554673981/MPL_Async.o ${OBJECTDIR}/_ext/554673981/MPL_Init.o ${OBJECTDIR}/_ext/554673981/MPL_ISR.o ${OBJECTDIR}/_ext/554673981/MPL_Local.o ${OBJECTDIR}/_ext/554673981/MPL_Mgmt.o ${OBJECTDIR}/_ext/554673981/MPL_Sync.o ${OBJECTDIR}/_ext/554673972/MPU_Async.o ${OBJECTDIR}/_ext/554673972/MPU_Init.o ${OBJECTDIR}/_ext/554673972/MPU_ISR.o ${OBJECTDIR}/_ext/554673972/MPU_Local.o ${OBJECTDIR}/_ext/554673972/MPU_Mgmt.o ${OBJECTDIR}/_ext/554673972/MPU_Reset.o ${OBJECTDIR}/_ext/554673972/MPU_Sync.o ${OBJECTDIR}/_ext/554668587/SDL_API.o ${OBJECTDIR}/_ext/554668587/SDL_Init.o ${OBJECTDIR}/_ext/554668587/SDL_ISR.o ${OBJECTDIR}/_ext/554668587/SDL_Local.o ${OBJECTDIR}/_ext/554667341/TMR.o ${OBJECTDIR}/_ext/554667341/TMRInit.o ${OBJECTDIR}/_ext/554667341/TMRLocal.o ${OBJECTDIR}/_ext/554667341/TMR_ISR.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/_ext/554684679/BLI.o.d ${OBJECTDIR}/_ext/554684679/BLIInit.o.d ${OBJECTDIR}/_ext/554684679/BLILocal.o.d ${OBJECTDIR}/_ext/554684679/BLIMorse.o.d ${OBJECTDIR}/_ext/554678764/I2C_Async.o.d ${OBJECTDIR}/_ext/554678764/I2C_Init.o.d ${OBJECTDIR}/_ext/554678764/I2C_ISR.o.d ${OBJECTDIR}/_ext/554678764/I2C_Local.o.d ${OBJECTDIR}/_ext/554678764/I2C_Sync.o.d ${OBJECTDIR}/_ext/554678764/I2C_SyncRead.o.d ${OBJECTDIR}/_ext/554678764/I2C_SyncWrite.o.d ${OBJECTDIR}/_ext/15113546/Init.o.d ${OBJECTDIR}/_ext/554673981/MPL_Async.o.d ${OBJECTDIR}/_ext/554673981/MPL_Init.o.d ${OBJECTDIR}/_ext/554673981/MPL_ISR.o.d ${OBJECTDIR}/_ext/554673981/MPL_Local.o.d ${OBJECTDIR}/_ext/554673981/MPL_Mgmt.o.d ${OBJECTDIR}/_ext/554673981/MPL_Sync.o.d ${OBJECTDIR}/_ext/554673972/MPU_Async.o.d ${OBJECTDIR}/_ext/554673972/MPU_Init.o.d ${OBJECTDIR}/_ext/554673972/MPU_ISR.o.d ${OBJECTDIR}/_ext/554673972/MPU_Local.o.d ${OBJECTDIR}/_ext/554673972/MPU_Mgmt.o.d ${OBJECTDIR}/_ext/554673972/MPU_Reset.o.d ${OBJECTDIR}/_ext/554673972/MPU_Sync.o.d ${OBJECTDIR}/_ext/554668587/SDL_API.o.d ${OBJECTDIR}/_ext/554668587/SDL_Init.o.d ${OBJECTDIR}/_ext/554668587/SDL_ISR.o.d ${OBJECTDIR}/_ext/554668587/SDL_Local.o.d ${OBJECTDIR}/_ext/554667341/TMR.o.d ${OBJECTDIR}/_ext/554667341/TMRInit.o.d ${OBJECTDIR}/_ext/554667341/TMRLocal.o.d ${OBJECTDIR}/_ext/554667341/TMR_ISR.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/_ext/554684679/BLI.o ${OBJECTDIR}/_ext/554684679/BLIInit.o ${OBJECTDIR}/_ext/554684679/BLILocal.o ${OBJECTDIR}/_ext/554684679/BLIMorse.o ${OBJECTDIR}/_ext/554678764/I2C_Async.o ${OBJECTDIR}/_ext/554678764/I2C_Init.o ${OBJECTDIR}/_ext/554678764/I2C_ISR.o ${OBJECTDIR}/_ext/554678764/I2C_Local.o ${OBJECTDIR}/_ext/554678764/I2C_Sync.o ${OBJECTDIR}/_ext/554678764/I2C_SyncRead.o ${OBJECTDIR}/_ext/554678764/I2C_SyncWrite.o ${OBJECTDIR}/_ext/15113546/Init.o ${OBJECTDIR}/_ext/554673981/MPL_Async.o ${OBJECTDIR}/_ext/554673981/MPL_Init.o ${OBJECTDIR}/_ext/554673981/MPL_ISR.o ${OBJECTDIR}/_ext/554673981/MPL_Local.o ${OBJECTDIR}/_ext/554673981/MPL_Mgmt.o ${OBJECTDIR}/_ext/554673981/MPL_Sync.o ${OBJECTDIR}/_ext/554673972/MPU_Async.o ${OBJECTDIR}/_ext/554673972/MPU_Init.o ${OBJECTDIR}/_ext/554673972/MPU_ISR.o ${OBJECTDIR}/_ext/554673972/MPU_Local.o ${OBJECTDIR}/_ext/554673972/MPU_Mgmt.o ${OBJECTDIR}/_ext/554673972/MPU_Reset.o ${OBJECTDIR}/_ext/554673972/MPU_Sync.o ${OBJECTDIR}/_ext/554668587/SDL_API.o ${OBJECTDIR}/_ext/554668587/SDL_Init.o ${OBJECTDIR}/_ext/554668587/SDL_ISR.o ${OBJECTDIR}/_ext/554668587/SDL_Local.o ${OBJECTDIR}/_ext/554667341/TMR.o ${OBJECTDIR}/_ext/554667341/TMRInit.o ${OBJECTDIR}/_ext/554667341/TMRLocal.o ${OBJECTDIR}/_ext/554667341/TMR_ISR.o

# Source Files
SOURCEFILES=main.c ../00-COMMON/BLI/BLI.c ../00-COMMON/BLI/BLIInit.c ../00-COMMON/BLI/BLILocal.c ../00-COMMON/BLI/BLIMorse.c ../00-COMMON/I2C/I2C_Async.c ../00-COMMON/I2C/I2C_Init.c ../00-COMMON/I2C/I2C_ISR.c ../00-COMMON/I2C/I2C_Local.c ../00-COMMON/I2C/I2C_Sync.c ../00-COMMON/I2C/I2C_SyncRead.c ../00-COMMON/I2C/I2C_SyncWrite.c ../00-COMMON/Init/Init.c ../00-COMMON/MPL/MPL_Async.c ../00-COMMON/MPL/MPL_Init.c ../00-COMMON/MPL/MPL_ISR.c ../00-COMMON/MPL/MPL_Local.c ../00-COMMON/MPL/MPL_Mgmt.c ../00-COMMON/MPL/MPL_Sync.c ../00-COMMON/MPU/MPU_Async.c ../00-COMMON/MPU/MPU_Init.c ../00-COMMON/MPU/MPU_ISR.c ../00-COMMON/MPU/MPU_Local.c ../00-COMMON/MPU/MPU_Mgmt.c ../00-COMMON/MPU/MPU_Reset.c ../00-COMMON/MPU/MPU_Sync.c ../00-COMMON/SDL/SDL_API.c ../00-COMMON/SDL/SDL_Init.c ../00-COMMON/SDL/SDL_ISR.c ../00-COMMON/SDL/SDL_Local.c ../00-COMMON/TMR/TMR.c ../00-COMMON/TMR/TMRInit.c ../00-COMMON/TMR/TMRLocal.c ../00-COMMON/TMR/TMR_ISR.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/18-I2C-All-ASync.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24EP512GP806
MP_LINKER_FILE_OPTION=,--script=p24EP512GP806.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554684679/BLI.o: ../00-COMMON/BLI/BLI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554684679 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLI.o.d 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/BLI/BLI.c  -o ${OBJECTDIR}/_ext/554684679/BLI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554684679/BLI.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554684679/BLI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554684679/BLIInit.o: ../00-COMMON/BLI/BLIInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554684679 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLIInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLIInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/BLI/BLIInit.c  -o ${OBJECTDIR}/_ext/554684679/BLIInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554684679/BLIInit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554684679/BLIInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554684679/BLILocal.o: ../00-COMMON/BLI/BLILocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554684679 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLILocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLILocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/BLI/BLILocal.c  -o ${OBJECTDIR}/_ext/554684679/BLILocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554684679/BLILocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554684679/BLILocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554684679/BLIMorse.o: ../00-COMMON/BLI/BLIMorse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554684679 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLIMorse.o.d 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLIMorse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/BLI/BLIMorse.c  -o ${OBJECTDIR}/_ext/554684679/BLIMorse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554684679/BLIMorse.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554684679/BLIMorse.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554678764/I2C_Async.o: ../00-COMMON/I2C/I2C_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554678764 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/I2C/I2C_Async.c  -o ${OBJECTDIR}/_ext/554678764/I2C_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554678764/I2C_Async.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554678764/I2C_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554678764/I2C_Init.o: ../00-COMMON/I2C/I2C_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554678764 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/I2C/I2C_Init.c  -o ${OBJECTDIR}/_ext/554678764/I2C_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554678764/I2C_Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554678764/I2C_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554678764/I2C_ISR.o: ../00-COMMON/I2C/I2C_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554678764 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/I2C/I2C_ISR.c  -o ${OBJECTDIR}/_ext/554678764/I2C_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554678764/I2C_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554678764/I2C_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554678764/I2C_Local.o: ../00-COMMON/I2C/I2C_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554678764 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/I2C/I2C_Local.c  -o ${OBJECTDIR}/_ext/554678764/I2C_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554678764/I2C_Local.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554678764/I2C_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554678764/I2C_Sync.o: ../00-COMMON/I2C/I2C_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554678764 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/I2C/I2C_Sync.c  -o ${OBJECTDIR}/_ext/554678764/I2C_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554678764/I2C_Sync.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554678764/I2C_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554678764/I2C_SyncRead.o: ../00-COMMON/I2C/I2C_SyncRead.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554678764 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_SyncRead.o.d 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_SyncRead.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/I2C/I2C_SyncRead.c  -o ${OBJECTDIR}/_ext/554678764/I2C_SyncRead.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554678764/I2C_SyncRead.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554678764/I2C_SyncRead.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554678764/I2C_SyncWrite.o: ../00-COMMON/I2C/I2C_SyncWrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554678764 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_SyncWrite.o.d 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_SyncWrite.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/I2C/I2C_SyncWrite.c  -o ${OBJECTDIR}/_ext/554678764/I2C_SyncWrite.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554678764/I2C_SyncWrite.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554678764/I2C_SyncWrite.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/15113546/Init.o: ../00-COMMON/Init/Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/15113546 
	@${RM} ${OBJECTDIR}/_ext/15113546/Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/15113546/Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/Init/Init.c  -o ${OBJECTDIR}/_ext/15113546/Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/15113546/Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/15113546/Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673981/MPL_Async.o: ../00-COMMON/MPL/MPL_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673981 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPL/MPL_Async.c  -o ${OBJECTDIR}/_ext/554673981/MPL_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673981/MPL_Async.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673981/MPL_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673981/MPL_Init.o: ../00-COMMON/MPL/MPL_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673981 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPL/MPL_Init.c  -o ${OBJECTDIR}/_ext/554673981/MPL_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673981/MPL_Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673981/MPL_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673981/MPL_ISR.o: ../00-COMMON/MPL/MPL_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673981 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPL/MPL_ISR.c  -o ${OBJECTDIR}/_ext/554673981/MPL_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673981/MPL_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673981/MPL_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673981/MPL_Local.o: ../00-COMMON/MPL/MPL_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673981 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPL/MPL_Local.c  -o ${OBJECTDIR}/_ext/554673981/MPL_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673981/MPL_Local.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673981/MPL_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673981/MPL_Mgmt.o: ../00-COMMON/MPL/MPL_Mgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673981 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Mgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Mgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPL/MPL_Mgmt.c  -o ${OBJECTDIR}/_ext/554673981/MPL_Mgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673981/MPL_Mgmt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673981/MPL_Mgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673981/MPL_Sync.o: ../00-COMMON/MPL/MPL_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673981 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPL/MPL_Sync.c  -o ${OBJECTDIR}/_ext/554673981/MPL_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673981/MPL_Sync.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673981/MPL_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673972/MPU_Async.o: ../00-COMMON/MPU/MPU_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673972 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPU/MPU_Async.c  -o ${OBJECTDIR}/_ext/554673972/MPU_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673972/MPU_Async.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673972/MPU_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673972/MPU_Init.o: ../00-COMMON/MPU/MPU_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673972 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPU/MPU_Init.c  -o ${OBJECTDIR}/_ext/554673972/MPU_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673972/MPU_Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673972/MPU_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673972/MPU_ISR.o: ../00-COMMON/MPU/MPU_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673972 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPU/MPU_ISR.c  -o ${OBJECTDIR}/_ext/554673972/MPU_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673972/MPU_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673972/MPU_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673972/MPU_Local.o: ../00-COMMON/MPU/MPU_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673972 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPU/MPU_Local.c  -o ${OBJECTDIR}/_ext/554673972/MPU_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673972/MPU_Local.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673972/MPU_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673972/MPU_Mgmt.o: ../00-COMMON/MPU/MPU_Mgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673972 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Mgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Mgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPU/MPU_Mgmt.c  -o ${OBJECTDIR}/_ext/554673972/MPU_Mgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673972/MPU_Mgmt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673972/MPU_Mgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673972/MPU_Reset.o: ../00-COMMON/MPU/MPU_Reset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673972 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Reset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPU/MPU_Reset.c  -o ${OBJECTDIR}/_ext/554673972/MPU_Reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673972/MPU_Reset.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673972/MPU_Reset.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673972/MPU_Sync.o: ../00-COMMON/MPU/MPU_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673972 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPU/MPU_Sync.c  -o ${OBJECTDIR}/_ext/554673972/MPU_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673972/MPU_Sync.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673972/MPU_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554668587/SDL_API.o: ../00-COMMON/SDL/SDL_API.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554668587 
	@${RM} ${OBJECTDIR}/_ext/554668587/SDL_API.o.d 
	@${RM} ${OBJECTDIR}/_ext/554668587/SDL_API.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/SDL/SDL_API.c  -o ${OBJECTDIR}/_ext/554668587/SDL_API.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554668587/SDL_API.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554668587/SDL_API.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554668587/SDL_Init.o: ../00-COMMON/SDL/SDL_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554668587 
	@${RM} ${OBJECTDIR}/_ext/554668587/SDL_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/554668587/SDL_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/SDL/SDL_Init.c  -o ${OBJECTDIR}/_ext/554668587/SDL_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554668587/SDL_Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554668587/SDL_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554668587/SDL_ISR.o: ../00-COMMON/SDL/SDL_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554668587 
	@${RM} ${OBJECTDIR}/_ext/554668587/SDL_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/554668587/SDL_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/SDL/SDL_ISR.c  -o ${OBJECTDIR}/_ext/554668587/SDL_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554668587/SDL_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554668587/SDL_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554668587/SDL_Local.o: ../00-COMMON/SDL/SDL_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554668587 
	@${RM} ${OBJECTDIR}/_ext/554668587/SDL_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/554668587/SDL_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/SDL/SDL_Local.c  -o ${OBJECTDIR}/_ext/554668587/SDL_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554668587/SDL_Local.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554668587/SDL_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554667341/TMR.o: ../00-COMMON/TMR/TMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554667341 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/TMR/TMR.c  -o ${OBJECTDIR}/_ext/554667341/TMR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554667341/TMR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554667341/TMR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554667341/TMRInit.o: ../00-COMMON/TMR/TMRInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554667341 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMRInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMRInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/TMR/TMRInit.c  -o ${OBJECTDIR}/_ext/554667341/TMRInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554667341/TMRInit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554667341/TMRInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554667341/TMRLocal.o: ../00-COMMON/TMR/TMRLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554667341 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMRLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMRLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/TMR/TMRLocal.c  -o ${OBJECTDIR}/_ext/554667341/TMRLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554667341/TMRLocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554667341/TMRLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554667341/TMR_ISR.o: ../00-COMMON/TMR/TMR_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554667341 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMR_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMR_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/TMR/TMR_ISR.c  -o ${OBJECTDIR}/_ext/554667341/TMR_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554667341/TMR_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554667341/TMR_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554684679/BLI.o: ../00-COMMON/BLI/BLI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554684679 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLI.o.d 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/BLI/BLI.c  -o ${OBJECTDIR}/_ext/554684679/BLI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554684679/BLI.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554684679/BLI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554684679/BLIInit.o: ../00-COMMON/BLI/BLIInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554684679 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLIInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLIInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/BLI/BLIInit.c  -o ${OBJECTDIR}/_ext/554684679/BLIInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554684679/BLIInit.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554684679/BLIInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554684679/BLILocal.o: ../00-COMMON/BLI/BLILocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554684679 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLILocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLILocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/BLI/BLILocal.c  -o ${OBJECTDIR}/_ext/554684679/BLILocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554684679/BLILocal.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554684679/BLILocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554684679/BLIMorse.o: ../00-COMMON/BLI/BLIMorse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554684679 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLIMorse.o.d 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLIMorse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/BLI/BLIMorse.c  -o ${OBJECTDIR}/_ext/554684679/BLIMorse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554684679/BLIMorse.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554684679/BLIMorse.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554678764/I2C_Async.o: ../00-COMMON/I2C/I2C_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554678764 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/I2C/I2C_Async.c  -o ${OBJECTDIR}/_ext/554678764/I2C_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554678764/I2C_Async.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554678764/I2C_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554678764/I2C_Init.o: ../00-COMMON/I2C/I2C_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554678764 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/I2C/I2C_Init.c  -o ${OBJECTDIR}/_ext/554678764/I2C_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554678764/I2C_Init.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554678764/I2C_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554678764/I2C_ISR.o: ../00-COMMON/I2C/I2C_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554678764 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/I2C/I2C_ISR.c  -o ${OBJECTDIR}/_ext/554678764/I2C_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554678764/I2C_ISR.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554678764/I2C_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554678764/I2C_Local.o: ../00-COMMON/I2C/I2C_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554678764 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/I2C/I2C_Local.c  -o ${OBJECTDIR}/_ext/554678764/I2C_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554678764/I2C_Local.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554678764/I2C_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554678764/I2C_Sync.o: ../00-COMMON/I2C/I2C_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554678764 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/I2C/I2C_Sync.c  -o ${OBJECTDIR}/_ext/554678764/I2C_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554678764/I2C_Sync.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554678764/I2C_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554678764/I2C_SyncRead.o: ../00-COMMON/I2C/I2C_SyncRead.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554678764 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_SyncRead.o.d 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_SyncRead.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/I2C/I2C_SyncRead.c  -o ${OBJECTDIR}/_ext/554678764/I2C_SyncRead.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554678764/I2C_SyncRead.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554678764/I2C_SyncRead.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554678764/I2C_SyncWrite.o: ../00-COMMON/I2C/I2C_SyncWrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554678764 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_SyncWrite.o.d 
	@${RM} ${OBJECTDIR}/_ext/554678764/I2C_SyncWrite.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/I2C/I2C_SyncWrite.c  -o ${OBJECTDIR}/_ext/554678764/I2C_SyncWrite.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554678764/I2C_SyncWrite.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554678764/I2C_SyncWrite.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/15113546/Init.o: ../00-COMMON/Init/Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/15113546 
	@${RM} ${OBJECTDIR}/_ext/15113546/Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/15113546/Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/Init/Init.c  -o ${OBJECTDIR}/_ext/15113546/Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/15113546/Init.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/15113546/Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673981/MPL_Async.o: ../00-COMMON/MPL/MPL_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673981 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPL/MPL_Async.c  -o ${OBJECTDIR}/_ext/554673981/MPL_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673981/MPL_Async.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673981/MPL_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673981/MPL_Init.o: ../00-COMMON/MPL/MPL_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673981 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPL/MPL_Init.c  -o ${OBJECTDIR}/_ext/554673981/MPL_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673981/MPL_Init.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673981/MPL_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673981/MPL_ISR.o: ../00-COMMON/MPL/MPL_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673981 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPL/MPL_ISR.c  -o ${OBJECTDIR}/_ext/554673981/MPL_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673981/MPL_ISR.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673981/MPL_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673981/MPL_Local.o: ../00-COMMON/MPL/MPL_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673981 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPL/MPL_Local.c  -o ${OBJECTDIR}/_ext/554673981/MPL_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673981/MPL_Local.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673981/MPL_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673981/MPL_Mgmt.o: ../00-COMMON/MPL/MPL_Mgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673981 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Mgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Mgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPL/MPL_Mgmt.c  -o ${OBJECTDIR}/_ext/554673981/MPL_Mgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673981/MPL_Mgmt.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673981/MPL_Mgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673981/MPL_Sync.o: ../00-COMMON/MPL/MPL_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673981 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673981/MPL_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPL/MPL_Sync.c  -o ${OBJECTDIR}/_ext/554673981/MPL_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673981/MPL_Sync.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673981/MPL_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673972/MPU_Async.o: ../00-COMMON/MPU/MPU_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673972 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPU/MPU_Async.c  -o ${OBJECTDIR}/_ext/554673972/MPU_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673972/MPU_Async.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673972/MPU_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673972/MPU_Init.o: ../00-COMMON/MPU/MPU_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673972 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPU/MPU_Init.c  -o ${OBJECTDIR}/_ext/554673972/MPU_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673972/MPU_Init.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673972/MPU_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673972/MPU_ISR.o: ../00-COMMON/MPU/MPU_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673972 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPU/MPU_ISR.c  -o ${OBJECTDIR}/_ext/554673972/MPU_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673972/MPU_ISR.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673972/MPU_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673972/MPU_Local.o: ../00-COMMON/MPU/MPU_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673972 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPU/MPU_Local.c  -o ${OBJECTDIR}/_ext/554673972/MPU_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673972/MPU_Local.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673972/MPU_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673972/MPU_Mgmt.o: ../00-COMMON/MPU/MPU_Mgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673972 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Mgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Mgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPU/MPU_Mgmt.c  -o ${OBJECTDIR}/_ext/554673972/MPU_Mgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673972/MPU_Mgmt.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673972/MPU_Mgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673972/MPU_Reset.o: ../00-COMMON/MPU/MPU_Reset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673972 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Reset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPU/MPU_Reset.c  -o ${OBJECTDIR}/_ext/554673972/MPU_Reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673972/MPU_Reset.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673972/MPU_Reset.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554673972/MPU_Sync.o: ../00-COMMON/MPU/MPU_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554673972 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/554673972/MPU_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/MPU/MPU_Sync.c  -o ${OBJECTDIR}/_ext/554673972/MPU_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554673972/MPU_Sync.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554673972/MPU_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554668587/SDL_API.o: ../00-COMMON/SDL/SDL_API.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554668587 
	@${RM} ${OBJECTDIR}/_ext/554668587/SDL_API.o.d 
	@${RM} ${OBJECTDIR}/_ext/554668587/SDL_API.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/SDL/SDL_API.c  -o ${OBJECTDIR}/_ext/554668587/SDL_API.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554668587/SDL_API.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554668587/SDL_API.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554668587/SDL_Init.o: ../00-COMMON/SDL/SDL_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554668587 
	@${RM} ${OBJECTDIR}/_ext/554668587/SDL_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/554668587/SDL_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/SDL/SDL_Init.c  -o ${OBJECTDIR}/_ext/554668587/SDL_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554668587/SDL_Init.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554668587/SDL_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554668587/SDL_ISR.o: ../00-COMMON/SDL/SDL_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554668587 
	@${RM} ${OBJECTDIR}/_ext/554668587/SDL_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/554668587/SDL_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/SDL/SDL_ISR.c  -o ${OBJECTDIR}/_ext/554668587/SDL_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554668587/SDL_ISR.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554668587/SDL_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554668587/SDL_Local.o: ../00-COMMON/SDL/SDL_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554668587 
	@${RM} ${OBJECTDIR}/_ext/554668587/SDL_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/554668587/SDL_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/SDL/SDL_Local.c  -o ${OBJECTDIR}/_ext/554668587/SDL_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554668587/SDL_Local.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554668587/SDL_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554667341/TMR.o: ../00-COMMON/TMR/TMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554667341 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/TMR/TMR.c  -o ${OBJECTDIR}/_ext/554667341/TMR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554667341/TMR.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554667341/TMR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554667341/TMRInit.o: ../00-COMMON/TMR/TMRInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554667341 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMRInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMRInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/TMR/TMRInit.c  -o ${OBJECTDIR}/_ext/554667341/TMRInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554667341/TMRInit.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554667341/TMRInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554667341/TMRLocal.o: ../00-COMMON/TMR/TMRLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554667341 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMRLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMRLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/TMR/TMRLocal.c  -o ${OBJECTDIR}/_ext/554667341/TMRLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554667341/TMRLocal.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554667341/TMRLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554667341/TMR_ISR.o: ../00-COMMON/TMR/TMR_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554667341 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMR_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMR_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/TMR/TMR_ISR.c  -o ${OBJECTDIR}/_ext/554667341/TMR_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554667341/TMR_ISR.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-COMMON" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554667341/TMR_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
dist/${CND_CONF}/${IMAGE_TYPE}/18-I2C-All-ASync.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/18-I2C-All-ASync.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/18-I2C-All-ASync.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/18-I2C-All-ASync.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/18-I2C-All-ASync.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
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
