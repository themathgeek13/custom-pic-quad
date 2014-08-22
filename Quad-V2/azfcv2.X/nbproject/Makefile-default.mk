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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/azfcv2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/azfcv2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=/Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADC.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCInit.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCLocal.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/Altimeter/Altimeter.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLI.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLIInit.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLILocal.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLIMorse.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DBG/DBG.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCM.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMBaseVectors.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMConstructors.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMLocal.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMMethods.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Async.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Init.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_ISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_ISR_INT2.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Local.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Mgmt.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Sync.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Async.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Init.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_ISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Local.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Sync.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_SyncRead.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_SyncWrite.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/IMU/IMU.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/IMU/IMUReset.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/Init/Init.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCM.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCMInit.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCMLocal.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Async.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Init.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_ISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Local.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Mgmt.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Sync.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Async.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Init.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_ISR_INT1.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Local.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Mgmt.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Reset.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Sync.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXB.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXB_ISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXBInit.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXBLocal.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMBatteryMgmt.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMConst.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMNormalize.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMPerformStep.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RC.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RC_ISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCInit.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCLocal.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCSym.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_Init.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_ISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_Local.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMR_ISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMRInit.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMRLocal.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_API.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_Init.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_ISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_Local.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/91-QCM_Altimetry/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1334973169/ADC.o ${OBJECTDIR}/_ext/1334973169/ADCInit.o ${OBJECTDIR}/_ext/1334973169/ADCISR.o ${OBJECTDIR}/_ext/1334973169/ADCLocal.o ${OBJECTDIR}/_ext/1034061016/Altimeter.o ${OBJECTDIR}/_ext/1334971954/BLI.o ${OBJECTDIR}/_ext/1334971954/BLIInit.o ${OBJECTDIR}/_ext/1334971954/BLILocal.o ${OBJECTDIR}/_ext/1334971954/BLIMorse.o ${OBJECTDIR}/_ext/1334970344/DBG.o ${OBJECTDIR}/_ext/1334970307/DCM.o ${OBJECTDIR}/_ext/1334970307/DCMBaseVectors.o ${OBJECTDIR}/_ext/1334970307/DCMConstructors.o ${OBJECTDIR}/_ext/1334970307/DCMLocal.o ${OBJECTDIR}/_ext/1334970307/DCMMethods.o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Async.o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Init.o ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR.o ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR_INT2.o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Local.o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Mgmt.o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Sync.o ${OBJECTDIR}/_ext/1334966039/I2C_Async.o ${OBJECTDIR}/_ext/1334966039/I2C_Init.o ${OBJECTDIR}/_ext/1334966039/I2C_ISR.o ${OBJECTDIR}/_ext/1334966039/I2C_Local.o ${OBJECTDIR}/_ext/1334966039/I2C_Sync.o ${OBJECTDIR}/_ext/1334966039/I2C_SyncRead.o ${OBJECTDIR}/_ext/1334966039/I2C_SyncWrite.o ${OBJECTDIR}/_ext/1334965184/IMU.o ${OBJECTDIR}/_ext/1334965184/IMUReset.o ${OBJECTDIR}/_ext/1565784705/Init.o ${OBJECTDIR}/_ext/1334961658/MCM.o ${OBJECTDIR}/_ext/1334961658/MCMInit.o ${OBJECTDIR}/_ext/1334961658/MCMLocal.o ${OBJECTDIR}/_ext/1314815130/MPL3115_Async.o ${OBJECTDIR}/_ext/1314815130/MPL3115_Init.o ${OBJECTDIR}/_ext/1314815130/MPL3115_ISR.o ${OBJECTDIR}/_ext/1314815130/MPL3115_Local.o ${OBJECTDIR}/_ext/1314815130/MPL3115_Mgmt.o ${OBJECTDIR}/_ext/1314815130/MPL3115_Sync.o ${OBJECTDIR}/_ext/1323215350/MPU6050_Async.o ${OBJECTDIR}/_ext/1323215350/MPU6050_Init.o ${OBJECTDIR}/_ext/1323215350/MPU6050_ISR_INT1.o ${OBJECTDIR}/_ext/1323215350/MPU6050_Local.o ${OBJECTDIR}/_ext/1323215350/MPU6050_Mgmt.o ${OBJECTDIR}/_ext/1323215350/MPU6050_Reset.o ${OBJECTDIR}/_ext/1323215350/MPU6050_Sync.o ${OBJECTDIR}/_ext/1334961018/MXB.o ${OBJECTDIR}/_ext/1334961018/MXB_ISR.o ${OBJECTDIR}/_ext/1334961018/MXBInit.o ${OBJECTDIR}/_ext/1334961018/MXBLocal.o ${OBJECTDIR}/_ext/1334957814/QCMBatteryMgmt.o ${OBJECTDIR}/_ext/1334957814/QCMConst.o ${OBJECTDIR}/_ext/1334957814/QCMNormalize.o ${OBJECTDIR}/_ext/1334957814/QCMPerformStep.o ${OBJECTDIR}/_ext/788220866/RC.o ${OBJECTDIR}/_ext/788220866/RC_ISR.o ${OBJECTDIR}/_ext/788220866/RCInit.o ${OBJECTDIR}/_ext/788220866/RCLocal.o ${OBJECTDIR}/_ext/788220866/RCSym.o ${OBJECTDIR}/_ext/1566053876/SR04.o ${OBJECTDIR}/_ext/1566053876/SR04_Init.o ${OBJECTDIR}/_ext/1566053876/SR04_ISR.o ${OBJECTDIR}/_ext/1566053876/SR04_Local.o ${OBJECTDIR}/_ext/1334954616/TMR.o ${OBJECTDIR}/_ext/1334954616/TMR_ISR.o ${OBJECTDIR}/_ext/1334954616/TMRInit.o ${OBJECTDIR}/_ext/1334954616/TMRLocal.o ${OBJECTDIR}/_ext/1566098207/UART_TX_API.o ${OBJECTDIR}/_ext/1566098207/UART_TX_Init.o ${OBJECTDIR}/_ext/1566098207/UART_TX_ISR.o ${OBJECTDIR}/_ext/1566098207/UART_TX_Local.o ${OBJECTDIR}/_ext/659535598/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1334973169/ADC.o.d ${OBJECTDIR}/_ext/1334973169/ADCInit.o.d ${OBJECTDIR}/_ext/1334973169/ADCISR.o.d ${OBJECTDIR}/_ext/1334973169/ADCLocal.o.d ${OBJECTDIR}/_ext/1034061016/Altimeter.o.d ${OBJECTDIR}/_ext/1334971954/BLI.o.d ${OBJECTDIR}/_ext/1334971954/BLIInit.o.d ${OBJECTDIR}/_ext/1334971954/BLILocal.o.d ${OBJECTDIR}/_ext/1334971954/BLIMorse.o.d ${OBJECTDIR}/_ext/1334970344/DBG.o.d ${OBJECTDIR}/_ext/1334970307/DCM.o.d ${OBJECTDIR}/_ext/1334970307/DCMBaseVectors.o.d ${OBJECTDIR}/_ext/1334970307/DCMConstructors.o.d ${OBJECTDIR}/_ext/1334970307/DCMLocal.o.d ${OBJECTDIR}/_ext/1334970307/DCMMethods.o.d ${OBJECTDIR}/_ext/1420275110/HMCMAG_Async.o.d ${OBJECTDIR}/_ext/1420275110/HMCMAG_Init.o.d ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR.o.d ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR_INT2.o.d ${OBJECTDIR}/_ext/1420275110/HMCMAG_Local.o.d ${OBJECTDIR}/_ext/1420275110/HMCMAG_Mgmt.o.d ${OBJECTDIR}/_ext/1420275110/HMCMAG_Sync.o.d ${OBJECTDIR}/_ext/1334966039/I2C_Async.o.d ${OBJECTDIR}/_ext/1334966039/I2C_Init.o.d ${OBJECTDIR}/_ext/1334966039/I2C_ISR.o.d ${OBJECTDIR}/_ext/1334966039/I2C_Local.o.d ${OBJECTDIR}/_ext/1334966039/I2C_Sync.o.d ${OBJECTDIR}/_ext/1334966039/I2C_SyncRead.o.d ${OBJECTDIR}/_ext/1334966039/I2C_SyncWrite.o.d ${OBJECTDIR}/_ext/1334965184/IMU.o.d ${OBJECTDIR}/_ext/1334965184/IMUReset.o.d ${OBJECTDIR}/_ext/1565784705/Init.o.d ${OBJECTDIR}/_ext/1334961658/MCM.o.d ${OBJECTDIR}/_ext/1334961658/MCMInit.o.d ${OBJECTDIR}/_ext/1334961658/MCMLocal.o.d ${OBJECTDIR}/_ext/1314815130/MPL3115_Async.o.d ${OBJECTDIR}/_ext/1314815130/MPL3115_Init.o.d ${OBJECTDIR}/_ext/1314815130/MPL3115_ISR.o.d ${OBJECTDIR}/_ext/1314815130/MPL3115_Local.o.d ${OBJECTDIR}/_ext/1314815130/MPL3115_Mgmt.o.d ${OBJECTDIR}/_ext/1314815130/MPL3115_Sync.o.d ${OBJECTDIR}/_ext/1323215350/MPU6050_Async.o.d ${OBJECTDIR}/_ext/1323215350/MPU6050_Init.o.d ${OBJECTDIR}/_ext/1323215350/MPU6050_ISR_INT1.o.d ${OBJECTDIR}/_ext/1323215350/MPU6050_Local.o.d ${OBJECTDIR}/_ext/1323215350/MPU6050_Mgmt.o.d ${OBJECTDIR}/_ext/1323215350/MPU6050_Reset.o.d ${OBJECTDIR}/_ext/1323215350/MPU6050_Sync.o.d ${OBJECTDIR}/_ext/1334961018/MXB.o.d ${OBJECTDIR}/_ext/1334961018/MXB_ISR.o.d ${OBJECTDIR}/_ext/1334961018/MXBInit.o.d ${OBJECTDIR}/_ext/1334961018/MXBLocal.o.d ${OBJECTDIR}/_ext/1334957814/QCMBatteryMgmt.o.d ${OBJECTDIR}/_ext/1334957814/QCMConst.o.d ${OBJECTDIR}/_ext/1334957814/QCMNormalize.o.d ${OBJECTDIR}/_ext/1334957814/QCMPerformStep.o.d ${OBJECTDIR}/_ext/788220866/RC.o.d ${OBJECTDIR}/_ext/788220866/RC_ISR.o.d ${OBJECTDIR}/_ext/788220866/RCInit.o.d ${OBJECTDIR}/_ext/788220866/RCLocal.o.d ${OBJECTDIR}/_ext/788220866/RCSym.o.d ${OBJECTDIR}/_ext/1566053876/SR04.o.d ${OBJECTDIR}/_ext/1566053876/SR04_Init.o.d ${OBJECTDIR}/_ext/1566053876/SR04_ISR.o.d ${OBJECTDIR}/_ext/1566053876/SR04_Local.o.d ${OBJECTDIR}/_ext/1334954616/TMR.o.d ${OBJECTDIR}/_ext/1334954616/TMR_ISR.o.d ${OBJECTDIR}/_ext/1334954616/TMRInit.o.d ${OBJECTDIR}/_ext/1334954616/TMRLocal.o.d ${OBJECTDIR}/_ext/1566098207/UART_TX_API.o.d ${OBJECTDIR}/_ext/1566098207/UART_TX_Init.o.d ${OBJECTDIR}/_ext/1566098207/UART_TX_ISR.o.d ${OBJECTDIR}/_ext/1566098207/UART_TX_Local.o.d ${OBJECTDIR}/_ext/659535598/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1334973169/ADC.o ${OBJECTDIR}/_ext/1334973169/ADCInit.o ${OBJECTDIR}/_ext/1334973169/ADCISR.o ${OBJECTDIR}/_ext/1334973169/ADCLocal.o ${OBJECTDIR}/_ext/1034061016/Altimeter.o ${OBJECTDIR}/_ext/1334971954/BLI.o ${OBJECTDIR}/_ext/1334971954/BLIInit.o ${OBJECTDIR}/_ext/1334971954/BLILocal.o ${OBJECTDIR}/_ext/1334971954/BLIMorse.o ${OBJECTDIR}/_ext/1334970344/DBG.o ${OBJECTDIR}/_ext/1334970307/DCM.o ${OBJECTDIR}/_ext/1334970307/DCMBaseVectors.o ${OBJECTDIR}/_ext/1334970307/DCMConstructors.o ${OBJECTDIR}/_ext/1334970307/DCMLocal.o ${OBJECTDIR}/_ext/1334970307/DCMMethods.o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Async.o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Init.o ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR.o ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR_INT2.o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Local.o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Mgmt.o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Sync.o ${OBJECTDIR}/_ext/1334966039/I2C_Async.o ${OBJECTDIR}/_ext/1334966039/I2C_Init.o ${OBJECTDIR}/_ext/1334966039/I2C_ISR.o ${OBJECTDIR}/_ext/1334966039/I2C_Local.o ${OBJECTDIR}/_ext/1334966039/I2C_Sync.o ${OBJECTDIR}/_ext/1334966039/I2C_SyncRead.o ${OBJECTDIR}/_ext/1334966039/I2C_SyncWrite.o ${OBJECTDIR}/_ext/1334965184/IMU.o ${OBJECTDIR}/_ext/1334965184/IMUReset.o ${OBJECTDIR}/_ext/1565784705/Init.o ${OBJECTDIR}/_ext/1334961658/MCM.o ${OBJECTDIR}/_ext/1334961658/MCMInit.o ${OBJECTDIR}/_ext/1334961658/MCMLocal.o ${OBJECTDIR}/_ext/1314815130/MPL3115_Async.o ${OBJECTDIR}/_ext/1314815130/MPL3115_Init.o ${OBJECTDIR}/_ext/1314815130/MPL3115_ISR.o ${OBJECTDIR}/_ext/1314815130/MPL3115_Local.o ${OBJECTDIR}/_ext/1314815130/MPL3115_Mgmt.o ${OBJECTDIR}/_ext/1314815130/MPL3115_Sync.o ${OBJECTDIR}/_ext/1323215350/MPU6050_Async.o ${OBJECTDIR}/_ext/1323215350/MPU6050_Init.o ${OBJECTDIR}/_ext/1323215350/MPU6050_ISR_INT1.o ${OBJECTDIR}/_ext/1323215350/MPU6050_Local.o ${OBJECTDIR}/_ext/1323215350/MPU6050_Mgmt.o ${OBJECTDIR}/_ext/1323215350/MPU6050_Reset.o ${OBJECTDIR}/_ext/1323215350/MPU6050_Sync.o ${OBJECTDIR}/_ext/1334961018/MXB.o ${OBJECTDIR}/_ext/1334961018/MXB_ISR.o ${OBJECTDIR}/_ext/1334961018/MXBInit.o ${OBJECTDIR}/_ext/1334961018/MXBLocal.o ${OBJECTDIR}/_ext/1334957814/QCMBatteryMgmt.o ${OBJECTDIR}/_ext/1334957814/QCMConst.o ${OBJECTDIR}/_ext/1334957814/QCMNormalize.o ${OBJECTDIR}/_ext/1334957814/QCMPerformStep.o ${OBJECTDIR}/_ext/788220866/RC.o ${OBJECTDIR}/_ext/788220866/RC_ISR.o ${OBJECTDIR}/_ext/788220866/RCInit.o ${OBJECTDIR}/_ext/788220866/RCLocal.o ${OBJECTDIR}/_ext/788220866/RCSym.o ${OBJECTDIR}/_ext/1566053876/SR04.o ${OBJECTDIR}/_ext/1566053876/SR04_Init.o ${OBJECTDIR}/_ext/1566053876/SR04_ISR.o ${OBJECTDIR}/_ext/1566053876/SR04_Local.o ${OBJECTDIR}/_ext/1334954616/TMR.o ${OBJECTDIR}/_ext/1334954616/TMR_ISR.o ${OBJECTDIR}/_ext/1334954616/TMRInit.o ${OBJECTDIR}/_ext/1334954616/TMRLocal.o ${OBJECTDIR}/_ext/1566098207/UART_TX_API.o ${OBJECTDIR}/_ext/1566098207/UART_TX_Init.o ${OBJECTDIR}/_ext/1566098207/UART_TX_ISR.o ${OBJECTDIR}/_ext/1566098207/UART_TX_Local.o ${OBJECTDIR}/_ext/659535598/main.o

# Source Files
SOURCEFILES=/Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADC.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCInit.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCLocal.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/Altimeter/Altimeter.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLI.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLIInit.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLILocal.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLIMorse.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DBG/DBG.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCM.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMBaseVectors.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMConstructors.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMLocal.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMMethods.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Async.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Init.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_ISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_ISR_INT2.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Local.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Mgmt.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Sync.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Async.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Init.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_ISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Local.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Sync.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_SyncRead.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_SyncWrite.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/IMU/IMU.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/IMU/IMUReset.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/Init/Init.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCM.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCMInit.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCMLocal.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Async.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Init.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_ISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Local.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Mgmt.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Sync.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Async.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Init.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_ISR_INT1.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Local.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Mgmt.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Reset.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Sync.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXB.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXB_ISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXBInit.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXBLocal.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMBatteryMgmt.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMConst.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMNormalize.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMPerformStep.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RC.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RC_ISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCInit.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCLocal.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCSym.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_Init.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_ISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_Local.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMR_ISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMRInit.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMRLocal.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_API.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_Init.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_ISR.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_Local.c /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/91-QCM_Altimetry/main.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/azfcv2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24HJ128GP204
MP_LINKER_FILE_OPTION=,--script=p24HJ128GP204.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1334973169/ADC.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334973169 
	@${RM} ${OBJECTDIR}/_ext/1334973169/ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334973169/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADC.c  -o ${OBJECTDIR}/_ext/1334973169/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334973169/ADC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334973169/ADC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334973169/ADCInit.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334973169 
	@${RM} ${OBJECTDIR}/_ext/1334973169/ADCInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334973169/ADCInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCInit.c  -o ${OBJECTDIR}/_ext/1334973169/ADCInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334973169/ADCInit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334973169/ADCInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334973169/ADCISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334973169 
	@${RM} ${OBJECTDIR}/_ext/1334973169/ADCISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334973169/ADCISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCISR.c  -o ${OBJECTDIR}/_ext/1334973169/ADCISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334973169/ADCISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334973169/ADCISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334973169/ADCLocal.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334973169 
	@${RM} ${OBJECTDIR}/_ext/1334973169/ADCLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334973169/ADCLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCLocal.c  -o ${OBJECTDIR}/_ext/1334973169/ADCLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334973169/ADCLocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334973169/ADCLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1034061016/Altimeter.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/Altimeter/Altimeter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1034061016 
	@${RM} ${OBJECTDIR}/_ext/1034061016/Altimeter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1034061016/Altimeter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/Altimeter/Altimeter.c  -o ${OBJECTDIR}/_ext/1034061016/Altimeter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1034061016/Altimeter.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1034061016/Altimeter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334971954/BLI.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334971954 
	@${RM} ${OBJECTDIR}/_ext/1334971954/BLI.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334971954/BLI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLI.c  -o ${OBJECTDIR}/_ext/1334971954/BLI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334971954/BLI.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334971954/BLI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334971954/BLIInit.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLIInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334971954 
	@${RM} ${OBJECTDIR}/_ext/1334971954/BLIInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334971954/BLIInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLIInit.c  -o ${OBJECTDIR}/_ext/1334971954/BLIInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334971954/BLIInit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334971954/BLIInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334971954/BLILocal.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLILocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334971954 
	@${RM} ${OBJECTDIR}/_ext/1334971954/BLILocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334971954/BLILocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLILocal.c  -o ${OBJECTDIR}/_ext/1334971954/BLILocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334971954/BLILocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334971954/BLILocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334971954/BLIMorse.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLIMorse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334971954 
	@${RM} ${OBJECTDIR}/_ext/1334971954/BLIMorse.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334971954/BLIMorse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLIMorse.c  -o ${OBJECTDIR}/_ext/1334971954/BLIMorse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334971954/BLIMorse.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334971954/BLIMorse.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334970344/DBG.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DBG/DBG.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334970344 
	@${RM} ${OBJECTDIR}/_ext/1334970344/DBG.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334970344/DBG.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DBG/DBG.c  -o ${OBJECTDIR}/_ext/1334970344/DBG.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334970344/DBG.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334970344/DBG.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334970307/DCM.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334970307 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCM.c  -o ${OBJECTDIR}/_ext/1334970307/DCM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334970307/DCM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334970307/DCM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334970307/DCMBaseVectors.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMBaseVectors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334970307 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCMBaseVectors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCMBaseVectors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMBaseVectors.c  -o ${OBJECTDIR}/_ext/1334970307/DCMBaseVectors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334970307/DCMBaseVectors.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334970307/DCMBaseVectors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334970307/DCMConstructors.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMConstructors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334970307 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCMConstructors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCMConstructors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMConstructors.c  -o ${OBJECTDIR}/_ext/1334970307/DCMConstructors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334970307/DCMConstructors.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334970307/DCMConstructors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334970307/DCMLocal.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334970307 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCMLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCMLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMLocal.c  -o ${OBJECTDIR}/_ext/1334970307/DCMLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334970307/DCMLocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334970307/DCMLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334970307/DCMMethods.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMMethods.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334970307 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCMMethods.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCMMethods.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMMethods.c  -o ${OBJECTDIR}/_ext/1334970307/DCMMethods.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334970307/DCMMethods.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334970307/DCMMethods.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1420275110/HMCMAG_Async.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1420275110 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Async.c  -o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1420275110/HMCMAG_Async.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1420275110/HMCMAG_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1420275110/HMCMAG_Init.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1420275110 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Init.c  -o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1420275110/HMCMAG_Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1420275110/HMCMAG_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1420275110 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_ISR.c  -o ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR_INT2.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_ISR_INT2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1420275110 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR_INT2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR_INT2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_ISR_INT2.c  -o ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR_INT2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR_INT2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR_INT2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1420275110/HMCMAG_Local.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1420275110 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Local.c  -o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1420275110/HMCMAG_Local.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1420275110/HMCMAG_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1420275110/HMCMAG_Mgmt.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Mgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1420275110 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Mgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Mgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Mgmt.c  -o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Mgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1420275110/HMCMAG_Mgmt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1420275110/HMCMAG_Mgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1420275110/HMCMAG_Sync.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1420275110 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Sync.c  -o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1420275110/HMCMAG_Sync.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1420275110/HMCMAG_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334966039/I2C_Async.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334966039 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Async.c  -o ${OBJECTDIR}/_ext/1334966039/I2C_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334966039/I2C_Async.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334966039/I2C_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334966039/I2C_Init.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334966039 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Init.c  -o ${OBJECTDIR}/_ext/1334966039/I2C_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334966039/I2C_Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334966039/I2C_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334966039/I2C_ISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334966039 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_ISR.c  -o ${OBJECTDIR}/_ext/1334966039/I2C_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334966039/I2C_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334966039/I2C_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334966039/I2C_Local.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334966039 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Local.c  -o ${OBJECTDIR}/_ext/1334966039/I2C_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334966039/I2C_Local.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334966039/I2C_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334966039/I2C_Sync.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334966039 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Sync.c  -o ${OBJECTDIR}/_ext/1334966039/I2C_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334966039/I2C_Sync.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334966039/I2C_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334966039/I2C_SyncRead.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_SyncRead.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334966039 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_SyncRead.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_SyncRead.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_SyncRead.c  -o ${OBJECTDIR}/_ext/1334966039/I2C_SyncRead.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334966039/I2C_SyncRead.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334966039/I2C_SyncRead.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334966039/I2C_SyncWrite.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_SyncWrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334966039 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_SyncWrite.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_SyncWrite.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_SyncWrite.c  -o ${OBJECTDIR}/_ext/1334966039/I2C_SyncWrite.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334966039/I2C_SyncWrite.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334966039/I2C_SyncWrite.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334965184/IMU.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/IMU/IMU.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334965184 
	@${RM} ${OBJECTDIR}/_ext/1334965184/IMU.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334965184/IMU.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/IMU/IMU.c  -o ${OBJECTDIR}/_ext/1334965184/IMU.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334965184/IMU.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334965184/IMU.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334965184/IMUReset.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/IMU/IMUReset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334965184 
	@${RM} ${OBJECTDIR}/_ext/1334965184/IMUReset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334965184/IMUReset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/IMU/IMUReset.c  -o ${OBJECTDIR}/_ext/1334965184/IMUReset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334965184/IMUReset.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334965184/IMUReset.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1565784705/Init.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/Init/Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1565784705 
	@${RM} ${OBJECTDIR}/_ext/1565784705/Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1565784705/Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/Init/Init.c  -o ${OBJECTDIR}/_ext/1565784705/Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1565784705/Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1565784705/Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334961658/MCM.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334961658 
	@${RM} ${OBJECTDIR}/_ext/1334961658/MCM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334961658/MCM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCM.c  -o ${OBJECTDIR}/_ext/1334961658/MCM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334961658/MCM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334961658/MCM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334961658/MCMInit.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCMInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334961658 
	@${RM} ${OBJECTDIR}/_ext/1334961658/MCMInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334961658/MCMInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCMInit.c  -o ${OBJECTDIR}/_ext/1334961658/MCMInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334961658/MCMInit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334961658/MCMInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334961658/MCMLocal.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCMLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334961658 
	@${RM} ${OBJECTDIR}/_ext/1334961658/MCMLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334961658/MCMLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCMLocal.c  -o ${OBJECTDIR}/_ext/1334961658/MCMLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334961658/MCMLocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334961658/MCMLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1314815130/MPL3115_Async.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1314815130 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Async.c  -o ${OBJECTDIR}/_ext/1314815130/MPL3115_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1314815130/MPL3115_Async.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314815130/MPL3115_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1314815130/MPL3115_Init.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1314815130 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Init.c  -o ${OBJECTDIR}/_ext/1314815130/MPL3115_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1314815130/MPL3115_Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314815130/MPL3115_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1314815130/MPL3115_ISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1314815130 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_ISR.c  -o ${OBJECTDIR}/_ext/1314815130/MPL3115_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1314815130/MPL3115_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314815130/MPL3115_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1314815130/MPL3115_Local.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1314815130 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Local.c  -o ${OBJECTDIR}/_ext/1314815130/MPL3115_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1314815130/MPL3115_Local.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314815130/MPL3115_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1314815130/MPL3115_Mgmt.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Mgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1314815130 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Mgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Mgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Mgmt.c  -o ${OBJECTDIR}/_ext/1314815130/MPL3115_Mgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1314815130/MPL3115_Mgmt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314815130/MPL3115_Mgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1314815130/MPL3115_Sync.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1314815130 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Sync.c  -o ${OBJECTDIR}/_ext/1314815130/MPL3115_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1314815130/MPL3115_Sync.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314815130/MPL3115_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1323215350/MPU6050_Async.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1323215350 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Async.c  -o ${OBJECTDIR}/_ext/1323215350/MPU6050_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1323215350/MPU6050_Async.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323215350/MPU6050_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1323215350/MPU6050_Init.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1323215350 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Init.c  -o ${OBJECTDIR}/_ext/1323215350/MPU6050_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1323215350/MPU6050_Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323215350/MPU6050_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1323215350/MPU6050_ISR_INT1.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_ISR_INT1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1323215350 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_ISR_INT1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_ISR_INT1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_ISR_INT1.c  -o ${OBJECTDIR}/_ext/1323215350/MPU6050_ISR_INT1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1323215350/MPU6050_ISR_INT1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323215350/MPU6050_ISR_INT1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1323215350/MPU6050_Local.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1323215350 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Local.c  -o ${OBJECTDIR}/_ext/1323215350/MPU6050_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1323215350/MPU6050_Local.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323215350/MPU6050_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1323215350/MPU6050_Mgmt.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Mgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1323215350 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Mgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Mgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Mgmt.c  -o ${OBJECTDIR}/_ext/1323215350/MPU6050_Mgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1323215350/MPU6050_Mgmt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323215350/MPU6050_Mgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1323215350/MPU6050_Reset.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Reset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1323215350 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Reset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Reset.c  -o ${OBJECTDIR}/_ext/1323215350/MPU6050_Reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1323215350/MPU6050_Reset.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323215350/MPU6050_Reset.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1323215350/MPU6050_Sync.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1323215350 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Sync.c  -o ${OBJECTDIR}/_ext/1323215350/MPU6050_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1323215350/MPU6050_Sync.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323215350/MPU6050_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334961018/MXB.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334961018 
	@${RM} ${OBJECTDIR}/_ext/1334961018/MXB.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334961018/MXB.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXB.c  -o ${OBJECTDIR}/_ext/1334961018/MXB.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334961018/MXB.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334961018/MXB.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334961018/MXB_ISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXB_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334961018 
	@${RM} ${OBJECTDIR}/_ext/1334961018/MXB_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334961018/MXB_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXB_ISR.c  -o ${OBJECTDIR}/_ext/1334961018/MXB_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334961018/MXB_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334961018/MXB_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334961018/MXBInit.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXBInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334961018 
	@${RM} ${OBJECTDIR}/_ext/1334961018/MXBInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334961018/MXBInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXBInit.c  -o ${OBJECTDIR}/_ext/1334961018/MXBInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334961018/MXBInit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334961018/MXBInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334961018/MXBLocal.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXBLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334961018 
	@${RM} ${OBJECTDIR}/_ext/1334961018/MXBLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334961018/MXBLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXBLocal.c  -o ${OBJECTDIR}/_ext/1334961018/MXBLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334961018/MXBLocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334961018/MXBLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334957814/QCMBatteryMgmt.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMBatteryMgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334957814 
	@${RM} ${OBJECTDIR}/_ext/1334957814/QCMBatteryMgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334957814/QCMBatteryMgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMBatteryMgmt.c  -o ${OBJECTDIR}/_ext/1334957814/QCMBatteryMgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334957814/QCMBatteryMgmt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334957814/QCMBatteryMgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334957814/QCMConst.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMConst.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334957814 
	@${RM} ${OBJECTDIR}/_ext/1334957814/QCMConst.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334957814/QCMConst.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMConst.c  -o ${OBJECTDIR}/_ext/1334957814/QCMConst.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334957814/QCMConst.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334957814/QCMConst.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334957814/QCMNormalize.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMNormalize.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334957814 
	@${RM} ${OBJECTDIR}/_ext/1334957814/QCMNormalize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334957814/QCMNormalize.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMNormalize.c  -o ${OBJECTDIR}/_ext/1334957814/QCMNormalize.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334957814/QCMNormalize.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334957814/QCMNormalize.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334957814/QCMPerformStep.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMPerformStep.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334957814 
	@${RM} ${OBJECTDIR}/_ext/1334957814/QCMPerformStep.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334957814/QCMPerformStep.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMPerformStep.c  -o ${OBJECTDIR}/_ext/1334957814/QCMPerformStep.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334957814/QCMPerformStep.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334957814/QCMPerformStep.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/788220866/RC.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/788220866 
	@${RM} ${OBJECTDIR}/_ext/788220866/RC.o.d 
	@${RM} ${OBJECTDIR}/_ext/788220866/RC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RC.c  -o ${OBJECTDIR}/_ext/788220866/RC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/788220866/RC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/788220866/RC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/788220866/RC_ISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RC_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/788220866 
	@${RM} ${OBJECTDIR}/_ext/788220866/RC_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/788220866/RC_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RC_ISR.c  -o ${OBJECTDIR}/_ext/788220866/RC_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/788220866/RC_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/788220866/RC_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/788220866/RCInit.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/788220866 
	@${RM} ${OBJECTDIR}/_ext/788220866/RCInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/788220866/RCInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCInit.c  -o ${OBJECTDIR}/_ext/788220866/RCInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/788220866/RCInit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/788220866/RCInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/788220866/RCLocal.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/788220866 
	@${RM} ${OBJECTDIR}/_ext/788220866/RCLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/788220866/RCLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCLocal.c  -o ${OBJECTDIR}/_ext/788220866/RCLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/788220866/RCLocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/788220866/RCLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/788220866/RCSym.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCSym.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/788220866 
	@${RM} ${OBJECTDIR}/_ext/788220866/RCSym.o.d 
	@${RM} ${OBJECTDIR}/_ext/788220866/RCSym.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCSym.c  -o ${OBJECTDIR}/_ext/788220866/RCSym.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/788220866/RCSym.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/788220866/RCSym.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1566053876/SR04.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1566053876 
	@${RM} ${OBJECTDIR}/_ext/1566053876/SR04.o.d 
	@${RM} ${OBJECTDIR}/_ext/1566053876/SR04.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04.c  -o ${OBJECTDIR}/_ext/1566053876/SR04.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1566053876/SR04.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1566053876/SR04.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1566053876/SR04_Init.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1566053876 
	@${RM} ${OBJECTDIR}/_ext/1566053876/SR04_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1566053876/SR04_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_Init.c  -o ${OBJECTDIR}/_ext/1566053876/SR04_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1566053876/SR04_Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1566053876/SR04_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1566053876/SR04_ISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1566053876 
	@${RM} ${OBJECTDIR}/_ext/1566053876/SR04_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1566053876/SR04_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_ISR.c  -o ${OBJECTDIR}/_ext/1566053876/SR04_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1566053876/SR04_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1566053876/SR04_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1566053876/SR04_Local.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1566053876 
	@${RM} ${OBJECTDIR}/_ext/1566053876/SR04_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1566053876/SR04_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_Local.c  -o ${OBJECTDIR}/_ext/1566053876/SR04_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1566053876/SR04_Local.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1566053876/SR04_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334954616/TMR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334954616 
	@${RM} ${OBJECTDIR}/_ext/1334954616/TMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334954616/TMR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMR.c  -o ${OBJECTDIR}/_ext/1334954616/TMR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334954616/TMR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334954616/TMR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334954616/TMR_ISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMR_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334954616 
	@${RM} ${OBJECTDIR}/_ext/1334954616/TMR_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334954616/TMR_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMR_ISR.c  -o ${OBJECTDIR}/_ext/1334954616/TMR_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334954616/TMR_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334954616/TMR_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334954616/TMRInit.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMRInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334954616 
	@${RM} ${OBJECTDIR}/_ext/1334954616/TMRInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334954616/TMRInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMRInit.c  -o ${OBJECTDIR}/_ext/1334954616/TMRInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334954616/TMRInit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334954616/TMRInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334954616/TMRLocal.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMRLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334954616 
	@${RM} ${OBJECTDIR}/_ext/1334954616/TMRLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334954616/TMRLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMRLocal.c  -o ${OBJECTDIR}/_ext/1334954616/TMRLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334954616/TMRLocal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334954616/TMRLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1566098207/UART_TX_API.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_API.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1566098207 
	@${RM} ${OBJECTDIR}/_ext/1566098207/UART_TX_API.o.d 
	@${RM} ${OBJECTDIR}/_ext/1566098207/UART_TX_API.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_API.c  -o ${OBJECTDIR}/_ext/1566098207/UART_TX_API.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1566098207/UART_TX_API.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1566098207/UART_TX_API.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1566098207/UART_TX_Init.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1566098207 
	@${RM} ${OBJECTDIR}/_ext/1566098207/UART_TX_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1566098207/UART_TX_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_Init.c  -o ${OBJECTDIR}/_ext/1566098207/UART_TX_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1566098207/UART_TX_Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1566098207/UART_TX_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1566098207/UART_TX_ISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1566098207 
	@${RM} ${OBJECTDIR}/_ext/1566098207/UART_TX_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1566098207/UART_TX_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_ISR.c  -o ${OBJECTDIR}/_ext/1566098207/UART_TX_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1566098207/UART_TX_ISR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1566098207/UART_TX_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1566098207/UART_TX_Local.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1566098207 
	@${RM} ${OBJECTDIR}/_ext/1566098207/UART_TX_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1566098207/UART_TX_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_Local.c  -o ${OBJECTDIR}/_ext/1566098207/UART_TX_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1566098207/UART_TX_Local.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1566098207/UART_TX_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/659535598/main.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/91-QCM_Altimetry/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/659535598 
	@${RM} ${OBJECTDIR}/_ext/659535598/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/659535598/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/91-QCM_Altimetry/main.c  -o ${OBJECTDIR}/_ext/659535598/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/659535598/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/659535598/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1334973169/ADC.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334973169 
	@${RM} ${OBJECTDIR}/_ext/1334973169/ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334973169/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADC.c  -o ${OBJECTDIR}/_ext/1334973169/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334973169/ADC.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334973169/ADC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334973169/ADCInit.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334973169 
	@${RM} ${OBJECTDIR}/_ext/1334973169/ADCInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334973169/ADCInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCInit.c  -o ${OBJECTDIR}/_ext/1334973169/ADCInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334973169/ADCInit.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334973169/ADCInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334973169/ADCISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334973169 
	@${RM} ${OBJECTDIR}/_ext/1334973169/ADCISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334973169/ADCISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCISR.c  -o ${OBJECTDIR}/_ext/1334973169/ADCISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334973169/ADCISR.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334973169/ADCISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334973169/ADCLocal.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334973169 
	@${RM} ${OBJECTDIR}/_ext/1334973169/ADCLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334973169/ADCLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/ADC/ADCLocal.c  -o ${OBJECTDIR}/_ext/1334973169/ADCLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334973169/ADCLocal.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334973169/ADCLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1034061016/Altimeter.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/Altimeter/Altimeter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1034061016 
	@${RM} ${OBJECTDIR}/_ext/1034061016/Altimeter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1034061016/Altimeter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/Altimeter/Altimeter.c  -o ${OBJECTDIR}/_ext/1034061016/Altimeter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1034061016/Altimeter.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1034061016/Altimeter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334971954/BLI.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334971954 
	@${RM} ${OBJECTDIR}/_ext/1334971954/BLI.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334971954/BLI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLI.c  -o ${OBJECTDIR}/_ext/1334971954/BLI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334971954/BLI.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334971954/BLI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334971954/BLIInit.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLIInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334971954 
	@${RM} ${OBJECTDIR}/_ext/1334971954/BLIInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334971954/BLIInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLIInit.c  -o ${OBJECTDIR}/_ext/1334971954/BLIInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334971954/BLIInit.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334971954/BLIInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334971954/BLILocal.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLILocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334971954 
	@${RM} ${OBJECTDIR}/_ext/1334971954/BLILocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334971954/BLILocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLILocal.c  -o ${OBJECTDIR}/_ext/1334971954/BLILocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334971954/BLILocal.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334971954/BLILocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334971954/BLIMorse.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLIMorse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334971954 
	@${RM} ${OBJECTDIR}/_ext/1334971954/BLIMorse.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334971954/BLIMorse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/BLI/BLIMorse.c  -o ${OBJECTDIR}/_ext/1334971954/BLIMorse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334971954/BLIMorse.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334971954/BLIMorse.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334970344/DBG.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DBG/DBG.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334970344 
	@${RM} ${OBJECTDIR}/_ext/1334970344/DBG.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334970344/DBG.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DBG/DBG.c  -o ${OBJECTDIR}/_ext/1334970344/DBG.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334970344/DBG.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334970344/DBG.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334970307/DCM.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334970307 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCM.c  -o ${OBJECTDIR}/_ext/1334970307/DCM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334970307/DCM.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334970307/DCM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334970307/DCMBaseVectors.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMBaseVectors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334970307 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCMBaseVectors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCMBaseVectors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMBaseVectors.c  -o ${OBJECTDIR}/_ext/1334970307/DCMBaseVectors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334970307/DCMBaseVectors.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334970307/DCMBaseVectors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334970307/DCMConstructors.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMConstructors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334970307 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCMConstructors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCMConstructors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMConstructors.c  -o ${OBJECTDIR}/_ext/1334970307/DCMConstructors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334970307/DCMConstructors.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334970307/DCMConstructors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334970307/DCMLocal.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334970307 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCMLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCMLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMLocal.c  -o ${OBJECTDIR}/_ext/1334970307/DCMLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334970307/DCMLocal.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334970307/DCMLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334970307/DCMMethods.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMMethods.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334970307 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCMMethods.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334970307/DCMMethods.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/DCM/DCMMethods.c  -o ${OBJECTDIR}/_ext/1334970307/DCMMethods.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334970307/DCMMethods.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334970307/DCMMethods.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1420275110/HMCMAG_Async.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1420275110 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Async.c  -o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1420275110/HMCMAG_Async.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1420275110/HMCMAG_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1420275110/HMCMAG_Init.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1420275110 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Init.c  -o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1420275110/HMCMAG_Init.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1420275110/HMCMAG_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1420275110 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_ISR.c  -o ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR_INT2.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_ISR_INT2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1420275110 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR_INT2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR_INT2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_ISR_INT2.c  -o ${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR_INT2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR_INT2.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1420275110/HMCMAG_ISR_INT2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1420275110/HMCMAG_Local.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1420275110 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Local.c  -o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1420275110/HMCMAG_Local.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1420275110/HMCMAG_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1420275110/HMCMAG_Mgmt.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Mgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1420275110 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Mgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Mgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Mgmt.c  -o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Mgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1420275110/HMCMAG_Mgmt.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1420275110/HMCMAG_Mgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1420275110/HMCMAG_Sync.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1420275110 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/1420275110/HMCMAG_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/HMCMAG/HMCMAG_Sync.c  -o ${OBJECTDIR}/_ext/1420275110/HMCMAG_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1420275110/HMCMAG_Sync.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1420275110/HMCMAG_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334966039/I2C_Async.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334966039 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Async.c  -o ${OBJECTDIR}/_ext/1334966039/I2C_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334966039/I2C_Async.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334966039/I2C_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334966039/I2C_Init.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334966039 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Init.c  -o ${OBJECTDIR}/_ext/1334966039/I2C_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334966039/I2C_Init.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334966039/I2C_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334966039/I2C_ISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334966039 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_ISR.c  -o ${OBJECTDIR}/_ext/1334966039/I2C_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334966039/I2C_ISR.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334966039/I2C_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334966039/I2C_Local.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334966039 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Local.c  -o ${OBJECTDIR}/_ext/1334966039/I2C_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334966039/I2C_Local.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334966039/I2C_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334966039/I2C_Sync.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334966039 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_Sync.c  -o ${OBJECTDIR}/_ext/1334966039/I2C_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334966039/I2C_Sync.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334966039/I2C_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334966039/I2C_SyncRead.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_SyncRead.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334966039 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_SyncRead.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_SyncRead.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_SyncRead.c  -o ${OBJECTDIR}/_ext/1334966039/I2C_SyncRead.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334966039/I2C_SyncRead.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334966039/I2C_SyncRead.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334966039/I2C_SyncWrite.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_SyncWrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334966039 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_SyncWrite.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334966039/I2C_SyncWrite.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/I2C/I2C_SyncWrite.c  -o ${OBJECTDIR}/_ext/1334966039/I2C_SyncWrite.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334966039/I2C_SyncWrite.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334966039/I2C_SyncWrite.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334965184/IMU.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/IMU/IMU.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334965184 
	@${RM} ${OBJECTDIR}/_ext/1334965184/IMU.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334965184/IMU.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/IMU/IMU.c  -o ${OBJECTDIR}/_ext/1334965184/IMU.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334965184/IMU.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334965184/IMU.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334965184/IMUReset.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/IMU/IMUReset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334965184 
	@${RM} ${OBJECTDIR}/_ext/1334965184/IMUReset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334965184/IMUReset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/IMU/IMUReset.c  -o ${OBJECTDIR}/_ext/1334965184/IMUReset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334965184/IMUReset.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334965184/IMUReset.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1565784705/Init.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/Init/Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1565784705 
	@${RM} ${OBJECTDIR}/_ext/1565784705/Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1565784705/Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/Init/Init.c  -o ${OBJECTDIR}/_ext/1565784705/Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1565784705/Init.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1565784705/Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334961658/MCM.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334961658 
	@${RM} ${OBJECTDIR}/_ext/1334961658/MCM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334961658/MCM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCM.c  -o ${OBJECTDIR}/_ext/1334961658/MCM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334961658/MCM.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334961658/MCM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334961658/MCMInit.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCMInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334961658 
	@${RM} ${OBJECTDIR}/_ext/1334961658/MCMInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334961658/MCMInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCMInit.c  -o ${OBJECTDIR}/_ext/1334961658/MCMInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334961658/MCMInit.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334961658/MCMInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334961658/MCMLocal.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCMLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334961658 
	@${RM} ${OBJECTDIR}/_ext/1334961658/MCMLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334961658/MCMLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MCM/MCMLocal.c  -o ${OBJECTDIR}/_ext/1334961658/MCMLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334961658/MCMLocal.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334961658/MCMLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1314815130/MPL3115_Async.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1314815130 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Async.c  -o ${OBJECTDIR}/_ext/1314815130/MPL3115_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1314815130/MPL3115_Async.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314815130/MPL3115_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1314815130/MPL3115_Init.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1314815130 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Init.c  -o ${OBJECTDIR}/_ext/1314815130/MPL3115_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1314815130/MPL3115_Init.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314815130/MPL3115_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1314815130/MPL3115_ISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1314815130 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_ISR.c  -o ${OBJECTDIR}/_ext/1314815130/MPL3115_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1314815130/MPL3115_ISR.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314815130/MPL3115_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1314815130/MPL3115_Local.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1314815130 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Local.c  -o ${OBJECTDIR}/_ext/1314815130/MPL3115_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1314815130/MPL3115_Local.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314815130/MPL3115_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1314815130/MPL3115_Mgmt.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Mgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1314815130 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Mgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Mgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Mgmt.c  -o ${OBJECTDIR}/_ext/1314815130/MPL3115_Mgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1314815130/MPL3115_Mgmt.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314815130/MPL3115_Mgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1314815130/MPL3115_Sync.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1314815130 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314815130/MPL3115_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPL3115/MPL3115_Sync.c  -o ${OBJECTDIR}/_ext/1314815130/MPL3115_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1314815130/MPL3115_Sync.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314815130/MPL3115_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1323215350/MPU6050_Async.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Async.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1323215350 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Async.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Async.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Async.c  -o ${OBJECTDIR}/_ext/1323215350/MPU6050_Async.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1323215350/MPU6050_Async.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323215350/MPU6050_Async.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1323215350/MPU6050_Init.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1323215350 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Init.c  -o ${OBJECTDIR}/_ext/1323215350/MPU6050_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1323215350/MPU6050_Init.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323215350/MPU6050_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1323215350/MPU6050_ISR_INT1.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_ISR_INT1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1323215350 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_ISR_INT1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_ISR_INT1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_ISR_INT1.c  -o ${OBJECTDIR}/_ext/1323215350/MPU6050_ISR_INT1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1323215350/MPU6050_ISR_INT1.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323215350/MPU6050_ISR_INT1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1323215350/MPU6050_Local.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1323215350 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Local.c  -o ${OBJECTDIR}/_ext/1323215350/MPU6050_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1323215350/MPU6050_Local.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323215350/MPU6050_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1323215350/MPU6050_Mgmt.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Mgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1323215350 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Mgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Mgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Mgmt.c  -o ${OBJECTDIR}/_ext/1323215350/MPU6050_Mgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1323215350/MPU6050_Mgmt.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323215350/MPU6050_Mgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1323215350/MPU6050_Reset.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Reset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1323215350 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Reset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Reset.c  -o ${OBJECTDIR}/_ext/1323215350/MPU6050_Reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1323215350/MPU6050_Reset.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323215350/MPU6050_Reset.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1323215350/MPU6050_Sync.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1323215350 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/1323215350/MPU6050_Sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MPU6050/MPU6050_Sync.c  -o ${OBJECTDIR}/_ext/1323215350/MPU6050_Sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1323215350/MPU6050_Sync.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1323215350/MPU6050_Sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334961018/MXB.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334961018 
	@${RM} ${OBJECTDIR}/_ext/1334961018/MXB.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334961018/MXB.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXB.c  -o ${OBJECTDIR}/_ext/1334961018/MXB.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334961018/MXB.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334961018/MXB.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334961018/MXB_ISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXB_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334961018 
	@${RM} ${OBJECTDIR}/_ext/1334961018/MXB_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334961018/MXB_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXB_ISR.c  -o ${OBJECTDIR}/_ext/1334961018/MXB_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334961018/MXB_ISR.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334961018/MXB_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334961018/MXBInit.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXBInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334961018 
	@${RM} ${OBJECTDIR}/_ext/1334961018/MXBInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334961018/MXBInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXBInit.c  -o ${OBJECTDIR}/_ext/1334961018/MXBInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334961018/MXBInit.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334961018/MXBInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334961018/MXBLocal.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXBLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334961018 
	@${RM} ${OBJECTDIR}/_ext/1334961018/MXBLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334961018/MXBLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/MXB/MXBLocal.c  -o ${OBJECTDIR}/_ext/1334961018/MXBLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334961018/MXBLocal.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334961018/MXBLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334957814/QCMBatteryMgmt.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMBatteryMgmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334957814 
	@${RM} ${OBJECTDIR}/_ext/1334957814/QCMBatteryMgmt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334957814/QCMBatteryMgmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMBatteryMgmt.c  -o ${OBJECTDIR}/_ext/1334957814/QCMBatteryMgmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334957814/QCMBatteryMgmt.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334957814/QCMBatteryMgmt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334957814/QCMConst.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMConst.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334957814 
	@${RM} ${OBJECTDIR}/_ext/1334957814/QCMConst.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334957814/QCMConst.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMConst.c  -o ${OBJECTDIR}/_ext/1334957814/QCMConst.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334957814/QCMConst.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334957814/QCMConst.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334957814/QCMNormalize.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMNormalize.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334957814 
	@${RM} ${OBJECTDIR}/_ext/1334957814/QCMNormalize.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334957814/QCMNormalize.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMNormalize.c  -o ${OBJECTDIR}/_ext/1334957814/QCMNormalize.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334957814/QCMNormalize.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334957814/QCMNormalize.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334957814/QCMPerformStep.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMPerformStep.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334957814 
	@${RM} ${OBJECTDIR}/_ext/1334957814/QCMPerformStep.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334957814/QCMPerformStep.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/QCM/QCMPerformStep.c  -o ${OBJECTDIR}/_ext/1334957814/QCMPerformStep.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334957814/QCMPerformStep.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334957814/QCMPerformStep.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/788220866/RC.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/788220866 
	@${RM} ${OBJECTDIR}/_ext/788220866/RC.o.d 
	@${RM} ${OBJECTDIR}/_ext/788220866/RC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RC.c  -o ${OBJECTDIR}/_ext/788220866/RC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/788220866/RC.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/788220866/RC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/788220866/RC_ISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RC_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/788220866 
	@${RM} ${OBJECTDIR}/_ext/788220866/RC_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/788220866/RC_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RC_ISR.c  -o ${OBJECTDIR}/_ext/788220866/RC_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/788220866/RC_ISR.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/788220866/RC_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/788220866/RCInit.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/788220866 
	@${RM} ${OBJECTDIR}/_ext/788220866/RCInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/788220866/RCInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCInit.c  -o ${OBJECTDIR}/_ext/788220866/RCInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/788220866/RCInit.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/788220866/RCInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/788220866/RCLocal.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/788220866 
	@${RM} ${OBJECTDIR}/_ext/788220866/RCLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/788220866/RCLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCLocal.c  -o ${OBJECTDIR}/_ext/788220866/RCLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/788220866/RCLocal.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/788220866/RCLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/788220866/RCSym.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCSym.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/788220866 
	@${RM} ${OBJECTDIR}/_ext/788220866/RCSym.o.d 
	@${RM} ${OBJECTDIR}/_ext/788220866/RCSym.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/RC/RCSym.c  -o ${OBJECTDIR}/_ext/788220866/RCSym.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/788220866/RCSym.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/788220866/RCSym.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1566053876/SR04.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1566053876 
	@${RM} ${OBJECTDIR}/_ext/1566053876/SR04.o.d 
	@${RM} ${OBJECTDIR}/_ext/1566053876/SR04.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04.c  -o ${OBJECTDIR}/_ext/1566053876/SR04.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1566053876/SR04.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1566053876/SR04.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1566053876/SR04_Init.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1566053876 
	@${RM} ${OBJECTDIR}/_ext/1566053876/SR04_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1566053876/SR04_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_Init.c  -o ${OBJECTDIR}/_ext/1566053876/SR04_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1566053876/SR04_Init.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1566053876/SR04_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1566053876/SR04_ISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1566053876 
	@${RM} ${OBJECTDIR}/_ext/1566053876/SR04_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1566053876/SR04_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_ISR.c  -o ${OBJECTDIR}/_ext/1566053876/SR04_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1566053876/SR04_ISR.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1566053876/SR04_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1566053876/SR04_Local.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1566053876 
	@${RM} ${OBJECTDIR}/_ext/1566053876/SR04_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1566053876/SR04_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/SR04/SR04_Local.c  -o ${OBJECTDIR}/_ext/1566053876/SR04_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1566053876/SR04_Local.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1566053876/SR04_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334954616/TMR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334954616 
	@${RM} ${OBJECTDIR}/_ext/1334954616/TMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334954616/TMR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMR.c  -o ${OBJECTDIR}/_ext/1334954616/TMR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334954616/TMR.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334954616/TMR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334954616/TMR_ISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMR_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334954616 
	@${RM} ${OBJECTDIR}/_ext/1334954616/TMR_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334954616/TMR_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMR_ISR.c  -o ${OBJECTDIR}/_ext/1334954616/TMR_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334954616/TMR_ISR.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334954616/TMR_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334954616/TMRInit.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMRInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334954616 
	@${RM} ${OBJECTDIR}/_ext/1334954616/TMRInit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334954616/TMRInit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMRInit.c  -o ${OBJECTDIR}/_ext/1334954616/TMRInit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334954616/TMRInit.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334954616/TMRInit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1334954616/TMRLocal.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMRLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1334954616 
	@${RM} ${OBJECTDIR}/_ext/1334954616/TMRLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1334954616/TMRLocal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/TMR/TMRLocal.c  -o ${OBJECTDIR}/_ext/1334954616/TMRLocal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1334954616/TMRLocal.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1334954616/TMRLocal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1566098207/UART_TX_API.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_API.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1566098207 
	@${RM} ${OBJECTDIR}/_ext/1566098207/UART_TX_API.o.d 
	@${RM} ${OBJECTDIR}/_ext/1566098207/UART_TX_API.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_API.c  -o ${OBJECTDIR}/_ext/1566098207/UART_TX_API.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1566098207/UART_TX_API.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1566098207/UART_TX_API.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1566098207/UART_TX_Init.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1566098207 
	@${RM} ${OBJECTDIR}/_ext/1566098207/UART_TX_Init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1566098207/UART_TX_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_Init.c  -o ${OBJECTDIR}/_ext/1566098207/UART_TX_Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1566098207/UART_TX_Init.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1566098207/UART_TX_Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1566098207/UART_TX_ISR.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1566098207 
	@${RM} ${OBJECTDIR}/_ext/1566098207/UART_TX_ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1566098207/UART_TX_ISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_ISR.c  -o ${OBJECTDIR}/_ext/1566098207/UART_TX_ISR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1566098207/UART_TX_ISR.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1566098207/UART_TX_ISR.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1566098207/UART_TX_Local.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_Local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1566098207 
	@${RM} ${OBJECTDIR}/_ext/1566098207/UART_TX_Local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1566098207/UART_TX_Local.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/00-Modules/UART/UART_TX_Local.c  -o ${OBJECTDIR}/_ext/1566098207/UART_TX_Local.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1566098207/UART_TX_Local.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1566098207/UART_TX_Local.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/659535598/main.o: /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/91-QCM_Altimetry/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/659535598 
	@${RM} ${OBJECTDIR}/_ext/659535598/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/659535598/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /Users/rich/quads/alexcontroller/svnRoot/Quad-V2/91-QCM_Altimetry/main.c  -o ${OBJECTDIR}/_ext/659535598/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/659535598/main.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/659535598/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
dist/${CND_CONF}/${IMAGE_TYPE}/azfcv2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/azfcv2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1  -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PICKIT2=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/azfcv2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/azfcv2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/azfcv2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
