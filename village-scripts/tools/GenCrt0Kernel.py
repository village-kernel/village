################GenKconfig.py###################
# this program generate kconfig and makefile file
################################################# 
import sys
import os
import re


crt0kernelContext = \
"//###########################################################################\r\n" \
"// %s\r\n" \
"// Low level file that manages kernel entry\r\n" \
"//\r\n" \
"// $Copyright: Copyright (C) village\r\n" \
"//###########################################################################\r\n" \
"#include <stddef.h>\r\n" \
"#include <stdint.h>\r\n" \
"\r\n" \
"/// @brief _estack\r\n" \
"extern void *_estack;\r\n" \
"\r\n" \
"\r\n" \
"/// @brief KernelSymbol\r\n" \
"void KernelSymbol();\r\n" \
"\r\n" \
"\r\n" \
"/// @brief SystemInit\r\n" \
"void SystemInit();\r\n" \
"\r\n" \
"\r\n" \
"/// @brief program entry main\r\n" \
"/// @param argc \r\n" \
"/// @param argv \r\n" \
"/// @return \r\n" \
"int main(int argc, char* argv[]);\r\n" \
"\r\n" \
"\r\n" \
"/// @brief Reset_Handler\r\n" \
"/// @param argc \r\n" \
"/// @param argv \r\n" \
"void Reset_Handler(int argc, char* argv[]);\r\n" \
"\r\n" \
"\r\n" \
"/// @brief Default_Handler\r\n" \
"void __attribute__ ((weak, naked)) Default_Handler()\r\n" \
"{\r\n" \
"    while (1) {}\r\n" \
"}\r\n" \
"\r\n" \
"\r\n" \
"/// @brief Default Handlers\r\n"\
"%s" \
"\r\n" \
"\r\n" \
"/// @brief isr_vector\r\n" \
"void * g_pfnVectors[] __attribute__ ((section (\".isr_vector\"), used)) = \r\n" \
"{\r\n" \
"    &_estack,\r\n" \
"%s" \
"};\r\n" \
"\r\n" \
"\r\n" \
"/// @brief Initialize data and bss section\r\n" \
"/// @param  \r\n" \
"void __init_data_bss(void)\r\n" \
"{\r\n" \
"    extern void *_sidata, *_sdata, *_edata;\r\n" \
"    extern void *_sbss,   *_ebss;\r\n" \
"    void **pSource, **pDest;\r\n" \
"\r\n" \
"    //Normally the CPU should will setup the based on the value from the first entry in the vector table.\r\n" \
"    //If you encounter problems with accessing stack variables during initialization, ensure the line below is enabled.\r\n" \
"    asm (\"ldr sp, =_estack\");\r\n" \
"\r\n" \
"    //Copy data segment initializers from disk to SRAM\r\n" \
"    for (pSource = &_sidata, pDest = &_sdata; pDest != &_edata; pSource++, pDest++)\r\n" \
"        *pDest = *pSource;\r\n" \
"\r\n" \
"    //Zero fill the bss segment.\r\n" \
"    for (pDest = &_sbss; pDest != &_ebss; pDest++)\r\n" \
"        *pDest = 0;\r\n" \
"}\r\n" \
"\r\n" \
"\r\n" \
"/// @brief execute preinit_arrary\r\n" \
"/// @param  \r\n" \
"void __preinit_arrary(void)\r\n" \
"{\r\n" \
"    extern void (*__preinit_array_start []) (void);\r\n" \
"    extern void (*__preinit_array_end   []) (void);\r\n" \
"\r\n" \
"    int count = __preinit_array_end - __preinit_array_start;\r\n" \
"    for (int i = 0; i < count; i++)\r\n" \
"        __preinit_array_start[i]();\r\n" \
"}\r\n" \
"\r\n" \
"\r\n" \
"/// @brief execute init_arrary\r\n" \
"/// @param  \r\n" \
"void __init_array(void)\r\n" \
"{\r\n" \
"    extern void (*__init_array_start []) (void);\r\n" \
"    extern void (*__init_array_end   []) (void);\r\n" \
"\r\n" \
"    int count = __init_array_end - __init_array_start;\r\n" \
"    for (int i = 0; i < count; i++)\r\n" \
"        __init_array_start[i]();\r\n" \
"}\r\n" \
"\r\n" \
"\r\n" \
"/// @brief execute fini_arrary\r\n" \
"/// @param  \r\n" \
"void __fini_array(void)\r\n" \
"{\r\n" \
"    extern void (*__fini_array_start []) (void);\r\n" \
"    extern void (*__fini_array_end   []) (void);\r\n" \
"\r\n" \
"    int count = __fini_array_end - __fini_array_start;\r\n" \
"\r\n" \
"    for (int i = 0; i < count; i++)\r\n" \
"    {\r\n" \
"        __fini_array_start[i]();\r\n" \
"    }\r\n" \
"}\r\n" \
"\r\n" \
"\r\n" \
"/// @brief Reset_Handler\r\n" \
"/// @param  \r\n" \
"void Reset_Handler(int argc, char* argv[])\r\n" \
"{\r\n" \
"    __init_data_bss();\r\n" \
"\r\n" \
"    KernelSymbol();\r\n" \
"\r\n" \
"    SystemInit();\r\n" \
"\r\n" \
"    __preinit_arrary();\r\n" \
"\r\n" \
"    __init_array();\r\n" \
"\r\n" \
"    main(argc, argv);\r\n" \
"\r\n" \
"    __fini_array();\r\n" \
"\r\n" \
"    for(;;) ;\r\n" \
"}\r\n"


#set argv
if len(sys.argv) < 2:
    print ('Invalid format')
    print ('Usage: %s [assembly.s]' % (os.path.basename(sys.argv[0])))
    sys.exit()
else:
    assemblyPath = sys.argv[1]
    crt0kernelPath = assemblyPath.replace('.s', '.c')
    crt0kernelPath = crt0kernelPath.replace('startup', 'crt0_kernel')
    crt0kernelName = os.path.basename(crt0kernelPath)
    

#open and read the assembly file 
assemblyFile = open(assemblyPath, 'r')
assemblyContext = assemblyFile.read()
assemblyFile.close()


#get handlers
vectorIdentifier = r'(?<=.word[\s])[^\n]+'
handlers = re.findall(vectorIdentifier, assemblyContext, flags=re.MULTILINE)


#g_handlers
g_handlers = ''
for handler in handlers:
    if 'Reset_Handler' not in handler and 'Handler' in handler:
        handler = re.findall(r'\w+Handler', handler, flags=re.MULTILINE)[0] + '()'
        g_handlers += 'void %-35s __attribute__ ((weak, alias ("Default_Handler")));\r\n' % handler


#g_pfnVectors
g_pfnVectors = ''
for handler in handlers:
    if 'Handler' in handler:
        g_pfnVectors += '    &%s\r\n' % handler.replace('Handler', 'Handler,').strip()
    elif '0' in handler:
        g_pfnVectors += '    %s\r\n' % handler.replace('0', '0, ').strip()


# save crt0 kernel content to file
crt0kernelFile = open(crt0kernelPath, mode="w", newline="\n")
crt0kernelFile.write(crt0kernelContext % (crt0kernelName, g_handlers, g_pfnVectors))
crt0kernelFile.close()
