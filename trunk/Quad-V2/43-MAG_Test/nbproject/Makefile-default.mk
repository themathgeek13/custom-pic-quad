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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/43-MAG_Test.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/43-MAG_Test.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../00-Modules/BLI/BLI.c ../00-Modules/BLI/BLIInit.c ../00-Modules/BLI/BLILocal.c ../00-Modules/BLI/BLIMorse.c ../00-Modules/DCM/DCM.c ../00-Modules/DCM/DCMBaseVectors.c ../00-Modules/DCM/DCMConstructors.c ../00-Modules/DCM/DCMLocal.c ../00-Modules/DCM/DCMMethods.c ../00-Modules/HMCMAG/HMCMAG_Async.c ../00-Modules/HMCMAG/HMCMAG_Init.c ../00-Modules/HMCMAG/HMCMAG_Local.c ../00-Modules/HMCMAG/HMCMAG_Mgmt.c ../00-Modules/HMCMAG/HMCMAG_Sync.c ../00-Modules/HMCMAG/HMCMAG_ISR.c ../00-Modules/I2C/I2C_Async.c ../00-Modules/I2C/I2C_Init.c ../00-Modules/I2C/I2C_ISR.c ../00-Modules/I2C/I2C_Local.c ../00-Modules/I2C/I2C_Sync.c ../00-Modules/I2C/I2C_SyncRead.c ../00-Modules/I2C/I2C_SyncWrite.c ../00-Modules/Init/Init.c ../00-Modules/TMR/TMR.c ../00-Modules/TMR/TMRInit.c ../00-Modules/TMR/TMRLocal.c ../00-Modules/TMR/TMR_ISR.c ../00-Modules/UART/UART_TX_API.c ../00-Modules/UART/UART_TX_Init.c ../00-Modules/UART/UART_TX_ISR.c ../00-Modules/UART/UART_TX_Local.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/261189241/BLI.o ${OBJECTDIR}/_ext/261189241/BLIInit.o ${OBJECTDIR}/_ext/261189241/BLILocal.o ${OBJECTDIR}/_ext/261189241/BLIMorse.o ${OBJECTDIR}/_ext/261190888/DCM.o ${OBJECTDIR}/_ext/261190888/DCMBaseVectors.o ${OBJECTDIR}/_ext/261190888/DCMConstructors.o ${OBJECTDIR}/_ext/261190888/DCMLocal.o ${OBJECTDIR}/_ext/261190888/DCMMethods.o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Async.o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Init.o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Local.o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Mgmt.o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Sync.o ${OBJECTDIR}/_ext/1219465957/HMCMAG_ISR.o ${OBJECTDIR}/_ext/261195156/I2C_Async.o ${OBJECTDIR}/_ext/261195156/I2C_Init.o ${OBJECTDIR}/_ext/261195156/I2C_ISR.o ${OBJECTDIR}/_ext/261195156/I2C_Local.o ${OBJECTDIR}/_ext/261195156/I2C_Sync.o ${OBJECTDIR}/_ext/261195156/I2C_SyncRead.o ${OBJECTDIR}/_ext/261195156/I2C_SyncWrite.o ${OBJECTDIR}/_ext/492825802/Init.o ${OBJECTDIR}/_ext/261206579/TMR.o ${OBJECTDIR}/_ext/261206579/TMRInit.o ${OBJECTDIR}/_ext/261206579/TMRLocal.o ${OBJECTDIR}/_ext/261206579/TMR_ISR.o ${OBJECTDIR}/_ext/492512300/UART_TX_API.o ${OBJECTDIR}/_ext/492512300/UART_TX_Init.o ${OBJECTDIR}/_ext/492512300/UART_TX_ISR.o ${OBJECTDIR}/_ext/492512300/UART_TX_Local.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/261189241/BLI.o.d ${OBJECTDIR}/_ext/261189241/BLIInit.o.d ${OBJECTDIR}/_ext/261189241/BLILocal.o.d ${OBJECTDIR}/_ext/261189241/BLIMorse.o.d ${OBJECTDIR}/_ext/261190888/DCM.o.d ${OBJECTDIR}/_ext/261190888/DCMBaseVectors.o.d ${OBJECTDIR}/_ext/261190888/DCMConstructors.o.d ${OBJECTDIR}/_ext/261190888/DCMLocal.o.d ${OBJECTDIR}/_ext/261190888/DCMMethods.o.d ${OBJECTDIR}/_ext/1219465957/HMCMAG_Async.o.d ${OBJECTDIR}/_ext/1219465957/HMCMAG_Init.o.d ${OBJECTDIR}/_ext/1219465957/HMCMAG_Local.o.d ${OBJECTDIR}/_ext/1219465957/HMCMAG_Mgmt.o.d ${OBJECTDIR}/_ext/1219465957/HMCMAG_Sync.o.d ${OBJECTDIR}/_ext/1219465957/HMCMAG_ISR.o.d ${OBJECTDIR}/_ext/261195156/I2C_Async.o.d ${OBJECTDIR}/_ext/261195156/I2C_Init.o.d ${OBJECTDIR}/_ext/261195156/I2C_ISR.o.d ${OBJECTDIR}/_ext/261195156/I2C_Local.o.d ${OBJECTDIR}/_ext/261195156/I2C_Sync.o.d ${OBJECTDIR}/_ext/261195156/I2C_SyncRead.o.d ${OBJECTDIR}/_ext/261195156/I2C_SyncWrite.o.d ${OBJECTDIR}/_ext/492825802/Init.o.d ${OBJECTDIR}/_ext/261206579/TMR.o.d ${OBJECTDIR}/_ext/261206579/TMRInit.o.d ${OBJECTDIR}/_ext/261206579/TMRLocal.o.d ${OBJECTDIR}/_ext/261206579/TMR_ISR.o.d ${OBJECTDIR}/_ext/492512300/UART_TX_API.o.d ${OBJECTDIR}/_ext/492512300/UART_TX_Init.o.d ${OBJECTDIR}/_ext/492512300/UART_TX_ISR.o.d ${OBJECTDIR}/_ext/492512300/UART_TX_Local.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/261189241/BLI.o ${OBJECTDIR}/_ext/261189241/BLIInit.o ${OBJECTDIR}/_ext/261189241/BLILocal.o ${OBJECTDIR}/_ext/261189241/BLIMorse.o ${OBJECTDIR}/_ext/261190888/DCM.o ${OBJECTDIR}/_ext/261190888/DCMBaseVectors.o ${OBJECTDIR}/_ext/261190888/DCMConstructors.o ${OBJECTDIR}/_ext/261190888/DCMLocal.o ${OBJECTDIR}/_ext/261190888/DCMMethods.o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Async.o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Init.o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Local.o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Mgmt.o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Sync.o ${OBJECTDIR}/_ext/1219465957/HMCMAG_ISR.o ${OBJECTDIR}/_ext/261195156/I2C_Async.o ${OBJECTDIR}/_ext/261195156/I2C_Init.o ${OBJECTDIR}/_ext/261195156/I2C_ISR.o ${OBJECTDIR}/_ext/261195156/I2C_Local.o ${OBJECTDIR}/_ext/261195156/I2C_Sync.o ${OBJECTDIR}/_ext/261195156/I2C_SyncRead.o ${OBJECTDIR}/_ext/261195156/I2C_SyncWrite.o ${OBJECTDIR}/_ext/492825802/Init.o ${OBJECTDIR}/_ext/261206579/TMR.o ${OBJECTDIR}/_ext/261206579/TMRInit.o ${OBJECTDIR}/_ext/261206579/TMRLocal.o ${OBJECTDIR}/_ext/261206579/TMR_ISR.o ${OBJECTDIR}/_ext/492512300/UART_TX_API.o ${OBJECTDIR}/_ext/492512300/UART_TX_Init.o ${OBJECTDIR}/_ext/492512300/UART_TX_ISR.o ${OBJECTDIR}/_ext/492512300/UART_TX_Local.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=../00-Modules/BLI/BLI.c ../00-Modules/BLI/BLIInit.c ../00-Modules/BLI/BLILocal.c ../00-Modules/BLI/BLIMorse.c ../00-Modules/DCM/DCM.c ../00-Modules/DCM/DCMBaseVectors.c ../00-Modules/DCM/DCMConstructors.c ../00-Modules/DCM/DCMLocal.c ../00-Modules/DCM/DCMMethods.c ../00-Modules/HMCMAG/HMCMAG_Async.c ../00-Modules/HMCMAG/HMCMAG_Init.c ../00-Modules/HMCMAG/HMCMAG_Local.c ../00-Modules/HMCMAG/HMCMAG_Mgmt.c ../00-Modules/HMCMAG/HMCMAG_Sync.c ../00-Modules/HMCMAG/HMCMAG_ISR.c ../00-Modules/I2C/I2C_Async.c ../00-Modules/I2C/I2C_Init.c ../00-Modules/I2C/I2C_ISR.c ../00-Modules/I2C/I2C_Local.c ../00-Modules/I2C/I2C_Sync.c ../00-Modules/I2C/I2C_SyncRead.c ../00-Modules/I2C/I2C_SyncWrite.c ../00-Modules/Init/Init.c ../00-Modules/TMR/TMR.c ../00-Modules/TMR/TMRInit.c ../00-Modules/TMR/TMRLocal.c ../00-Modules/TMR/TMR_ISR.c ../00-Modules/UART/UART_TX_API.c ../00-Modules/UART/UART_TX_Init.c ../00-Modules/UART/UART_TX_ISR.c ../00-Modules/UART/UART_TX_Local.c main.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/43-MAG_Test.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24HJ128GP204
MP_LINKER_FILE_OPTION=,--script=p24HJ128GP204.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/261189241/BLI.o: ../00-Modules/BLI/BLI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261189241 
	@${RM} ${OBJECTDIR}/_ext/261189241/BLI.o.d 
	@${RM} ${OBJECTDIR}/_ext/261189241/BLI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/BLI/BLI.c  -o ${OBJECTDIR}/_ext/261189241/BLI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261189241/BLI.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261189241/BLI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261189241/BLIInit.o: ../00-Modules/BLI/BLIInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261189241 
	@${RM} ${OBJECTDIR}/_ext/261189241/BLIInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/261189241/BLIInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/BLI/BLIInit.c  -o ${OBJECTDIR}/_ext/261189241/BLIInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261189241/BLIInit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261189241/BLIInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261189241/BLILocal.o: ../00-Modules/BLI/BLILocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261189241 
	@${RM} ${OBJECTDIR}/_ext/261189241/BLILocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/261189241/BLILocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/BLI/BLILocal.c  -o ${OBJECTDIR}/_ext/261189241/BLILocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261189241/BLILocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261189241/BLILocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261189241/BLIMorse.o: ../00-Modules/BLI/BLIMorse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261189241 
	@${RM} ${OBJECTDIR}/_ext/261189241/BLIMorse.o.d 
	@${RM} ${OBJECTDIR}/_ext/261189241/BLIMorse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/BLI/BLIMorse.c  -o ${OBJECTDIR}/_ext/261189241/BLIMorse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261189241/BLIMorse.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261189241/BLIMorse.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261190888/DCM.o: ../00-Modules/DCM/DCM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261190888 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCM.o.d 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/DCM/DCM.c  -o ${OBJECTDIR}/_ext/261190888/DCM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261190888/DCM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261190888/DCM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261190888/DCMBaseVectors.o: ../00-Modules/DCM/DCMBaseVectors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261190888 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCMBaseVectors.o.d 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCMBaseVectors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/DCM/DCMBaseVectors.c  -o ${OBJECTDIR}/_ext/261190888/DCMBaseVectors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261190888/DCMBaseVectors.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261190888/DCMBaseVectors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261190888/DCMConstructors.o: ../00-Modules/DCM/DCMConstructors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261190888 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCMConstructors.o.d 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCMConstructors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/DCM/DCMConstructors.c  -o ${OBJECTDIR}/_ext/261190888/DCMConstructors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261190888/DCMConstructors.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261190888/DCMConstructors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261190888/DCMLocal.o: ../00-Modules/DCM/DCMLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261190888 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCMLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCMLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/DCM/DCMLocal.c  -o ${OBJECTDIR}/_ext/261190888/DCMLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261190888/DCMLocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261190888/DCMLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261190888/DCMMethods.o: ../00-Modules/DCM/DCMMethods.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261190888 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCMMethods.o.d 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCMMethods.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/DCM/DCMMethods.c  -o ${OBJECTDIR}/_ext/261190888/DCMMethods.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261190888/DCMMethods.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261190888/DCMMethods.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1219465957/HMCMAG_Async.o: ../00-Modules/HMCMAG/HMCMAG_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1219465957 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/HMCMAG/HMCMAG_Async.c  -o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1219465957/HMCMAG_Async.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1219465957/HMCMAG_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1219465957/HMCMAG_Init.o: ../00-Modules/HMCMAG/HMCMAG_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1219465957 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/HMCMAG/HMCMAG_Init.c  -o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1219465957/HMCMAG_Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1219465957/HMCMAG_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1219465957/HMCMAG_Local.o: ../00-Modules/HMCMAG/HMCMAG_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1219465957 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/HMCMAG/HMCMAG_Local.c  -o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1219465957/HMCMAG_Local.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1219465957/HMCMAG_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1219465957/HMCMAG_Mgmt.o: ../00-Modules/HMCMAG/HMCMAG_Mgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1219465957 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Mgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Mgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/HMCMAG/HMCMAG_Mgmt.c  -o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Mgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1219465957/HMCMAG_Mgmt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1219465957/HMCMAG_Mgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1219465957/HMCMAG_Sync.o: ../00-Modules/HMCMAG/HMCMAG_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1219465957 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/HMCMAG/HMCMAG_Sync.c  -o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1219465957/HMCMAG_Sync.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1219465957/HMCMAG_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1219465957/HMCMAG_ISR.o: ../00-Modules/HMCMAG/HMCMAG_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1219465957 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/HMCMAG/HMCMAG_ISR.c  -o ${OBJECTDIR}/_ext/1219465957/HMCMAG_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1219465957/HMCMAG_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1219465957/HMCMAG_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261195156/I2C_Async.o: ../00-Modules/I2C/I2C_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261195156 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/I2C/I2C_Async.c  -o ${OBJECTDIR}/_ext/261195156/I2C_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261195156/I2C_Async.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261195156/I2C_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261195156/I2C_Init.o: ../00-Modules/I2C/I2C_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261195156 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/I2C/I2C_Init.c  -o ${OBJECTDIR}/_ext/261195156/I2C_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261195156/I2C_Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261195156/I2C_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261195156/I2C_ISR.o: ../00-Modules/I2C/I2C_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261195156 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/I2C/I2C_ISR.c  -o ${OBJECTDIR}/_ext/261195156/I2C_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261195156/I2C_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261195156/I2C_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261195156/I2C_Local.o: ../00-Modules/I2C/I2C_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261195156 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/I2C/I2C_Local.c  -o ${OBJECTDIR}/_ext/261195156/I2C_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261195156/I2C_Local.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261195156/I2C_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261195156/I2C_Sync.o: ../00-Modules/I2C/I2C_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261195156 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/I2C/I2C_Sync.c  -o ${OBJECTDIR}/_ext/261195156/I2C_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261195156/I2C_Sync.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261195156/I2C_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261195156/I2C_SyncRead.o: ../00-Modules/I2C/I2C_SyncRead.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261195156 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_SyncRead.o.d 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_SyncRead.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/I2C/I2C_SyncRead.c  -o ${OBJECTDIR}/_ext/261195156/I2C_SyncRead.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261195156/I2C_SyncRead.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261195156/I2C_SyncRead.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261195156/I2C_SyncWrite.o: ../00-Modules/I2C/I2C_SyncWrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261195156 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_SyncWrite.o.d 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_SyncWrite.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/I2C/I2C_SyncWrite.c  -o ${OBJECTDIR}/_ext/261195156/I2C_SyncWrite.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261195156/I2C_SyncWrite.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261195156/I2C_SyncWrite.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/492825802/Init.o: ../00-Modules/Init/Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/492825802 
	@${RM} ${OBJECTDIR}/_ext/492825802/Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/492825802/Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/Init/Init.c  -o ${OBJECTDIR}/_ext/492825802/Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/492825802/Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/492825802/Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261206579/TMR.o: ../00-Modules/TMR/TMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261206579 
	@${RM} ${OBJECTDIR}/_ext/261206579/TMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/261206579/TMR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/TMR/TMR.c  -o ${OBJECTDIR}/_ext/261206579/TMR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261206579/TMR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261206579/TMR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261206579/TMRInit.o: ../00-Modules/TMR/TMRInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261206579 
	@${RM} ${OBJECTDIR}/_ext/261206579/TMRInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/261206579/TMRInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/TMR/TMRInit.c  -o ${OBJECTDIR}/_ext/261206579/TMRInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261206579/TMRInit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261206579/TMRInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261206579/TMRLocal.o: ../00-Modules/TMR/TMRLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261206579 
	@${RM} ${OBJECTDIR}/_ext/261206579/TMRLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/261206579/TMRLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/TMR/TMRLocal.c  -o ${OBJECTDIR}/_ext/261206579/TMRLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261206579/TMRLocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261206579/TMRLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261206579/TMR_ISR.o: ../00-Modules/TMR/TMR_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261206579 
	@${RM} ${OBJECTDIR}/_ext/261206579/TMR_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/261206579/TMR_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/TMR/TMR_ISR.c  -o ${OBJECTDIR}/_ext/261206579/TMR_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261206579/TMR_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261206579/TMR_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/492512300/UART_TX_API.o: ../00-Modules/UART/UART_TX_API.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/492512300 
	@${RM} ${OBJECTDIR}/_ext/492512300/UART_TX_API.o.d 
	@${RM} ${OBJECTDIR}/_ext/492512300/UART_TX_API.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/UART/UART_TX_API.c  -o ${OBJECTDIR}/_ext/492512300/UART_TX_API.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/492512300/UART_TX_API.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/492512300/UART_TX_API.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/492512300/UART_TX_Init.o: ../00-Modules/UART/UART_TX_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/492512300 
	@${RM} ${OBJECTDIR}/_ext/492512300/UART_TX_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/492512300/UART_TX_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/UART/UART_TX_Init.c  -o ${OBJECTDIR}/_ext/492512300/UART_TX_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/492512300/UART_TX_Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/492512300/UART_TX_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/492512300/UART_TX_ISR.o: ../00-Modules/UART/UART_TX_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/492512300 
	@${RM} ${OBJECTDIR}/_ext/492512300/UART_TX_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/492512300/UART_TX_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/UART/UART_TX_ISR.c  -o ${OBJECTDIR}/_ext/492512300/UART_TX_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/492512300/UART_TX_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/492512300/UART_TX_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/492512300/UART_TX_Local.o: ../00-Modules/UART/UART_TX_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/492512300 
	@${RM} ${OBJECTDIR}/_ext/492512300/UART_TX_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/492512300/UART_TX_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/UART/UART_TX_Local.c  -o ${OBJECTDIR}/_ext/492512300/UART_TX_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/492512300/UART_TX_Local.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/492512300/UART_TX_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/261189241/BLI.o: ../00-Modules/BLI/BLI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261189241 
	@${RM} ${OBJECTDIR}/_ext/261189241/BLI.o.d 
	@${RM} ${OBJECTDIR}/_ext/261189241/BLI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/BLI/BLI.c  -o ${OBJECTDIR}/_ext/261189241/BLI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261189241/BLI.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261189241/BLI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261189241/BLIInit.o: ../00-Modules/BLI/BLIInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261189241 
	@${RM} ${OBJECTDIR}/_ext/261189241/BLIInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/261189241/BLIInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/BLI/BLIInit.c  -o ${OBJECTDIR}/_ext/261189241/BLIInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261189241/BLIInit.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261189241/BLIInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261189241/BLILocal.o: ../00-Modules/BLI/BLILocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261189241 
	@${RM} ${OBJECTDIR}/_ext/261189241/BLILocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/261189241/BLILocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/BLI/BLILocal.c  -o ${OBJECTDIR}/_ext/261189241/BLILocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261189241/BLILocal.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261189241/BLILocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261189241/BLIMorse.o: ../00-Modules/BLI/BLIMorse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261189241 
	@${RM} ${OBJECTDIR}/_ext/261189241/BLIMorse.o.d 
	@${RM} ${OBJECTDIR}/_ext/261189241/BLIMorse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/BLI/BLIMorse.c  -o ${OBJECTDIR}/_ext/261189241/BLIMorse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261189241/BLIMorse.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261189241/BLIMorse.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261190888/DCM.o: ../00-Modules/DCM/DCM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261190888 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCM.o.d 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/DCM/DCM.c  -o ${OBJECTDIR}/_ext/261190888/DCM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261190888/DCM.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261190888/DCM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261190888/DCMBaseVectors.o: ../00-Modules/DCM/DCMBaseVectors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261190888 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCMBaseVectors.o.d 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCMBaseVectors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/DCM/DCMBaseVectors.c  -o ${OBJECTDIR}/_ext/261190888/DCMBaseVectors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261190888/DCMBaseVectors.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261190888/DCMBaseVectors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261190888/DCMConstructors.o: ../00-Modules/DCM/DCMConstructors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261190888 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCMConstructors.o.d 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCMConstructors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/DCM/DCMConstructors.c  -o ${OBJECTDIR}/_ext/261190888/DCMConstructors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261190888/DCMConstructors.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261190888/DCMConstructors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261190888/DCMLocal.o: ../00-Modules/DCM/DCMLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261190888 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCMLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCMLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/DCM/DCMLocal.c  -o ${OBJECTDIR}/_ext/261190888/DCMLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261190888/DCMLocal.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261190888/DCMLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261190888/DCMMethods.o: ../00-Modules/DCM/DCMMethods.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261190888 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCMMethods.o.d 
	@${RM} ${OBJECTDIR}/_ext/261190888/DCMMethods.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/DCM/DCMMethods.c  -o ${OBJECTDIR}/_ext/261190888/DCMMethods.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261190888/DCMMethods.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261190888/DCMMethods.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1219465957/HMCMAG_Async.o: ../00-Modules/HMCMAG/HMCMAG_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1219465957 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/HMCMAG/HMCMAG_Async.c  -o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1219465957/HMCMAG_Async.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1219465957/HMCMAG_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1219465957/HMCMAG_Init.o: ../00-Modules/HMCMAG/HMCMAG_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1219465957 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/HMCMAG/HMCMAG_Init.c  -o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1219465957/HMCMAG_Init.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1219465957/HMCMAG_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1219465957/HMCMAG_Local.o: ../00-Modules/HMCMAG/HMCMAG_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1219465957 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/HMCMAG/HMCMAG_Local.c  -o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1219465957/HMCMAG_Local.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1219465957/HMCMAG_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1219465957/HMCMAG_Mgmt.o: ../00-Modules/HMCMAG/HMCMAG_Mgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1219465957 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Mgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Mgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/HMCMAG/HMCMAG_Mgmt.c  -o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Mgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1219465957/HMCMAG_Mgmt.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1219465957/HMCMAG_Mgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1219465957/HMCMAG_Sync.o: ../00-Modules/HMCMAG/HMCMAG_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1219465957 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/HMCMAG/HMCMAG_Sync.c  -o ${OBJECTDIR}/_ext/1219465957/HMCMAG_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1219465957/HMCMAG_Sync.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1219465957/HMCMAG_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1219465957/HMCMAG_ISR.o: ../00-Modules/HMCMAG/HMCMAG_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1219465957 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219465957/HMCMAG_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/HMCMAG/HMCMAG_ISR.c  -o ${OBJECTDIR}/_ext/1219465957/HMCMAG_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1219465957/HMCMAG_ISR.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1219465957/HMCMAG_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261195156/I2C_Async.o: ../00-Modules/I2C/I2C_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261195156 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/I2C/I2C_Async.c  -o ${OBJECTDIR}/_ext/261195156/I2C_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261195156/I2C_Async.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261195156/I2C_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261195156/I2C_Init.o: ../00-Modules/I2C/I2C_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261195156 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/I2C/I2C_Init.c  -o ${OBJECTDIR}/_ext/261195156/I2C_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261195156/I2C_Init.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261195156/I2C_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261195156/I2C_ISR.o: ../00-Modules/I2C/I2C_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261195156 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/I2C/I2C_ISR.c  -o ${OBJECTDIR}/_ext/261195156/I2C_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261195156/I2C_ISR.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261195156/I2C_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261195156/I2C_Local.o: ../00-Modules/I2C/I2C_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261195156 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/I2C/I2C_Local.c  -o ${OBJECTDIR}/_ext/261195156/I2C_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261195156/I2C_Local.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261195156/I2C_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261195156/I2C_Sync.o: ../00-Modules/I2C/I2C_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261195156 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/I2C/I2C_Sync.c  -o ${OBJECTDIR}/_ext/261195156/I2C_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261195156/I2C_Sync.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261195156/I2C_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261195156/I2C_SyncRead.o: ../00-Modules/I2C/I2C_SyncRead.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261195156 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_SyncRead.o.d 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_SyncRead.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/I2C/I2C_SyncRead.c  -o ${OBJECTDIR}/_ext/261195156/I2C_SyncRead.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261195156/I2C_SyncRead.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261195156/I2C_SyncRead.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261195156/I2C_SyncWrite.o: ../00-Modules/I2C/I2C_SyncWrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261195156 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_SyncWrite.o.d 
	@${RM} ${OBJECTDIR}/_ext/261195156/I2C_SyncWrite.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/I2C/I2C_SyncWrite.c  -o ${OBJECTDIR}/_ext/261195156/I2C_SyncWrite.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261195156/I2C_SyncWrite.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261195156/I2C_SyncWrite.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/492825802/Init.o: ../00-Modules/Init/Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/492825802 
	@${RM} ${OBJECTDIR}/_ext/492825802/Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/492825802/Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/Init/Init.c  -o ${OBJECTDIR}/_ext/492825802/Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/492825802/Init.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/492825802/Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261206579/TMR.o: ../00-Modules/TMR/TMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261206579 
	@${RM} ${OBJECTDIR}/_ext/261206579/TMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/261206579/TMR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/TMR/TMR.c  -o ${OBJECTDIR}/_ext/261206579/TMR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261206579/TMR.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261206579/TMR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261206579/TMRInit.o: ../00-Modules/TMR/TMRInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261206579 
	@${RM} ${OBJECTDIR}/_ext/261206579/TMRInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/261206579/TMRInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/TMR/TMRInit.c  -o ${OBJECTDIR}/_ext/261206579/TMRInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261206579/TMRInit.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261206579/TMRInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261206579/TMRLocal.o: ../00-Modules/TMR/TMRLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261206579 
	@${RM} ${OBJECTDIR}/_ext/261206579/TMRLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/261206579/TMRLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/TMR/TMRLocal.c  -o ${OBJECTDIR}/_ext/261206579/TMRLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261206579/TMRLocal.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261206579/TMRLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/261206579/TMR_ISR.o: ../00-Modules/TMR/TMR_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/261206579 
	@${RM} ${OBJECTDIR}/_ext/261206579/TMR_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/261206579/TMR_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/TMR/TMR_ISR.c  -o ${OBJECTDIR}/_ext/261206579/TMR_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/261206579/TMR_ISR.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/261206579/TMR_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/492512300/UART_TX_API.o: ../00-Modules/UART/UART_TX_API.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/492512300 
	@${RM} ${OBJECTDIR}/_ext/492512300/UART_TX_API.o.d 
	@${RM} ${OBJECTDIR}/_ext/492512300/UART_TX_API.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/UART/UART_TX_API.c  -o ${OBJECTDIR}/_ext/492512300/UART_TX_API.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/492512300/UART_TX_API.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/492512300/UART_TX_API.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/492512300/UART_TX_Init.o: ../00-Modules/UART/UART_TX_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/492512300 
	@${RM} ${OBJECTDIR}/_ext/492512300/UART_TX_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/492512300/UART_TX_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/UART/UART_TX_Init.c  -o ${OBJECTDIR}/_ext/492512300/UART_TX_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/492512300/UART_TX_Init.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/492512300/UART_TX_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/492512300/UART_TX_ISR.o: ../00-Modules/UART/UART_TX_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/492512300 
	@${RM} ${OBJECTDIR}/_ext/492512300/UART_TX_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/492512300/UART_TX_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/UART/UART_TX_ISR.c  -o ${OBJECTDIR}/_ext/492512300/UART_TX_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/492512300/UART_TX_ISR.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/492512300/UART_TX_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/492512300/UART_TX_Local.o: ../00-Modules/UART/UART_TX_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/492512300 
	@${RM} ${OBJECTDIR}/_ext/492512300/UART_TX_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/492512300/UART_TX_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-Modules/UART/UART_TX_Local.c  -o ${OBJECTDIR}/_ext/492512300/UART_TX_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/492512300/UART_TX_Local.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/492512300/UART_TX_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -O0 -I"../00-Modules" -msmart-io=1 -Wall -msfr-warn=off
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
dist/${CND_CONF}/${IMAGE_TYPE}/43-MAG_Test.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/43-MAG_Test.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/43-MAG_Test.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/43-MAG_Test.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -D__PIC24H__ -D__MAG_Use__ -fast-math -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/43-MAG_Test.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
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
