################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
COMEX_C2000_V3.obj: ../COMEX_C2000_V3.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --fp_mode=relaxed --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/common/include" -g --define=CPU1 --display_error_number --diag_warning=225 --diag_suppress=10063 --preproc_with_compile --preproc_dependency="COMEX_C2000_V3.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_CodeStartBranch.obj: ../F2837xD_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --fp_mode=relaxed --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/common/include" -g --define=CPU1 --display_error_number --diag_warning=225 --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_CodeStartBranch.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_DefaultISR.obj: ../F2837xD_DefaultISR.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --fp_mode=relaxed --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/common/include" -g --define=CPU1 --display_error_number --diag_warning=225 --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_DefaultISR.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_GlobalVariableDefs.obj: ../F2837xD_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --fp_mode=relaxed --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/common/include" -g --define=CPU1 --display_error_number --diag_warning=225 --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_GlobalVariableDefs.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_Gpio.obj: ../F2837xD_Gpio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --fp_mode=relaxed --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/common/include" -g --define=CPU1 --display_error_number --diag_warning=225 --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_Gpio.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_Ipc.obj: ../F2837xD_Ipc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --fp_mode=relaxed --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/common/include" -g --define=CPU1 --display_error_number --diag_warning=225 --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_Ipc.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_PieCtrl.obj: ../F2837xD_PieCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --fp_mode=relaxed --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/common/include" -g --define=CPU1 --display_error_number --diag_warning=225 --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_PieCtrl.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_PieVect.obj: ../F2837xD_PieVect.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --fp_mode=relaxed --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/common/include" -g --define=CPU1 --display_error_number --diag_warning=225 --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_PieVect.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_SysCtrl.obj: ../F2837xD_SysCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --fp_mode=relaxed --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/common/include" -g --define=CPU1 --display_error_number --diag_warning=225 --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_SysCtrl.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837xD_usDelay.obj: ../F2837xD_usDelay.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --fp_mode=relaxed --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/common/include" -g --define=CPU1 --display_error_number --diag_warning=225 --diag_suppress=10063 --preproc_with_compile --preproc_dependency="F2837xD_usDelay.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

IO_Helpers.obj: ../IO_Helpers.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --fp_mode=relaxed --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/common/include" -g --define=CPU1 --display_error_number --diag_warning=225 --diag_suppress=10063 --preproc_with_compile --preproc_dependency="IO_Helpers.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Initialize.obj: ../Initialize.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --fp_mode=relaxed --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/headers/include" --include_path="C:/ti/C2000Ware_1_00_00_00_Software/device_support/f2837xd/common/include" -g --define=CPU1 --display_error_number --diag_warning=225 --diag_suppress=10063 --preproc_with_compile --preproc_dependency="Initialize.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


