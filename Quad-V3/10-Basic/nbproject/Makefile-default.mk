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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/10-Basic.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/10-Basic.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../00-COMMON/BLI/BLI.c ../00-COMMON/BLI/BLIInit.c ../00-COMMON/BLI/BLILocal.c ../00-COMMON/BLI/BLIMorse.c ../00-COMMON/Init/Init.c ../00-COMMON/TMR/TMR.c ../00-COMMON/TMR/TMRInit.c ../00-COMMON/TMR/TMRLocal.c ../00-COMMON/TMR/TMR_ISR.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/554684679/BLI.o ${OBJECTDIR}/_ext/554684679/BLIInit.o ${OBJECTDIR}/_ext/554684679/BLILocal.o ${OBJECTDIR}/_ext/554684679/BLIMorse.o ${OBJECTDIR}/_ext/15113546/Init.o ${OBJECTDIR}/_ext/554667341/TMR.o ${OBJECTDIR}/_ext/554667341/TMRInit.o ${OBJECTDIR}/_ext/554667341/TMRLocal.o ${OBJECTDIR}/_ext/554667341/TMR_ISR.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/554684679/BLI.o.d ${OBJECTDIR}/_ext/554684679/BLIInit.o.d ${OBJECTDIR}/_ext/554684679/BLILocal.o.d ${OBJECTDIR}/_ext/554684679/BLIMorse.o.d ${OBJECTDIR}/_ext/15113546/Init.o.d ${OBJECTDIR}/_ext/554667341/TMR.o.d ${OBJECTDIR}/_ext/554667341/TMRInit.o.d ${OBJECTDIR}/_ext/554667341/TMRLocal.o.d ${OBJECTDIR}/_ext/554667341/TMR_ISR.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/554684679/BLI.o ${OBJECTDIR}/_ext/554684679/BLIInit.o ${OBJECTDIR}/_ext/554684679/BLILocal.o ${OBJECTDIR}/_ext/554684679/BLIMorse.o ${OBJECTDIR}/_ext/15113546/Init.o ${OBJECTDIR}/_ext/554667341/TMR.o ${OBJECTDIR}/_ext/554667341/TMRInit.o ${OBJECTDIR}/_ext/554667341/TMRLocal.o ${OBJECTDIR}/_ext/554667341/TMR_ISR.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=../00-COMMON/BLI/BLI.c ../00-COMMON/BLI/BLIInit.c ../00-COMMON/BLI/BLILocal.c ../00-COMMON/BLI/BLIMorse.c ../00-COMMON/Init/Init.c ../00-COMMON/TMR/TMR.c ../00-COMMON/TMR/TMRInit.c ../00-COMMON/TMR/TMRLocal.c ../00-COMMON/TMR/TMR_ISR.c main.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/10-Basic.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24EP512GP806
MP_LINKER_FILE_OPTION=,--script=p24EP512GP806.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/554684679/BLI.o: ../00-COMMON/BLI/BLI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554684679 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLI.o.d 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/BLI/BLI.c  -o ${OBJECTDIR}/_ext/554684679/BLI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554684679/BLI.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554684679/BLI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554684679/BLIInit.o: ../00-COMMON/BLI/BLIInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554684679 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLIInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLIInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/BLI/BLIInit.c  -o ${OBJECTDIR}/_ext/554684679/BLIInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554684679/BLIInit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554684679/BLIInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554684679/BLILocal.o: ../00-COMMON/BLI/BLILocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554684679 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLILocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLILocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/BLI/BLILocal.c  -o ${OBJECTDIR}/_ext/554684679/BLILocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554684679/BLILocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554684679/BLILocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554684679/BLIMorse.o: ../00-COMMON/BLI/BLIMorse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554684679 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLIMorse.o.d 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLIMorse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/BLI/BLIMorse.c  -o ${OBJECTDIR}/_ext/554684679/BLIMorse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554684679/BLIMorse.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554684679/BLIMorse.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/15113546/Init.o: ../00-COMMON/Init/Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/15113546 
	@${RM} ${OBJECTDIR}/_ext/15113546/Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/15113546/Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/Init/Init.c  -o ${OBJECTDIR}/_ext/15113546/Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/15113546/Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/15113546/Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554667341/TMR.o: ../00-COMMON/TMR/TMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554667341 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/TMR/TMR.c  -o ${OBJECTDIR}/_ext/554667341/TMR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554667341/TMR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554667341/TMR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554667341/TMRInit.o: ../00-COMMON/TMR/TMRInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554667341 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMRInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMRInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/TMR/TMRInit.c  -o ${OBJECTDIR}/_ext/554667341/TMRInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554667341/TMRInit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554667341/TMRInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554667341/TMRLocal.o: ../00-COMMON/TMR/TMRLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554667341 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMRLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMRLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/TMR/TMRLocal.c  -o ${OBJECTDIR}/_ext/554667341/TMRLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554667341/TMRLocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554667341/TMRLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554667341/TMR_ISR.o: ../00-COMMON/TMR/TMR_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554667341 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMR_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMR_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/TMR/TMR_ISR.c  -o ${OBJECTDIR}/_ext/554667341/TMR_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554667341/TMR_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554667341/TMR_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/554684679/BLI.o: ../00-COMMON/BLI/BLI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554684679 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLI.o.d 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/BLI/BLI.c  -o ${OBJECTDIR}/_ext/554684679/BLI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554684679/BLI.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554684679/BLI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554684679/BLIInit.o: ../00-COMMON/BLI/BLIInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554684679 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLIInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLIInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/BLI/BLIInit.c  -o ${OBJECTDIR}/_ext/554684679/BLIInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554684679/BLIInit.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554684679/BLIInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554684679/BLILocal.o: ../00-COMMON/BLI/BLILocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554684679 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLILocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLILocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/BLI/BLILocal.c  -o ${OBJECTDIR}/_ext/554684679/BLILocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554684679/BLILocal.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554684679/BLILocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554684679/BLIMorse.o: ../00-COMMON/BLI/BLIMorse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554684679 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLIMorse.o.d 
	@${RM} ${OBJECTDIR}/_ext/554684679/BLIMorse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/BLI/BLIMorse.c  -o ${OBJECTDIR}/_ext/554684679/BLIMorse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554684679/BLIMorse.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554684679/BLIMorse.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/15113546/Init.o: ../00-COMMON/Init/Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/15113546 
	@${RM} ${OBJECTDIR}/_ext/15113546/Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/15113546/Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/Init/Init.c  -o ${OBJECTDIR}/_ext/15113546/Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/15113546/Init.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/15113546/Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554667341/TMR.o: ../00-COMMON/TMR/TMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554667341 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/TMR/TMR.c  -o ${OBJECTDIR}/_ext/554667341/TMR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554667341/TMR.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554667341/TMR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554667341/TMRInit.o: ../00-COMMON/TMR/TMRInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554667341 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMRInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMRInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/TMR/TMRInit.c  -o ${OBJECTDIR}/_ext/554667341/TMRInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554667341/TMRInit.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554667341/TMRInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554667341/TMRLocal.o: ../00-COMMON/TMR/TMRLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554667341 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMRLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMRLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/TMR/TMRLocal.c  -o ${OBJECTDIR}/_ext/554667341/TMRLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554667341/TMRLocal.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554667341/TMRLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/554667341/TMR_ISR.o: ../00-COMMON/TMR/TMR_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/554667341 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMR_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/554667341/TMR_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../00-COMMON/TMR/TMR_ISR.c  -o ${OBJECTDIR}/_ext/554667341/TMR_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/554667341/TMR_ISR.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/554667341/TMR_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"../00-Common" -msmart-io=1 -Wall -msfr-warn=off
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
dist/${CND_CONF}/${IMAGE_TYPE}/10-Basic.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/10-Basic.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/10-Basic.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/10-Basic.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/10-Basic.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
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
